#!/usr/bin/env bash

# Check if we build the project
if [ ! -f bin/vxd ] || [ ! -f bin/vxadmin ]; then
    echo "Not all programs found"
    echo "Make sure all the projects are build and executables are moven into bin"
    exit
fi

rm -rf dist

echo "Distributions:"
ls -dl install/* | cut -f2 -d '/'

exit
while true; do
  echo -n "Enter target distribution [ENTER]: "
  read distname
  if [ -d install/"$distname" ]; then
    break;
  else
    echo "Distribution not found"
  fi
done

# Create directory structure
mkdir -p dist
mkdir -p dist/bin
mkdir -p dist/srv
mkdir -p dist/share
mkdir -p dist/www
mkdir -p dist/etc

# Copy files
cp bin/vxd dist/bin
cp bin/vxadmin dist/bin
cp config.json dist/etc
cp LICENSE dist/
cp -R install/$distname/* dist/srv
cp scheme/* dist/share
cp www/* dist/www
touch dist/README
ln -s srv/"$distname"_install.sh dist/install.sh

tar -pczf "$distname"_dist.tar.gz dist/

echo "Distribution tarbal: "$distname"_dist.tar.gz"
echo "Done"
