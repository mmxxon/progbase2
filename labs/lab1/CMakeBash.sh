#!/bin/bash
echo -e "\e[41mCMAKE\e[0m"
cd ./build
cmake ..
echo -e "\e[41mMAKING FILE\e[0m"
make
echo -e "\e[41mLAUNCH W TEXT FILE FROM MAIN DIRECTORY\e[0m"
./lab1.out ../data.txt
echo -e "\e[41mCLEANING BUILD\e[0m"
# ls | xargs rm -rf 
ls | grep -v -E 'lab1.out' | xargs rm -rf
