#!/usr/bin/bash

LIBDIR="/usr/local/lib"
CMS="$LIBDIR/libcppcms.so.1.0.5"
CMSDB="$LIBDIR/libcppdb.so.0.3.1"
CMSDDM="$LIBDIR/libcppdb_mysql.so.0.3.1"
BOOSTER="$LIBDIR/libbooster.so.0.0.3"

# Check if we build the project
if [ ! -f bin/vxd ] || [ ! -f bin/vxque ] || [ ! -f bin/vxadmin ]; then
    echo "Not all programs found"
    echo "Make sure all the projects are build and executables are moven into bin"
    exit
fi

rm -rf dist

echo "Distributions:"
ls -dl install/* | cut -f2 -d '/'

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
mkdir -p dist/lib
mkdir -p dist/srv
mkdir -p dist/share
mkdir -p dist/www
mkdir -p dist/etc

# Copy files
cp bin/vxd dist/bin
cp bin/vxadmin dist/bin
cp bin/vxque dist/bin
cp $CMS dist/lib
cp $CMSDB dist/lib
cp $CMSDDM dist/lib
cp $BOOSTER dist/lib
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
