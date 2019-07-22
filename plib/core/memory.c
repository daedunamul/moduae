/*
	memory
*/
#include "memory.h"

// pool
bool memory_pool_create( struct memory_Pool *Pool , uint8_t Size , uint8_t Length )
{
	if( Pool != NULL || Size = 0 || Length == 0 )
		return false ;
	
	Pool->Size = Size ;
	Pool->Length = Length ;
	Pool->Memory = malloc( Size * Length ) ;
	
	return true ;
}
bool memory_pool_delete( struct memory_Pool *Pool )
{
	if( Pool == NULL )
		return false ;
	
	free( Pool->Memory ) ;
	
	return true ;
}

// manager
enum bst_STATUS memory_manager_judge( void *Key1 , void *Key2 )
{
	if( Key1 < Key2 )
		return bst_status_LESS ;
	else if( Key1 > Key2 )
		return bst_status_GREAT ;
	else
		return bst_status_EQUAL ;
}
bool memory_manager_insert( struct memory_Manager *MemoryManager , void *Address )
{
	struct bst_Node *NewNode = ( struct bst_Node* )malloc( sizeof( struct bst_Node ) ) ;
	bool Flag ;
	
	NewNode->Key = Address ;
	NewNode->Value = NULL ;
	NewNode->Left = NULL ;
	NewNode->Right = NULL ;
		
	Flag = bst_insert( &( MemoryManager->RootMemoryNode ) , NewNode , memory_manager_judge ) ;
	if( Flag == false )
		free( NewNode ) ;

	return Flag ;
}
bool memory_manager_desert( struct memory_Manager *MemoryManager , void *Address )
{
	struct bst_Node *OldNode = bst_desert( &( MemoryManager->RootMemoryNode ) , Address , memory_manager_judge ) ;
	
	if( OldNode == NULL )
		return false ;
	else
		free( OldNode ) ;
	
	return true ;
}
