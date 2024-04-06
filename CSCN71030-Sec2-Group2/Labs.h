#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Define patient structures include arrays or strings
#define labName 100
#define labCost 100
#define labTime 50
#define labCategory 50


// Define lab with typedef structure
typedef struct lab
{
    char name[labName];
    char cost[labCost];
    char time[labTime];
    char category[labCategory];

} LAB;

// Functions for patient lab test
char* saveLabToFile();
char* addLabs(const LAB lab);
char* LoadLabs();
char* printLabsSorted(const char* sortBy);

