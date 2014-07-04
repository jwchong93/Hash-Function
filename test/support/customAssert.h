#ifndef customAssert_H
#define customAssert_H
#include "Person.h"

#define TEST_ASSERT_EQUAL_Person(expected,actual)		\
		assertEqualPerson(expected,actual,__LINE__,NULL)
void assertEqualPerson(Person *expected,Person *actual, int line, char *msg);

#endif // customAssert_H
