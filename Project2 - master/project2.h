//header file for project 2



//Swap bytes 1 and 3 in 32 bit number
#define XODD(n) ((((n>>24)&(0xFF))<<8) | (((n>>8)&0xFF)<<24) | (n&0x00FF00FF));
//Swap bytes 0 and 2 in 32 bit number
#define XEVEN(n) (((n>>16)&(0xFF)) | ((n&0xFF)<<16) | (n&0xFF00FF00));

#ifdef BINARY
#define base 0
#elif HEXADECIMAL
#define base 1
#else
#define base 2
#endif


void display(int);