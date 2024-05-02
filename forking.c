#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

void task(int task_number){
	//Getting the provess ID of the current process
	pid_t pid = getpid();

	//simulate a task by printing a message
	printf("\nProcess %d: Task %d Started\n", pid, task_number);

	//Simulate some work by sleeping
	sleep(5);
	printf("Process %d: Task %d Completed\n",pid, task_number);
}

int main(){
	int num_tasks = 5;

	printf("Main process started\n");

	//Create child proccesses to perform tasks
	for (int i =1; i <= num_tasks; i++){
		pid_t parentId = getpid();
	//	printf("Parent pid: %d \n", parentId);
		pid_t pid = fork();
		
		//Child process
		if(pid == 0){
			task(i); // execute the task	
			return 0;
			
		} else if (pid < 0){
			
			//Error Handling if fork fails
			perror( "Fork failed");
				return 1;
		}
	}

	//Parent process waits for all child processes to complete
	for (int i =0; i < num_tasks; i++){
		wait(NULL);
	}

	printf("All tasks completed\n");
	return 0;
}

