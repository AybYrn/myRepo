#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define SIZE 10

typedef struct {
	int id;
	char name[25];
	double price;
}vegAndFruit_t;

#include"linkedList_int.h"

void displayList(node_t* Hp[]);
int menu();
node_t* searchNode(node_t* Hp[], int id);
void addToHash(node_t* Hp[]); 
void createList(FILE* inp, node_t* Hp[]);
void updateList(node_t* Hp[]);             
void writeList(node_t* Hp[], FILE* out);
void initArray(node_t* Hp[]);
int hashCode(int item);
void addANode(node_t* Hp[], vegAndFruit_t t);
void searchAndDelete(node_t* Hp[], int id);

int main() {
	
	FILE* inp;
	char file[SIZE];
	
	do {
		printf("Enter the text file name:");
		scanf("%s", file);
		
		inp = fopen("vegAndFruit.txt", "r");

	} while (inp == NULL);
	
	printf("the file %s was opened successfully!\n", file);

	int ch;
	node_t* Hp[SIZE], t;

	initArray(Hp);
	createList(inp, Hp);
	
	printf("\nID\tName\tPrice\n-------------------------\n");
	displayList(Hp);
	ch = menu();

	while (ch != 3) {
		switch (ch) {
		case 1: addToHash(Hp); break;
		case 2: updateList(Hp); break;
		}
		printf("\nID\tName\tPrice\n-------------------------\n");
		displayList(Hp);
		ch = menu();
	}
	FILE* out = fopen("vegandfruit.bin", "wb");
	writeList(Hp, out);
	
	return 0;
}
void writeList(node_t* Hp[], FILE* out) {
	
	vegAndFruit_t t;
	int i;

	for (i = 0;i < SIZE;i++) {
		node_t* t = Hp[i];
		while (t != NULL)
		{
			fwrite(&t, sizeof(vegAndFruit_t), 1, out);
			t = t->next;
		}
	}
	fclose(out);
	printf("Writing linkedlist to binary file ""vegandfruit.bin""\nGoodbye.");
}
void updateList(node_t* Hp[]) {
	vegAndFruit_t t;
	int ch;

	printf("Enter vegetable Id :");
	scanf("%d", &t.id);

	node_t* p = searchNode(Hp, t.id);

	if (p != NULL) {

		printf("%-8d %-13s %.2f\n", p->data.id, p->data.name, p->data.price);

		printf("Update (1. ID, 2. Name, and 3. Price):");
		scanf("%d", &ch);

		switch (ch) {
		case 1:
			t = p->data;

			searchAndDelete(Hp, t.id);

			printf("Enter the new Id:");
			scanf("%d", &t.id);

			addANode(Hp, t);
			break;
		case 2:
			printf("Enter the new name:");
			scanf("%s", t.name);
			strcpy(p->data.name, t.name);
			break;
		case 3:
			printf("Enter the new price:");
			scanf("%lf", &t.price);
			p->data.price = t.price;
			break;
		}
	}
}
void addANode(node_t *Hp[], vegAndFruit_t t) {
		int index = hashCode(t.id);

	if (Hp[index] == NULL)
		Hp[index] = addBegining(Hp[index], t);
	else
	{
		node_t* tmp = Hp[index];
		while (tmp->next != NULL)
			tmp = tmp->next;
		addAfter(tmp, t);
	}

}
void searchAndDelete(node_t* Hp[], int id) {

	LType deleted = { 0,"",0.0 };
	int index = hashCode(id);

	if (Hp[index]->data.id == id) {
		Hp[index] = deleteFirst(Hp[index], deleted);
	}
	else
	{
		int found = 0;
		node_t* p = Hp[index];
		while (p->next != NULL && !found) {
			if (p->next->data.id == id) {
				deleteAfter(p, deleted);
				found = 1;
			}
			else
				p = p->next;
		}
	}
}
void addToHash(node_t* Hp[]) {
	
	vegAndFruit_t t;
	node_t *p;

	do {
		printf("Enter vegetable Id :");
		scanf("%d", &t.id);

		p = searchNode(Hp, t.id);
	} while (p != NULL);

	printf("Enter vegetable name:");
	scanf("%s", t.name);
	printf("Enter vegetable price:");
	scanf("%lf", &t.price);

	addANode(Hp, t);
}
node_t* searchNode(node_t* Hp[], int id) {
	
	int index = hashCode(id);
	
	if (Hp[index] == NULL) {
		return NULL;
	}
	else
	{
		node_t* p = Hp[index];
		while (p != NULL) {
			if (p->data.id == id) {
				printf("The ID: %d already exists\n", id);
				return p;
			}
			p = p->next;
		}
		return p;
	}
}
void displayList(node_t* Hp[]) {
	int i;
	printf("\n");
	for (i = 0; i < SIZE; i++)
	{
		node_t* t = Hp[i];

		printf("[%2d]: ", i);

		if (Hp[i] == NULL)
			printf("Empty\n");
		else
		{
			while (t != NULL)
			{
				printf("%-5d %-13s %.2f -> ", t->data.id, t->data.name, t->data.price);
				t = t->next;
			}
		}
		printf(" NULL\n");
	}
}
void createList(FILE* inp, node_t* Hp[]) {

	LType t;
	int index;

	while (fscanf(inp, " %d", &t.id) != EOF) {

		index = hashCode(t.id);

		fscanf(inp, " %s %lf", t.name, &t.price);

		if (Hp[index] == NULL)
			Hp[index] = addBegining(Hp[index], t);
		else
		{
			node_t* p = Hp[index];
			while (p->next != NULL)
				p = p->next;
			addAfter(p, t);
		}
	}
}
void initArray(node_t* Hp[])
{
	int i;
	for (i = 0; i < SIZE; i++)
		Hp[i] = NULL;
}
int hashCode(int item)
{
	return(item % SIZE);
}
int menu() {
	int n;
	printf("    MENU\n****************\n");
	printf("1. Add record\n2. Update record\n3. Exit\n");
	do {
		printf("Enter your choice:");
		scanf("%d", &n);

	} while (n < 0 || n>3);
	return n;
	return n;
}