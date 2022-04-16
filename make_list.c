//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#pragma warning(disable : 4996)
//
//typedef struct node {
//	char name[20];
//	int id;
//	struct node* link;
//} node;
//
//node* head = NULL;
//
//int main() {
//	node* new;
//
//	new = (node*)malloc(sizeof(node));
//	strcpy(new->name, "ÀüÃ¢¿Ï");
//	new->id= 1000;
//	new->link = NULL;
//
//	head = new;
//
//	new = (node*)malloc(sizeof(node));
//	strcpy(new->name, "À±Àç¼®");
//	new->id= 2000;
//	new->link = NULL;
//
//	head->link = new;
//
//
//	new = (node*)malloc(sizeof(node));
//	strcpy(new->name, "±è´ëÈñ");
//	new->id = 3000;
//	new->link = NULL;
//
//	head->link->link = new;
//
//
//	printf("ÀÌ¸§ : %s, id : %d\n", head->name, head->id);
//	printf("ÀÌ¸§ : %s, id : %d\n", head->link->name, head->link->id);
//	printf("ÀÌ¸§ : %s, id : %d\n", head->link->link->name, head->link->link->id);
//
//}
//
//
