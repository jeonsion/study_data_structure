#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct node {
	char name[20];
	int id;
	struct node* link;
} node;

node* head = NULL;


void print_list() {
	node* p;
	p = head;
	for (; p; p = p->link) {
		printf("(%s, %d) ", p->name, p->id);
	}

}

node* search_list_by_name(char* name) {
	node* p;
	p = head;
	for (; p; p = p->link) {
		if (strcmp(p->name, name) == 0) {
			return p;
		}
	}
	return NULL;
}

node* search_list_by_id(int id) {
	node* p;
	p = head;

	for (; p; p = p->link) {
		if (p->id == id) {
			return p;
		}
	}
	return NULL;
}

int main() {
	node* new;
	
		new = (node*)malloc(sizeof(node));
		strcpy(new->name, "ÀüÃ¢¿Ï");
		new->id = 1000;
		new->link = NULL;
	
		head = new;
	
		new = (node*)malloc(sizeof(node));
		strcpy(new->name, "À±Àç¼®");
		new->id = 2000;
		new->link = NULL;
	
		head->link = new;
	
	
		new = (node*)malloc(sizeof(node));
		strcpy(new->name, "±è´ëÈñ");
		new->id = 3000;
		new->link = NULL;
	
		head->link->link = new;
		print_list();
		printf("\n");

		new = search_list_by_name("À±Àç¼®");
		if (new != NULL)	
			printf("name : %s  id : %d\n", new->name, new->id);

		new = search_list_by_id(1000);
		if (new != NULL)
			printf("name : %s  id : %d\n", new->name, new->id);

		new = search_list_by_name("²¿ºÏ");
		if (new != NULL) 
			printf("name : %s  id : %d\n", new->name, new->id);

		new = search_list_by_id(3000);
		if (new != NULL)
			printf("name : %s  id : %d\n", new->name, new->id);




}

