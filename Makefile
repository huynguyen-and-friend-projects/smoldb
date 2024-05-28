CC := clang
BUILD ?= cli

#if clang is not present, use the default compiler
ifeq ($(call get_dep_path,$(CC)),)
	CC := cc
endif

#convenient functions

#print a fancy success log on compilation success
success_log = [$(GREEN)SUCCESS$(SGR0)] $(BOLD)Compiled $(1) from $(2)$(SGR0)\n
#get the path of dependency using the command `whereis`
get_dep_path = $(strip $(patsubst $(1):%,%,$(shell whereis $(1))))
#compile into [first-argument] using [second-argument] and print success log
compile_obj = $(CC) $(CFLAGS) -c -o $(1) $(2) &&\
							printf "$(call success_log,$(1),$(2))"

#fancy output, if tput is present
#color
ifneq ($(call get_dep_path,tput),)
SGR0 = `tput sgr0`
RED = `tput setaf 1`
GREEN = `tput setaf 2`
BLUE = `tput setaf 4`
#style
BOLD = `tput bold`
endif

ifeq ($(BUILD),cli)
	DIRS = $(shell find ./src -type d -not -name '*api')
else
	ifeq ($(BUILD),api)
		DIRS = $(shell find ./src -type d -not -name '*cli')
	else
$(error BUILD must be 'cli' or 'api'; received $(BUILD) instead)
	endif
endif
HEADER_INCL := $(addprefix -I,$(DIRS))

#files
OBJ_EXT = .o
LIB_EXT = .so
#MacOS compatibility, which will be needed for the C API dynamic library
ifeq ($(shell uname -s),Darwin)
	LIB_EXT = .dylib
else
endif

SRC_BASE := $(wildcard ./src/*.c)
OBJ_BASE := $(patsubst ./src/%.c,./build/obj/%$(OBJ_EXT),$(SRC_BASE))

SRC_CLI := $(wildcard ./src/cli/*.c)
OBJ_CLI := $(patsubst ./src/cli/%.c,./build/obj/%$(OBJ_EXT),$(SRC_CLI))

SRC_INTERNAL := $(wildcard ./src/internal/*.c)
OBJ_INTERNAL := $(patsubst ./src/internal/%.c,./build/obj/%$(OBJ_EXT),$(SRC_INTERNAL))

OBJS := $(OBJ_BASE) $(OBJ_CLI) $(OBJ_INTERNAL)
FINAL_CLI := ./build/smoldb.out

CFLAGS = -pedantic -Og -g $(HEADER_INCL)

.DELETE_ON_ERROR:
.PHONY: all
all: info-start $(FINAL_CLI) info-end
	@echo $(DIRS)

#final build step
$(FINAL_CLI): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^
	@printf "$(call success_log,$@,$^)"

#object build steps
$(OBJ_BASE): ./build/obj/%$(OBJ_EXT): ./src/%.c
	@$(call compile_obj,$@,$^)

$(OBJ_CLI): ./build/obj/%$(OBJ_EXT): ./src/cli/%.c
	@$(call compile_obj,$@,$^)

$(OBJ_INTERNAL): ./build/obj/%$(OBJ_EXT): ./src/internal/%.c
	@$(call compile_obj,$@,$^)

#print Makefile info at the start and end
.PHONY: info-start
info-start:
	@printf "$(BOLD)----MAKEFILE FOR SMOLDB-----$(SGR0)\n"
	@printf "Written by Huy Nguyen (nguyenhuy0905)\n\n"

.PHONY: info-end
info-end:
	@printf "$(BOLD)-----COMPILE COMPLETE-----$(SGR0)\n"
	@printf "To execute the program, run the executable $(FINAL_CLI) or the symlink ./smoldb\n"

.PHONY: clean
clean:
	$(RM) $(OBJS) ./build/*.out
	@printf "[$(GREEN)SUCCESS$(SGR0)]$(BOLD)Cleanup finished$(SGR0)\n"

#leak-check with valgrind
#NOTE: only runs on Linux, afaik
VALGRIND := valgrind --leak-check=full --track-origins=yes
ifeq ($(call get_dep_path,valgrind),)
	# won't run valgrind
	VALGRIND :=
endif

.PHONY: check
check: $(FINAL_CLI)
ifeq ($(VALGRIND),)
$(error VALGRIND is not installed)
endif
	@$(VALGRIND) $(FINAL_CLI)
	@printf "[$(GREEN)SUCCESS$(SGR0)] $(BOLD)Check finished$(SGR0)\n"
