#include <stdlib.h>
#include <stdio.h>
#include "project2.h"



int main(){
	
	int number;	//number input by user
	int temp;	//temp variable to store XEVEN/OR value
	int option;	//option selected from menu
	int done;	//bool to leave loop

	printf("Input number: ");
	scanf("%i", &number);

	do{
		done = 0; //set not done
		printf("Select option:\n");
		printf("\t1. Display number in designated base.\n");
		printf("\t2. Exchange odd numbered bytes.\n");
		printf("\t3. Exchange even numbered bytes.\n");
		printf("\t4. Take the one's complement of the number.\n");
		printf("\t5. Exit.\n");
		printf("->");
		scanf("%i", &option);
	
		switch(option){
			case 1:	display(number);
			break;
			case 2: temp = XODD(number);
					printf("Number before: ");
					display(number);
					printf("Number after : ");
					display(temp);
			break;
			case 3: temp = XEVEN(number);
					printf("Number before: ");
					display(number);
					printf("Number after : ");
					display(temp);
			break;
			case 4: temp = ~number;
					printf("Number before: ");
					display(number);
					printf("Number after : ");
					display(temp);
			break;
			default: done = 1; //set done
			break;
		}
		
	}while(!done);
	return 0;
}



void display(int num){
	//base is assigned 0 for binary, 1 for hex, and not defined for decimal
	if(base == 0){
		//convert in to binary and display
		for(int i = 31; i >= 0; i--){
			if((num & (1 << i)) != 0){
				printf("1");
			}else{
				printf("0");
			} 
		}
		printf("\n");
	}
	else if(base == 1){
		printf("0x");
		printf("%X\n", num); //%X will display int in hex
	}
	else{
		printf("%i\n", num); //do nothing for decimal
	}
}
