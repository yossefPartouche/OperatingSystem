#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int id = fork();
    if (id == 0){
        //puposely causing the parent to finish its task before the child//
        //thus causing a zombie process -- causing a memory leak//
        sleep(1);
    }
    //printf("%d\n", getpid());
    printf("Current ID: %d\nParent ID: %d\n", getpid(), getppid());
    int res = wait(NULL);
    if (res != -1){
        printf("No children to wait for\n");
    }
    else{
        printf("%d finnished execution - waiting complete\n", res);
    }
    return 0;
}
