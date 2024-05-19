#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
    int arr[] = {1, 2, 3, 4, 1,2, 6,8};
    int arrSize = sizeof(arr)/sizeof(int);
    int fd1[2];
    int fd2[2];
    int start, end;
    if (pipe(fd1) == -1 || pipe(fd2) == -1){
        printf("error opening one of the pipes");
        return 1;
    }

    int id1 = fork();
    int id2;
    if (id1 == -1){
        printf("Error creating a process");
        return 2;
    }       
    if (id1 == 0){
        start =0;
        end = arrSize/3; //floored value
    }
    else{
        id2 = fork();
        if(id2 == 0){
            start = arrSize /3;
            end = arrSize - arrSize/3;
        }
        else {
            start = arrSize - arrSize/3;; 
            end = arrSize;
        }
    }
    int sum = 0; 
    int i;
    for ( i = start; i < end; i++){
        sum += arr[i];
    }
    printf("Caluculated partial sum: %d\n", sum);
    printf("This was calulcated by process %d\n", getpid());
    printf("Trying to understand the difference between between getpid and the return value of fork(): %d\n", id1);
    if( id1 == 0){
        close(fd1[0]);
        if (write(fd1[1], &sum, sizeof(int)) == -1){
            printf("unable to write to the pipe 1");
            return 2;
        }
        close(fd1[1]);
    }
    else {
        if (id2 == 0){
            close(fd2[0]);
            if( write(fd2[1], &sum, sizeof(int)) == -1){
                printf("unable to write into pipe 2");
                return 2;
            }
            close(fd2[1]);
        }
        else {
            int sumFromChild1, sumFromChild2;
            close(fd1[1]);
            close(fd2[1]);
            if (read(fd1[0], &sumFromChild1, sizeof(int)) == -1 ){
                printf("unable to read from pipe1");
                return 3;
            }
            if (read(fd2[0], &sumFromChild2, sizeof(int)) ==-1) {
                printf("unable to read from pipe2");
                return 4;
            }
            close(fd1[0]);
            close(fd2[0]);
            int totalSum = sum + sumFromChild1 + sumFromChild2;
            printf("Total sum is %d\n", totalSum);
            wait(NULL);
            }
    }
    return 0;
}
