#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "AirportManager.h"
#include "Airport.h"
#include "Airline.h"
#include "Flight.h"
#include "functionsLib.h"

int f_addFlight(AirportManager* pam, Airline* pai);
int f_addAirport(AirportManager* pam);
int f_printAirline(Airline* pai);
int f_printAirlineManager(AirportManager* pam);
int f_printNumberOfFlightFromLocation(Airline* pai);
int f_printFlightsWithAirplaneCode(Airline* pai);
int f_printFlightsWithAirplaneType(Airline* pai);
int f_calculateSizes(void);

int main(void)
{
	int p = 1;

	AirportManager* pam = initAirportManager();
	if (!pam)
	{
		return 1;
	}

	printf("airportMan was Created! num of airports: %d\n", pam->numOfAirports);

	Airline* pai = initAirline();
		

	printf("Would you like to add an airport? (1 - Yes)\n");
	scanf_s("%d", &p);
	while (p == 1)
	{
		clearBuffer();
		f_addAirport(pam);
		printf("Would you like to add another airport? (1 - Yes, other - No)\n");
		scanf_s("%d", &p);
	}
	
	char menu[L_1024] = "Please pick one:\n";
	char* pmenu = menu;
	strcat(menu, "1. Add flight\n");
	strcat(menu, "2. Add Airport\n");
	strcat(menu, "3. Print Airline\n");
	strcat(menu, "4. Print Airline Manager\n");
	strcat(menu, "5. Print Number Of Flight From Location\n");
	strcat(menu, "6. Print Flights With Airplane Code\n");
	strcat(menu, "7. Print Flights With Airplane Type\n");
	strcat(menu, "8. Exit\n");
	strcat(menu, "============================================\n");
	strcat(menu, "\n");

		
	printf("\nWelcome, ");
	do
	{
		printf(	"%s", menu);

		scanf_s("%d", &p);
		clearBuffer();
		switch (p)
		{
		case 1: f_addFlight(pam, pai); break;
		case 2: f_addAirport(pam);  break;
		case 3: f_printAirline(pai); break;
		case 4: f_printAirlineManager(pam);  break;
		case 5: f_printNumberOfFlightFromLocation(pai); break;
		case 6: f_printFlightsWithAirplaneCode(pai); break;
		case 7: f_printFlightsWithAirplaneType(pai); break;
		case 321: f_calculateSizes(); break;
		case 8: break;
		default: printf("Pick a number between 1-8!\n\n"); break;
		}
		printf("\n");
		// clearBuffer(); // when returning from function - promising the empty buffer
	} while (p != 8);
	printf("Goodbye\n");

	return 0;
}

int f_addFlight(AirportManager* pam, Airline* pai)
{

	char* from = inputWithMessage("Insert the Flight's source: ");
	if (!from) { printError(); return 0; }
	if (!findAirportByName(pam, from))
	{
		free(from);
		printf("Airport not exists");
		return 0;
	}

	char* to = inputWithMessage("Insert the Flight's  destination: ");
	if (!to) { free(from); printError(); return 0; }
	if (!findAirportByName(pam, to))
	{
		free(from); free(to); 
		printf("Airport not exists");
		return 0;
	}

	char* date = inputDate("Insert the Flight's date: (dd$$mm$$yyyy)\n");

	if (!date) { free(from); free(to); printError(); return 0; }

	if (strcmp(date, EMPTY) == 0)
	{
		free(from); free(to);
		printf("Invalid Date.\n");
		return 0;
	}

	char* code = inputWithMessage("Insert the Airplane's code: (4 digits)");
	if (!code) { free(from); free(to); free(date); printError();  return 0; }

	else if (strnlen(code, 5) != 4) {//strlen??
		free(from); free(to); free(date); free(code);
		printf("Error: code must be in length of 4\n"); return 0;
	}
	int isCapital = 1;
	for (int i = 0; i < 4; i++)
	{
		if (code[i]<'A' && code[i]>'Z')
		{
			isCapital = 0;
		}
	}
	if (!isCapital) {
		free(from); free(to); free(date); free(code);
		printf("Error: code may be capital letters only \n"); return 0;
	}

	int type;
	printf("Insert the Airplane type: (1-3)\n1. Passengers\n2. Container\n3. Military\n");
	scanf_s("%d", &type);
	if(!(type > 0 && type <= L_TYPE)) {
		free(from); free(to); free(date); free(code);
		printf("Error: Invalid number");
		return 0;
	}
	type -= 1;
	Airplane* a1 = malloc(sizeof(Airplane));
	if (!a1) { free(from); free(to); free(date); free(code); printError(); return 0; }

	strcpy(a1->code, code);
	a1->type = type;

	Flight* pf = malloc(sizeof(Flight));
	if (!pf) { free(a1); free(from); free(to); free(date); free(code); printError(); return 0; }
	pf->airplane = *a1;
	pf->from = *findAirportByName(pam, from);
	pf->to = *findAirportByName(pam, to);

	Date sdate ;
	sdate.day = atoi(strtok(date, "$$"));
	sdate.month = atoi(strtok(NULL, "$$"));
	sdate.year = atoi(strtok(NULL, "$$"));

	pf->date = sdate;
	addFlight(pai, pf);
	printf("\nFlight Details: \n");
	doPrintFlight((pai->flights)[(pai->numOfFlights)-1]);
	printf("Flight added successfully.");
	// freeFlight(pf);
	// freeAirplane(a1);
	free(date);
	return 1;

}

int f_addAirport(AirportManager* pam)
{
	/*
	char* address = inputAddress(); // mem allocation

	if (!address)
	{
		return 0;
	}

	char* name = inputWithMessage("Insert Airport name please: \n");

	if (!name) {
		printf("Error: cannot assign memory.");
		free(address);
		return 0;
	}

	if (strlen(name) == 0) {
		printf("Error: Name cannot be empty.");
		free(address);
		free(name);
		return 0;
	}

	Airport* pai = malloc(sizeof(Airport));
	// changed _______ START 

	// Airport* pai = initAirport(name, address);

	// changed _______ END 
	if (!pai)
	{
		printf("Error: cannot assign memory.");
		free(address);
		free(name);
		return 0;
	}

	pai->address = address;
	pai->name = name;

	*/
	Airport* pai = initAirport();

	printf("airportname: %s", pai->name);
	if (!addAirport(pam, pai))
	{
		printf("Couldn't add Airport\n");
	}
	freeAirport(pai);
	return 1;
}

int f_printAirline( Airline* pai)
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