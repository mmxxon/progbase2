#!/bin/bash
if test ! -f build;
then
  mkdir build
fi
cd ./build
if test ! -f Makefile;
then
  echo -e "\e[41mCMAKE\e[0m"
  cmake ..
fi
echo -e "\e[41mMAKING FILE\e[0m"
make
echo -e "\e[41mCLEANING BUILD\e[0m"
# ls | xargs rm -rf
ls | grep -v -E '*.out|CMakeLists.txt|Makefile' | xargs rm -rf
echo -e "\e[41mLAUNCH W TEXT FILE FROM MAIN DIRECTORY\e[0m"
./lab.out -o ../CSV/out.csv ../CSV/data.csv US -b
