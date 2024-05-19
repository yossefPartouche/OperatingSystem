#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
    //understanding the limitation of unnamed pipes//
   // int fd[2];
   //if( pipe(fd) == -1){
   //     return 1;
   //}
    //^^ from the above as soon as we create a fd and fork a process 
    //the child process inherits a method of communication to its parent//
    //this implies that only within the same hierarchy can they communicate//

    //CREATING NAMED PIPE - FIFO FILE//

    /*mkfifo(the file name, the permission to the file) */
   if (mkfifo("myfifo1", 0777) ==-1){
       /*we can also check whether the file exsts - by checking the type of error */
       if (errno != EEXIST){
        printf("unable to make the fifo file\n");
        return 1; 
       }   
   }
   printf("Opening...\n");
   int fd = open("myfifo1", O_WRONLY);
   printf("Opened\n");
   int x = 97;
   printf("Writing...\n");
   if (write(fd, &x, sizeof(int)) == -1){
        return 2;
   }
   printf("Written\n");
   close(fd);
   printf("Closed\n");
   return 0;
}

