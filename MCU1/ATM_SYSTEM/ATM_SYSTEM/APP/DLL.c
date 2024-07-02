/*
 * DLL.c
 *
 * Created: 7/1/2024 10:45:42 AM
 *  Author: Jana Wael
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DLL.h"
#include "../Lib/STD_TYPES.h"

typedef struct user{
	u8 user_name[50];
	u8 user_password[50];
	struct node*next;
	struct node*prev;
};

typedef struct List{
	struct user*head;
	u32 size;
};
struct List L1;

void main_menu(){
	printf("%c\n1-Add Book\n2-Delete Book\n3-View Books\n4-Search for Author Works\n5-Exit",7);

}


void createlist(struct List* pBook){
	pBook->head = NULL;
	pBook->size = 0;
}

u32 list_size(struct List* pList){
	return pList->size;
}

void DLL_voidAddUser(struct List* pList, u8 name[], u8 author[], f32 price, u32 id ,u32 pos){
	struct book*temp = (struct book*)malloc(sizeof(struct book));
	if (temp == NULL){
		printf("No space available");
	}
	strcpy(temp->book_name,strlwr(name)); //Node initialization
	strcpy(temp->book_author,strlwr(author));
	temp->book_id = id;
	temp->book_price = price;

	temp->next = NULL;
	if(pos == 0){ //INSERT AT THE BEGINNING
		temp->next = pList->head;
		pList->head = temp;
		temp->prev = pList->head;
	}
	else if(pos == pList->size){
		struct book* temp1 = pList->head;

		while(temp1->next != NULL){
			temp1 = temp1->next;
		}
		temp1->next = temp;
		temp->prev = temp1;
		temp->next = NULL;

	}
	else if(pos>0 && pos<pList->size){
		struct book* temp1 = pList->head;

		for(int i = 0;i<pos-1; i++){
			temp1 = temp1 -> next;
		}
		temp->next = temp1->next;
		temp1->next = temp;
		temp->prev = temp1;
		temp1 = temp->next;
		temp1->prev = temp;

	}
	pList->size ++;
	printf("\nNo. of current books available in the library : %d",pList->size);
}

void delete_book_by_name(struct List*pList, u8 name[]){
	u32 pos=0;
	struct user* temp1 = pList->head;
	u32 x = strcmp(temp1->user_name,strlwr(name));
	while(x!=0){
		temp1 = temp1->next;
		pos++;
		if(temp1== NULL){
			printf("\nBook doesn't exist in library");
			break;
		}
		x = strcmp(temp1->user_name,name);
	}
	if(pList->head == NULL){
		printf("\nLibrary is empty!");
	}
	else if(pos == 0){
		temp1 = pList->head;
		pList->head = temp1->next;
		free(temp1);
		pList->size --;
	}
	else if(pos>0 && pos<((pList->size)-1)){
		struct book* temp2 = temp1->prev;
		temp1 = temp1->next;
		temp1->prev = temp2;
		temp1 = temp2->next;
		temp2->next = temp1->next;
		free(temp1);
		pList->size --;
	}
	else if(pos == (pList->size -1)){
		struct book* temp2 = temp1->prev;
		temp2->next = NULL;
		free(temp1);
		pList->size --;
	}

	printf("\nNo. of books available in the library : %d",pList->size);
}


void delete_book_by_id(struct List* pList,u32 id){
	u32 pos=0;
	struct book* temp1 = pList->head;
	while(temp1->book_id != id ){
		temp1 = temp1->next;
		pos++;
		if(temp1== NULL){
			printf("\nBook doesn't exist in library");
			break;
		}
	}
	if(pList->head == NULL){
		printf("\nLibrary is empty!");
	}
	else if(pos == 0){
		temp1 = pList->head;
		pList->head = temp1->next;
		free(temp1);
	}
	else if(pos>0 && pos<((pList->size)-1)){
		struct book* temp2 = temp1->prev;
		temp1 = temp1->next;
		temp1->prev = temp2;
		temp1 = temp2->next;
		temp2->next = temp1->next;
		free(temp1);
	}
	else if(pos == (pList->size -1)){
		struct book* temp2 = temp1->prev;
		temp2->next = NULL;
		free(temp1);
	}
	pList->size --;
	printf("\nNo. of books available in the library : %d",pList->size);
}

u32 check_name(struct List* pList,u8 name[]){
	struct book* temp = pList->head;
	u32 counter=0;
	while(temp!=NULL){
		u32 x = strcmp(temp->book_name,strlwr(name));
		if(x==0){
			counter=1;
			return 1;
			break;
		}
		temp=temp->next;
	}
	return 0;
}
