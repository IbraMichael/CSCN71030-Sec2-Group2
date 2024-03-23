#include "Labs.h"


#define MAX_LABS 50
LAB lab [MAX_LABS];
int labCount = 0;

// Helper functions
int compareNames(const void* a, const void* b) {
    const LAB* pa = (const LAB*)a;
    const LAB* pb = (const LAB*)b;
    return strcmp(pa->name, pb->name);
}

void saveLabToFile() 
{
    FILE* file = fopen("lab.txt", "w");
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }
    for (int i = 0; i < labCount; ++i) {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
            lab[i].name, lab[i].cost, lab[i].time,
            lab[i].category);
    }
    fclose(file);

}


void LoadLabs() 
{
    FILE* file = fopen("lab.txt", "r");
    if (!file) {
        printf("Error opening file for reading.\n");
        return;
    }
    labCount = 0;
    while (fscanf(file, "%99[^,],%99[^,],%10[^,],%1023[^,],%99[^,],%19[^,],%99[^,],%99[^,],%9[^\n]\n",
        lab[labCount].name, lab[labCount].cost,
        lab[labCount].time, lab[labCount].category) == 9) {
        labCount++;
        if (labCount >= MAX_LABS) {
            printf("Reached max capacity. Some labs may not be loaded.\n");
            break;
        }
    }
    fclose(file);


}

void printLabsSorted(const char* sortBy) {
    // Load labs from file
    LoadLabs();

    // Sort labs by name
    qsort(lab, labCount, sizeof(LAB), compareNames);

    for (int i = 0; i < labCount; ++i) {
        printf("\---------------------------------------------------\n");
        printf("Name: %s %s\n", lab[i].name);
        printf("Cost: %s\n", lab[i].cost);
        printf("Time: %s\n", lab[i].time);
        printf("Category: %s\n", lab[i].category);
        printf("---------------------------------------------------\n");
    }
}