#include <stdio.h>


enum MessageType {
    Text = 0xb0,
    Numeric = 0xba
};


void streamFile(const char *filename, size_t bufferSize);

const static char * outputFilename = "output.tlv";

