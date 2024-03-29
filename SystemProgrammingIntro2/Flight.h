#ifndef __FLIGHT__
#define __FLIGHT__

#include "AirportManager.h"
#include "Airport.h"
#include "functionsLib.h"

typedef enum { PASSENGERS = 0, CONTAINER = 1, MILITARY = 2 } AirplaneType;

typedef struct
{
	unsigned char type;//should be enum????
	char code[L_CODE+1];//capitals only
}Airplane;

typedef struct
{
	unsigned char day;
	unsigned char month;
	unsigned short int year;
}Date;

typedef struct
{
	Airport from;
	Airport to;
	Airplane airplane;
	Date date;
}Flight;

Flight* initFlight(AirportManager* pam);
Airplane* initAirplane();
Date* initDate();
int isFlightFromSourceName(const Flight *pf, const char from[]);
int isFlightFromDestName(const Flight *pf, const char to[]);
int isPlaneCodeInFlight(const Flight *pf, const char code[]);
int isPlaneTypeInFlight(const  Flight *pf, const  AirplaneType type);
void doPrintFlight(const Flight *pf);
void freeFlight (Flight* pf);
void freeAirplane(Airplane* a1);
void freeDate(Date* pd);
int inputAirplaneType();
char* inputAirplaneCode();

// add more here for flight

#endif