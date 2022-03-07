#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
        
        int pipeFileDescriptor[2];
        char writeMessages[2][20] = {"Hey Erico","Hey Michael"};
        char readMessages[20];
        int returnPipe = pipe(pipeFileDescriptor);

        if (returnPipe == -1) {
                printf("Error to create pipe!\n");
                return 1;
        }

        int pid = fork();

        if (pid > 0) { //parent

                for (int i = 0; i < 2; i++) {
                        printf("Writing message %d: \"%s\"\n", i, writeMessages[i]);
                        write(pipeFileDescriptor[1], writeMessages[i], sizeof(char) * 20);

                }
                
        } else if (pid == 0) {

                for (int i = 0; i < 2; i++) {
                        read(pipeFileDescriptor[0], readMessages, sizeof(char) * 20);
                        printf("Reading message %d: \"%s\"\n",i, readMessages);

                }

        } else {

                printf("Error creating child process");
        }
        
        
}