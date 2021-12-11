#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Airport.h"

int isSameAirport(const Airport *a1, const Airport *a2)
{
	return strcmp(a1->name, a2->name) == 0;
}
int isAirportName(const Airport *a1, const char name[])
{
	return strcmp(a1->name, name) == 0;
}
void doPrintAirport(const Airport* pai)
{
	printf("Airport name: %s\n", pai->name);
	printf("Airport address: %s\n", pai->address);
}

Airport* initAirport() 
{
	// 1. Get airport address
	char* address = inputAddress(); 

	if (!address)
	{
		return NULL;
	}
	// 2. get airport's Name
	char* name = inputWithMessage("Insert Airport name please: \n");
	if (!name) {
		printError();
		free(address);return NULL;
	}
	if (strlen(name) == 0) {
		printf("Error: Name cannot be empty.");
		free(address);free(name);return NULL;
	}

	// 3. create airport struct & insert (address, name)
	Airport* pai = malloc(sizeof(Airport));

	if (!pai)
	{
		printError();
		free(address);free(name);return NULL;
	}

	pai->address = address;
	pai->name = name;
	printf("airportName is: %s", pai->name);
	return pai;
}

void freeAirport(Airport* a1)
{// method not used
	
	free(a1->address);
	free(a1->name);
	free(a1);
}