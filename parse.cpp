#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

char* str = "14*8+2";


char** parse(char* str) {
	int len = strlen(str);
	char** parsed = (char**) malloc(len*sizeof(char*));
	
	int i,j, length = 0,counter=0;
	char* buf = (char*)malloc(5);
	for(i=0;i<=len;i++) {
		switch(str[i])  {
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
				buf[length++] =str[i];
				break;
			case '+':
			case '-':
			case '*':
			case '/':
				buf[length] = '\0';
				parsed[counter] = (char*)malloc(length);
				strcpy (parsed[counter++], buf);
			
				length = 0;
				parsed[counter] = (char*)malloc(1);
				parsed[counter][0] = str[i] ;
				parsed[counter++][1] = '\0' ;
				
				break;
		}
	}
	
	buf[length] = '\0';
	parsed[counter++] = buf;
	parsed[counter] = (char*)malloc(1);
	parsed[counter] = "end";
	return parsed;
}

int compute(char** parsed, char* OperationStack, double* OperandStack) {
	int i;
	int OperationCounter = 0, OperandCounter = 0;
	for(i=0; parsed[i]!="end";i++) {
		switch(parsed[i][0]) {
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
			 OperandStack[OperandCounter++] = atoi(parsed[i]);
				break;
			case '+':
			case '-':
				if(OperationStack[OperationCounter-1] == '*' || OperationStack[OperationCounter-1] == '/') {
					double a2 = OperandStack[--OperandCounter];
			
					double a1 = OperandStack[--OperandCounter];
			
					double result;
					switch(OperationStack[--OperationCounter]) {
						case '+':
							result = a1+a2;
							break;
						case '-':
							result = a1-a2;
							break;
						case '*':
							result = a1*a2;
							break;
						case '/':
							result = a1/a2;
							break;
					}
					OperandStack[OperandCounter++] = result;
					//printf("%lf&%lf = %lf",a1, a2,OperandStack[OperandCounter-1]);
					break;
				}
			case '*':
			case '/':
				OperationStack[OperationCounter++] = parsed[i][0];
				break;
		}
		
	}
	printf("%d", OperandCounter);
//	while(OperationCounter)	
}






int main() {
	
	
	
	char** parsed = parse(str);
	int i;
//	for(i=0; parsed[i]!="end";i++)
	//	printf("%s\n", parsed[i]);
	
	char* OperationStack = (char*) malloc(i);
	double* OperandStack = (double*) malloc(i*sizeof(double));
	compute(parsed, OperationStack, OperandStack);
		
}
