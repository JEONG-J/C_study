#include <stdio.h>

#define MAX_TERMS 101
typedef struct temrs{
	float coef; //밑
    int expon; //지수
	}terms;

#define MAX_DEGREE 101
typedef struct poly_B{
	int degree;
	float coef[MAX_DEGREE];
	}poly_b;

int startD;₩
int D; //전역변수

void attach(terms poly[],int coef,int expon,int start)
{
poly[start].coef=coef;
poly[start].expon=expon;
}

int coef_b(struct poly_B b,int start)
{
	return b.coef[start];
}

int coef_a(terms a[],int start)
{
	return a[start].coef;
}

int compare(int a, int b)
{
	if(a<b) return -1;
	else if(a==b) return 0;
    else return -1;
}

void padd_h(terms *a, struct poly_B B, int startA, int finishA, int startB, int finishB, int startD)
{
	int sum;
		while(startA<=finishA||startB<=finishB)
			{
				switch(compare(a[startA].expon, finishB-startB+1))
					{
						case -1 :
							if(B.coef[startB]==0)
								{
									startB++;
									break;
								}
							attach(a,coef_b(B,startB),finishB-startB+1,startD);
							startB++;
							startD++;
							break;
						case 0 :
							sum=coef_a(a,startA)+coef_b(B,startB);
							if(sum>0)
								{
									attach(a,sum,a[startA].expon,startD);
									startD++;
									startB++;
									startA++;
								}
								break;
						case 1 :
							attach(a,coef_a(a,startA),a[startA].expon,startD);
							startA++;
							startD++;
							break;
					}
				}
		D=startD;
}


int main(void)
{
	int q; //a항
	int w; //b항 입력
	int b_e; //b지수
	int im_de;
	terms a[MAX_TERMS];
	for(int i=0;i<MAX_TERMS;i++)
			{
				a[i].coef=0;
				a[i].expon=0;
			}
		printf("Enter A(x) : \n");
		printf("게수가 0이 아닌 항의 수? : ");
		scanf("%d", &q);
		for(int i=0;i<q;i++)
			{
				printf("계수? : ");
				scanf("%f",&a[i].coef);
				printf("지수? : ");
				scanf("%d", &a[i].expon);
			}

		printf("Enter B(x) : \n");
		printf("계수가 0이 아닌 항의 수? : ");
		scanf("%d", &w);
	
		struct poly_B B;
		for(int i=0;i<MAX_DEGREE;i++)
		{
			B.coef[i]=0;
		}

	printf("계수? : ");
	scanf("%f", &B.coef[0]);
	printf("지수? : ");
	scanf("%d", &b_e);
	B.degree=b_e;
	im_de=b_e;
	

	for(int i=1;i<w;i++)
		{
			printf("계수? : ");
			scanf("%f", &B.coef[i]);
			printf("지수? : ");
			scanf("%d", &b_e);
		
			
		}
	printf("A항 출력 : ");
	for(int i=0;i<=q;i++){
		if(a[i].coef==0) continue;
		printf("%3.0fx^%d ",a[i].coef, a[i].expon);
		if(i<q-1) printf(" +");
			}
		printf("\n");

	printf("B항 출력 : ");
	for(int i=0;i<B.degree;i++)
		{
		if(B.coef[i]==0) continue;	
		printf("%3.0fx^%d ",B.coef[i],B.degree-i);
			if(i<B.degree-1) printf(" +");
		}
			printf("\n");
	//b항 출력문 작성 자리//

		padd_h(a, B, 0, q-1, 0, B.degree-1, startD);
		printf("\n");
		
		printf("D항 출력 : ");
		for(int i=0;i<D;i++)
		{
			if(a[i].coef == 0) continue;
			printf("%3.0fx^%d ", a[i].coef, a[i].expon);
			if(i<D-1) printf(" +");
		}
}
