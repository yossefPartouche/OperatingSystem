#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

//signal handler function

void sigint_handler(int signum){
    printf("\nRecieved SIGINT (Ctrl+C)\n");
    //from this point you would add specific actions upon receiving SIGINT
}

int main(){
    if (signal(SIGINT, sigint_handler) == SIG_ERR){
        perror("signal");
        exit(EXIT_FAILURE);
    }

    printf("Signal handler registered. Press Ctrl+C to send SIGINT.\n");

    //Infinite loop to keep the program runnnig until SIGINT is recieved
    while(1){

        //Do nothing, just keep the program running
        sleep(1);
    }
    
    return 0;
}
