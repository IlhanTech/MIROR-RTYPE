FROM gcc:latest

WORKDIR /usr/src/rtype

COPY . .

RUN apt-get update && \
    apt-get install -y libsfml-dev cmake

RUN ./build.sh server

EXPOSE 3004

RUN ./r_type_server 3004
