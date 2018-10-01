#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFLEN 1000

int main(int argc, char *argv[], char *envp[]){
	
	int err;				//checks for errors
	int id;					//process id
	int i;					//for while loop to convert input to lowercase
	int toDB[2];			//for pipe to child
	int fromDB[2];			//for pipe from child
	int status;
	char param0[10];		//first param for db
	char param1[10];		//second param for db
	char buffer[BUFLEN];	//buffer for piping
	
	
	err = pipe(toDB);	//create the first pipe
	if(err == -1){		//check if there is an error on first pipe
		printf("Error on first pipe: %d\n", errno);
		exit(1);
	}
	
	err = pipe(fromDB);	//create the second pipe
	if(err == -1){		//check if there is an error on the second pipe
		printf("Error on second pipe: %d\n", errno);
		exit(2);
	}
	
	id = fork();		//create the child
	if(id == 0){		//child
		
		close(toDB[1]);						//close read pipe to DB
		close(fromDB[0]);					//close write pipe from DB
		
		sprintf(param0, "%d", fromDB[1]);	//send write stream
		sprintf(param1, "%d", toDB[0]);		//send read stream
		
		err = execl("./db", param0, param1, (char *)NULL);	//execute db
		if(err == -1){	//check to see if error executing db
			printf("Error executing db: %d\n", errno);
			exit(3);
		}
	}
	else if(id > 0){	//parent
		
		
		
		char input[100] = "list";
		close(toDB[0]); 					//close read pipe to DB.
		close(fromDB[1]);					//close write pipe from DB
		
		
		do{
			//char buffer[BUFLEN];	//buffer for piping
			// convert input to lower case
			i = 0;
			while(input[i]){
				input[i] = tolower(input[i]);
				i++;
			}
			//if the user inputs "exit"
			
			
			err = write(toDB[1], input, strlen(input)+1); //send input to DB
			if(err == -1){
				printf("Error while writing in interface: %d\n", errno);
			}
			
			if(!strcmp("exit", input)){
				printf("child process %d completed\n", getpid());
				waitpid(-1,&status,0);
				printf("child process exit status = %d\n", status);
				printf("db is complete\n");
				
				exit(0);
			}
			
			err = read(fromDB[0], buffer, BUFLEN+1); //recieve response from DB
			if(err == -1){
				printf("Error while reading in interface: %d\n", errno);
			}
			
			//buffer[BUFLEN] = '\0';
			printf("Response: %s\n", buffer);
			printf("\nInput command (account,id | add,id,cn,date,amount | delete,id,cn | list | exit):\n");
			

			scanf("%s",input);
			
		}while(1);
		
		
		//waitpid(-1,0,0);
		
		exit(0);
	}
}







