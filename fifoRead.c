#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>


int main (int argc, char* argv[]){
    int arr[5];
    clock_t time;
    int fd = open("sumfifo", O_RDONLY);
    if (fd ==-1){
        return 1;
    }

    int i;
    int sum =0;
    for (i=0; i < 5; i++){
        if(read(fd, &arr[i], sizeof(int)) == -1){
            return 2;
        }
        printf("Recieved %d\n", arr[i]);
        sum += arr[i];
    }
    printf("The sum was %d\n time of execution: %lu\n", sum, time);
    printf("Sending back to Number Generator\n");
    close(fd);
    
    fd = open("sumfifo", O_WRONLY);
    if( fd == -1){
        return -1;
    }

    if (write(fd, &sum, sizeof(int)) == -1){
        printf("can't write to the file");
        return 2;
    }
    printf("Sum written and Sent: %d\n time of execution: %lu\n", sum, time);
    close(fd);
    return 0;
}
