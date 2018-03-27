#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex1,mutex2,mutex3,r,w;
int data = 0,rcount = 0,wcount=0;

void *reader(void *arg)
{
  int f;
  f = ((int)arg);
  sem_wait(&mutex3);
  sem_wait(&r);
  sem_wait(&mutex1);
  	rcount = rcount + 1;
  	if(rcount==1)
		sem_wait(&w);
  sem_post(&mutex1);
  sem_post(&r);
  sem_post(&mutex3);
  	printf("Data read by the reader%d is %d\n",f,data);
  	sleep(2);
  sem_wait(&mutex1);
  	rcount = rcount - 1;
  	if(rcount==0)
   		sem_post(&w);
  sem_post(&mutex1);
}

void *writer(void *arg)
{
  int f;
  f = ((int) arg);
  sem_wait(&mutex2);
  	wcount=wcount+1;
  	if(wcount==1)
  		sem_wait(&r);
  sem_post(&mutex2);
  sem_wait(&w);		
  	data++;
  	printf("Data writen by the writer%d is %d\n",f,data);
  	sleep(2);
  sem_post(&w);
  sem_wait(&mutex2);
  	wcount=wcount-1;
  	if(wcount==0)
  		sem_post(&r);
  sem_post(&mutex2);
}

void main()
{
  int i;
  pthread_t rtid[5],wtid[5];
  sem_init(&mutex1,0,1);
  sem_init(&mutex2,0,1);
  sem_init(&mutex3,0,1);
  sem_init(&r,0,1);
  sem_init(&w,0,1);
  for(i=0;i<=4;i++)
  {
    
    pthread_create(&rtid[i],NULL,reader,(void *)i);
    pthread_create(&wtid[i],NULL,writer,(void *)i);
  }
  for(i=0;i<=4;i++)
  {
    pthread_join(wtid[i],NULL);
    pthread_join(rtid[i],NULL);
  }
}
