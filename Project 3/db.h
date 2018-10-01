
#define BUFFLEN 2000
#define INVAL_CMD "Invalid command "
typedef struct Record{
	
	long int id;
	int checkNumber;
	float amount;
	char date[9];

}Record;


int getRecordNum(char filename[]);

void getRecordData(Record records[], char filename[]);

void printList(Record records[], int recordNum, char response[]);

int readCommand(char buffer[]);

void getAccountAmount(Record records[], int recordNum, char buffer[], char filename[], char response[]);

void addRecord(Record records[], int *recordNum, char buffer[], char filename[], char response[]);

void deleteRecord(Record records[], int *recordNum, char buffer[], char filename[], char response[]);