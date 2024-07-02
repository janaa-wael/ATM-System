/*
 * DLL.h
 *
 * Created: 7/1/2024 10:45:20 AM
 *  Author: Jana Wael
 */ 


#ifndef DLL_H_
#define DLL_H_
#include "../Lib/STD_TYPES.h"

extern typedef struct user;

extern typedef struct List;
extern struct List L1;

void main_menu();
void createlist(struct List* pBook);
u32 list_size(struct List* pList);
void DLL_voidAddUser(struct List* pList, u8 name[], u8 author[], f32 price, u32 id ,u32 pos);



#endif /* DLL_H_ */