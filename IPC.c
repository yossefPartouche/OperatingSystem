#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int fd[2];
    //fd[0] = read end 
    //fd[1] = write end
    if (pipe(fd) == -1){
        printf("An error occured with opening the pipe\n");
        return 1;
    }
    int id = fork();
    //creating a fork AFTER the pipe creation leads to independent piping communication//

    if(id == 0){
      close(fd[0]);
      int x;
      printf("Input a number: ");
      scanf("%d", &x);
     if ( write(fd[1], &x, sizeof(int))== -1){
        printf("An error occured writing to the pipe");
     }
      close(fd[1]);
    } else{
        int y;
        close(fd[1]);
        if (read(fd[0], &y, sizeof(int))==-1){
            printf("An error occured with reading to the pipe\n");
        }
        close(fd[0]);
        printf("Got from child process %d\n", y);
    }

    return 0;
} 
