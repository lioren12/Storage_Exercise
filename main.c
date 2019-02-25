//  File Header
/*
	main.c
	Author - Lior Oren
	Project - Storage_Exercise
	Description - main file that initial the hash table and implements testing code with time stamps to verify the correctness of the code.
				  Test code:
				  1) First, I used time stamps using <time.h> library of c. In that way I could prevent concurrent access to data.
				  2) In the beginning, I filled the database with 3 different keys using addNewElement.
				  3) Then, I called 3 times to retrieveKeyValue and checked if the time stamp is smaller than the eviction time or bigger. 
					-> For the first 2 checks, the time stamp was smaller, and therefore it was found.
					-> For the 3rd, the time stamp was bigger, and therefore, no key was inside. (Already evicted - A message printed out)
				  4) Then, I called 2 more times to isExist and checked if the time stamp is smaller than the eviction time or bigger.
				    -> The first one was success and the second was failure.
				  5) Assertions were added when needed. (For tests logic verification)
				  6) The keys I added also tested the linked list that is implemented. (2 key to the same place in the hash table)
*/

#include <assert.h>
#include <time.h>
#include "key_value_db.h"

#define _CRT_SECURE_NO_WARNINGS

#define SIZE_OF_HASH_TABLE 100 // Arbitrary - can be changed for any different program (bigger for very busy systems)
#define TIME_FAILURE_MESSAGE "A failure on time call has occured"
#define TIME_BETWEEN_TESTS 10000000 // Arbitrary - can be changed 

// For test purposes
#define FIRST_KEY_RETRIEVE_REQUEST 101 // Success
#define SECOND_KEY_RETRIEVE_REQUEST 1 // Success
#define THIRD_KEY_RETRIEVE_REQUEST 5 // Failure
#define FIRST_IS_KEY_REQUEST 101 // Success
#define SECOND_IS_KEY_REQUEST 32 // Failure

unsigned int main() {
	unsigned int adding_success; //Success check
	const unsigned int size = SIZE_OF_HASH_TABLE;
	Storage **hash_table; // A pointer to the storage
	clock_t start_time; // Time stamp of starting the program
	clock_t current_time_a, current_time_b, current_time_c, current_time_d, current_time_e; // Time stamps sending to retrieveKeyValue & isExist
	unsigned long long time_index; // For time stamping
	unsigned int value_num_a, value_num_b, value_num_c; // Three checks for retrieveKeyValue function
	bool is_exist_a, is_exist_b; // Two checks for isExist function

	// Storage creation and initialization - dynamic allocated
	hash_table = createStorageAndInit(size);

	start_time = clock();
	if (FAILURE == start_time) {
		printf(TIME_FAILURE_MESSAGE);
		exit(FAILURE);
	}
	
	// Testing code starts here

	adding_success = addNewElement(101, 44, 15000, hash_table, size); // Values chosen arbitrary - can be changed.
	assert(SUCCESS == adding_success);
	adding_success = addNewElement(1, 22, 20000, hash_table, size); // Values chosen arbitrary - can be changed.
	assert(SUCCESS == adding_success);
	adding_success = addNewElement(32, 88, 25, hash_table, size); // Values chosen arbitrary - can be changed.
	assert(SUCCESS == adding_success);

	// First test - success
	for (time_index = 0; time_index < TIME_BETWEEN_TESTS; time_index++) {
	}
	printf("Test #1:\n");
	current_time_a = clock();
	if (FAILURE == current_time_a) {
		printf(TIME_FAILURE_MESSAGE);
		exit(FAILURE);
	}
	value_num_a = retrieveKeyValue(FIRST_KEY_RETRIEVE_REQUEST, current_time_a, hash_table, size); 
	assert(FAILURE != value_num_a); 
	if (FAILURE != value_num_a) {
		printf("The value of key number %d is %d\n", FIRST_KEY_RETRIEVE_REQUEST, value_num_a);
	}
	printf("\n");

	// Second test - success
	for (time_index = 0; time_index < TIME_BETWEEN_TESTS; time_index++) {
	}
	printf("Test #2:\n");
	current_time_b = clock();
	if (FAILURE == current_time_b) {
		printf(TIME_FAILURE_MESSAGE);
		exit(FAILURE);
	}
	value_num_b = retrieveKeyValue(SECOND_KEY_RETRIEVE_REQUEST, current_time_b, hash_table, size);
	assert(FAILURE != value_num_b);
	if (FAILURE != value_num_b) {
		printf("The value of key number %d is %d\n", SECOND_KEY_RETRIEVE_REQUEST, value_num_b);
	}
	printf("\n");

	// Third test - failure
	for (time_index = 0; time_index < TIME_BETWEEN_TESTS; time_index++) {
	}
	printf("Test #3:\n");
	current_time_c = clock();
	if (FAILURE == current_time_c) {
		printf(TIME_FAILURE_MESSAGE);
		exit(FAILURE);
	}
	value_num_c = retrieveKeyValue(THIRD_KEY_RETRIEVE_REQUEST, current_time_c, hash_table, size);
	assert(FAILURE == value_num_c);
	if (FAILURE != value_num_c) {
		printf("The value of key number %d is %d\n", THIRD_KEY_RETRIEVE_REQUEST, value_num_c);
	}
	printf("\n");

	// Fourth test - success
	for (time_index = 0; time_index < TIME_BETWEEN_TESTS; time_index++) {
	}
	printf("Test #4:\n");
	current_time_d = clock();
	if (FAILURE == current_time_d) {
		printf(TIME_FAILURE_MESSAGE);
		exit(FAILURE);
	}
	is_exist_a = isExist(FIRST_IS_KEY_REQUEST, current_time_d, hash_table, size);
	assert(true == is_exist_a);
	if (true == is_exist_a) {
		printf("The key %d is exist\n", FIRST_IS_KEY_REQUEST);
	}
	else {
		printf("The key %d is not exist\n", FIRST_IS_KEY_REQUEST);
	}
	printf("\n");

	// Fifth test - Failure
	for (time_index = 0; time_index < TIME_BETWEEN_TESTS; time_index++) {
	}
	printf("Test #5:\n");
	current_time_e = clock();
	if (FAILURE == current_time_e) {
		printf(TIME_FAILURE_MESSAGE);
		exit(FAILURE);
	}
	is_exist_b = isExist(SECOND_IS_KEY_REQUEST, current_time_e, hash_table, size);
	assert(true != is_exist_b);
	if (true == is_exist_b) {
		printf("The key %d is exist\n", SECOND_IS_KEY_REQUEST);
	}
	else {
		printf("the key %d is not exist\n", SECOND_IS_KEY_REQUEST);
	}
	printf("\n");

	freeHashTableAllocatedMemory(hash_table, size);

	return (SUCCESS);
}