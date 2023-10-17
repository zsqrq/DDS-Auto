#!/bin/bash
set -e

script_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
docker build -t dds_auto_image:latest $script_path/..
sleep 2

DOCKER_IMAGE="dds_auto_image:latest"
CONTAINER_NAME="TRos_Auto"
HOST_MAP_DIR="$script_path/../.."
TARGET_MAP_DIR="/home/work/docker"

docker run -idt -u root \
    --gpus all \
    --network host \
    --name $CONTAINER_NAME \
    --privileged \
    -v $HOST_MAP_DIR:$TARGET_MAP_DIR \
    -w $TARGET_MAP_DIR \
    $DOCKER_IMAGE \
    /bin/bash
