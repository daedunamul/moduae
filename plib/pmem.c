/*
	pmem
*/
#include "pmem.h"

// pool
void* pmem_pool_create( uint8_t Size , uint8_t Length )
{
	if( Size == 0 || Length == 0 )
		return NULL ;
		
	struct pmem_Pool *NewPool = ( struct pmem_Pool* )malloc( sizeof( struct pmem_Pool ) ) ;
	
	NewPool->Size = Size ;
	NewPool->Length = Length ;
	NewPool->Memory = malloc( Size * Length ) ;
	NewPool->FreeStack = ( void** )malloc( sizeof( void* ) * Length ) ;
	
	if( NewPool->Memory == NULL )
	{
		free( NewPool ) ;
		return NULL ;
	}
	else if( NewPool->FreeStack == NULL )
	{
		free( NewPool ) ;
		free( NewPool->Memory ) ;
		return NULL ;
	}
	
	return NewPool ;
}
void pmem_pool_delete( struct pmem_Pool **Pool )
{
	if( *Pool == NULL )
		return ;
	
	free( ( *Pool )->FreeStack ) ;
	free( ( *Pool )->Memory ) ;
	free( *Pool ) ;
	
	*Pool = NULL ;
}
void* pmem_pool_allocate( struct pmem_Pool *Pool )
{
	if( Pool == NULL || Pool->Count == 0 )
		return NULL ;
		
	return Pool->FreeStack[ -- Pool->Count ] ;
}
bool pmem_pool_deallocate( struct pmem_Pool *Pool , void *Address )
{
	if( Pool == NULL || Pool->Count == Pool->Length )
		return false ;
	
	Pool->FreeStack[ Pool->Count ++ ] = Address ;
	return true ;
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
