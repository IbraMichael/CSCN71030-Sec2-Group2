#pragma once
#define _CRT_SECURE_NO_WARNINGS

#define labName 100
#define labCost 100
#define labTime 50
#define labCategory 50




#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct lab
{
    char name[labName];
    char cost[labCost];
    char time[labTime];
    char category[labCategory];

} LAB;

void saveLabToFile();
void LoadLabs();
void printLabsSorted(const char* sortBy);

