#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
int sum = 500;

void * thread1()
{	int i =1;	  
        while(i<10){
                printf("Hello!\n");
                i++;
                sleep(2);
                }
}

void * thread2()
{	int i =1;	  
        while(i<10){
                printf("How are you?\n");
                i++;
                sleep(3);
        }
}

int main()
{
       
        pthread_t tid1,tid2;

        pthread_create(&tid1,NULL,thread1,NULL);
        pthread_create(&tid2,NULL,thread2,NULL);
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        return 0;
}
