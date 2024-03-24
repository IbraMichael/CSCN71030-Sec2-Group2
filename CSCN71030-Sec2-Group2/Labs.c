#include "Labs.h"



#define MAX_LABS 500
LAB test[MAX_LABS];
int labCount = 0;




// Helper functions
int compareLabNames(const void* a, const void* b) {
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
        fprintf(file, "%s,%s,%s,%s\n",
            test[i].name, test[i].cost, test[i].time,
            test[i].category);
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
    while (fscanf(file, "%99[^,],%99[^,],%99[^,],%99[^\n]\n",
        test[labCount].name, test[labCount].cost,
        test[labCount].time, test[labCount].category) == 4) {
        labCount++;
        if (labCount >= MAX_LABS) {
            printf("Reached max capacity. Some labs may not be loaded.\n");
            break;
        }
    }
    fclose(file);


}

void addLabs(const LAB lab) {
    if (labCount >= MAX_LABS) {
        printf("Cannot add more labs. Storage full.\n");
        return;
    }
    test[labCount++] = lab;
    saveLabToFile();
}

void printLabsSorted(const char* sortBy) {
    // Load labs from file
    LoadLabs();

    // Sort labs by name
    qsort(labs, labCount, sizeof(LAB), compareLabNames);

    for (int i = 0; i < labCount; ++i) {
        printf("\---------------------------------------------------\n");
        printf("Name: %s\n", test[i].name);
        printf("Cost: $%s\n", test[i].cost);
        printf("Time: %s\n", test[i].time);
        printf("Category: %s\n", test[i].category);
        printf("---------------------------------------------------\n");
    }
}