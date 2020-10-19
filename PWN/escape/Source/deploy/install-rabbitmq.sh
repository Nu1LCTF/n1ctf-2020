#!/bin/sh

wget -O- https://packages.erlang-solutions.com/ubuntu/erlang_solutions.asc | apt-key add -
wget -O- https://dl.bintray.com/rabbitmq/Keys/rabbitmq-release-signing-key.asc | apt-key add -
wget -O- https://www.rabbitmq.com/rabbitmq-release-signing-key.asc | apt-key add -
echo "deb https://packages.erlang-solutions.com/ubuntu $(lsb_release -sc) contrib" | tee -a /etc/apt/sources.list.d/rabbitmq.list
echo "deb https://dl.bintray.com/rabbitmq/debian $(lsb_release -sc) main" | tee -a /etc/apt/sources.list.d/rabbitmq.list

apt update && apt upgrade -y
apt install erlang rabbitmq-server

