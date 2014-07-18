#ifndef Map_H
#define Map_H
#include <stdio.h>
#define isBucketEmpty(x) ((x) == NULL || (x) == (void *)-1) 
#define isBucketMarked(x) (x) == (void *)-1
typedef struct Map Map;

struct Map{
  void **bucket;
  int length;     // total number of buckets
  int size;       // number of buckets used
};

Map *mapNew(int length);

//implementing separate chaining method
void mapStore(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *));

// implementing separate chaining method
void *mapFind(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *));

// implementing separate chaining method
void *mapRemove(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *));

//implementing linear probing method 
void mapLinearStore(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *));

// implementing linear probing method
void *mapLinearFind(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *));

//implementing linear probing method
void *mapLinearRemove(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *));
#endif // Map_H
