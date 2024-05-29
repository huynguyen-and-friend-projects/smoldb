FROM debian:latest

WORKDIR /smoldb
COPY . /smoldb

RUN apt-get update
RUN apt-get install -y build-essential
RUN apt-get upgrade -y
ENV PATH=$PATH:/usr/bin
ENV TERM=xterm-256color

CMD ["./cli-container.sh"]
