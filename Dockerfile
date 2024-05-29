# compile this as smoldb-img
FROM debian:latest

WORKDIR /smoldb
COPY . /smoldb/

RUN apt-get update
RUN apt-get install -y build-essential valgrind
RUN apt-get upgrade -y
RUN cd /smoldb
ENV PATH=$PATH:/usr/bin
ENV TERM=xterm-256color
