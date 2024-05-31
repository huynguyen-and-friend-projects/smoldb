FROM debian:latest
WORKDIR /smoldb
COPY .. /smoldb/

RUN cd /smoldb
RUN apt-get update
RUN apt-get install -y build-essential clang valgrind git nano
RUN git config --global core.editor nano