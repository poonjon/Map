#include "unity.h"
#include "Map.h"
#include "Person.h"
#include "mock_Hash.h"
#include "List.h"
#include "CustomAssert.h"
#include "ComparePerson.h"
#include "CException.h"
#include "ErrorCode.h"

#define getPersonFromBucket(x) ((Person *)((List *)(x))->data)

void setUp(){}
void tearDown(){}

void test_mapNew_given_length_of_10_should_create_a_new_map(){
  Map  *map = mapNew(10);
  
  TEST_ASSERT_NOT_NULL(map);
  TEST_ASSERT_NOT_NULL(map->bucket);
  TEST_ASSERT_EQUAL(10, map->length);
  TEST_ASSERT_EQUAL(0, map->size);
	
}

void test_mapStore_given_Ali_should_add_it_to_map(){
  Person *person = personNew("Ali", 25, 70.3); 
  Map  *map = mapNew(5);
  
  hash_ExpectAndReturn(person, 3);
  
  mapStore(map, person, comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  // TEST_ASSERT_EQUAL_STRING("Ali", ((Person *)((List *)map->bucket[3])->data)->name);
  // TEST_ASSERT_EQUAL_Person(person,(Person *)((List *)map->bucket[3])->data);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, getPersonFromBucket(map->bucket[3]));
	
}

void test_mapStore_given_Ali_but_Ali_is_in_the_Map_should_throw_ERR_SAME_ELEMENT_exception(){
  CEXCEPTION_T e;
  Person *person = personNew("Ali", 25, 70.3);
  Map *map = mapNew(5);
  List *list = listNew(person, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(person, 3);
  
  
  Try{
    mapStore(map, person, comparePerson, hash);
    TEST_FAIL_MESSAGE("Expect ERR_SAME_ELEMENT exception to be thrown.");
  } Catch(e){
    TEST_ASSERT_EQUAL(ERR_SAME_ELEMENT, e);
    // TEST_ASSERT_NOT_NULL(map->bucket[3]);
    // TEST_ASSERT_EQUAL_Person(person, getPersonFromBucket(map->bucket[3]));
    TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, getPersonFromBucket(map->bucket[3]));
  }

}

void test_mapStore_given_zorro_should_add_it_to_map(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *person2 = personNew("Zorro", 40, 100.3); 
  Map *map = mapNew(5);
  List *list = listNew(person1, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(person2, 3);
  
  
  mapStore(map, person2, comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  // TEST_ASSERT_EQUAL_STRING("Zorro", ((Person *)((List *)map->bucket[3])->data)->name);
  // TEST_ASSERT_EQUAL_Person(person2,(Person *)((List *)map->bucket[3])->data);
	TEST_ASSERT_EQUAL_Person("Zorro", 40, 100.3, getPersonFromBucket(map->bucket[3]));
}

void test_comparePerson_ali_with_ali_return_1(){
  int result = 5;
  Person *person1 = personNew("Ali", 5, 5.5);
  Person *person2 = personNew("Ali", 5, 5.5);
  
  result = comparePerson(&person1, &person2);
  
  TEST_ASSERT_EQUAL(1, result);  
}

void test_mapFind_ali_should_return_ali(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Map *map = mapNew(5);
  Person *result;
  List *list = listNew(person1, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(person1, 3);
  result = mapFind(map, person1, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Ali", result->name);
}

void test_mapFind_nope_should_return_NULL(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *shouldFind = personNew("Nope", 25, 70.3); 
  Map *map = mapNew(5);
  Person *result;
  List *list = listNew(person1, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(shouldFind, 3);
  
  result = mapFind(map, shouldFind, comparePerson, hash);

  TEST_ASSERT_NULL(result);
}

void test_mapFind_ali_in_a_list(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *person2 = personNew("Zorro", 50, 100.3); 
  Person *shouldFind = personNew("Zorro", 50, 100.3); 
  Map *map = mapNew(5);
  Person *result;
  List *list = listNew(person1, NULL);
  list = listNew(person2, list);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(shouldFind, 3);
  
  result = mapFind(map, shouldFind, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Zorro", result->name);
}

void test_mapFind_Nope_in_a_list_should_return_null(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *person2 = personNew("Zorro", 50, 100.3); 
  Person *shouldFind = personNew("Nope", 50, 100.3); 
  Map *map = mapNew(5);
  Person *result;
  List *list = listNew(person1, NULL);
  list = listNew(person2, list);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(shouldFind, 3);
  
  result = mapFind(map, shouldFind, comparePerson, hash);

  TEST_ASSERT_NULL(result);
}

void test_mapRemove_should_remove_Ali(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *personRemove = personNew("Ali", 25, 70.3); 
  Map *map = mapNew(5);
  Person *result;
  List *list = listNew(person1, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(personRemove, 3);
  result = mapRemove(map, personRemove, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Ali", result->name);
}

void test_mapRemove_nope_should_return_NULL(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *personRemove = personNew("Nope", 25, 70.3); 
  Map *map = mapNew(5);
  Person *result;
  List *list = listNew(person1, NULL);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(personRemove, 3);
  
  result = mapRemove(map, personRemove, comparePerson, hash);

  TEST_ASSERT_NULL(result);
}

void test_mapRemove_should_remove_ali_in_the_list(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *person2 = personNew("Zorro", 50, 100.3); 
  Person *personRemove = personNew("Ali", 50, 100.3); 
  Map *map = mapNew(5);
  Person *result;
  List *list = listNew(person1, NULL);
  list = listNew(person2, list);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(personRemove, 3);
  
  result = mapRemove(map, personRemove, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Ali", result->name);
  TEST_ASSERT_NULL(list->next);
}

void test_mapRemove_nope_in_a_list_should_return_null(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *person2 = personNew("Zorro", 50, 100.3); 
  Person *personRemove = personNew("Nope", 50, 100.3); 
  Map *map = mapNew(5);
  Person *result;
  List *list = listNew(person1, NULL);
  list = listNew(person2, list);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(personRemove, 3);
  
  result = mapRemove(map, personRemove, comparePerson, hash);

  TEST_ASSERT_NULL(result);
}

void test_mapRemove_should_remove_Zorro_in_the_list(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *person2 = personNew("Zorro", 50, 100.3); 
  Person *person3 = personNew("Loco", 30, 50.3); 
  Person *personRemove = personNew("Zorro", 50, 100.3); 
  Map *map = mapNew(5);
  Person *result;
  List *list = listNew(person1, NULL);
  list = listNew(person2, list);
  list = listNew(person3, list);
  
  map->bucket[3] = list;
  hash_ExpectAndReturn(personRemove, 3);
  
  result = mapRemove(map, personRemove, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Zorro", result->name);
  TEST_ASSERT_NULL((list->next)->next);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, getPersonFromBucket(((List *)map->bucket[3])->next));
  
}

void test_mapLinearStore_given_Ali_should_add_it_to_map(){
  Person *person = personNew("Ali", 25, 70.3); 
  Map  *map = mapNew(5);
  
  hash_ExpectAndReturn(person, 3);
  
  mapLinearStore(map, person, comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
  TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, map->bucket[3]);
	
}

void test_mapLinearStore_given_Ali_but_Ali_is_in_the_Map_should_throw_ERR_SAME_ELEMENT_exception(){
  CEXCEPTION_T e;
  Person *person1 = personNew("Ali", 25, 70.3);
  Person *person2 = personNew("Ali", 25, 70.3);
  Map *map = mapNew(5);

  hash_ExpectAndReturn(person1, 3);
  hash_ExpectAndReturn(person2, 3);
  
  
  Try{
    mapLinearStore(map, person1, comparePerson, hash);
    mapLinearStore(map, person2, comparePerson, hash);
    TEST_FAIL_MESSAGE("Expect ERR_SAME_ELEMENT exception to be thrown.");
  } Catch(e){
    TEST_ASSERT_EQUAL(ERR_SAME_ELEMENT, e);
    TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, map->bucket[3]);
  }

}

void test_mapLinearStore_given_zorro_should_add_it_to_map(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *person2 = personNew("Zorro", 40, 100.3); 
  Map *map = mapNew(5);
  
  hash_ExpectAndReturn(person1, 3);
  hash_ExpectAndReturn(person2, 3);
  
  mapLinearStore(map, person1, comparePerson, hash);
  mapLinearStore(map, person2, comparePerson, hash);
  
  TEST_ASSERT_NOT_NULL(map->bucket[3]);
	TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, map->bucket[3]);
	TEST_ASSERT_EQUAL_Person("Zorro", 40, 100.3, map->bucket[4]);
}

void test_mapLinearStore_given_Rylai_but_exceed_length_should_throw_ERR_EXCEED_BUCKET_exception(){
  CEXCEPTION_T e;
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *person2 = personNew("Zorro", 40, 100.3); 
  Person *person3 = personNew("Rylai", 18, 45.3); 
  Map *map = mapNew(5);
  
  hash_ExpectAndReturn(person1, 3);
  hash_ExpectAndReturn(person2, 3);
  hash_ExpectAndReturn(person3, 3);
  
  Try{
    mapLinearStore(map, person1, comparePerson, hash);
    mapLinearStore(map, person2, comparePerson, hash);
    mapLinearStore(map, person3, comparePerson, hash);
    TEST_FAIL_MESSAGE("Expect ERR_EXCEED_BUCKET exception to be thrown.");
  } Catch(e){
    TEST_ASSERT_EQUAL(ERR_EXCEED_BUCKET, e);
    TEST_ASSERT_EQUAL_Person("Ali", 25, 70.3, map->bucket[3]);
    TEST_ASSERT_EQUAL_Person("Zorro", 40, 100.3, map->bucket[4]);
  }

}

void test_mapLinearFind_ali_should_return_ali(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Map *map = mapNew(5);
  Person *result;
  map->bucket[3] = person1;
  hash_ExpectAndReturn(person1, 3);
  
  result = mapLinearFind(map, person1, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Ali", result->name);
}

void test_mapLinearFind_abu_should_return_ali(){
  Person *person1 = personNew("Ali", 25, 70.3); 
  Person *person2 = personNew("Abu", 45, 123.3); 
  Person *personToFind = personNew("Abu", 45, 123.3); 
  Map *map = mapNew(5);
  Person *result;
  map->bucket[3] = person1;
  map->bucket[4] = person2;
  
  hash_ExpectAndReturn(personToFind, 4);
  
  
  result = mapLinearFind(map, personToFind, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Abu", result->name);
}

void test_mapLinearFind_abu_with_marked_should_return_abu(){
  Person *person1 = personNew("Abu", 45, 123.3); 
  Person *personToFind = personNew("Abu", 45, 123.3); 
  Map *map = mapNew(5);
  Person *result;
  map->bucket[3] = (void *)-1;
  map->bucket[4] = person1;
  
  
  hash_ExpectAndReturn(personToFind, 3);
  
  
  result = mapLinearFind(map, personToFind, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Abu", result->name);
}

void test_mapLinearFind_nope_should_return_NULL(){
  Person *person1 = personNew("Ali", 76, 75.3); 
  Person *person2 = personNew("Abu", 45, 123.3); 
  Person *personToFind = personNew("Nope", 45, 123.3); 
  Map *map = mapNew(5);
  Person *result;
  map->bucket[3] = person1;
  map->bucket[4] = person2;
  
  hash_ExpectAndReturn(personToFind, 3);
  
  result = mapLinearFind(map, personToFind, comparePerson, hash);

  TEST_ASSERT_NULL(result);
}

void test_mapLinearFind_abu_with_marked_should_return_abu_case2(){
  Person *person1 = personNew("Ali", 78, 75.3); 
  Person *person3 = personNew("Abu", 45, 123.3); 
  Person *personToFind = personNew("Abu", 45, 123.3); 
  Map *map = mapNew(6);
  Person *result;
  map->bucket[3] = person1;
  map->bucket[4] = (void *)-1;
  map->bucket[5] = person3;
  
  hash_ExpectAndReturn(personToFind, 3);
  
  result = mapLinearFind(map, personToFind, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Abu", result->name);
}

void test_mapLinearRemove_Ali_should_null(){
  Person *person1 = personNew("Ali", 78, 75.3); 
  Person *personToRemove = personNew("Ali", 78, 75.3); 
  Map *map = mapNew(5);
  Person *mark;
  map->bucket[3] = person1;
  
  hash_ExpectAndReturn(personToRemove, 3);
  
  mark = mapLinearRemove(map, personToRemove, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Ali", mark->name);
  TEST_ASSERT_NULL(map->bucket[3]);
}

void test_mapLinearRemove_Ali_should_mark(){
  Person *person1 = personNew("Ali", 78, 75.3); 
  Person *person2 = personNew("Abu", 56, 100.3); 
  Person *personToRemove = personNew("Ali", 78, 75.3); 
  Map *map = mapNew(5);
  Person *mark;
  map->bucket[3] = person1;
  map->bucket[4] = person2;
  
  hash_ExpectAndReturn(personToRemove, 3);
  
  mark = mapLinearRemove(map, personToRemove, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Ali", mark->name);
  TEST_ASSERT_EQUAL_PTR(-1, map->bucket[3]);
}

void test_mapLinearRemove_Abu_should_null(){
  Person *person1 = personNew("Ali", 78, 75.3); 
  Person *person2 = personNew("Abu", 56, 100.3); 
  Person *personToRemove = personNew("Abu", 56, 100.3);
  Map *map = mapNew(5);
  Person *mark;
  map->bucket[3] = person1;
  map->bucket[4] = person2;
  
  hash_ExpectAndReturn(personToRemove, 3);
  
  mark = mapLinearRemove(map, personToRemove, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Abu", mark->name);
  TEST_ASSERT_NULL(map->bucket[4]);
}

void test_mapLinearRemove_Abu_should_mark(){
  Person *person1 = personNew("Ali", 78, 75.3); 
  Person *person2 = personNew("Abu", 56, 100.3); 
  Person *person3 = personNew("Rylai", 18, 45.3); 
  Person *personToRemove = personNew("Abu", 56, 100.3); 
  Map *map = mapNew(6);
  Person *mark;
  map->bucket[3] = person1;
  map->bucket[4] = person2;
  map->bucket[5] = person3;
  
  hash_ExpectAndReturn(personToRemove, 3);
  
  mark = mapLinearRemove(map, personToRemove, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Abu", mark->name);
  TEST_ASSERT_EQUAL_PTR(-1, map->bucket[4]);
}

void test_mapLinearRemove_Abu_should_mark_case2(){
  
  Person *person2 = personNew("Abu", 56, 100.3); 
  Person *person3 = personNew("Rylai", 18, 45.3); 
  Person *personToRemove = personNew("Abu", 56, 100.3); 
  Map *map = mapNew(6);
  Person *mark;
  map->bucket[3] = (void *)-1;
  map->bucket[4] = person2;
  map->bucket[5] = person3;
  
  hash_ExpectAndReturn(personToRemove, 3);
  
  mark = mapLinearRemove(map, personToRemove, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Abu", mark->name);
  TEST_ASSERT_EQUAL_PTR(-1, map->bucket[4]);
}

void test_mapLinearRemove_Ami_but_not_found_should_return_null(){
  
  Person *person2 = personNew("Abu", 56, 100.3); 
  Person *person3 = personNew("Rylai", 18, 45.3); 
  Person *personToRemove = personNew("Ami", 780, 50.3); 
  Map *map = mapNew(6);
  Person *mark;
  map->bucket[3] = (void *)-1;
  map->bucket[4] = person2;
  map->bucket[5] = person3;
  
  hash_ExpectAndReturn(personToRemove, 3);
  
  mark = mapLinearRemove(map, personToRemove, comparePerson, hash);

  TEST_ASSERT_NULL(mark);
}

void test_mapLinearRemove_Rylai_should_null_and_null_previous_mark(){
  
  Person *person1 = personNew("Abu", 56, 100.3); 
  Person *person3 = personNew("Rylai", 18, 45.3); 
  Person *personToRemove = personNew("Rylai", 18, 45.3); 
  Map *map = mapNew(6);
  Person *mark;
  map->bucket[3] = person1;
  map->bucket[4] = (void *)-1;
  map->bucket[5] = person3;
  
  hash_ExpectAndReturn(personToRemove, 3);
  
  mark = mapLinearRemove(map, personToRemove, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Rylai", mark->name);
  TEST_ASSERT_NULL(map->bucket[5]);
  TEST_ASSERT_NULL(map->bucket[4]);
}

void test_mapLinearRemove_Rylai_should_null_and_null_previous_mark_and_null_previous_mark(){
  
  Person *person3 = personNew("Rylai", 18, 45.3); 
  Person *personToRemove = personNew("Rylai", 18, 45.3); 
  Map *map = mapNew(6);
  Person *mark;
  map->bucket[3] = (void *)-1;
  map->bucket[4] = (void *)-1;
  map->bucket[5] = person3;
  
  hash_ExpectAndReturn(personToRemove, 3);
  
  mark = mapLinearRemove(map, personToRemove, comparePerson, hash);

  TEST_ASSERT_EQUAL_STRING("Rylai", mark->name);
  TEST_ASSERT_NULL(map->bucket[5]);
  TEST_ASSERT_NULL(map->bucket[4]);
  TEST_ASSERT_NULL(map->bucket[3]);
}

