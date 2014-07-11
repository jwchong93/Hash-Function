#include "unity.h"
#include "Person.h"
#include "List.h"
void setUp(void)
{
}

void tearDown(void)
{
}

void test_PersonList_explore(void)
{

	List *list,*nextList;
	
	Person *person = personNew("Ali",23,64.4);
	list=listNew(person,NULL);
	person = personNew("Zorro",60,55.4);
	list=listNew(person,list);
	person = personNew("Suparman",88,42.3);
	list=listNew(person,list);


		
	TEST_ASSERT_NOT_NULL(list);
	TEST_ASSERT_EQUAL_STRING("Suparman",((Person*)list->data)->name);

	nextList=list->next;
	TEST_ASSERT_NOT_NULL(nextList);
	TEST_ASSERT_EQUAL_STRING("Zorro",((Person*)nextList->data)->name);
	
	nextList=nextList->next;
	TEST_ASSERT_NOT_NULL(nextList);
	TEST_ASSERT_EQUAL_STRING("Ali",((Person*)nextList->data)->name);
	listDump(list,personDump);
}
