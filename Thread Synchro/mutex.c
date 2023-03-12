#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10

int count = 0;
int f1_wallet[MAX];
int f1_count = 0;
int total_balance = 1000000;
int sum_f1 = 0;
int sum_f2 = 0;
int save;
int i;

void enter_region() {

	asm(

			".data\n"

			"lock:\n"

			".byte 0\n"

			".text\n"

			"_enter_region:\n"

			"movb $1, %al\n" // move 1 to AL

			"xchgb lock,%al\n"	

			"cmp $0, %al\n"

			"jne _enter_region\n"

	   );

}



void leave_region() {

	asm("movb $0, lock");

}


int bank(int money){
	total_balance = total_balance - money;
	f1_wallet[f1_count] = money;
	f1_count += 1;
}

void critical_region_f1(char *p) {

	int d = rand()%1000000;

	printf("--------------------------------------------------------\n");

	save = rand() % 10000 + 1;
	printf("\t%d원 빌렸습니다.\n",save);
	bank(save);
	sum_f1 = sum_f1 + save;
	printf("--------------------------------------------------------\n");

	usleep(d);

}

void critical_region_f2(char *p) {

	int d = rand()%1000000;

	printf("--------------------------------------------------------\n");	

	total_balance = total_balance + f1_wallet[i];
	printf("\t%d원을 갚았습니다.\n",f1_wallet[i]);

	sum_f2 = sum_f2 + f1_wallet[i];
	printf("--------------------------------------------------------\n");

	usleep(d);

}




void noncritical_region(char *p) {

	int d = rand()%1000000;



	usleep(d); 

}




static void* f1(void* p) {
	srand(time(NULL));
	for(int i=0; i<10; i++) {
		enter_region();

		printf("[%d] >> f1이 돈을 빌리기 시작합니다. <<\n\n",i+1);

		critical_region_f1(p);

		leave_region();

		noncritical_region(p);
		printf("\n");


	}
	printf("빌린 총 액수 : %d\n",sum_f1);
	printf("현재 은행 잔액 : %d\n",total_balance);
	return NULL;

}

static void* f2(void* p) {
	int return_money;
	for(i=0; i<10; i++) {
		enter_region();

		printf("[%d] >> f2가 돈을 갚기 시작합니다. <<\n\n",i+1);
		critical_region_f2(p);

		leave_region();

		noncritical_region(p);

		printf("\n");
	}
	printf("갚은 총 액수 : %d\n",sum_f2);
	printf("현재 은행 잔액 : %d\n",total_balance);

	return NULL;
}



int main() {
	int rc;


	pthread_t t1, t2;

	rc = pthread_create(&t1, NULL, f1, "f1");
	if(rc != 0) {
		fprintf(stderr, "pthread f1 failed\n");
		return EXIT_FAILURE;
	}
	sleep(3);

	rc = pthread_create(&t2, NULL, f2, "f2");
	if(rc != 0) {
		fprintf(stderr, "pthread f2 failed\n");
		return EXIT_FAILURE;
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);



	puts("All threads finished.");
	return 0;
}