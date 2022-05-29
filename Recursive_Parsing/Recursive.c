#include <stdio.h>
#include <ctype.h>

void exper();
void term();
void factor();
void addChar();
void getChar();
void getNonBlank();
void error();
int lexLen;
int nextToken;
int lex();
int charClass;
int cnt = 1;
char nextChar;
char lexeme[100];

FILE *in_fp, *fopen();

#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define INPUT_OP 27
#define END 28

void error(){
	printf("ERROR\n");
}

int lookup(char ch){
	switch(ch){
		case '(':
			addChar();
			nextToken = LEFT_PAREN;
			break;
		case ')':
			addChar();
			nextToken = RIGHT_PAREN;
			break;
		case '+':
			addChar();
			nextToken = ADD_OP;
			break;
		case '-':
			addChar();
			nextToken = SUB_OP;
			break;
		case '*':
			addChar();
			nextToken = MULT_OP;
			break;
		case '/':
			addChar();
			nextToken = DIV_OP;
			break;
		case '=':
			addChar();
			nextToken = INPUT_OP;
			break;
		case ';':
			addChar();
			nextToken = END;
			break;
		default:
			addChar();
			nextToken = EOF;
			break;
	}
	return nextToken;
}

void addChar(){
	if(lexLen <= 98){
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long\n");
}

void getChar(){
	if ((nextChar = getc(in_fp)) != EOF){
		if(isalpha(nextChar))
			charClass = LETTER;
		else if(isdigit(nextChar))
			charClass = DIGIT;
		else
			charClass = UNKNOWN;
	}
	else
		charClass = EOF;
}

void getNonBlank(){
	while(isspace(nextChar))
		getChar();
}

int lex(){
	lexLen = 0;
	getNonBlank();
	switch (charClass){
		case LETTER:
			addChar();
			getChar();
			while(charClass == LETTER || charClass == DIGIT){
				addChar();
				getChar();
			}
			nextToken = IDENT;
			break;
		case DIGIT:
			addChar();
			getChar();
			while(charClass == LETTER || charClass == DIGIT){
				addChar();
				getChar();
			}
			nextToken = INT_LIT;
			break;
		case UNKNOWN:
			lookup(nextChar);
			getChar();
			break;
		case EOF:
			nextToken = EOF;
			break;
	}
	if(nextToken != EOF){
		if(nextToken == END){
			printf("----------------\n");
			cnt = 1;
		}
		else{
			printf("[%d] :  %s\n",cnt++,lexeme);
		}
	}
		return nextToken;
}

void expr(){
	term();
	while (nextToken == ADD_OP || nextToken == SUB_OP){
		lex();
		term();
	}
}

void term(){
	factor();
	while (nextToken == MULT_OP || nextToken == DIV_OP){
		lex();
		factor();
	}
}

void factor(){
	if (nextToken == IDENT || nextToken == INT_LIT){
		lex();
	}
	else{
		if (nextToken == LEFT_PAREN){
			lex();
			expr();
			if(nextToken == RIGHT_PAREN){
				lex();
			}
			else{
				error();
			}
		}
		else{
			lex();
		}
	}
}

int main(void){
	if((in_fp = fopen("test.txt", "r")) == NULL)
		printf("ERROR\n");
	else{
		getChar();
		lex();
		while(feof(in_fp) == 0){
			expr();
		}
	}
}

