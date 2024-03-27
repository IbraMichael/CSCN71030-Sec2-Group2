#include "EList.h"
#include <stdlib.h>

//takes employee and returns node with allocated memory
ENODE* createENode(EMPLOYEE e) {
	ENODE* e1 = (ENODE*)malloc(sizeof(ENODE));
	e1->e = e;
	e1->next = NULL;
	return e1;
}
//inserts node to existing list
void insertENode(ENODE** head, ENODE* newNode) {
	newNode->next = head;
	head = newNode;
}
//returns node with specified username
ENODE* searchENode(ENODE* head, char* username) {
	ENODE* current = head;
	while (current != NULL) {
		if (current->e.username == username)
			return current;
		current = current->next;
	}
	printf("Couldn't find employee with username %s\n", username);
	return NULL;
}
//deletes node while preserving list functionality
void deleteENode(ENODE* toDelete, ENODE** head) {
	ENODE* current = head;
	if (toDelete == head) {
		head = current->next;
		free(current);
		return;
	}
	ENODE* prev = head;
	while (current != NULL) {
		if (current == toDelete) {
			prev->next = current->next;
			free(current);
		}
		prev = current;
		current = current->next;
	}
}
//saves entire list to file
void saveListToFile(ENODE* head, char* filename) {
	// Save the entire task list to a binary file
	ENODE *current = head;

	FILE* file = fopen(filename, "wb");
	if (file == NULL) {
		printf("Error opening file for writing\n");
		return false;
	}
	// Write each employee to the file
	while (current != NULL) {
		fwrite(&(current->e), sizeof(EMPLOYEE), 1, file);
		current = current->next;
	}

	fclose(file);
}
//returns entire list from file
ENODE* loadListFromFile(char* filename) {
	// Load an employee list from a binary file
	FILE* file;
	if (file = fopen(filename, "rb")) {
		if (file == NULL) {
			printf("Error opening file to read");
			exit(0);
		}

		ENODE* list = NULL;
		ENODE* current = NULL;
		EMPLOYEE temp = { 0 };
		// Read each employee from the file and create a new node for it in the list
		while (fread(&temp, sizeof(EMPLOYEE), 1, file) == 1) {
			ENODE* new = (ENODE*)malloc(sizeof(ENODE));
			if (new == NULL) {
				printf("Memory Allocation Error");
				exit(0);
			}
			new->e = temp;
			new->next = NULL;

			if (list == NULL) {
				list = new;
				current = list;
			}
			else {
				current->next = new;
				current = current->next;
			}
		}

		fclose(file);
		return list;
	}
	else printf("Admin must create file\n");
	return NULL;
}