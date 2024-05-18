#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    int id = fork();

    //to check if you're in the child process//
    if (id != 0){
        fork();
    }
    //Since each process fork is of magnitude 2^n then we control 
    //the number of processes created by only creating a process at one point
    //i.e. in our case at the parent
    printf("Hello world from id: %d\n", id);
    return 0;
}
