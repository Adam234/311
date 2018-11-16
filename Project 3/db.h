
#define BUFFLEN 2000

//struct to hold the records in the file
typedef struct Record{
	
	long int id; //identity of the record
	int checkNumber; //id of the check
	float amount; //amount of the check
	char date[9]; //date on the check

}Record;

//Get the number of records in the file
int getRecordNum(char filename[]);

//assign the records in the file to the record struct
void getRecordData(Record records[], char filename[]);

//return the list in string format to the the interface
void printList(Record records[], int recordNum, char response[]);

//determine what command was entered by the user
int readCommand(char buffer[]);

//if account is command then return the total amount for that account to the interface
void getAccountAmount(Record records[], int recordNum, char buffer[], char filename[], char response[]);

//add a record the the Record struct and append the new record to the file
void addRecord(Record records[], int *recordNum, char buffer[], char filename[], char response[]);

//delete a record from the record struct and delete the record from the file.
void deleteRecord(Record records[], int *recordNum, char buffer[], char filename[], char response[]);