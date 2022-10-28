#include <iostream>
#include <string>
#include "file.h"
#include "sys.h"
#include <map>


using namespace std;

enum cmd{
    leave,
    getcwd,
    help
};

static map<string, cmd> sToCmdMap;

void initialize_commands(){
    sToCmdMap["leave"] = leave;
    sToCmdMap["getcwd"] = getcwd;
    sToCmdMap["help"] = help;
}

int run_command(char ** argv){
    char * cmd = argv[0];
    switch(sToCmdMap[cmd]){
        case leave:
            return 0;
        case getcwd:
            return show_dir();
        case help:
            return get_help();
        default:
            printf("Invalid Command\n");
            return 1;
    }
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
        printf(":) ");
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
    initialize_commands();
    run_shell();
    exit(0);
}