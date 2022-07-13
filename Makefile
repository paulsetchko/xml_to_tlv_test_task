CFLAGS = -I/usr/include/libxml2 -Werror -Wall -march=corei7-avx -std=c17 -m64 -g -pedantic -O3 -s -c
LDFLAGS = -lxml2

all: main.c tlv.c tlv.h
	$(CC) $(CFLAGS) main.c -o main.o
	$(CC) $(CFLAGS) tlv.c -o tlv.o
	$(CC) -o xml_to_tlv main.o tlv.o $(LDFLAGS)

run:
	./$(app) input.xml

clean:
	$(RM) main.o tlv.o xml_to_tlv
