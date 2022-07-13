#include <sys/stat.h>
#include "tlv.h"


int main(int argc, char **argv) {
    struct stat st;
    int returnCode = 0;

    if (argc != 2) {
        printf("missing the filename parameter\n");
        returnCode = 1;
    } else {
        stat(argv[1], &st);
        streamFile(argv[1], st.st_size);
        /* debug file size print */
	stat(outputFilename, &st);
        printf("%s byte size is %zu\n", outputFilename, st.st_size);
    }
    return returnCode;
}
