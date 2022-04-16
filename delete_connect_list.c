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
	printf("\n");

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


void insert(node* pre, char* name, int id) {
	node* new;
	new = (node*)malloc(sizeof(node));
	strcpy(new->name, name);
	new->id = id;
	new->link = NULL;

	if (pre == NULL) {
		new->link = head;
		head = new;
	}
	else {
		new->link = pre->link;
		pre->link = new;

	}

}


void delete(char* name, int id) {
	node* pre;
	node* del;

	//strcmp(pre->link->name, name) == 0 && pre->link->id == id
	if (head == NULL) {
		printf("List is empty!!\n");
		return;
	}
	
	if ((strcmp(head->name, name) == 0 )&& (head->id == id)) {
		del = head;
		head = del->link;
		free(del);
	}
	else {
		pre = head;
		while (pre->link != NULL) {
			if ((strcmp(pre->link->name, name) == 0 && pre->link->id == id)) {
				del = pre->link;
				pre->link = del->link;
				free(del);
				return;
			}
			pre = pre->link;
		}
		printf("No items\n");
	}

}


int main() {
	node* pre = NULL;

	insert(NULL, "ÀüÃ¢¿Ï", 1000);
	print_list();

	insert(NULL, "À±Àç¼®", 2000);
	print_list();

	pre = search_list_by_name("ÀüÃ¢¿Ï");
	insert(pre, "±è´ëÈñ", 3000);
	print_list();

	pre = search_list_by_id(1000);
	insert(pre, "±èµ¿¹Î", 4000);
	print_list();

	insert(NULL, "¼ÛÅÂ¿ø", 5000);
	print_list();


	printf("Delete start\n");
	delete("¼ÛÅÂ¿ø", 5000);
	print_list();

	delete("À±Àç¼®", 2000);
	print_list();

	delete("±èµ¿¹Î", 4000);
	print_list();

	delete("±è´ëÈñ", 3000);
	print_list();

	delete("ÀüÃ¢¾È", 1000);
	print_list();

	delete("ÀüÃ¢¿Ï", 1000);
	print_list();

	delete("±è´ëÈñ", 3000);


	
}

