FROM gcc:latest

WORKDIR /usr/src/rtype

COPY . .

RUN apt-get update && \
    apt-get install -y libsfml-dev cmake

RUN ./build.sh server

RUN chmod +x r_type_server

EXPOSE 3004

RUN ./r_type_server 3004
