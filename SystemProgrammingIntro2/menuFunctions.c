#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "menuFunctions.h"
//#include "functionsLib.h"


int f_addFlight(AirportManager* pam, Airline* pai)
{

	Flight* pf = initFlight(pam);
	if (pf)
	{
		addFlight(pai, pf);
		printf("\nFlight Details: \n");
		doPrintFlight((pai->flights)[(pai->numOfFlights) - 1]);
		printf("has been added successfully.");
		return 1;
	}
	printError();
	return 0;

}

int f_addAirport(AirportManager* pam)
{

	Airport* pai = initAirport();

	if (pai)
	{
		if (!addAirport(pam, pai))
		{
			printf("Couldn't add Airport\n");
		}
		free(pai);
		return 1;
	}
	printError();
	return 0;
}

int f_printAirline(Airline* pai)
{
	printf("\nAirline details:\n");
	printf("Name:%s\n", pai->name);


	int max = pai->numOfFlights;
	for (int i = 0; i < max; i++)
	{
		Flight* pf = (pai->flights)[i];
		doPrintFlight(pf);
	}

	if (max == 0) { printf("There are no flights now.\n"); }
	else { printf("\nTotal: %d flights.\n", max); }
	return 0;
}

int f_printAirlineManager(AirportManager* pam)
{
	printf("Airport Manager info\n");
	int max = pam->numOfAirports;
	for (int i = 0; i < max; i++)
	{
		Airport* pai = &((pam->airports)[i]);
		doPrintAirport(pai);
		printf("\n");
	}

	if (max == 0) { printf("\nThere are no airports now\n"); }
	else { printf("Total: %d airports.\n", max); }

	return 1;
}

int f_printNumberOfFlightFromLocation(Airline* pai)
{
	int count = 0;

	char* name = inputWithMessage("Please insert source name: ");
	if (!name)
	{
		printError();
		return 0;
	}

	count = doCountFlightsFromName(pai, name);
	if (count)
		printf("Total flights from %s: %d", name, count);
	else
		printf("There are currently no flights from %s", name);
	printf("\n");
	free(name);
	return 1;
}

int f_printFlightsWithAirplaneCode(Airline* pai)//longer than 25 rows
{
	char* code = inputWithMessage("Insert an airplane code: (4 digits)");
	if (!code) {
		printError();
		return 0;
	}
	if (strlen(code) != 4) {//used to be "strlen(code, 5) != 4" changed to "strlen(code) != 4"
		printf("Invalid code");
		return 0;
	}
	int count = 0;
	int max = pai->numOfFlights;
	for (int i = 0; i < max; i++)
	{
		Flight* pf = (pai->flights)[i];
		Airplane* a1 = &(pf->airplane);
		if (isPlaneCodeInFlight(pf, code))
		{
			doPrintFlight(pf);
			count++;
		}
	}

	if (count == 0) { printf("\nThere are no flight with code \"%s\"\n", code); }
	else { printf("Total: %d flights.\n", count); }
	free(code);

	return 1;
}

int f_printFlightsWithAirplaneType(Airline* pai)
{
	AirplaneType type = 0;
	printf("Insert the Airplane type: (1-3)\n1. Passengers\n2. Container\n3. Military\n");
	scanf("%d", &type);
	if (!(type > 0 && type <= L_TYPE)) {
		printError();
		return 0;
	}
	type -= 1;
	int count = 0;
	int max = pai->numOfFlights;
	for (int i = 0; i < max; i++)
	{
		Flight* pf = (pai->flights)[i];
		Airplane* a1 = &(pf->airplane);
		if (isPlaneTypeInFlight(pf, type))
		{
			doPrintFlight(pf);
			count++;
		}
	}

	if (count == 0) { printf("\nThere are no flight with such type"); }
	else { printf("Total: %d flights.\n", count); }

	return 1;
}

int f_calculateSizes(void)
{
	printf("\n=========================\n");
	printf("Sizes: \n");
	printf("Airpalne is %d bytes\n", sizeof(Airplane));
	printf("Flight is %d bytes\n", sizeof(Flight));
	printf("Airline is %d bytes\n", sizeof(Airline));
	printf("AirportManager is %d bytes\n", sizeof(AirportManager));
	printf("Date is %d bytes\n", sizeof(Date));
	printf("Airport is %d bytes\n", sizeof(Airport));
	printf("AirplaneType is %d bytes\n", sizeof(AirplaneType));
	printf("\n=========================\n");

}