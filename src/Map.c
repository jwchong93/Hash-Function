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
	
}

void mapFind(Map *map, void *element, int (*compare)(void*,void*),unsigned int (*hash)(void*))
{
	
}