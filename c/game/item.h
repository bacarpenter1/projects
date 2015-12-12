#include <stdio.h>
#include <stdlib.h>

#ifndef ITEM_H
#define ITEM_H

enum itemType
{
	sword,
	no_item	
};


struct Item
{
	char* name;
	enum itemType type;
	char symbol;
};


#define TERMINDEX 0
extern const struct Item ItemList[];
 
#endif //ITEM_H
