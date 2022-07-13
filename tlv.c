#include <libxml/xmlreader.h>
#include <string.h>
#include <stdlib.h>
#include "tlv.h"


static char * outputBuffer;
static char * currentPosition;


inline static void fillInLengthValue(int * isNodeOpened, const char * xmlText) {
    uint32_t typeLength = (uint32_t)strlen(xmlText);
    memcpy(currentPosition, &typeLength, sizeof(typeLength));
    currentPosition += sizeof(typeLength);
    memcpy(currentPosition, xmlText, strlen(xmlText));
    currentPosition += strlen(xmlText);
    *isNodeOpened = 0;
}


static void processNode(xmlTextReaderPtr reader) {
    static int isNodeOpened;
    uint32_t type;
    const char * xmlType;
    const char * xmlText;

    if (xmlTextReaderDepth(reader)) {
        if (isNodeOpened) {
            xmlText = (const char *)xmlTextReaderConstValue(reader);
            fillInLengthValue(&isNodeOpened, xmlText);
        }
        if (!isNodeOpened && xmlTextReaderNodeType(reader) == 1) {
            xmlType = (const char *)xmlTextReaderConstName(reader);
            if (!strcmp(xmlType, "text")) {
                type = Text;
            } else {
                type = Numeric;
            }
            memcpy(currentPosition, &type, sizeof(type));
            currentPosition += sizeof(type);
            isNodeOpened = 1;
        }
    }
}


void streamFile(const char *filename, size_t bufferSize) {
    xmlTextReaderPtr reader;
    int ret;
    FILE * filePtr;

    outputBuffer = (char *)malloc(bufferSize);
    currentPosition = outputBuffer;
    reader = xmlReaderForFile(filename, NULL, 0);
    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        while (ret == 1) {
            processNode(reader);
            ret = xmlTextReaderRead(reader);
        }
        if (ret) {
            fprintf(stderr, "%s : failed to parse\n", filename);
        }
    } else {
        fprintf(stderr, "Unable to open %s\n", filename);
    }
    filePtr = fopen(outputFilename, "wb");
    fwrite(outputBuffer, currentPosition - outputBuffer, 1, filePtr);
    fclose(filePtr);
    xmlCleanupParser();
    free(outputBuffer);
}
