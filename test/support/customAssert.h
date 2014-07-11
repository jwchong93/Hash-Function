#ifndef customAssert_H
#define customAssert_H
#include "Person.h"

#define TEST_ASSERT_EQUAL_Person(expectedName,\
								expectedAge, \
								expectedWeight,\
								actual)		\
		assertEqualPerson(expectedName,\
						expectedAge, \
						expectedWeight,\
						actual,__LINE__,NULL)
void assertEqualPerson(char *expectedName,
						int expectedAge,
						float expectedWeight,
						Person *actual, 
						int line, char *msg);

#endif // customAssert_H
