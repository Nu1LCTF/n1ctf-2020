#!/bin/bash

if [ "$UID" != "0" ]; then
  echo "Run this script as root."
  exit 1
fi

# install packages
apt update && apt upgrade -y
apt install -y xinetd python2.7 python-pip apache2 libapache2-mod-wsgi unzip sqlite3 parallel
pip install -U pip
pip install docker flask uwsgi pika

# install beanstalkd & its python library
apt install beanstalkd
pip install beanstalkc 

# create ctf user
useradd -U -s /bin/bash ctf

# make directories & install database
mkdir -p /challenge/log/ /challenge/attempts/ /shared/
echo "CREATE TABLE submissions (ticket VARCHAR(255) NOT NULL UNIQUE, status INT NOT NULL)" | sqlite3 /shared/tickets.sqlite3 
chmod 666 /shared/tickets.sqlite3
chmod 777 /shared/

# install challenge
cp -r ./deploy/frontend ./deploy/backend /challenge 
mkdir /root/.systemd/
cp ./deploy/backend/chalbackend.service /root/.systemd/
ln -s /root/.systemd/chalbackend.service /etc/systemd/system/multi-user.target.wants/chalbackend.service   # systemd wants us to use symlinks only...
cp ./deploy/frontend/frontend.conf /etc/apache2/sites-enabled/
systemctl daemon-reload
service chalbackend restart

echo "Done! Manually configure your apache port to 13337 and restart service."

