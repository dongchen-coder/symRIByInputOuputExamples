FROM ubuntu:16.04

RUN \
    sed -i 's/# \(.*multiverse$\)/\1/g' /etc/apt/sources.list && \
    apt-get update && \
    apt-get -y upgrade && \
    apt-get install -y build-essential && \
    apt-get install -y software-properties-common && \
    apt-get install -y byobu curl git htop man unzip vim wget && \
    rm -rf /var/lib/apt/lists/*

RUN apt-get update -qq -y

RUN apt-get install -qq -y wget

RUN apt-get install -qq -y cmake

RUN apt-get install time

RUN apt-get install libpthread-stubs0-dev

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y mysql-server
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y mysql-client
RUN apt-get install -y libmysqlcppconn-dev

RUN /etc/init.d/mysql start
