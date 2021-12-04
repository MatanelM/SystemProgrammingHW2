#ifndef __AIRPLANE_MANAGER__
#define __AIRPLANE_MANAGER__

#include "functionsLib.h"
#include "Airport.h"

typedef struct
{
	Airport* airports;
	int numOfAirports;
	int sizeOfAirports;
}AirportManager;

int isAirportExists(const AirportManager *pam, const Airport *pai);
int addAirport(AirportManager* *pam, const Airport *pai);
Airport* findAirportByName(const AirportManager *pam, const char name[]);
void freeAirportManager(AirportManager* pam);
// add more as required

#endif