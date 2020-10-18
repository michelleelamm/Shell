#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// To-do
// Create makefile
// Create log file of tests we can run and find cases where our shell fails
// Create a instructions.txt

void printDir() 
{ 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); // Documentation: https://man7.org/linux/man-pages/man3/getcwd.3.html
    printf("Directory: %s\n", cwd); 
} 
void printIntro(){
    printf("\e[1;1H\e[2J"); // SRC: https://www.geeksforgeeks.org/clear-console-c-language/
    printf("-----------------------------------------------------------------------\n");
    printf("\t\t\tTeam Swyft's Shell in C");
    printf("\n-----------------------------------------------------------------------\n");

}
int main(){

    printIntro();

    while(1){

        printDir();
        char line[60]; //Arbitrary Length
        fgets(line, 60, stdin); //Read from console
        char *token; //Token will hold word

        char *commandArg[1024]; //Will store our tokenized strings
        int index = 0; //Will serve as our index and length for our tokenized string array

        token = strtok(line, " \n");
        // Documentation for tokenizing: https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
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
            printf("\n");
            exit(0);
        }
        else{
            // Create a child process to run command, parent process will wait until child termiantes
            if( fork() != 0) // Documentation: https://www.geeksforgeeks.org/fork-system-call/
                wait(NULL); // Documentation: https://man7.org/linux/man-pages/man2/wait.2.html
            else{
                execvp(commandArg[0], commandArg);
                exit(0); 
            }
        }
    }
   

    return 0;
}



