FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    pdftk \
    && apt-get clean

WORKDIR /workspace

COPY . /workspace

CMD ["bash"]