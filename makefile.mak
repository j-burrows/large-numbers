#makefile
CC = gcc
WARNINGS = -Wall

all: LargeNumbers.dll

LargeNumbers.dll: MathFunctionsLargeNumber.o
	$(CC) -shared -o LargeNumbers.dll MathFunctionsLargeNumber.o -Wl,--out-implib,libmessage.a
	
MathFunctionsLargeNumber.o: MathFunctionsLargeNumber.c MathFunctionsLargeNumber.h
	$(CC) -c -DBUILD_DLL MathFunctionsLargeNumber.c
	
clean:
	rm -rf *o LargeNumbers.dll
