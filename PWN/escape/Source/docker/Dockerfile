FROM ubuntu:18.04
MAINTAINER i@shiki7.me

RUN apt -y update && apt -y upgrade
RUN apt -y install ca-certificates fonts-liberation libasound2 libatk-bridge2.0-0 libatk1.0-0 libatspi2.0-0 libc6 libcairo2 libcups2 libdbus-1-3 libdrm2 libexpat1 libgbm1 libgcc1 libgdk-pixbuf2.0-0 libglib2.0-0 libgtk-3-0 libnspr4 libnss3 libpango-1.0-0 libx11-6 libx11-xcb1 libxcb1 libxcomposite1 libxdamage1 libxext6 libxfixes3 libxkbcommon0 libxrandr2 wget xdg-utils netcat

RUN groupadd -g 1000 ctf
RUN useradd -g ctf -m -u 1000 ctf -s /bin/bash

ADD ./dist/chromium-browser-stable_88.0.4291.0-1_amd64.deb /tmp/
ADD ./flag.txt /
RUN chmod 644 /flag.txt 
RUN dpkg -i /tmp/chromium-browser-stable_88.0.4291.0-1_amd64.deb

USER ctf
CMD ["/bin/bash"]

