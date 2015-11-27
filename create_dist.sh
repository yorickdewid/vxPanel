#!/usr/bin/env bash

# Check if we build the project
if [ ! -f bin/vxd ]; then
    echo "Binaries not found in bin"
fi

# Create directory structure
mkdir -p dist
mkdir -p dist/bin
mkdir -p dist/etc

# Copy files
cp bin/vxd dist/bin
cp config.json dist/etc
cp LICENSE dist/
cp install/* dist/
cp scheme/* dist/
touch dist/README

tar -pczf dist.tar.gz dist/