//  File Header
/*  
	key_value_db.c
	Author - Lior Oren
	Project - Storage_Exercise
	Description - This module implements the parsing of related functions that are used for the storage.
				 Implementation: 
				 1) I used a chained hash table (hash table with linked list in each cell).
				 2) The hash table was implemented with changable size in order to be able to change it according to the 
					quantity of data coming in. (Can be different for each aplication)
				 3) I used a hash function of my own: "(unsigned int) key % SIZE_OF_HASH_TABLE".
				 4) I assumed no need to implement the eviction function. (Not requested)
				 4) Error handling:
					-> I assumed that in case of failure in the memory allocation for the hash table, I can exit from the program (with code -1)
					-> I also assumed that in the other case of failure in the memory allocation (for a key), I dont need to get out from the 
					   program, and just return -1 for failure. (It predicts an actual situation within the program shouldnt exit for any key 
					   insertion failure, but will exit for the initial allocation of the hash table)
				 5) I wasn't sure about "instance of some binary safe" (for key and value) meaning - From google I understood that is more 
					relevant in C++ so I implement it as unsigned integers. Hopefully thats fine.
*/

// Project Includes --------------------------------------------------------------------

#include "key_value_db.h"

// Inner Functions Declarations --------------------------------------------------------

/*
Description: The function returns the hashCode.
Parameters: input - key.
Returns: the hashCode.
*/
const int hashCode(const int key, const unsigned int size);

/*
Description: The function enters a new element to the start of the linked list in the hash table using addNewElement.
Parameters: Input Airplane type, name, age and a pointer to the head of list in the right cell, and output pointer to new list head.
Returns: None.
*/
const int pushElementToStartOfLinkedList(const unsigned int key, const Storage *new_element, const Storage **hash_table, const unsigned int size);

/*
Description: The function creates a new element to the db.
Parameters: input  Airplane type, name, age and a pointer to the new item.
Returns: None.
*/
void updateStorageData(const unsigned int key, const unsigned int value, unsigned int const deletion_point_in_time, Storage *new_element);

// Function Definitions -------------------------------------------------------------

Storage *createStorageAndInit(const unsigned int size) {
	int index_in_hash_table;
	Storage **hash_table = (Storage*)malloc(sizeof(Storage)*size);
	// Memory allocation check
	if (hash_table == NULL) {
		printf(ERROR_MESSAGE);
		free(hash_table); // release before exit.
		exit(FAILURE); // Memory allocation failed. no hash table and therefore exit the program.
	}
	// Storage initiation
	for (index_in_hash_table = 0; index_in_hash_table < size; index_in_hash_table++) {
		hash_table[index_in_hash_table] = NULL;
	}
	return (hash_table);
}

const int hashCode(const int key, const unsigned int size) {
	return (key % size);
}

const int addNewElement(const unsigned int key, const unsigned int value, const unsigned int deletion_point_in_time, const Storage **hash_table, const unsigned int size) {

	int push_element_success;
	int hash_index;
	hash_index = hashCode(key,size);
	Storage *head = hash_table[hash_index];

	while (head != NULL) // To find if key already exist and update it
	{
		if (head->key == key) { 
			updateStorageData(key, value, deletion_point_in_time, head);
			return (SUCCESS);
		}
		head = hash_table[hash_index]->next_key;
	}

	// Creating new element
	Storage *newElement = (Storage*)malloc(sizeof(Storage));

	// Allocation check
	if (newElement == NULL) {
		printf(ERROR_MESSAGE);
		free(newElement); // Release allocated memory before return. 
		return(FAILURE); // Return failure but not affect the rest of the program
	}
	updateStorageData(key, value, deletion_point_in_time, newElement);
	push_element_success = pushElementToStartOfLinkedList(key, newElement, hash_table, size);
	return (SUCCESS);
}

void updateStorageData(const unsigned int key, const unsigned int value, const unsigned int deletion_point_in_time, Storage *new_element) {

	new_element->key = key;
	new_element->value = value;
	new_element->eviction = deletion_point_in_time;
	new_element->next_key = NULL;
}

const int pushElementToStartOfLinkedList(const unsigned int key, Storage *new_element, const Storage **hash_table, const unsigned int size) {
	
	int hash_index;
	hash_index = hashCode(key, size);
	if (hash_table[hash_index] == NULL) {
		hash_table[hash_index] = new_element;
		return (SUCCESS);
	}
	new_element->next_key = hash_table[hash_index];
	hash_table[hash_index] = new_element;
	return (SUCCESS);
}

const unsigned int retrieveKeyValue(const unsigned int key, const clock_t current_time_stamp, const Storage **hash_table, const const unsigned int size){
	int hash_index;
	//get the hash
	hash_index = hashCode(key, size);
	Storage *head = hash_table[hash_index];

	// Check if array is empty in hash_table in the hash_index
	if (head == NULL) {
		printf("No such a key %d in the storage\n", key);
		return (FAILURE);
	}
	while (head != NULL) // find the key in the linked list
		{
		if (head->eviction > current_time_stamp) { // eviction time not arrived yet 
			if (head->key == key) {
				return (head->value);
			}
			else {
				head = head->next_key;
			}
			if (head == NULL) {
				printf("No such a key %d in the storage\n", key);
				return (FAILURE);
			}
		}
		else {
			printf(EVICTION_TIME_PASSED_MESSEGE);
			return (FAILURE);
		}
	}
}

bool const isExist(const unsigned int key, const clock_t current_time_stamp, const Storage **hash_table, const unsigned int size) {
	int hash_index;
	//get the hash
	hash_index = hashCode(key, size);
	Storage *head = hash_table[hash_index];

	if (head == NULL) {
		return (false);
	}
	while (head != NULL) // find the key in the linked list
	{
		if (head->eviction > current_time_stamp) { // eviction time not arrived yet 
			if (head->key == key) {
				return (true);
			}
			else { // Not the key - move on to the next node in the list
				head = head->next_key;
			}
			if (head == NULL) { // end of linked list arrived
				return (false);
			}
		}
		else { // eviction time smaller than current_time_stamp
			printf(EVICTION_TIME_PASSED_MESSEGE);
			return (false);
		}
	}
}

const unsigned int freeHashTableAllocatedMemory(const Storage **hash_table, const unsigned int size) {
	int table_index;
	for (table_index = 0; table_index < size; table_index++) {
		if (hash_table[table_index] == NULL) {
			continue;
		}
		free(hash_table[table_index]);
	}
	return (SUCCESS);
}
