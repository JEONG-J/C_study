#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

int f1_wallet[MAX];
int f1_count = 0;
int total_balance = 1000000;
int sum_f1 = 0;
int sum_f2 = 0;
sem_t bin_sem;

int bank(int money){
	total_balance = total_balance - money;
	f1_wallet[f1_count] = money;
	f1_count += 1;
}


static void* f1(void* p){
	sem_wait(&bin_sem);
	srand(time(NULL));
	for(int i=0;i<10;i++){
		printf("--------------------------------------------------------\n");
		printf("[%d] >> f1이 돈을 빌리기 시작합니다. <<\n\n",i+1);
		int money = rand() % 10000 + 1;
		printf("\t%d원 빌렸습니다.\n",money);
		bank(money);
		sum_f1 = sum_f1 + money;
		printf("--------------------------------------------------------\n");
	}

	printf("현재 은행 잔액 : %d\n",total_balance);
	printf("빌린 총 액수 : %d\n\n",sum_f1);
	
	sem_post(&bin_sem);

	return NULL;

}

static void* f2(void* p) {
	sleep(2);
	sem_wait(&bin_sem);
	int save;
	int return_money;
	for(int i=0; i<10; i++) {
		printf("--------------------------------------------------------\n");
		printf("[%d] >> f2가 돈을 갚기 시작합니다. <<\n\n",i+1);
		save = f1_wallet[i];
		total_balance = total_balance + save;
		printf("\t%d원을 갚았습니다.\n",save);
		printf("--------------------------------------------------------\n");
		sum_f2 = sum_f2 + save;
	}
	printf("현재 은행 잔액 : %d\n",total_balance);
	printf("갚은 총 액수 : %d\n\n",sum_f2);

	sem_post(&bin_sem);
	return NULL;
}

int main() {
	int rc;

	pthread_t t1, t2;

	sem_init(&bin_sem, 0, 1);

	rc = pthread_create(&t1, NULL, f1, "f1");
	if(rc != 0) {
		fprintf(stderr, "pthread f1 failed\n");
		return EXIT_FAILURE;
	}

	rc = pthread_create(&t2, NULL, f2, "f2");
	if(rc != 0) {
		fprintf(stderr, "pthread f2 failed\n");
		return EXIT_FAILURE;
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	sem_destroy(&bin_sem);

	puts("All threads finished.");
	return 0;
}