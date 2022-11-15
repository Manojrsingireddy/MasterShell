#include <iostream>
#include <string>
#include "sys.h"
#include <map>
#include <sys/types.h>
#include <unistd.h>
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif


using namespace std;

const char *builtin_str[] = {
  "cd",
  "help",
  "exit"
};
int msh_cd(char ** argv);
int msh_help(char ** argv);
int msh_exit(char ** argv);

int (*builtin_func[]) (char **) = {
  &msh_cd,
  &msh_help,
  &msh_exit
};
const char *supportedFeaturesMessage[] = {
    "Below are a list of features supported by MSH",
    "Executing standard shell commands with arguemnts",
    "Whitespace separated commands and arguments"
};

int msh_cd(char ** argv){
    if (argv[1] == NULL) {
        fprintf(stderr, "MSH: expected argument to \"cd\"\n");
    } 
    else {
        if (chdir(argv[1]) != 0) {
            perror("lsh");
        }
    }
    return 1;
}
int msh_help(char ** argv){
    printf("Manoj Singireddy's MSH\n");
    printf("Type your command followed by the required arguments.");
    for(int i = 0; i < sizeof(supportedFeaturesMessage)/sizeof(char *); i++){
        printf("%s\n",supportedFeaturesMessage[i]);
    }
    return 1;
}
int msh_exit(char ** argv){
    return 0;
}

int run_executable(char ** argv){
    int id = fork();
    if(id == 0) { // Child
        if(execvp(argv[0], argv) == -1) {
            fprintf(stderr, "MSH: Invalid Command\n");
        }
        exit(EXIT_FAILURE);
    } 
    else if(id < 0) { // Fork Error
        // Error forking
        fprintf(stderr, "MSH: Error Forking for Program Execution\n");
    } 
    else {
        // Parent process
        int status;
        do {
        id = waitpid(id, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
  return 1;
}

int run_command(char ** argv){
    if(argv[0] == NULL)
    {
        return 1;
    }
    for(int i = 0; i < sizeof(builtin_func)/sizeof(char *); i++){
        if (strcmp(argv[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(argv);
        }
    }
    return run_executable(argv);
}

#define BUF_SIZE 10
#define SPLIT_ARG " \t\r\n\a"
void parse_line(char * line, char ** argv){
    char * element = strtok(line, SPLIT_ARG);
    int position = 0;
    while(element){
        argv[position++] = element;
        if(position % BUF_SIZE == 0){
            argv = (char **) realloc(argv, BUF_SIZE * (position / BUF_SIZE + 1) * sizeof(char *));
        }
        element = strtok(NULL, SPLIT_ARG);
    }
}

void run_shell(){  
    int status = 0;
    printf("Welcome to the Master Shell\n");
    do{
        char buffer [FILENAME_MAX];
        GetCurrentDir(buffer, FILENAME_MAX);
        printf("%s :) ", buffer);
        string line;
        char ** argv = (char **) malloc(BUF_SIZE * sizeof(char *));
        getline(cin, line);
        char line_char[line.length() + 1];
        strcpy(line_char, line.c_str());
        parse_line(line_char, argv);
        status = run_command(argv);
    }
    while(status != 0);
}

int main(){
    clear_console();
    run_shell();
    printf("Thank you for using Manoj Singireddy's MSH\n");
    exit(0);
}