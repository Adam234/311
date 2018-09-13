#include <stdlib.h>
#include <stdio.h>
#include "project2.h"

int main(){
	
	int number;
	int temp;
	int option;
	int exit = 0;
	printf("Input number: ");
	scanf("%i", &number);
	
	do{
		exit = 1;
		printf("Select option:\n");
		printf("\t1. Display number in designated base.\n");
		printf("\t2. Exchange odd numbered bytes.\n");
		printf("\t3. Exchange even numbered bytes.\n");
		printf("\t4. Take the one's complement of the number.\n");
		printf("\t5. Exit.\n");
		printf("->");
		scanf("%i", &option);
	
		switch(option){
			case 1:	printf("%X\n", number);
			break;
			case 2: temp = XODD(number);
					printf("Number before: %X\n", number);
					printf("Number after : %X\n", temp);
			break;
			case 3: temp = XEVEN(number);
					printf("Number before: %X\n", number);
					printf("Number after : %X\n", temp);
			break;
			case 4: temp = ~number;
					printf("Number before: %X\n", number);
					printf("Number after : %X\n", temp);
			break;
			default: exit = 0;
			break;
		}
		
	}while(exit);
	return 0;
}