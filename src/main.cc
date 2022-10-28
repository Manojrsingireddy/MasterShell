#include <iostream>
#include <string>



using namespace std;

int run_command(char ** argv){
    char * cmd = argv[0];
    if(strcmp(cmd, "exit")==0){
        return 0;
    }
    return 1;
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
        printf(">");
        string line;
        char ** argv = (char **) malloc(BUF_SIZE * sizeof(char *));
        getline(cin, line);
        char line_char[line.length() + 1];
        strcpy(line_char, line.c_str());
        parse_line(line_char, argv);
        status = run_command(argv);
    }
    while(status > 0);
}

int main(){
    run_shell();
    exit(0);
}