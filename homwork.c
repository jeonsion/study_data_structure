#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

typedef struct Name_card {
	char name[20];
	int id;
	struct name_card* link;
}Namecard;

Namecard* head = NULL;

Namecard* getnode(int pos) {
	Namecard* p;

	p = head;
	for (int i = 0; i < pos; i++) {
		if (p == NULL)
			return NULL;

		p = p->link;
	}
	return p;
}

Namecard make_Namecard(char name[], int id) {
	Namecard newcard;

	strcpy(newcard.name, name);
	newcard.id = id;
	newcard.link = NULL;

	return newcard;
}

void init() {			//리스트 내의 모든 노드를 삭제
	Namecard* p, * removed;

	for (p = head; p != NULL;) {
		removed = p;
		p = p->link;
		free(removed);
	}
	head = NULL;
}

int is_empty(void) {
	if (head == NULL) {
		return 1;
	}
	else
		return 0;
}

int size(void) {
	int count = 0;
	Namecard* p;
	p = head;
	for (; p; p = p->link) {
		count++;
	}
	return count;
}

void print_list(char* msg) {
	Namecard* p;
	p = head;
	printf("%s :", msg);
	for (; p; p = p->link) {
		printf("( %s, %d )", p->name, p->id);
	}
	printf("\n");
}

void insert(int pos, Namecard item) {
	Namecard* node;
	Namecard* pre;
	//처음에 삽입하는 경우
	if (pos > size()) {
		printf("삽입위치오류\n");
	}
	else if (pos==0) {
		
		node = (Namecard*)malloc(sizeof(Namecard));
		strcpy(node->name, item.name);
		node->id = item.id;

	
		node->link = head;
		head = node;
	}
	else {
		node = (Namecard*)malloc(sizeof(Namecard));
		strcpy(node->name, item.name);
		node->id = item.id;
		node->link = NULL;
		
		pre = getnode(pos - 1);
		node->link = pre->link;
		pre->link = node;

	}

}

void replace(int pos, Namecard item) {
	Namecard* p;
	Namecard* pre;
	if (pos > size()) {
		printf("교체위치 오류\n");
	}
	else {
		p = getnode(pos);
		strcpy(p->name, item.name);
		p->id = item.id;
	}
		
}

void delete(int pos) {
	Namecard* pre;
	Namecard* del;

	if (pos > size()) {
		printf("삭제위치 오류\n");
	}
	else if(pos ==0) {
		del = head;
		head = del->link;
		free(del);
	}
	else {
		pre = getnode(pos - 1);
		del = pre->link;
		pre->link = del->link;
		free(del);
	}
}

Namecard get_entry(int pos) {
	Namecard* p = getnode(pos);
	Namecard node;


	if (p == NULL) {
		p->id = -1;
	}
	else {
		strcpy(node.name, p->name);
		node.id = p->id;
		node.link = p->link;
		return node;
	}

	
	


}

int find(Namecard item) {
	Namecard* p;
	p = head;
	int count = 0;
	for (; p; p = p->link) {
		if ((strcmp(item.name, p->name) == 0) && (item.id == p->id)){
			return count;
		}
		count += 1;
	}
	return -1;

}

int main() {
	init();
	print_list("Init");

	insert(0, make_Namecard("김대희", 20170031));
	insert(0, make_Namecard("서재연", 20111521));
	insert(1, make_Namecard("김준형", 20211516));
	insert(size(), make_Namecard("서승진", 20211506));
	insert(3, make_Namecard("신서연", 20211501));
	insert(size(), make_Namecard("김지연", 20211530));
	insert(10, make_Namecard("김현수", 20211522));
	print_list("Insert");
	
	printf("현재 size : %d\n", size());
	replace((size() - 1), make_Namecard("정현", 20211504));
	replace(4, make_Namecard("채경훈", 20211498));
	replace(20, make_Namecard("정현", 20211490));
	print_list("Replace");
	
	delete(3);
	delete(size() - 1);
	delete(0);
	delete(30);
	print_list("Delete");

	///*for (int i = 0; i < length; i++) {
	//	printf("(%s, %d)", iot_list[i].name, iot_list[i].id);		//테스트
	//}*/

	//sort_list();
	//print_list("Sort");

	//printf("\n");
	printf("%s is found at %d\n", "김준형", find(make_Namecard("김준형", 20211516)));
	printf("%s is found at %d\n", "김정우", find(make_Namecard("김정우", 20211526)));
	printf("%s is found at %d\n", "채경훈", find(make_Namecard("채경훈", 20211234)));

	Namecard temp = get_entry(1);
	if (temp.id != -1) {
		printf("\nEntry 1: (%s, %d)\n", temp.name, temp.id);
	}
	Namecard asd = get_entry(4);
	printf(" \n%d", asd.id);

}