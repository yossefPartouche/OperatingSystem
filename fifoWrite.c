#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
int main(int argc, char* argv[]){
        clock_t t;
        if(mkfifo("sumfifo", 0777) ==-1){
            if ( errno != EEXIST){
                printf("unable to make a fifo file");
                return 1;
            }
        }
        int arr[5];
        srand(time(NULL));
        int i;
        for (i = 0; i < 5; i++){
         arr[i] = rand() % 100;
        }

        int fd = open("sumfifo", O_WRONLY);
        if (fd == -1){
            return 1;
        }
        for (i = 0; i <5; i++){
          if (write(fd, &arr[i], sizeof(int)) == -1){
             printf("can't write to the file");
             return 2;
          }    
          printf("Wrote %d\n", arr[i]);
        }
        close(fd);
        if ((fd = open("sumfifo", O_RDONLY)) == -1){
            return -1;
        }   
        int sum;
        if (read(fd, &sum, sizeof(int)) ==-1){
            return 2;
        }
        printf ("Recieved %d\n", sum);
        printf("Time of execution %lu\n", t);
        close(fd);
        return 0;
}
