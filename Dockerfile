# compile this as smoldb-img
# NOTE: this Dockerfile and its two docker-composes are no longer needed due to CMake alredy being cross-platform,
# hence will soon be removed
FROM debian:latest

WORKDIR /smoldb
COPY . /smoldb/

RUN apt-get update
RUN apt-get install -y git clang cmake clang-tools ninja-build valgrind
RUN apt-get upgrade -y
RUN cd /smoldb
RUN mkdir build && cd build
RUN cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_BUILD_TYPE=Debug ..
RUN cmake --build .
ENV PATH=$PATH:/usr/bin
ENV TERM=xterm-256color
