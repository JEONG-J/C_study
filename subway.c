#include<stdio.h>
#include<limits.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define MAX_SUBWAY 31
#define INF 9999
#define SIZE 30 //이름 단어 수
#define 서울역 1


typedef struct Seoul {
	char name[SIZE];
	double ArraySub[MAX_SUBWAY];
}Seoul;

Seoul seoul[MAX_SUBWAY] = {
	{"사당역", {0,1.1,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1.6,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"이수역", {1.1,0,1.9,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.98,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"동작역", {INF,1.9,0,2.7,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.97,INF,INF,INF,INF,INF,INF,INF}},
	{"이촌역", {INF,INF,2.7,0,2.1,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1.3,INF,INF,INF,INF,INF}},
	{"신용산역", {INF,INF,INF,2.1,0,1.4,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"삼각지", {INF,INF,INF,INF,1.4,0,84,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1.1,INF,INF,INF}},
	{"숙대역", {INF,INF,INF,INF,INF,0.84,0,1.1,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"서울역", {INF,INF,INF,INF,INF,INF,1.1,0,0.7,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"회현역", {INF,INF,INF,INF,INF,INF,INF,0.7,0,0.5,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"명동역", {INF,INF,INF,INF,INF,INF,INF,INF,0.5,0,0.47,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"충무로역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,0.47,0,1.1,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"동대입구역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1.1,0,0.53,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"약수역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.53,0,0.67,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.61}},
	{"금호역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.67,0,0.64,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"옥수역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.64,0,0.2,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1.5,INF,INF,INF,INF}},
	{"압구정역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.2,0,1.4,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"신사역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1.4,0,89,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"잠원역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.89,0,1.4,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"고속터미널역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1.4,0,1.6,INF,INF,2.2,INF,0.66,INF,INF,INF,INF,INF,INF}},
	{"교대역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1.6,0,0.46,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"서초역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.46,0,1.7,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"방배역", {1.6,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1.7,0,INF,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"내방역", {INF,0.98,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,2.2,INF,INF,INF,0,INF,INF,INF,INF,INF,INF,INF,INF}},
	{"구반포역", {INF,INF,0.97,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0,0.93,INF,INF,INF,INF,INF,INF}},
	{"신반포역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,66,INF,INF,INF,INF,93,0,INF,INF,INF,INF,INF,INF}},
	{"서빙고역", {INF,INF,INF,1.3,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0,2.2,INF,INF,INF,INF}},
	{"한남역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1.5,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,2.2,0,INF,INF,INF,INF}},
	{"녹사평역", {INF,INF,INF,INF,1.1,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0,0.67,INF,INF}},
	{"이태원역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.67,0,0.1,INF}},
	{"한강진역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.1,0,1.1}},
	{"버티고개역", {INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,0.61,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,INF,1.1,0}}
};

double weight[MAX_SUBWAY][MAX_SUBWAY];
int record[MAX_SUBWAY][MAX_SUBWAY];
double distance[MAX_SUBWAY];
int found[MAX_SUBWAY];

int Choose(double distance[], int n, int found[]){
	int min,min_index;
	min=INT_MAX;
	min_index = -1;
	for(int i=0;i<n;i++){
		if(distance[i]<min && !found[i]){
			min = distance[i];
			min_index=i;
			}
		}
		return min_index;
}

void InitWeight(int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			weight[i][j]=seoul[i].ArraySub[j];
		}
	}
}

void InitRecord(int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			record[i][j]=INT_MIN;
		}
	}
}

void ShortPath(int start, int n){
	int w,u,j;
	for(int i=0;i<n;i++){
		if(weight[start][i]!=INF){
			record[i][0]=start;
			record[i][1]=i;
			}
		distance[i]=weight[start][i];
		found[i]=FALSE;
		}
	found[start]=TRUE;
	distance[start]=0;
	for(int i=0;i<n-2;i++){
		u=Choose(distance,n,found);
		found[u]=TRUE;
			for(w=0;w<n;w++){
				if(!found[w])
					if(distance[u]+weight[u][w] < distance[w]){
						distance[w]=distance[u]+weight[u][w];
					for(j=0;j<n;j++){
						record[w][j]=INT_MIN;
					}
						for(j=0;j<n;j++){
							if(record[u][j]!=INT_MIN)
								record[w][j]=record[u][j];
							else break;
						}
				record[w][j]=w;
				}
			}
		}
	  }
	
void PrintDistance(int start, int n){
	int list;
	for(int i=0;i<n;i++){
		if(distance[i] != INF){
			printf("\x1b[32m출발 : %s\x1b[0m\n",seoul[start].name);
			 printf("\x1b[31m목적지 : %s\x1b[0m\n",seoul[i].name);
			printf("\x1b[33m이동거리(단위 : km) : %.2lf\x1b[0m\n",distance[i]);
			printf("이동 방법 :: ");
		}
		else{
			printf("거리를 찾을 수 없습니다.\n");
		}
			for(int j=0;j<n;j++){
				if(record[i][j]>=0){
					printf("\x1b[36m%s\x1b[0m ",seoul[record[i][j]].name);
					list = j;
						}
							if(record[i][list+1]>=0){
									printf("->> ");
								}
							}
					/*	if(record[i+1][j+1]>=0){
							printf("->> "); */
				printf("\n\n");
						}
					}

int Name(char *str){
	int k=0;
	for(int i=0;i<MAX_SUBWAY;i++){
		if(strcmp(str,seoul[i].name)!=0)
			k++;
		if(strcmp(str,seoul[i].name)==0)
			break;
		}
	return k;
}

int main(void){
	char input[SIZE];
	int SaveInput;
	char ask = 'Y';
	while(ask == 'Y')
	{
	printf("출발 역 입력 : ");
	scanf("%s",input);
	SaveInput=Name(input);
	InitWeight(MAX_SUBWAY);
	InitRecord(MAX_SUBWAY);
	ShortPath(SaveInput,MAX_SUBWAY);
	PrintDistance(SaveInput,MAX_SUBWAY);
	printf("계속 진행하겠습니까?(Y|N) : ");
	scanf(" %c",&ask);
		if(ask == 'N')
			break;
	}
}

						

