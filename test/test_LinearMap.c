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














