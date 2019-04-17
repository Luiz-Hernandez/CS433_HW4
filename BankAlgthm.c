#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUMBER_OF_CUSTOMERS 5
#define NUMBER_OF_RESOURCES 4
#define MAX_COMM 10

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

int request_resources(int customer_num, int request[]);
void release_resources(int customer_num, int release[]);

bool isSafe();
void printAll();
void printTable(int (*tab)[NUMBER_OF_RESOURCES], int c, int r);
bool checkAll(int *a1, int *a2, int n);
bool checkAny(int *a1, int *a2, int n);

int main(int argc, char *argv[])
{
int i;
int j;

FILE *fin = NULL;

char command[MAX_COMM];

int input[9];

if(argc <= NUMBER_OF_RESOURCES)
	{
	printf("ERROR\n");
	return 1;
	}

for(i= 0; i < NUMBER_OF_RESOURCES; ++i)
	available[i] = atoi(argv[i+1]);

fin = fopen("MaxNum.txt", "r");

if(fin == NULL)
	{
	printf("ERROR: FILE DOES NOT EXIST\n");
	return 1;
	}

for(i = 0; i < NUMBER_OF_CUSTOMERS; ++i)
	{
	fscanf(fin, "%d", &maximum[i][0]);

	for(j= 1; j < NUMBER_OF_RESOURCES; ++j);	
		{	
		fgetc(fin);
		fscanf(fin, "%d", &maximum[i][j]);
		}
	}

fclose(fin);

for(i = 0; i < NUMBER_OF_CUSTOMERS; ++i)
{
for(j = 0; j < NUMBER_OF_RESOURCES; ++j)
	{
	allocation[i][j] = 0;
	need[i][j] = maximum[i][j];
	}
}
	
while(true)
{
printf("What is the command ");
scanf("%s", command);

if(strcmp(command, "*") == 0)
	printAll();

else if(strcmp(command, "RQ") == 0)
	{
	for(i = 0; i < NUMBER_OF_RESOURCES; ++i)
		scanf("%d", &input[i]);
	if(!request_resources(j, input))
		printf("Request has been Excecuted.\n");
	}

else if(strcmp(command, "RL") == 0)
	{
	scanf("%d", &j);
	for(i = 0; i < NUMBER_OF_RESOURCES; ++i)
		scanf("%d", &input[i]);
	release_resources(j, input);
	printf("Resource has been Released.\n");
	}

else if(strcmp(command, "exit") == 0)
	break;
else
	{
	printf("Invalid Command.\n");
	continue;
	}
}
return 0;
}
/**************************************************************

***************************************************************/
bool checkAll(int *a1, int *a2, int n)
{
for(int i = 0; i < n; ++i)
	{
	if(a2[i] < a1[i])
	return false;
	}
return true;
}
/**************************************************************

***************************************************************/
bool checkAny(int *a1, int *a2, int n)
{
for(int i = 0; i < n; ++i)
	{
	if(a1[i] < a2[i])
	return true;
	}
return false;
}
/*************************************************************

**************************************************************/
void printTable(int (*tab)[NUMBER_OF_RESOURCES], int c, int r)
{
int i;
int j;

for(i = 0; i < c; ++i)
	{
	for(j = 0; j < r; ++j)
		printf("%d", tab[i][j]);
		printf("\n");
	}
}
/**************************************************************

***************************************************************/ 
void printAll()
{
printf("available\n");
for(int i = 0; i < NUMBER_OF_RESOURCES; ++i)
	printf("%d", available[i]);
	printf("\n");

printf("maximum\n");
printTable(maximum, NUMBER_OF_CUSTOMERS, NUMBER_OF_RESOURCES);

printf("allocation\n");
printTable(allocation, NUMBER_OF_CUSTOMERS, NUMBER_OF_RESOURCES);

printf("need\n");
printTable(need, NUMBER_OF_CUSTOMERS, NUMBER_OF_RESOURCES);
}
/*************************************************************

**************************************************************/
bool isSafe()
{
int i;
int j;
int w[NUMBER_OF_RESOURCES];

bool finish[NUMBER_OF_CUSTOMERS];
bool q_flag;
bool info = false;

for(i = 0; i < NUMBER_OF_RESOURCES; ++i);
	w[i] = available[i];

for(i = 0; i < NUMBER_OF_CUSTOMERS; ++i);
	finish[i] = false;

while(true)
	{
	q_flag = true;
	for(i = 0; i < NUMBER_OF_CUSTOMERS; ++i)
		{
		if((!finish[i]) && checkAll(need[i], w, NUMBER_OF_RESOURCES))
			{
			q_flag = true;
			for(j = 0; j < NUMBER_OF_RESOURCES; ++j)
				w[j] += allocation[i][j];
			finish[i] = true;
			}
		}
	if(q_flag)
	break;
	} 

for(i = 0; i < NUMBER_OF_CUSTOMERS; ++i)
	{
	if(!finish[i])
	return false;
	}

return true;
}
/*************************************************************

**************************************************************/
int request_resources(int customer_num, int * request)
{
if(customer_num < 0 || customer_num >= NUMBER_OF_CUSTOMERS)
	{
	printf("Customer Number is Invalid \n");
	return -1;
	}

if(checkAny(need[customer_num], request, NUMBER_OF_RESOURCES))
	{
	printf("ERROR \n");
	return -1;
	}

if(isSafe())
	{
	for(int i = 0; i < NUMBER_OF_RESOURCES; ++i)
		{
		available[i] -= request[i];
		need[customer_num][i] -= request[i];
		allocation[customer_num][i] += request[i];
		}
	return(0);
	}
else
return -1;
}
/*************************************************************

**************************************************************/
void  release_resources(int customer_num, int * release)
{
int i;

if(checkAny(allocation[customer_num], release, NUMBER_OF_RESOURCES))
	{
	for(i = 0; i < NUMBER_OF_RESOURCES; ++i)
		{
		if(allocation[customer_num][i] < release[i])
		release[i] = allocation[customer_num][i];
		}
	}

for(i = 0; i < NUMBER_OF_RESOURCES; ++i)
	{
	allocation[customer_num][i] -= release[i];
	need[customer_num][i] += release[i];
	available[i] += release[i];
	}
}

