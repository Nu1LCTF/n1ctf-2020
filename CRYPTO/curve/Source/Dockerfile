FROM sagemath/sagemath:9.1
MAINTAINER i@shiki7.me

USER root
RUN apt update && apt upgrade -y
RUN apt install -y xinetd 

RUN mkdir /challenge/
RUN chmod 755 /challenge/

ADD ./flag.txt /challenge/flag.txt
ADD ./run.sh /challenge/run.sh
ADD ./chall.sage /challenge/chall.sage
RUN chmod 755 /challenge/run.sh
ADD ./problem /etc/xinetd.d/
RUN chown -R sage:sage /challenge/

USER sage
CMD ["/usr/sbin/xinetd", "-dontfork"]

