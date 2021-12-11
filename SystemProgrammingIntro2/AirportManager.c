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
	return pam;
}

int addAirport(AirportManager* pam, Airport* pai)
{
	if (!pai || !pam)
	{
		printError();
		return 0;
	}

	if (pam->numOfAirports == MAX_AIRPORTS)
	{
		printf("Error: Airports array reached maximum\n");
		return 0;
	}

	if (isAirportExists(pam, pai))
	{
		printf("Airport already exists\n");
		return 0;
	}
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

Airport* findAirportFromInput(const AirportManager *pam, const char* message)
{
	char* name = inputWithMessage(message);
	if (!name)
	{
		printError(); return NULL;
	}
	Airport* ap = findAirportByName(pam, name);
	free(name);
	return ap;
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