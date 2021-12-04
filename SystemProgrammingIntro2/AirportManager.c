#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include "Airport.h"
#include "AirportManager.h"

int addAirport(AirportManager* *pam, const Airport *pai)
{
	unsigned char num, size;
	num = (*pam)->numOfAirports;
	if (num == MAX_AIRPORTS)
	{
		printf("Error: Airports array reached maximum\n");
		return 0;
	}

	if (isAirportExists((*pam), pai))
	{
		printf("Airport exists\n");
		return 0;
	}

	size = (*pam)->sizeOfAirports;
	if (num == size)
	{
		size *= 2;

		Airport* arr = (*pam)->airports; // array
		Airport* newArr = malloc(size * sizeof(Airport));
		for (int i = 0; i < num; i++)
		{
			*(newArr + i) = *(arr + i);
		}
		free((*pam)->airports);
		(*pam)->airports = newArr;
		(*pam)->sizeOfAirports = size;
	}
	char* address = malloc(strlen(pai->address), sizeof(char));
	char* name = malloc(strlen(pai->name), sizeof(char));

	strcpy(address, pai->address);
	strcpy(name, pai->name);

	(*pam)->airports[num].address = address;
	(*pam)->airports[num].name = name;
	
	(*pam)->numOfAirports = num + 1;
	return 1;
}

Airport* findAirportByName(const AirportManager *pam, const char name[])
{
	int max = pam->numOfAirports;
	for (int i = 0; i < max; i++)
	{
		Airport* a1 = &(pam->airports[i]);
		if (isAirportName(a1, name))
		{
			return a1;
		}
	}
	return NULL; // todo - return null if not exists
}

int isAirportExists(AirportManager *pam, const Airport *pai)
{
	int exists = 0;
	int max = pam->numOfAirports;
	for (int i = 0; i < max; i++)
	{
		Airport* a1 =  &((pam->airports)[i]);
		if (isSameAirport(pai, a1)) {
			exists = 1;
			break;
		}
	}
	return exists; // todo - return null if not exists
}

void freeAirportManager(AirportManager* pam)
{
	free(pam);
}

// add more as required