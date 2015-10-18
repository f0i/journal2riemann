FROM buildpack-deps

MAINTAINER Arnaud Wetzel version: 0.1

RUN apt-get update && apt-get install -y libsystemd-journal-dev protobuf-c-compiler libprotobuf-dev && apt-get clean && rm -rf /var/lib/apt/lists/*
RUN git clone https://github.com/algernon/riemann-c-client && \
    cd riemann-c-client && autoreconf -i && \
    ./configure && make && make check && make install && \
    cd .. && rm -rf riemann-c-client

VOLUME ["/srv/data/build:/build"]
WORKDIR /build
CMD ["/usr/bin/make"]
