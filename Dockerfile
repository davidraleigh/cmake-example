FROM debian:buster

RUN apt-get update -y \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y --fix-missing --no-install-recommends \
    curl \
    make \
    g++ \
    libgtest-dev \
    cmake

WORKDIR /opt/src/cpp-maps-app

COPY ./ ./

WORKDIR /opt/src/cpp-maps-app/build
RUN cmake .. && \
    make -j 8

ENTRYPOINT ["/opt/src/cpp-maps-app/build/cpp-maps-app/cpp_maps_app"]
