#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main(){
    int pipefd[2]; //File descriptors for pipe
    pid_t pid;
    char buffer[100]; //Buffer to store the message

    //Create the pipe 
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    //Fork a child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);

    }


    if (pid == 0){
        
        //Child process
        close(pipefd[1]); //Close write end of pipe in child

        int bytes_read = read(pipefd[0], buffer, sizeof(buffer));
        if (bytes_read == -1){
            perror("read");
            exit(EXIT_FAILURE);
        }

        //Print the messsage recieved from the pipe

        printf("Child process recieved message: %s\n", buffer);

        close(pipefd[0]);
        exit(EXIT_SUCCESS);
    } else {

        //Parent process
        close(pipefd[0]); //Close read end of pipe in Parent 

        const char *message = "\nHello, child! This is a messge from the parent.";
        int bytes_written = write(pipefd[1], message, strlen(message)+1);
        if (bytes_written == -1){
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]); //Close write end of pipe in parent

    }
    return 0;
}

