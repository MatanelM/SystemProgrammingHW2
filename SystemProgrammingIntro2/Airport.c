#define _CRT_SECURE_NO_WARNINGS//**
#include <stdio.h>//*
#include <string.h>
#include <stdlib.h>//**
#include "Airport.h"

/*
Airport* initAirport()//did addnewairport instead
{
	Airport* ap = malloc(sizeof(Airport));

	if (!ap)
	{
		printError();
		return 0;
	}
	ap->name = NULL;
	ap->address = NULL;
}
*/
int isSameAirport(const Airport *a1, const Airport *a2)
{
	return strcmp(a1->name, a2->name) == 0;
}
int isAirportName(const Airport *a1, const char name[])
{
	return strcmp(a1->name, name) == 0;
}
void doPrintAirport(Airport* pai)
{
	printf("Airport name: %s\n", pai->name);
	printf("Airport address: %s\n", pai->address);
}
/*
void doGetAddressFromUser()//??
{
	int i;
	char* country, city, street, houseNum ;
	printf("please enter a country: \n");
	fgets(country,L_255,stdin);
	printf("please enter a city: \n");
	fgets(city, L_255, stdin);
	printf("please enter a street: \n");
	fgets(street, L_255, stdin);
	printf("please enter a house number: \n");
	fgets(houseNum, L_255, stdin);

	for (i = 0; i < strlen(country); i++)
	{
		while (country[i] != '\0')
		{
			if (isspace(country[i]))
			{
				country[i] = '#';
			}
		}
	}

}
*/
Airport* initAirport() //**malloc to the address and the name??
{

	// 1. Get airport address
	char* address = inputAddress(); // mem allocation
	printf("this is the saved address: %s\n", address);

	if (!address)
	{
		return NULL;
	}

	// 2. get airport's Name
	char* name = inputWithMessage("Insert Airport name please: \n");
	printf("this is the saved name: %s\n", name);
	if (!name) {
		printf("Error: cannot assign memory.");
		free(address);
		return NULL;
	}
	if (strlen(name) == 0) {
		printf("Error: Name cannot be empty.");
		free(address);
		free(name);
		return NULL;
	}

	// 3. create airport struct & insert (address, name)
	Airport* pai = malloc(sizeof(Airport));
	// changed _______ START 
	// Airport* pai = initAirport()
	// Airport* pai = initAirport(name, address);

	// changed _______ END 
	if (!pai)
	{
		printf("Error: cannot assign memory.");
		free(address);
		free(name);
		return NULL;
	}

	pai->address = address;
	pai->name = name;
	printf("airportName is: %s", pai->name);
	return pai;
}

void freeAirport(Airport* a1)
{
	
	free(a1->address);//
	free(a1->name);//
	free(a1);
}