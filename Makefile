# Makefile�����������Ƃ̖�����Ƃ萢��Ȃ̂ł�����ƓK���ł��B
# �Ƃ肠�����Aix.exe��xtal.exe����������܂��B
# cygwin�ŃR���p�C���ł����̂ŁA����Linux�ł��o����񂶂�Ȃ����Ǝv���܂��B
#

CC = gcc

n: ix.exe xtal.exe

ix.exe: xtal/ixmain.cpp
	$(CC) -o ix.exe xtal/ixmain.cpp -O2 -lstdc++

xtal.exe: xtal/main.cpp
	$(CC) -o xtal.exe xtal/main.cpp -O2 -lstdc++
