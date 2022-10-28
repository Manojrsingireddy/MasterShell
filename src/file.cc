#include "file.h"
#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>

int show_dir(){
    try{        
    char buffer [FILENAME_MAX];
    GetCurrentDir(buffer, FILENAME_MAX);
    printf("You are in %s\n",buffer);
    return 1;
    }
    catch(...){
        fprintf(stderr, "MSH: Could not find directory\n");
        return -1;
    }
}