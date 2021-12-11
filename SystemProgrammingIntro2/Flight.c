#include <string.h>
#include <stdlib.h>//**
#include "Flight.h"

const char* airplaneTypes[] = { "Passengers", "Container", "Military" };

Flight* initFlight()//***
{
	Flight* fl = malloc(sizeof(Flight));

	if (!fl)
	{
		printError();
		return 0;
	}
	// 1. create all sub-"objects" for creating our flight
	Airport from = *initAirport();//taking the object that inside the address
	Airport to = *initAirport();//taking the object that inside the address
	Airplane airplane = *initAirplane();
	Date date = *initDate();

	//free flight if one throws 0:
	if (&from == NULL || &to == NULL || &airplane == NULL || &date == NULL)//not sure about this
	{
		freeFlight(fl);
	}
}

Airplane* initAirplane()//**
{
	Airplane* ap = malloc(sizeof(Airplane));

	ap->type = NULL;
	//ap->code = NULL;??
	
}

Date* initDate()//**
{
	Date* da = malloc(sizeof(Date));

	da->day = NULL;
	da->month = NULL;
	da->year = NULL;
	
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
void freeFlight(Flight* pf)//changed
{
	free(&pf->from);
	free(&pf->to);
	freeAirplane(&(pf->airplane));
	free(&pf->date);
	free(pf);
}

void freeAirplane(Airplane* a1)
{
	free(a1->code);//not sure is needed
	free(a1);

}

// add more here for flight
