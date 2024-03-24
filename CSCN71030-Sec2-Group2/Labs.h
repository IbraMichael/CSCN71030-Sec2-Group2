#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define labName 100
#define labCost 100
#define labTime 50
#define labCategory 50



typedef struct lab
{
    char name[labName];
    char cost[labCost];
    char time[labTime];
    char category[labCategory];

} LAB;

void saveLabToFile();
void addLabs(const LAB lab);
void LoadLabs();
void printLabsSorted(const char* sortBy);

