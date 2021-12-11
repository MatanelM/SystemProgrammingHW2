#define _CRT_SECURE_NO_WARNINGS//**

#include <stdio.h>//*
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

int addAirport(AirportManager* pam, Airport* pai)
{
	// assert incoming "objects" aren't null 
	if (!pai || !pam)
	{
		printError();
		return 0;
	}

	// test if reached max size of airports
	if (pam->numOfAirports == MAX_AIRPORTS)
	{
		// TODO: ALLOCATE MORE MEMORY for more airports (realloctate) 
		printf("Error: Airports array reached maximum\n");
		return 0;
	}

	// Airport* pai = (Airport *)malloc(sizeof(Airport));

	// check if the airport exists 
	if (isAirportExists(pam, pai))
	{
		printf("Airport already exists\n");
		return 0;
	}
	
	// increase array size. 
	// if array pointer is null - size is 0, then allocate array in size 1
	pam->airports = (Airport *)realloc(pam->airports,
		(pam->numOfAirports + 1) * sizeof(Airport));//changed from 2 ** to 1

	if (!pam->airports)
	{ 
		printError();
		return 0;
	}

	pam->airports[pam->numOfAirports] = *pai;
	pam->numOfAirports++;

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

int isAirportExists(const AirportManager *pam, const Airport *pai)//added const**
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