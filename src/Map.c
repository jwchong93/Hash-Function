#include "Map.h"
#include <stdio.h>
#include <malloc.h>
#include "List.h"
Map *mapNew(int length)
{
	Map *map = malloc(sizeof(Map));
	map->bucket= calloc(sizeof(void*),length);
	map->length= length;
	map->size=0;
	return map;
}

void mapStore(Map *map, void *element, int (*compare)(void*,void*),unsigned int (*hash)(void*))
{
	int location;
	List *newList;
	location = hash(element);
	if(map->bucket[location]!=NULL)
	{
		if(compare(((List*)map->bucket[location])->data,element)==1)
		{
			Throw(ERR_SAME_ELEMENT);
		}
		else
		{
			newList = listNew(element,map->bucket[location]);
		}
	}
	else
	{
		newList = listNew(element,NULL);
	}
	map->bucket[location]= newList;
	map->size++;
	
}

void *mapRemove(Map *map, void *element, int (*compare)(void*,void*),unsigned int (*hash)(void*))
{
	int location;
	location = hash(element);
	void *elem=NULL;
	List *tempList=(List*)map->bucket[location];
	List *previousList=NULL;
	while(tempList!=NULL)
	{
		
		if(compare(tempList->data,element)==1)
		{
			elem = tempList->data;
			if(previousList==NULL)
			{
				map->bucket[location]=((List*)map->bucket[location])->next;
			}
			else
			{
				previousList->next=tempList->next;
			}
			break;
		}
		previousList=tempList;
		tempList=tempList->next;

	}
	return elem;
}

void *mapFind(Map *map, void *element, int (*compare)(void*,void*),unsigned int (*hash)(void*))
{
	int location;
	location = hash(element);
	void *elem=NULL;
	List *tempList=(List*)map->bucket[location];
	while(tempList!=NULL)
	{
		
		if(compare(tempList->data,element)==1)
		{
			elem = tempList->data;
			break;
		}
		tempList=tempList->next;

	}
	// else
	// {
		// elem=NULL;
	// }
	return elem;
}

void mapLinearStore(Map *map, void *element, int (*copmpare)(void*,void*),unsigned int (*hash)(void*))
{
	int location;
	List *newList;
	location = hash(element);
	if(map->bucket[location]!=NULL)
	{
		while(map->bucket[location]!=NULL)
		{
			location++;
		}
		if(location>=map->length)
		{
			Throw(ERR_OUT_OF_BOUND);
		}
		
	}
	map->bucket[location]=element;
	map->size++;
}

























