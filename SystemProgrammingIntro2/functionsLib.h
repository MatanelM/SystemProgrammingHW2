#ifndef __FUNCTIONS_LIB__
#define __FUNCTIONS_LIB__

#define L_TYPE 3
#define L_CODE 4
#define L_AIRPORTS_INIT 1
#define L_MONTHS 12
#define L_255 255
#define L_1024 1024

#define MAX_AIRPORTS 128
#define MAX_FLIGHTS 128
#define YEAR 2021

#define EMPTY " "
#define AIRLINE_NAME "SPARSE AIRLINE"
#define AIRPORT_NAME "NULL AIRLINE"//**?
#define AIRPORT_ADDRESS "NULL ADDRESS"//**?

void printError();

void clearBuffer();

char* inputDate();

char* inputAddress();

typedef enum { JAN = 0, FEB=1, MAR=2, APR=3, MAY=4,
JUN=5, JUL=6, AUG=7, SEP=8, OCT=9, NOV=10, DEC=11, initSize=12} Month;

int isStringDateValid(char* *pd);

int isYearFromCurrent(int year);

int isMonthInCalendar(int month);

int isDayInMonth(int day, Month month);

int isupper(char c);

int islower(char c);

int toupper(char c);

int tolower(char c);

void trim(char* *theWord);

void strip(char* *theWord);

void capitalize(char* *theWord);

void replaceSpaceWithChar(char* *theWord, const char c);

void replaceSpaceWithHashtag(char* *theWord);

void replaceSpaceWithAtSign(char* *theWord);

void capitalizeWordAlternatively(char* *theWord);

char* inputWithMessage(char* msg);

char* input();

#endif