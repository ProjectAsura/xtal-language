# Makefile�����������Ƃ̖�����Ƃ萢��Ȃ̂ł�����ƓK���ł��B
# �Ƃ肠�����Aix.exe��xtal.exe����������܂��B
# cygwin�ŃR���p�C���ł����̂ŁA����Linux�ł��o����񂶂�Ȃ����Ǝv���܂��B
#

CC = gcc

all: ix xtal

ix: xtal/ixmain.cpp
	$(CC) xtal/ixmain.cpp -o ix -O2 -finline-functions -lstdc++

xtal: xtal/main.cpp
	$(CC) xtal/main.cpp -o xtal -O2 -lstdc++ -pg
