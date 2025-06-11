#!/bin/bash

# Ensure X server accepts local connections
xhost +local:

# Start the container if it's not running
if ! docker ps | grep -q mmex-dev; then
    echo "Starting container..."
    docker start mmex-dev
    sleep 3
fi

# Run MMEX in the dev container
docker exec mmex-dev /workspaces/moneymanagerex/build/_CPack_Packages/Linux/DEB/mmex-1.9.1-Beta.1-Linux/usr/bin/mmex
