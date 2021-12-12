#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Flight.h"
#include "AirportManager.h"

const char* airplaneTypes[] = { "Passengers", "Container", "Military" };

Flight* initFlight(AirportManager* pam)
{	
	if (pam->numOfAirports < 2)
	{
		printf("Cannot add flight when have less than 2 airports!\n");
		return NULL;
	}

	Flight* pf = (Flight*)malloc(sizeof(Flight));
	if (pf)
	{
		printf("Insert the Flight's source: ");
		Airport* pFrom = findAirportFromInput(pam);
		if (!pFrom){
			printf("Airport not exists"); return NULL;
		}
		pf->from = *pFrom;

		printf("Insert the Flight's destination: ");
		Airport* pTo = findAirportFromInput(pam);
		if (!pTo){
			free(pf);printf("Airport not exists"); return NULL;
		}
		if (isFlightFromSourceName(pf, pTo->name))
		{
			free(pf); printf("Error: Cannot have same origin and destination airport");return NULL;
		}
		
		pf->to = *pTo;

		Airplane* ap = initAirplane(pam);
		if (!ap){
			free(pf);return NULL;
		}
		pf->airplane = *ap;


		Date* date = initDate();
		if (!date) {
			free(pf); free(ap); free(pTo);return NULL;
		}
		pf->date = *date;

		free(ap);
		free(date);
		return pf;
	}
	printError();
	return NULL;
}

Airplane* initAirplane()
{
	Airplane* ap = (Airplane *)malloc(sizeof(Airplane));

	if (ap) {

		char* code = inputAirplaneCode();
		if (!code) { free(ap); return NULL; }
	
		AirplaneType type = inputAirplaneType();
		if (type == -1) { free(ap); free(code);  return NULL; }

		strcpy(ap->code, code);
		ap->type = type;

		return ap;
	}
	printError();
	return NULL;
}

int inputAirplaneType()
{
	
	int type = -1;
	printf("Insert the Airplane type: (1-3)\n1. Passengers\n2. Container\n3. Military\n");
	scanf_s("%d", &type);
	if (!(type > 0 && type <= L_TYPE)) {
		printf("Error: Invalid number"); -1;
	}
	type -= 1;
	clearBuffer();
	return type;
}

char* inputAirplaneCode()
{
	char* code = inputWithMessage("Insert the Airplane's code: (4 capital letters)");
	if (!code)
	{
		printError(); return NULL;
	}
	else if (strnlen(code, 5) != 4) {
		free(code); 
		printf("Error: code must be in length of 4\n"); return NULL;

	}

	int isCapital = 1;
	for (int i = 0; i < 4; i++)
	{
		if (code[i]<'A' || code[i]>'Z')
		{
			isCapital = 0;
		}
	}
	if (!isCapital) {
		free(code); 
		printf("Error: code may be capital letters only \n");
		return NULL;
	}
	return code;
}

Date* initDate()
{ // date is in format dd$$mm$$yyyy

	char* date = inputDate("Insert the Flight's date: (dd$$mm$$yyyy)\n");
	if (!date)
	{
		printError(); return NULL;
	}
	if (strcmp(date, EMPTY) == 0)
	{
		printf("Invalid Date\n");  return NULL;
	}

	Date* sdate = (Date *)malloc(sizeof(Date));
	if (!sdate)
	{
		printError(); free(date); return NULL;
	}
	sdate->day = atoi(strtok(date, "$$"));
	sdate->month = atoi(strtok(NULL, "$$"));
	sdate->year = atoi(strtok(NULL, "$$"));
	return sdate;
}

int isFlightFromSourceName(const Flight *pf, const char from[])
{
	return strcmp(pf->from.name, from) == 0;
}
int isFlightFromDestName(const Flight *pf, const char to[])
{
	return strcmp(pf->to.name, to) == 0;
}
int isPlaneCodeInFlight(const Flight *pf, const char code[])
{
	return strcmp(pf->airplane.code, code) == 0;
}
int isPlaneTypeInFlight(const Flight *pf, const AirplaneType type)
{
	return pf->airplane.type == type;
}
void freeFlight(Flight* pf)
{
	free(pf);
}

void freeAirplane(Airplane* a1)
{
	free(a1);

}
void freeDate(Date* pd)
{
	free(pd);
}

// add more here for flight
