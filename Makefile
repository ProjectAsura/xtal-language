# Makefile�����������Ƃ̖�����Ƃ萢��Ȃ̂ł�����ƓK���ł��B
# �Ƃ肠�����Aix.exe��xtal.exe����������܂��B
# cygwin�ŃR���p�C���ł����̂ŁA����Linux�ł��o����񂶂�Ȃ����Ǝv���܂��B
#

CC = g++

all: ix xtal

ix: xtal/ixmain.cpp
	$(CC) -o ix xtal/ixmain.cpp -O2 -lstdc++

xtal: xtal/main.cpp
	$(CC) -o xtal xtal/main.cpp -O2 -lstdc++
