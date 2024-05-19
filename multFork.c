#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int id1 = fork();
    int id2 = fork();
    if (id1 == 0){
        if(id2 == 0){
            printf("we are a leaf\n");
        }
        else {
            printf("we are an internal node process\n");
        }
    }
    else {
        if( id2 == 0){
            printf("we are a leaf process, but not the deepest depth leaf\n");}
            else{
                printf("we are the root/ parent process\n");
            }
    }

    return 0;
}
