FROM debian:latest
WORKDIR /smoldb
COPY .. /smoldb/

RUN cd /smoldb
RUN apt-get update
RUN apt-get install -y ca-certificates curl 
RUN install -m 0755 -d /etc/apt/keyrings
RUN curl -fsSL https://download.docker.com/linux/debian/gpg -o /etc/apt/keyrings/docker.asc
RUN echo \
    "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.asc] https://download.docker.com/linux/debian \
    $(. /etc/os-release && echo "$VERSION_CODENAME") stable" | \
    tee /etc/apt/sources.list.d/docker.list > /dev/null
RUN apt-get update
RUN apt-get install -y docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
RUN apt-get install -y build-essential clang valgrind git gh nano
RUN apt-get update
RUN git config --global core.editor nano
