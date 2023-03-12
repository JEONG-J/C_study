#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node *treePointer;
typedef struct node{
char data;
struct node *leftChild;
struct node *rightChild;
}node;

typedef struct qnode{ // 큐 구조체 생성
	treePointer queue[100];
	int front,rear;
}qnode;

typedef struct linknode
{
	node* data;
	struct linknode* link;
}tnode;

//연결리스트 큐 프론트 리어
tnode* front = NULL;
tnode* rear = NULL;


char ask[4]; //입력받기 변수
char x; //입력 앞자리
char y; //입력 뒷자리
char z; //입력 중간자리
char* end = "$$$"; // 종료 변수

treePointer temp; //a저장 노드
treePointer temp1; //b저장 노드
treePointer temp2; //새로 생성 노드
treePointer top; //최고 위치 노드
treePointer b_top;//이전 최고 위치 노드

int empty(){//큐 비었는지 확인
	return front == NULL;
	}

void init(){ //큐 초기화
	front = rear = NULL;
}

void addq(node* ptr){ //연결리스트 큐데이터 추가
	tnode* p = (tnode*)malloc(sizeof(tnode));
	p->data = ptr;
	p->link = NULL;
	if(empty()) front = rear = p;
	else{
		rear->link = p;
		rear = p;
	}
}

node* deleteq(){
	tnode* p;
	node* e;
	p=front;
	front = front->link;
	if(front == NULL) rear = NULL;
	e = p->data;
	free(p);
	return e;
}

treePointer new(char data){
	temp2 = (treePointer)malloc(sizeof(node));
	temp2->leftChild = NULL;
	temp2->rightChild = NULL;
	temp2->data = data;
		return temp2;
}

void levelOrder(node* ptr){
	node* n;
	if(ptr == NULL) return;
	init();
	addq(ptr);
	while(!empty()){
		n = deleteq();
		if(n != NULL){
			printf("%c", n->data);
				addq(n->leftChild);
				addq(n->rightChild);
		}
	}
}

void search(node* root){ //같은게 있나 없나 탐색
	if(root == NULL)
		return;
	else if(root->data == x){
		new(ask[2]);//노드 생성 후 값 저장
			if(z=='F'){
				root->leftChild = temp2;
				root = temp2;
			}
			else if(z=='M'){
				root->rightChild = temp2;
				root = temp2;
			}
		}
	else if(root->data == y){
		new(ask[0]);
		b_top=top;
		top=temp2;
			if(z=='F')
				top->leftChild = b_top;
			else if(z=='M')
				top->rightChild = b_top;
		}
	search(root->leftChild);
	search(root->rightChild);
}

int main(void){
	printf(">>\n");
	printf(">>");
	scanf("%s",ask);
	if(strcmp(ask, end) !=0)
	{ 
		temp = new(ask[0]);
		temp1 = new(ask[2]);
		if(ask[1]=='F'){
		temp->leftChild = temp1;
		top = temp;
		}
		else if(ask[1]=='M'){
		temp->rightChild = temp1;
		top = temp;
		}
		levelOrder(top);
		printf("\n");
	}
	while(strcmp(ask, end) != 0){//두번째 입력부터 작동
		printf(">>");
		scanf("%s",ask);
		if(strcmp(ask, end) == 0) break;
		x=ask[0];
		y=ask[2];
		z=ask[1];
		search(top);
		levelOrder(top);
		printf("\n");
		}
}
