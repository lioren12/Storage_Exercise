//  File Header
/*  
	key_value_db.h
	Author - Lior Oren
	Project - Storage_Exercise
	Description - This module declares all functions\ Data structure\ Macros that are used for the storage.
*/

#ifndef KEY_VALUE_DB
#define KEY_VALUE_DB

#define _CRT_SECURE_NO_WARNINGS

// Library Includes --------------------------------------------------------------------

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Macros & Definitions --------------------------------------------------------------------

#define ERROR_MESSAGE "An error occurred during Memory allocation, couln't complete the task!\n"
#define EVICTION_TIME_PASSED_MESSEGE "Eviction time has passed.\n"
#define FAILURE -1
#define SUCCESS 0

// Declarations --------------------------------------------------------------------------

typedef struct Storage {
	unsigned int key; //an instance of some binary safe data
	unsigned int value; // an instance of some binary safe data
	unsigned int eviction; // time before eviction
	struct Storage *next_key; 
} Storage;

/*
Description: The function creates a new element and add it to the db.
Parameters: input Element key, value, deletion_point_in_time, the storage and its size.
Returns: Pointer to the head of new list in the hash table.
*/
const int addNewElement(const unsigned int key, const unsigned int value, const unsigned int deletion_point_in_time, const Storage **hash_table, const unsigned int size);

/*
Description: The function search for the key value in the hash table and return it if exist.
Parameters: Input - unsigned int key, current_time_stamp, the storage and its size, output - value.
Returns: 0 for success, -1 for failure.
*/
const unsigned int retrieveKeyValue(const unsigned int key, const clock_t current_time_stamp, const Storage **hash_table, const unsigned int size);

/*
Description: The function search for the key existance in the hash table.
Parameters: Input - unsigned int key and unsigned int size, output - key.
Returns: true for existance, false for absence.
*/
bool const isExist(const unsigned int key, const clock_t current_time_stamp, const Storage **hash_table, const unsigned int size);

/*
Description: The function creates a storage of size "size".
Parameters: input - size.
Returns: pointer to the storage (hash table).
*/
Storage *createStorageAndInit(const unsigned int size);

/*
Description: The function free all lists in the hash table.
Parameters: input - the global hash_table list.
Returns: 0 for success, -1 for failure.
*/
const unsigned int freeHashTableAllocatedMemory(const Storage **hash_table, const unsigned int size);

#endif // KEY_VALUE_DB 

