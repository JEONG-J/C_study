#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

int gNumber;
int run_now = 0;
int Sum_Producer = 0;
int Sum_Consumer = 0;

void SaveRandom(){
	int randTemp;
	srand(time(0));
	randTemp = rand() % 100;
	gNumber = randTemp;
}

void *producer(void *arg){
	int Cnt = 1;
	while(Cnt <= 100){
		if(run_now == 0){
			SaveRandom();
			run_now = 1;
			sleep(1);
			printf("[%d] random number(producer thread) : %d\n",Cnt,gNumber);
			fflush(stdout);
			Sum_Producer += gNumber;
			Cnt += 1;
		}
	}
	return Sum_Producer;
}

void *consumer(void *arg){
	int Cnt2 = 1;
	while(Cnt2 <= 100){
		if(run_now == 1){
			printf("[%d] random number(consumer thread) : %d\n",Cnt2,gNumber);
			fflush(stdout);
			Sum_Consumer += gNumber;
			run_now = 0;
			Cnt2 += 1;
		}
		else
			sleep(0.3);
	}
	return Sum_Consumer;
}

int main(){
	int Return_producer, Return_consumer;
	int res;
	pthread_t producer_thread, consumer_thread;
	void *thread_result;

	res = pthread_create(&producer_thread, NULL, producer, NULL);
	if(res != 0)
		perror("producer creation failed\n");

	res = pthread_create(&consumer_thread, NULL, consumer, NULL);
	if(res != 0)
		perror("consumer creation failed\n");

	res = pthread_join(producer_thread, &thread_result);
	Return_producer = (int)thread_result;

	res = pthread_join(consumer_thread, &thread_result);
	Return_consumer = (int)thread_result;

	if(Return_producer == Return_consumer)
		printf("success\n");
	else
		printf("fail\n");

	return 0;
}
