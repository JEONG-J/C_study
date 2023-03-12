#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int tableready = 0; //테이블 대기수
int select; //기능 선택
int people; //입력 인원수
int tablesize; //식탁 크기
int r_num = 9; //초기 대기번호
int n = 0;
int q = 0; //큐 인덱스
int result;//대기번호 반환
int result0; //인원수 반환

typedef struct element{
	int key; //대기번호
	int num; //인원수
}element;

element heap[20];
element queue[30];

void init(){ //큐 초기화
	for(int i=0;i<30;i++){
		queue[i].key = 0;
		queue[i].num = 0;
		}
}


void swap(int *a, int *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void push(element item){
	if(n>MAX) return;
	heap[++n] = item;
	int child = n;
	int parent = child/2;
	while(child>1 && heap[parent].key<heap[child].key){
		swap(&heap[parent].key, &heap[child].key);
		swap(&heap[parent].num, &heap[child].num);
		child = parent;
		parent = child/2;
	}
}

int pop(){
	result = heap[1].key;
	result0 = heap[1].num;
	swap(&heap[1].key, &heap[n].key);
	swap(&heap[1].num, &heap[n].num);
	n--;

	int parent = 1;
	int child = 2;
	if(child+1 <= n){
		child = (heap[child].key > heap[child + 1].key) ? child : child + 1;
	}
	while(child <= n && heap[parent].key < heap[child].key){
		swap(&heap[parent].key, &heap[child].key);
		swap(&heap[parent].num, &heap[child].num);

		parent = child;
		child = child*2;
		if(child + 1 <= n){
			child = (heap[child].key > heap[child+1].key) ? child:child+1;
		}
	}
		return result; //대기번호 반환
		return result0; //인원수 반환
}

void s_print(){ //시작화면 출력
	printf("Start of Program\n");
	printf("기능\n");
	printf("0.종료 1.대기접수 2.식탁배정\n");
	printf("식탁 대기수: %d\n",tableready);
	printf("-------------\n");
}

void sel_m(){ //기능선택 문구
	printf("기능 선택?: ");
	scanf("%d",&select);
}

void sel1(){
	printf("대기번호 : %d\n",r_num);
	printf("인원수?: ");
	scanf("%d",&people);
	printf("식탁 대기수 : %d\n",tableready);
	printf("-------------\n");
}

void sel2(){
	printf("식탁 크기?: ");
	scanf("%d",&tablesize);
	while(1){
		pop();			
		if(result0<=tablesize){
			printf("배정:: 대기번호: %d 인원수: %d\n",result,result0);
			tableready = tableready - 1;
			printf("식탁 대기수 : %d\n",tableready);
			printf("-------------\n");
			break;
			}
		else if(result0>tablesize){
				queue[q].key = result;
				queue[q].num = result0;
				q = q+1;
					if(n==0){
						printf("배정불가::\n");
						printf("식탁 대기수: %d\n",tableready);
						printf("-------------\n");
						break;
						}
			}
		}
		for(int i=0;i<=q;i++){
			if(queue[i].key != 0 && queue[i].num != 0)
				push(queue[i]);
			}
		init();
	}

int main(void){
	init();
	element root;
	s_print();
	while(1){
		sel_m();
			if(select == 0){
				printf("End of Program\n");
				break;
				}
			else if(select == 1){
				tableready = tableready + 1;
				sel1();
				root.key = r_num; //대기번호
				root.num = people; //인원수
				push(root);
				r_num = r_num - 1;
				}
			else if(select == 2){
				sel2();
				}
		}
}
