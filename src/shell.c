#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<readline/readline.h> 
#include <unistd.h>
#include <sys/wait.h>
int main(){
    // Read and Tokenize Input
    char line[60]; //Arbitrary Length
    fgets(line, 60, stdin); //Read from console
    char *token; //Token will hold word

    char *commandArg[1024]; //Will store our tokenized strings
    int index = 0; //Will serve as our index and length for our tokenized string array

    token = strtok(line, " \t\r\n\a");
    while( token != NULL){  
        commandArg[index] = token;
        index++;
        token = strtok(NULL, " \t\r\n\a");
    }
    int j;


    // Create a child process to run command, parent process will wait until child termiantes
    if( fork() != 0)
        wait(NULL);
    else{
        execvp(commandArg[0], commandArg);
        exit(0); 
    }



    return 0;
}