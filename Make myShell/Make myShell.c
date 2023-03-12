#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 500

char store[MAX];
char* argv[100];
char* path="/bin/";
char full[20];

void Type_prompt(){
	printf("\x1b[36mJStart$\x1b[0m ");
}

void Read_command(){
		while(1){
			Type_prompt();
		char* symbol;

		if(!fgets(store, MAX, stdin))
			break;
		size_t length = strlen(store);
		if(store[length-1] == '\n')
			store[length - 1] = '\0';
		if(strcmp(store, "exit")==0)
			break;

		symbol = strtok(store, " ");
		int i=0;
		while(symbol != NULL && i<100){
			argv[i]=symbol;
			symbol = strtok(NULL," ");
			i++;
		}
		argv[i]=NULL;

		strcpy(full, path);
		strcat(full, argv[0]);

 		if (access(full,F_OK)==0){       
            pid_t pid, wpid;
            int status;
            
            pid = fork();
            if (pid == 0) {  
            	execvp(full,argv);
	    } 
            else if (pid > 0) { 
			wpid = waitpid(-1,&status,0);
            } 
		}
		else
			printf("Please re-enter\n");
    }
}
int main(void){
	system("clear");
	Read_command();
}