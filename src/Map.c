#include <stdio.h>
#include <malloc.h>
#include "Map.h"
#include "List.h"
#include "Person.h"
#include "CException.h"
#include "ErrorCode.h"

Map *mapNew(int length){
  Map *map = malloc(sizeof(Map));
  map->bucket = calloc(sizeof(void *), length);
  map->length = length;
  map->size = 0;
  return map;
}

void mapStore(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *)){
  List *list;
  int index;
  
  list = listNew(element, NULL);
  
  index = hash(element);
  
  if(map->bucket[index] != NULL){
    if(comparePerson(((List *)map->bucket[index])->data, element) == 1){
      Throw(ERR_SAME_ELEMENT);
    }
  }
    
  map->bucket[index] = list;
}

void *mapFind(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *)){
  Person *person;
  List *list;
  
  int index;
  
  index = hash(element);
  list = (List *)map->bucket[index];
  
  if(comparePerson(list->data, element) == 1){
    person = (Person *)element;
    return person;
  }
  
  else if(comparePerson(list->data, element) == 0){
    list = list->next;
      
    if(list == NULL)
      return NULL;
    
    else if(comparePerson(list->data, element) == 1){
      person = (Person *)element;
      return person;
    }
  }
}

void *mapRemove(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *)){
  Person *person;
  Person *toRemove;
  List *list;
  List *newList;
  int index;
  
  index = hash(element);
  list = (List *)map->bucket[index];
  newList = (List *)map->bucket[index];
 
  while(list != NULL){
    if(comparePerson(list->data, element) == 1){
      toRemove = (Person *)element;
      map->bucket[index] = list->next;
      return toRemove;
    }

    else if(comparePerson(list->data, element) == 0){
      list = list->next;
        
      if(list == NULL)
        return NULL;
        
      else if(comparePerson(list->data, element) == 1){
        toRemove = (Person *)element;
        
        list = list->next;
        newList->next = list;
        
        return toRemove;
      }
    }
  }
}

void mapLinearStore(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *)){
  int index;
  
  index = hash(element);
  
  void *currentBucket = map->bucket[index];
  
  while(map->length >= index){
    if(map->bucket[index] != NULL){
      
      if(comparePerson(map->bucket[index], element) == 1)
        Throw(ERR_SAME_ELEMENT);
      
      else if(map->bucket[index] != NULL)
        index++;
    }
    
    else if(isBucketEmpty(currentBucket)){
      map->bucket[index] = element;
      return;
    }
  }

  
  if(index > map->length){
    Throw(ERR_EXCEED_BUCKET);
  }
}

void *mapLinearFind(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *)){
  Person *person;
  int index;
  
  index = hash(element);
  
  if(comparePerson(map->bucket[index], element) == 1){
    person = (Person *)element;
    return person;
  }
  
  else if(comparePerson(map->bucket[index], element) == 0){
    index++;
      
    if(map->bucket[index] == NULL)
      return NULL;
    
    else if(comparePerson(map->bucket[index], element) == 1){
      person = (Person *)element;
      return person;
    }
  }
}

void *mapLinearRemove(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *)){

}