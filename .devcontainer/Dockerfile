FROM fedora:latest

# dependencies
RUN dnf install -y git cmake ninja-build clang clang-tools-extra vim
# set default compilers to clang
ENV CC=clang
ENV CXX=clang++

# remove random artifacts
RUN dnf autoremove -y

