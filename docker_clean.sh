#!/bin/bash

if [ "$(docker ps -q)" ]; then
  docker stop $(docker ps -q)
fi

if [ "$(docker ps -aq)" ]; then
  docker rm $(docker ps -aq)
fi

docker volume prune -f
docker image prune -a -f
docker network prune -f
docker system prune -f

docker-compose down --volumes --remove-orphans


docker builder prune -a

echo "Docker a été nettoyé avec succès."
