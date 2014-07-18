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

/*
 * input: map = the map
 *        element = element to remove
 *        compare = to compare 2 elements 
 *        hash = hash function
 *
 */
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

/*
 * input: map = the map
 *        element = element to remove
 *        compare = to compare 2 elements 
 *        hash = hash function
 *
 */
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

/*
 * input: map = the map
 *        element = element to remove
 *        compare = to compare 2 elements 
 *        hash = hash function
 *
 */
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

/*
 * input: map = the map
 *        element = element to remove
 *        compare = to compare 2 elements 
 *        hash = hash function
 *
 */
void mapLinearStore(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *)){
  int index;
  
  index = hash(element);
  
  void *currentBucket = map->bucket[index];
  
  while((map->length)-1 >= index){
    if(map->bucket[index] != NULL){                           //if element not null
      
      if(comparePerson(map->bucket[index], element) == 1)     //if same element throw error
        Throw(ERR_SAME_ELEMENT);
      
      else if(map->bucket[index] != NULL)
        index++;
    }
    
    else{
      map->bucket[index] = element;
      return;
    }
  }
  
  if(index > (map->length)-1){                                //if exceed bucket throw error
    Throw(ERR_EXCEED_BUCKET);
  }
}

/*
 * input: map = the map
 *        element = element to remove
 *        compare = to compare 2 elements 
 *        hash = hash function
 *
 */
void *mapLinearFind(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *)){
  Person *person;
  int index;
  
  index = hash(element);
  void *currentBucket = map->bucket[index];

  if(isBucketMarked(map->bucket[index]) || map->bucket[index] != NULL){ //check if current element is marked or not null
    
    while((map->length)-1 >= index){                                    //loop if map length is shorter than index, stop when index exceeds bucket length
      
      if(isBucketMarked(map->bucket[index])){
        index++;
      }
      
      else if(comparePerson(map->bucket[index], element) == 1){
          person = ((Person *)map->bucket[index]);
          return person;
      }
      
      else
        index++;
    }
    
    return NULL;
  }
  
}

/*
 * input: map = the map
 *        element = element to remove
 *        compare = to compare 2 elements 
 *        hash = hash function
 *
 */
void *mapLinearRemove(Map *map, void *element, int (*compare)(void *, void *), unsigned int(*hash)(void *)){
  Person *person;
  int index;
  
  index = hash(element);
  void *currentBucket = map->bucket[index];

  if(isBucketMarked(map->bucket[index]) || map->bucket[index] != NULL){  //check if current element is marked or not null
    
    while((map->length)-1 >= index){                                     //loop if map length is shorter than index, stop when index exceeds bucket length
      
      if(isBucketMarked(map->bucket[index])){
        index++;
      }
      
      else if(comparePerson(map->bucket[index], element) == 1){
          person = ((Person *)map->bucket[index]);
            
          if(map->bucket[index+1] == NULL || index+1 > (map->length)-1){ //to check if next element is null or next element exceeds the bucket
            map->bucket[index] = NULL;                                   //null contents if exceeds bucket length or next element is null
            while(isBucketMarked(map->bucket[index-1])){                 //loop to null previous element if previous element is marked
              map->bucket[index-1] = NULL;
              index--;
            }
          }
          else if(map->bucket[index+1] != NULL)                          //if next element is not null then mark current element
            map->bucket[index] = (void *)-1;
           
          return person;
      }   
      else
        index++;
    }   
    return NULL;
  }
}