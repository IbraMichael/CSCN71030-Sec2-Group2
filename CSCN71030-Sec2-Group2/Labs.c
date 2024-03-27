// Implemetation of patient lab test results. Thhis file will add, load and save patient results to patient file and history
//it will be stored with a unique Id from the medical provider

#include "Labs.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define variables for patient lab test implementation
#define MAX_LABS 500
LAB test[MAX_LABS];
int labCount = 0;


// Helper functions to compare patient lab test results
int compareLabNames(const void* a, const void* b) 
{
    const LAB* pa = (const LAB*)a;
    const LAB* pb = (const LAB*)b;
    return strcmp(pa->name, pb->name);
}

// Save patient lab test results to file
void saveLabToFile() 
{
    FILE* file = fopen("lab.txt", "w");
    if (!file) 
    {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < labCount; ++i) 
    {
        fprintf(file, "%s,%s,%s,%s\n",
            test[i].name, test[i].cost, test[i].time,
            test[i].category);
    }
    fclose(file);

}

// Load patient lab test from or to file
void LoadLabs() 
{
    FILE* file = fopen("lab.txt", "r");
    if (!file) 
    {
        printf("Error opening file for reading.\n");
        return;
    }
    labCount = 0;
    while (fscanf(file, "%99[^,],%99[^,],%99[^,],%99[^\n]\n",
        test[labCount].name, test[labCount].cost,
        test[labCount].time, test[labCount].category) == 4) 
    {
        labCount++;
        if (labCount >= MAX_LABS) {
            printf("Reached max capacity. Some labs may not be loaded.\n");
            break;
        }
    }
    fclose(file);


}

// Add patient lab test to patient file or history
void addLabs(const LAB lab) 
{
    if (labCount >= MAX_LABS) 
    {
        printf("Cannot add more labs. Storage full.\n");
        return;
    }
    test[labCount++] = lab;
    saveLabToFile();
}

// Display patient lab test using printf
void printLabsSorted(const char* sortBy) 
{
    // Load labs from file
    LoadLabs();

    // Sort labs by name
    qsort(labs, labCount, sizeof(LAB), compareLabNames);

    for (int i = 0; i < labCount; ++i) 
    {
        printf("\---------------------------------------------------\n");
        printf("Name: %s\n", test[i].name);
        printf("Cost: $%s\n", test[i].cost);
        printf("Time: %s\n", test[i].time);
        printf("Category: %s\n", test[i].category);
        printf("---------------------------------------------------\n");
    }
}