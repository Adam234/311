
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include "db.h"


int main(int argc, char *argv[], char *envp[]){
	
	if(argc  == 0){
		printf("No arguments for db.");
		
	}
	else{
		int recordNum;
		int err;
		int writeFD = atoi(argv[0]);
		int readFD = atoi(argv[1]);
		char filename[] = "accountData.txt";
		char response[BUFFLEN];
		char buffer[BUFFLEN];
		char command[BUFFLEN];
		
		Record records[100];
		
		recordNum = getRecordNum(filename);
		getRecordData(records, filename);
		
		do{
			err = read(readFD, buffer, BUFFLEN); 
			if(err == -1){
				printf("Error reading from pipe in db: %d\n", errno);
				exit(8);
			}
			
			switch(readCommand(buffer)){
				case 1: sprintf(response, "db complete");
					exit(0);
					break;
				case 2: printList(records, recordNum, response);
					break;
				case 3: getAccountAmount(records, recordNum, buffer, filename, response);
					break;
				case 4: addRecord(records, &recordNum, buffer, filename, response);
					break;
				case 5: deleteRecord(records, &recordNum, buffer, filename, response);
			}
			
			//sprintf(response,"Hello");
			err = write(writeFD, response, strlen(response)+1);
			if (err == -1)
			{
				printf ("Error on write to pipe: %d\n", errno);
				exit(9);
			}
		
			
		}while(1);
	
	}
	exit(0);
}

int getRecordNum(char filename[]){
	
	FILE *fp;
	int count = 0;
	char ch;
	
	fp = fopen(filename, "r");
	
	if(fp == NULL){
		printf("Could not open file %s", filename);
	}
	
	while((ch = fgetc(fp)) != EOF){
		
		if(ch == '\n'){
			count++;
		}
	}
	fclose(fp);
	return count;
}

void getRecordData(Record records[], char filename[]){
	
	FILE *fp;
	long int id;
	int checkNumber, i, input;
	float amount;
	char date[9];
	fp = fopen(filename, "r");
	if(fp == NULL){
		printf("Could not open file %s", filename);
	}
	
	for(i = 0; !feof(fp); i++){
		
		input = fscanf(fp, "%ld %d %s %f", &id, &checkNumber, date, &amount);
		
		records[i].id = id;
		records[i].checkNumber = checkNumber;
		records[i].amount = amount;
		sprintf(records[i].date, "%s", date);
	}
	fclose(fp);
	
}

void printList(Record records[], int recordNum, char response[]){

	
	for(int i = 0; i < recordNum; i++){
		printf("element[%d]:",i);
		printf("  id = %ld,",records[i].id);
		printf("  check Number: %d,",records[i].checkNumber);
		printf("  date: %s,",records[i].date);
		printf("  amount: %.2f\n",records[i].amount);
	}
	sprintf(response, "List complete");
}

int readCommand(char buffer[]){
	
	if(!strcmp(buffer,"exit")){
		
		return 1;
		
	}
	else if(!strcmp(buffer,"list")){
		return 2;
	}
	else if(!strncmp(buffer,"account",strlen("account"))){
		return 3;
		
	}
	else if(!strncmp(buffer,"add",strlen("add"))){
		return 4;
		
	}
	else if(!strncmp(buffer,"delete",strlen("delete"))){
		return 5;
		
	} 
	return 0;
}

void getAccountAmount(Record records[], int recordNum, char buffer[], char filename[],char response[]){
	getRecordData(records, filename);
	
	char *id;
	char token[2] = ",";
	float amount = 0;
	
	id = strtok(buffer,token);
	id = strtok(NULL,token);
	
	for(int i = 0; i < recordNum; i++){
		
		if(records[i].id == atoi(id)){
			amount += records[i].amount;
		}
	}
	
	sprintf(response, "Total for account %s: %.2f\n", id, amount);
}

void addRecord(Record records[], int *recordNum, char buffer[], char filename[], char response[]){
	long int id;
	int cn;
	int rn = *recordNum;
	char date[9];
	char token[2] = ",";
	char *command;
	float amount;
	FILE *fp;
	
	command = strtok(buffer,token);
	command = strtok(NULL,token);
	id = atol(command);
	
	command = strtok(NULL,token);
	cn = atoi(command);
	
	command = strtok(NULL,token);
	strcpy(date,command);
	
	command = strtok(NULL,token);
	amount = atof(command);
	sprintf(response,"%ld, %i, %s, %.2f\n", id,cn,date,amount);
	
	rn++;
	records[rn-1].id = id;
	records[rn-1].checkNumber = cn;
	records[rn-1].amount = amount;
	sprintf(records[rn-1].date, "%s", date);
	*recordNum = rn;
	fp = fopen(filename, "a");
	
	if(fp == NULL){
		printf("Could not open file %s", filename);
	}
	fprintf(fp, "\r\n%ld %d %s %.2f", id, cn, date, amount);
	fclose(fp);
	sprintf(response, "added:\nelement[%d]: id = %ld, checkNumber: %d, date: %s, amount: %.2f", rn-1, id, cn, date, amount);
	
	
}

void deleteRecord(Record records[], int *recordNum, char buffer[], char filename[], char response[]){
	
	
	long int id;
	int cn;
	int rn = *recordNum;
	char token[2] = ",";
	char *command;
	FILE *fp;
	
	command = strtok(buffer,token);
	command = strtok(NULL,token);
	id = atol(command);
	
	command = strtok(NULL,token);
	cn = atoi(command);
	
	rn--;
	for(int i = 0; i < rn; i++){
		
		if(records[i].id == id && records[i].checkNumber == cn)
			records[i] = records[i+1];
		
	}
	*recordNum = rn;
	
	fp = fopen(filename, "w");
	if(fp == NULL){
		printf("Could not open file %s", filename);
	}
	
	for(int i = 0; i < rn ; i++){
		
		fprintf(fp, "%ld %d %s %f", records[i].id, records[i].checkNumber, records[i].date, records[i].amount);

	}
	fclose(fp);
	sprintf(response, "Record deleted.");
}