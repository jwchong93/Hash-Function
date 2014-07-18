#ifndef Map_H
#define Map_H

typedef struct Map Map;

struct Map
{
	void **bucket;
	int length;
	int size;
	
};

typedef enum CEXCEPTION_T {ERR_SAME_ELEMENT,ERR_OUT_OF_BOUND}CEXCEPTION_T;

Map *mapNew(int length);

void mapStore(Map *map, void *element, int (*compare)(void*,void*),unsigned int (*hash)(void*));
void * mapRemove(Map *map, void *element, int (*compare)(void*,void*),unsigned int (*hash)(void*));
void * mapFind(Map *map, void *element, int (*compare)(void*,void*),unsigned int (*hash)(void*));

//Linear mode functions.
void mapLinearStore(Map *map, void *element, int (*copmpare)(void*,void*),unsigned int (*hash)(void*));
void * mapLinearFind(Map *map, void *element, int (*compare)(void*,void*),unsigned int (*hash)(void*));
void *mapLinearRemove(Map *map, void *element, int (*compare)(void*,void*),unsigned int (*hash)(void*));
#endif // Map_H
