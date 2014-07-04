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
	List *newList = listNew(element,NULL);
	//newList->data=element;
	location = hash(element);
	map->bucket[location]= newList;
	
}

void mapFind(Map *map, void *element, int (*compare)(void*,void*),unsigned int (*hash)(void*))
{
	
}