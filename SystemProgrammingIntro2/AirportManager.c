#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include "Airport.h"
#include "AirportManager.h"

AirportManager* initAirportManager()
{
	AirportManager* pam = malloc(sizeof(AirportManager));
	if (!pam)
	{
		printError();
		return 0;
	}
	pam->airports = NULL;
	pam->numOfAirports = 0;
}

int addAirport(AirportManager* pam)
{
	unsigned char num;
	num = pam->numOfAirports;
	if (num == MAX_AIRPORTS)
	{
		printf("Error: Airports array reached maximum\n");
		return 0;
	}
	Airport* pai = (Airport *)mallloc(sizeof(Airport));

	if (isAirportExists(pam, pai))
	{
		printf("Airport exists\n");
		return 0;
	}
	
	if (!pai)
	{
		printError();
		return 0;
	}
	if (!initAirport(pai))
	{
		printError();
	}
	
	// increase array size. 
	// if array pointer is null - size is 0, then alllocate array in size 1
	pam->airports = (Airport **)realloc(pam->airports,
		(num + 1) * sizeof(Airport*));

	if (!pam->airports)
	{ 
		printError();
		return 0;
	}

	pam->airports[num] = *pai;
	pam->numOfAirports++;

	freeAirport(pai);
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