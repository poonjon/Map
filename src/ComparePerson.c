#include "ComparePerson.h"
#include "Person.h"
#include <String.h>

int comparePerson(void *person1, void *person2){
  Person *comparePerson1;
  Person *comparePerson2;
  
  comparePerson1 = (Person *)person1;
  comparePerson2 = (Person *)person2;
  
  if(strcmp(comparePerson1->name, comparePerson2->name) == 0)
    return 1;
  else
    return 0;
}
