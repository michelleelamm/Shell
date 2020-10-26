#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <unistd.h>
#include <sys/wait.h>


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
    printf("\nEnter \"help\" for list of commands.\n\n");

}
void printHelp() {
    printf("\nWelcome to Team Swyft's help page!\n");
    printf("\nBelow are the implemented commands for our shell: ");
    printf("\ncd - change directory");
    printf("\npwd - print working directory");
    printf("\nmkdir - creates a new directory (does not create when directory already exists)");
    printf("\nrmdir - removes a directory (does not remove if directory is nonempty)");
    printf("\nls - lists contents");
    printf("\ntouch - creates file");
    printf("\ncp file1 file2 - copies contents from file1 to file2");
    printf("\nexit - exit the shell");
    printf("\nOur shell also can run executables. \n");
    printf("\nThank you for using our Shell.\n\n");
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
        else if (strcmp(commandArg[0], "help") == 0) {
            printHelp();
            continue;
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



