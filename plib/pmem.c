/*
	pmem
*/
#include "pmem.h"

// node pool
struct pmem_bst_Pool* pmem_bst_createPool( uint32_t MaxCount )
{
	if( MaxCount == 0 )
		return NULL ;
		
	struct pmem_bst_Pool *NewPool ;
	struct bst_Node *TempNode ;
	
	NewPool = ( struct pmem_bst_Pool* )malloc( sizeof( struct pmem_bst_Pool ) ) ;
	NewPool->MaxCount = MaxCount ;
	NewPool->Count = 0 ;
	NewPool->Entry = ( struct bst_Node* )malloc( sizeof( struct bst_Node ) ) ;
	NewPool->Entry->Left = NULL ;
	if( MaxCount > 1 )
	{
		for( MaxCount = 1 ; MaxCount != NewPool->MaxCount ; MaxCount ++ )
		{
			TempNode = NewPool->Entry ;
			NewPool->Entry = ( struct bst_Node* )malloc( sizeof( struct bst_Node ) ) ;
			NewPool->Entry->Left = TempNode ;
		}
	}
	
	return NewPool ;
}
bool pmem_bst_deletePool( struct pmem_bst_Pool **Pool )
{
	if( *Pool == NULL )
		return false ;
	
	struct bst_Node *TempNode ;
		
	for( TempNode = ( *Pool )->Entry ; TempNode != NULL ; TempNode = TempNode->Left )
		free( TempNode ) ;
	free( *Pool ) ;
	*Pool = NULL ;
	
	return true ;
}
struct bst_Node* pmem_bst_allocatePool( struct pmem_bst_Pool *Pool )
{
	if( Pool == NULL || Pool->Count == Pool->MaxCount )
		return NULL ;
		
	struct bst_Node *TempNode = Pool->Entry ;
	Pool->Entry = Pool->Entry->Left ;
	Pool->Count ++ ;
	
	TempNode->Key = NULL ;
	TempNode->Left = NULL ;
	TempNode->Right = NULL ;
	TempNode->Value = NULL ;
	
	return TempNode ;
}
void pmem_bst_deallocatePool( struct pmem_bst_Pool *Pool , struct bst_Node *Node )
{
	Node->Left = Pool->Entry ;
	Pool->Entry = Node ;
	Pool->Count -- ;
}

// manager
enum bst_STATUS pmem_manager_judge( void *Key1 , void *Key2 )
{
	if( Key1 < Key2 )
		return bst_status_LESS ;
	else if( Key1 > Key2 )
		return bst_status_GREAT ;
	else
		return bst_status_EQUAL ;
}
bool pmem_manager_insert( struct pmem_Manager *Manager , void *Address )
{
	struct bst_Node *NewNode = ( struct bst_Node* )malloc( sizeof( struct bst_Node ) ) ;
	bool Flag ;
	
	NewNode->Key = Address ;
	NewNode->Value = NULL ;
	NewNode->Left = NULL ;
	NewNode->Right = NULL ;
		
	Flag = bst_insert( &( Manager->RootMemoryNode ) , NewNode , pmem_manager_judge ) ;
	if( Flag == false )
		free( NewNode ) ;
	else
		Manager->Count ++ ;

	return Flag ;
}
bool pmem_manager_desert( struct pmem_Manager *Manager , void *Address )
{
	struct bst_Node *OldNode = bst_desert( &( Manager->RootMemoryNode ) , Address , pmem_manager_judge ) ;
	
	if( OldNode == NULL )
		return false ;
	else
	{
		free( OldNode ) ;
		Manager->Count -- ;
	}
	
	return true ;
}
