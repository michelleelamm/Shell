#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include<readline/readline.h> 
#include <unistd.h>
#include <sys/wait.h>
// To-do
// Initial screen clear and user prompt 
// Optimize for error detections 
// Piping? 

void printDir() 
{ 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); // Documentation: https://man7.org/linux/man-pages/man3/getcwd.3.html
    printf("Directory: %s\n", cwd); 
} 

#define LSH_TOK_BUFSIZE 64
int main(){

    printf("\e[1;1H\e[2J"); // SRC: https://www.geeksforgeeks.org/clear-console-c-language/
    while(1){

        printDir();

        char line[60]; //Arbitrary Length
        fgets(line, 60, stdin); //Read from console
        char *token; //Token will hold word

        char *commandArg[1024]; //Will store our tokenized strings
        int index = 0; //Will serve as our index and length for our tokenized string array

        token = strtok(line, " \n");
        while( token != NULL){  
            commandArg[index] = token;
            index++;
            token = strtok(NULL, " \n");
        }

        commandArg[index] = NULL; //Must null-terminate our array or will continue reading remaining spaces

        // Determine if it was a built-in or system command and run accordingly
        char *builtInCmds[2] = {"cd","exit"};
        if(strcmp(commandArg[0], builtInCmds[0]) == 0){
            chdir(commandArg[1]);
        }
        else if(strcmp(commandArg[0], builtInCmds[1]) == 0){
            exit(0);
        }
        else{
            // Create a child process to run command, parent process will wait until child termiantes
            if( fork() != 0)
                wait(NULL);
            else{
                execvp(commandArg[0], commandArg);
                exit(0); 
            }
        }
    }
   

    return 0;
}



