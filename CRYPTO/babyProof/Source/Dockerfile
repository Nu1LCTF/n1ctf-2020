FROM python:3.8-alpine
LABEL Description="babyProof" VERSION='1.0'

RUN apk update && apk add gcc g++ make openssl-dev python3-dev libffi-dev autoconf socat

WORKDIR /opt/babyproof
RUN mkdir -p /opt/proof

COPY task.py .
COPY secret.py .
COPY start_from_here.py .

RUN pip install pycryptodome

EXPOSE 23333
CMD ["python", "start_from_here.py", ">>", "log.txt"]
