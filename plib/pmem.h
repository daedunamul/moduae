/*
	pmem
*/
#pragma once
#include "core/bst.h"
#include <stdlib.h>

// pool
struct pmem_Pool
{
	uint8_t Size , Length , Count ;
	void *Memory ;
	void **FreeStack ;
} ;

void* pmem_pool_create( uint8_t Size , uint8_t Length ) ;
void pmem_pool_delete( struct pmem_Pool **Pool ) ;
void* pmem_pool_allocate( struct pmem_Pool *Pool ) ;
bool pmem_pool_deallocate( struct pmem_Pool *Pool , void *Address ) ;

// manager
struct pmem_Manager
{
	uint32_t Count ;
	struct bst_Node *RootMemoryNode ;
} ;

enum bst_STATUS pmem_manager_judge( void *Key1 , void *Key2 ) ;
bool pmem_manager_insert( struct pmem_Manager *Manager , void *Address ) ;
bool pmem_manager_desert( struct pmem_Manager *Manager , void *Address ) ;
