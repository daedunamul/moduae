/*
	pmem
*/
#pragma once
#include "core/bst.h"
#include <stdlib.h>

// bst pool
struct pmem_bst_Pool
{
	uint32_t MaxCount , Count ;
	struct bst_Node *Entry ;
} ;

struct pmem_bst_Pool* pmem_bst_createPool( uint32_t MaxCount ) ;
bool pmem_bst_deletePool( struct pmem_bst_Pool **Pool ) ;
struct bst_Node* pmem_bst_allocatePool( struct pmem_bst_Pool *Pool ) ;
void pmem_bst_deallocatePool( struct pmem_bst_Pool *Pool , struct bst_Node *Node ) ;

// manager
struct pmem_Manager
{
	uint32_t Count ;
	struct bst_Node *RootMemoryNode ;
} ;

enum bst_STATUS pmem_manager_judge( void *Key1 , void *Key2 ) ;
bool pmem_manager_insert( struct pmem_Manager *Manager , void *Address ) ;
bool pmem_manager_desert( struct pmem_Manager *Manager , void *Address ) ;
