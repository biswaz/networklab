#include <stdio.h>
#include <sys/types.h>


void ChildProcess();
void ParentProcess();

void main(){
	pid_t pid;

	pid = fork();

	if(pid < 0)
	printf("Child creation failed");
	else if(pid == 0){
		//printf("Child process is executing\n");
		ChildProcess();
	}
	else{
		//printf("Parent process is executing\n");
		ParentProcess();
	}
}

void ChildProcess(){
	for(int i; i<10; i++)
	if(i%2 == 0)
	printf("From child: %d\n", i);
}

void ParentProcess(){
	for(int i; i<10; i++)
	if(i%2 != 0)
	printf("From parent: %d\n", i);
}
