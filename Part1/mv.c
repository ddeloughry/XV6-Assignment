#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
int main(int numArguments, char *files[]){
    char buf[512];
    int openInput, openOutput, reader, writer = 0;
    if(numArguments != 3){
        printf(2, "Error: please specify input and output files!\n");
        exit();
    }
    char *inputFile = files[1], *outputFile = files[2];
    if ((openInput = open(inputFile, O_RDONLY)) < 0){
        printf(2, "Error: cannot open input %s!\n", inputFile);
        exit();
    }
    if ((openOutput = open(outputFile, O_CREATE|O_WRONLY)) < 0){
        printf(2, "Error: cannot open output %s!\n", outputFile);
        exit();
    }
    while ((reader = read(openInput, buf, sizeof(buf))) > 0){
        writer = write(openOutput, buf, reader);
        if (writer != reader || writer < 0){
            break;
        }
    }
    int removeOriginal = unlink(inputFile);
    if (reader < 0 || writer < 0 || removeOriginal < 0){
        printf(2, "Error: copying files failed!\n");
    }
    close(openInput);
    close(openOutput);
    exit();
}
