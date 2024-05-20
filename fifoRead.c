#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>


int main (int argc, char* argv[]){
    int arr[5];
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
    printf("The sum was %d\n", sum);
    close(fd);

    return 0;
}
