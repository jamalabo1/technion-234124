FROM ubuntu:22.04
RUN apt update -y
RUN apt-get install -y g++ valgrind