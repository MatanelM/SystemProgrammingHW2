#define _CRT_SECURE_NO_WARNINGS//**
#include <stdio.h>//**
#include <stdlib.h>//**
#include <string.h>
#include "functionsLib.h"
#include "Airline.h"

Airline* initAirline()
{
	Airline* pai = (Airline *)malloc(sizeof(Airline));//should be casting before malloc?
	if (!pai)
	{
		printError(); return 0;
	}
	char* name = NULL;
	do
	{
		if (name)
		{
			free(pai);
		}
		name = inputWithMessage("Insert Ailine name please: \n");

		if (!name) {
			printError(); return NULL;
		}
		trim(&name);
		printf("%s\n", name);
		if (strlen(name) == 0) {
			printf("Error: name cannot be empty.\n");
		}
	} while (strlen(name) == 0);

	pai->numOfFlights = 0;
	pai->name = name;
	pai->flights = NULL;
	return pai;
}

int addFlight(Airline *pai, Flight *pf)
{
	int num = pai->numOfFlights;
	if (num == MAX_FLIGHTS) 
	{
		printf("You have reached maximum flights!\n");
		return 0;
	}

	if (!pf)
	{
		printError(); return 0;
	}

	// at first time if null then it is 0
	pai->flights = (Flight **)realloc(pai->flights,
		(num + 1) * sizeof(Flight*));

	if (!pai->flights)
	{
		printError();
		return 0;
	}
	pai->flights[num] = pf;
	pai->numOfFlights++;
	return 1;

}
void doPrintFlightsWithPlaneCode(const Airline *pai, const char code[L_CODE])
{
	int flag = 0;
	for (int i = 0; i < pai->numOfFlights; i++)
	{
		Flight* pf = pai->flights[i];
		Airplane a1 = (pai->flights[i])->airplane;

		if (strcmp(a1.code, code) == 0)
		{
			doPrintFlight(pf);
			if (!flag) flag = 1;
		}
	}
	if (!flag)
	{
		printf("There are currently no flight planned with the given code.\n");
	}
}


void doPrintFlightsWithPlaneType(const Airline *pai, const AirplaneType type)
{

	if (pai->numOfFlights == 0)
	{
		printf("there are no flights yet!\n");
	}
	
	int i;
	//missing stuff here

	for (i = 0; i < pai->numOfFlights; i++)
	{
		Flight* pf = (pai->flights)[i];
		Airplane* ap = &(pf->airplane);
		if (ap->type == type)
		{
			doPrintFlight(pf);
		}
	}

}


int doCountFlightsFromName(const Airline *pai, const char name[L_255])
{
	int count = 0;
	int max = pai->numOfFlights;
	for (int i = 0; i < max; i++)
	{
		Flight* pf = (pai->flights)[i];
		count += isFlightFromSourceName(pf, name);
	}
	return count;
}

void doPrintFlight(const Flight *pf)
{
	printf("Flight with a ");
	switch ((pf->airplane).type)
	{
	case PASSENGERS:printf("passengers"); break;
	case CONTAINER: printf("container"); break;
	case MILITARY: printf("military"); break;
	default: break;
	}
	printf(" airplane, ID:%s\n", (pf->airplane).code);
	printf("From: %s\n", (pf->from).name);
	printf("To: %s\n", (pf->to).name);
	printf("On date: %d/%d/%d\n", (pf->date).day, (pf->date).month, (pf->date).year);
}
void doPrintAirline(const Airline *pai)
{
	int max = pai->numOfFlights;
	printf("Airport Name: %s\n", pai->name);
	
	for (int i = 0; i < max; i++)
	{
		printf("%d - ", i);
		Flight* pf = (pai->flights)[i];
		doPrintFlight(pf);
	}
	printf("\nTotal num of flights: %d", pai->numOfFlights);
	printf("\n---------------------------------\n");
}

void freeAirline(Airline* pai)
{
	free(pai);
}