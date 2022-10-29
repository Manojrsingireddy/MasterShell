# include "sys.h"
#include <iostream>

int get_help(){
    printf("Supported commands:\n");
    printf("> leave: terminate msh\n");
    printf("> getdir: print current working directory\n");
    printf("> up: change current directory to parent directory\n");
    printf("> help: show this help menu\n");
    return 1;
}