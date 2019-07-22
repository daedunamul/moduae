/*
	memory
*/
#pragma once
#include "bst.h"
#include <stdlib.h>

// pool
struct memory_Pool
{
	uint8_t Size , uint8_t Length ;
	void *Memory ;
} ;

bool memory_pool_create( struct memory_Pool *Pool , uint8_t Size , uint8_t Length ) ;
bool memory_pool_delete( struct memory_Pool *Pool ) ;

// manager
struct memory_Manager
{
	uint32_t Count ;
	struct bst_Node *RootMemoryNode ;
} ;

enum bst_STATUS memory_manager_judge( void *Key1 , void *Key2 ) ;
bool memory_manager_insert( struct memory_Manager *MemoryManager , void *Address ) ;
bool memory_manager_desert( struct memory_Manager *MemoryManager , void *Address ) ;
