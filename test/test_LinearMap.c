#include "unity.h"
#include "Map.h"
#include <stdio.h>
#include "Person.h"
#include "mock_ComparePerson.h"
#include "mock_Hash.h"
#include "List.h"
#include "customAssert.h"


void setUp(void)
{
}

void tearDown(void)
{
}


void test_mapLinearStore_should_add_ali_into_the_bucket_directly_if_the_location_is_NULL()
{
	Map *map = mapNew(5);
	Person *person = personNew("Ali",25,70.3);
	
	hash_ExpectAndReturn(person,3);
	
	mapLinearStore(map,person,comparePerson,hash);
	TEST_ASSERT_NOT_NULL(map->bucket[3]);
	TEST_ASSERT_EQUAL_Person("Ali",25,70.3,map->bucket[3]);
	TEST_ASSERT_EQUAL(1,map->size);

}


void test_mapLinearStore_should_add_zorro_next_to_the_location_when_found_ali_is_being_in_the_same_location()
{
	Map *map = mapNew(5);
	Person *person = personNew("Ali",25,70.3);
	Person *person2 = personNew("Zorro",35,65.4);
	
	hash_ExpectAndReturn(person,3);
	hash_ExpectAndReturn(person2,3);
	mapLinearStore(map,person,comparePerson,hash);
	mapLinearStore(map,person2,comparePerson,hash);
	TEST_ASSERT_NOT_NULL(map->bucket[3]);
	TEST_ASSERT_EQUAL_Person("Ali",25,70.3,map->bucket[3]);
	TEST_ASSERT_NOT_NULL(map->bucket[4]);
	TEST_ASSERT_EQUAL_Person("Zorro",35,65.4,map->bucket[4]);
	TEST_ASSERT_EQUAL(2,map->size);
	
	
}

void test_mapLinearStore_should_add_muthu_next_to_the_location_when_found_ali_is_being_in_the_same_location_and_zorro_at_the_next_location()
{
	Map *map = mapNew(10);
	Person *person = personNew("Ali",25,70.3);
	Person *person2 = personNew("Zorro",35,65.4);
	Person *person3 = personNew("Muthu",40,85.2);
	
	hash_ExpectAndReturn(person,3);
	hash_ExpectAndReturn(person2,3);
	hash_ExpectAndReturn(person3,3);
	
	mapLinearStore(map,person,comparePerson,hash);
	mapLinearStore(map,person2,comparePerson,hash);
	mapLinearStore(map,person3,comparePerson,hash);
	TEST_ASSERT_NOT_NULL(map->bucket[3]);
	TEST_ASSERT_EQUAL_Person("Ali",25,70.3,map->bucket[3]);
	TEST_ASSERT_NOT_NULL(map->bucket[4]);
	TEST_ASSERT_EQUAL_Person("Zorro",35,65.4,map->bucket[4]);
	TEST_ASSERT_NOT_NULL(map->bucket[5]);
	TEST_ASSERT_EQUAL_Person("Muthu",40,85.2,map->bucket[5]);
	TEST_ASSERT_EQUAL(3,map->size);
}

void test_mapLinearStore_should_throw_an_error_when_adding_reach_the_end_of_the_bucket()
{
	CEXCEPTION_T e;
	
	Map *map = mapNew(5);
	Person *person = personNew("Ali",25,70.3);
	Person *person2 = personNew("Zorro",35,65.4);
	Person *person3 = personNew("Muthu",40,85.2);
	
	hash_ExpectAndReturn(person,3);
	hash_ExpectAndReturn(person2,3);
	hash_ExpectAndReturn(person3,3);
	
	mapLinearStore(map,person,comparePerson,hash);
	mapLinearStore(map,person2,comparePerson,hash);
	Try
	{
		mapLinearStore(map,person3,comparePerson,hash);
		TEST_FAIL_MESSAGE("Expect ERR_OUT_OF_BOUND exception to be thrown.");
	}
	Catch(e)
	{
		TEST_ASSERT_EQUAL(ERR_OUT_OF_BOUND,e);
		TEST_ASSERT_NOT_NULL(map->bucket[3]);
		TEST_ASSERT_EQUAL_Person("Ali",25,70.3,map->bucket[3]);
		TEST_ASSERT_NOT_NULL(map->bucket[4]);
		TEST_ASSERT_EQUAL_Person("Zorro",35,65.4,map->bucket[4]);
		TEST_ASSERT_EQUAL(2,map->size);
	}
	
}

void test_mapLinearFind_will_return_NULL_when_the_location_of_the_bucket_is_empty()
{
	Map *map = mapNew(5);
	void *returnedData;
	Person *person = personNew("Ali",25,70.3);
	Person *testPerson = personNew("Ali",0,0);
	
	hash_ExpectAndReturn(testPerson,3);
	returnedData = mapLinearFind(map, testPerson, comparePerson,hash);
	TEST_ASSERT_NULL(returnedData);
}

void test_mapLinearFind_will_return_ali_when_ali_being_in_the_bucket()
{
	Map *map = mapNew(5);
	void *returnedData;
	Person *person = personNew("Ali",25,70.3);
	Person *testPerson = personNew("Ali",0,0);
	
	map->bucket[3]=person;
	map->size++;
	
	hash_ExpectAndReturn(testPerson,3);
	comparePerson_ExpectAndReturn(person,testPerson,1);
	returnedData = mapLinearFind(map, testPerson, comparePerson,hash);
	TEST_ASSERT_NOT_NULL(returnedData);
	TEST_ASSERT_EQUAL_Person("Ali",25,70.3,returnedData);
	TEST_ASSERT_NOT_NULL(map->bucket[3]);
	TEST_ASSERT_EQUAL(1,map->size);
}

void test_mapLinearFind_will_return_ali_when_ali_in_the_next_location_of_the_bucket()
{
	Map *map = mapNew(5);
	void *returnedData;
	Person *person2 = personNew("Ali",25,70.3);
	Person *person = personNew("Muthu",30,65.6);
	Person *testPerson = personNew("Ali",0,0);
	
	map->bucket[3]=person;
	map->bucket[4]=person2;
	map->size+=2;
	
	hash_ExpectAndReturn(testPerson,3);
	comparePerson_ExpectAndReturn(person,testPerson,0);
	comparePerson_ExpectAndReturn(person2,testPerson,1);
	returnedData = mapLinearFind(map, testPerson, comparePerson,hash);
	TEST_ASSERT_NOT_NULL(returnedData);
	TEST_ASSERT_EQUAL_Person("Ali",25,70.3,returnedData);
	TEST_ASSERT_NOT_NULL(map->bucket[4]);
	TEST_ASSERT_EQUAL(2,map->size);
}

void test_mapLinearFind_will_return_ali_when_ali_is_next_next_location_of_the_hash_number()
{
	Map *map = mapNew(10);
	void *returnedData;
	Person *person3 = personNew("Ali",25,70.3);
	Person *person2 = personNew("Zorro",90,40.5);
	Person *person = personNew("Muthu",30,65.6);
	Person *testPerson = personNew("Ali",0,0);
	
	map->bucket[3]=person;
	map->bucket[4]=person2;
	map->bucket[5]=person3;
	map->size+=3;
	
	hash_ExpectAndReturn(testPerson,3);
	comparePerson_ExpectAndReturn(person,testPerson,0);
	comparePerson_ExpectAndReturn(person2,testPerson,0);
	comparePerson_ExpectAndReturn(person3,testPerson,1);
	returnedData = mapLinearFind(map, testPerson, comparePerson,hash);
	TEST_ASSERT_NOT_NULL(returnedData);
	TEST_ASSERT_EQUAL_Person("Ali",25,70.3,returnedData);
	TEST_ASSERT_NOT_NULL(map->bucket[5]);
	TEST_ASSERT_EQUAL(3,map->size);
}


void test_mapLinearFind_will_return_NULL_when_ali_was_not_inside_the_bucket_but_there_are_element_for_same_hash_number()
{
	Map *map = mapNew(5);
	void *returnedData;
	Person *person2 = personNew("Zorro",90,40.5);
	Person *person = personNew("Muthu",30,65.6);
	Person *testPerson = personNew("Ali",0,0);
	
	map->bucket[3]=person;
	map->bucket[4]=person2;
	map->size+=3;
	
	hash_ExpectAndReturn(testPerson,3);
	comparePerson_ExpectAndReturn(person,testPerson,0);
	comparePerson_ExpectAndReturn(person2,testPerson,0);
	returnedData = mapLinearFind(map, testPerson, comparePerson,hash);
	TEST_ASSERT_NULL(returnedData);
	TEST_ASSERT_EQUAL(3,map->size);
}

void test_mapLinearRemove_will_return_NULL_when_ali_was_not_inside_the_bucket()
{
	Map *map = mapNew(5);
	void *returnedData;
	Person *person2 = personNew("Zorro",90,40.5);
	Person *person = personNew("Muthu",30,65.6);
	Person *testPerson = personNew("Ali",0,0);
	
	hash_ExpectAndReturn(testPerson,3);
	returnedData = mapLinearRemove(map, testPerson, comparePerson,hash);
	TEST_ASSERT_NULL(returnedData);
}

void test_mapLinearRemove_will_return_NULL_when_ali_was_not_inside_the_bucket_but_there_are_element_for_same_hash_number()
{
	Map *map = mapNew(5);
	void *returnedData;
	Person *person2 = personNew("Zorro",90,40.5);
	Person *person = personNew("Muthu",30,65.6);
	Person *testPerson = personNew("Ali",0,0);
	
	map->bucket[3]=person;
	map->bucket[4]=person2;
	map->size+=2;
	
	hash_ExpectAndReturn(testPerson,3);
	comparePerson_ExpectAndReturn(person,testPerson,0);
	comparePerson_ExpectAndReturn(person2,testPerson,0);
	returnedData = mapLinearRemove(map, testPerson, comparePerson,hash);
	TEST_ASSERT_NULL(returnedData);
	TEST_ASSERT_EQUAL(2,map->size);
}

void test_mapLinearRemove_will_return_ali_when_ali_being_in_the_bucket()
{
	Map *map = mapNew(5);
	void *returnedData;
	Person *person = personNew("Ali",25,70.3);
	Person *testPerson = personNew("Ali",0,0);
	
	map->bucket[3]=person;
	map->size++;
	
	hash_ExpectAndReturn(testPerson,3);
	comparePerson_ExpectAndReturn(person,testPerson,1);
	hash_ExpectAndReturn(NULL,0);
	returnedData = mapLinearRemove(map, testPerson, comparePerson,hash);
	TEST_ASSERT_NOT_NULL(returnedData);
	TEST_ASSERT_EQUAL_Person("Ali",25,70.3,returnedData);
	TEST_ASSERT_NULL(map->bucket[3]);
	TEST_ASSERT_EQUAL(0,map->size);
}

void test_mapLinearRemove_will_return_ali_when_ali_being_in_between_of_two_elements()
{
	Map *map = mapNew(5);
	void *returnedData;
	Person *person2 = personNew("Ali",25,70.3);
	Person *person = personNew("Muthu",40,56.3);
	Person *person3 = personNew("Zorro",35,79.3);
	Person *testPerson = personNew("Ali",0,0);
	
	map->bucket[3]=person;
	map->bucket[4]=person2;
	map->bucket[5]=person3;
	map->size+=3;
	
	hash_ExpectAndReturn(testPerson,3);
	comparePerson_ExpectAndReturn(person,testPerson,0);
	comparePerson_ExpectAndReturn(person2,testPerson,1);
	hash_ExpectAndReturn(person3,3);
	returnedData = mapLinearRemove(map, testPerson, comparePerson,hash);
	TEST_ASSERT_NOT_NULL(returnedData);
	TEST_ASSERT_EQUAL_Person("Ali",25,70.3,returnedData);
	
	TEST_ASSERT_EQUAL_Person("Muthu",40,56.3,map->bucket[3]);
	TEST_ASSERT_EQUAL(-1,map->bucket[4]);
	TEST_ASSERT_EQUAL_Person("Zorro",35,79.3,map->bucket[5]);
	TEST_ASSERT_EQUAL(2,map->size);
}

void test_mapLinearRemove_will_continue_find_the_next_element_when_found_negative_one_in_the_bucket()
{

	Map *map = mapNew(10);
	void *returnedData;
	Person *person2 = personNew("Ali",25,70.3);
	Person *person = personNew("Muthu",40,56.3);
	Person *testPerson = personNew("Ali",0,0);
	
	map->bucket[3]=(void*)-1;
	map->bucket[4]=person;
	map->bucket[5]=person2;
	map->size+=2;
	
	hash_ExpectAndReturn(testPerson,3);
	comparePerson_ExpectAndReturn(person,testPerson,0);
	comparePerson_ExpectAndReturn(person2,testPerson,1);
	hash_ExpectAndReturn(NULL,0);
	returnedData = mapLinearRemove(map, testPerson, comparePerson,hash);
	TEST_ASSERT_NOT_NULL(returnedData);
	TEST_ASSERT_EQUAL_Person("Ali",25,70.3,returnedData);
	
	
	TEST_ASSERT_EQUAL(-1,map->bucket[3]);
	TEST_ASSERT_EQUAL_Person("Muthu",40,56.3,map->bucket[4]);
	TEST_ASSERT_EQUAL(0,map->bucket[5]);
	TEST_ASSERT_EQUAL(1,map->size);
	
	
}

void test_mapLinearRemove_will_remove_the_element_when_the_element_being_at_the_last()
{

	Map *map = mapNew(10);
	void *returnedData;
	Person *person2 = personNew("Ali",25,70.3);
	Person *person = personNew("Muthu",40,56.3);
	Person *testPerson = personNew("Ali",0,0);
	
	map->bucket[3]=person;
	map->bucket[4]=(void*)-1;
	map->bucket[5]=person2;
	map->size+=2;
	
	hash_ExpectAndReturn(testPerson,3);
	comparePerson_ExpectAndReturn(person,testPerson,0);
	comparePerson_ExpectAndReturn(person2,testPerson,1);
	hash_ExpectAndReturn(NULL,0);
	returnedData = mapLinearRemove(map, testPerson, comparePerson,hash);
	TEST_ASSERT_NOT_NULL(returnedData);
	TEST_ASSERT_EQUAL_Person("Ali",25,70.3,returnedData);
	
	TEST_ASSERT_EQUAL_Person("Muthu",40,56.3,map->bucket[3]);
	TEST_ASSERT_EQUAL(0,map->bucket[4]);
	TEST_ASSERT_EQUAL(0,map->bucket[5]);
	TEST_ASSERT_EQUAL(1,map->size);
}





