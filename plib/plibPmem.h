/*
	plib
	plibPmem
*/
#pragma once
#include "Std/plibStdBST.h"
#include <stdlib.h>

// bst pool
struct plibPmem_bst_Pool
{
	uint32_t MaxCount , Count ;
	struct plibStdBST_Node *Entry ;
} ;

struct plibPmem_bst_Pool* plibPmem_bst_createPool( uint32_t MaxCount ) ;
bool plibPmem_bst_deletePool( struct plibPmem_bst_Pool **Pool ) ;
struct plibStdBST_Node* plibPmem_bst_allocatePool( struct plibPmem_bst_Pool *Pool ) ;
void plibPmem_bst_deallocatePool( struct plibPmem_bst_Pool *Pool , struct plibStdBST_Node *Node ) ;

// manager
struct plibPmem_Manager
{
	uint32_t Count ;
	struct plibStdBST_Node *RootMemoryNode ;
} ;

enum plibStdBST_STATUS plibPmem_manager_judge( void *Key1 , void *Key2 ) ;
bool plibPmem_manager_insert( struct plibPmem_Manager *Manager , void *Address ) ;
bool plibPmem_manager_desert( struct plibPmem_Manager *Manager , void *Address ) ;
