FROM gcc:latest

WORKDIR /usr/src/rtype

COPY . .

RUN apt-get update && \
    apt-get install -y libsfml-dev cmake

RUN ./build.sh server

COPY ./r_type_server /usr/bin

EXPOSE 3004

CMD ["./r_type_server", "3004"]
