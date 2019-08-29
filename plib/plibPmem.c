/*
	plib
	plibPmem
*/
#include "plibplibPmem.h"

// node pool
struct plibPmem_bst_Pool* plibPmem_bst_createPool( uint32_t MaxCount )
{
	if( MaxCount == 0 )
		return NULL ;
		
	struct plibPmem_bst_Pool *NewPool ;
	struct plibStdBST_Node *TempNode ;
	
	NewPool = ( struct plibPmem_bst_Pool* )malloc( sizeof( struct plibPmem_bst_Pool ) ) ;
	NewPool->MaxCount = MaxCount ;
	NewPool->Count = 0 ;
	NewPool->Entry = ( struct plibStdBST_Node* )malloc( sizeof( struct plibStdBST_Node ) ) ;
	NewPool->Entry->Left = NULL ;
	if( MaxCount > 1 )
	{
		for( MaxCount = 1 ; MaxCount != NewPool->MaxCount ; MaxCount ++ )
		{
			TempNode = NewPool->Entry ;
			NewPool->Entry = ( struct plibStdBST_Node* )malloc( sizeof( struct plibStdBST_Node ) ) ;
			NewPool->Entry->Left = TempNode ;
		}
	}
	
	return NewPool ;
}
bool plibPmem_bst_deletePool( struct plibPmem_bst_Pool **Pool )
{
	if( *Pool == NULL )
		return false ;
	
	struct plibStdBST_Node *TempNode ;
		
	for( TempNode = ( *Pool )->Entry ; TempNode != NULL ; TempNode = TempNode->Left )
		free( TempNode ) ;
	free( *Pool ) ;
	*Pool = NULL ;
	
	return true ;
}
struct plibStdBST_Node* plibPmem_bst_allocatePool( struct plibPmem_bst_Pool *Pool )
{
	if( Pool == NULL || Pool->Count == Pool->MaxCount )
		return NULL ;
		
	struct plibStdBST_Node *TempNode = Pool->Entry ;
	Pool->Entry = Pool->Entry->Left ;
	Pool->Count ++ ;
	
	TempNode->Key = NULL ;
	TempNode->Left = NULL ;
	TempNode->Right = NULL ;
	TempNode->Value = NULL ;
	
	return TempNode ;
}
void plibPmem_bst_deallocatePool( struct plibPmem_bst_Pool *Pool , struct plibStdBST_Node *Node )
{
	Node->Left = Pool->Entry ;
	Pool->Entry = Node ;
	Pool->Count -- ;
}

// manager
enum plibStdBST_STATUS plibPmem_manager_judge( void *Key1 , void *Key2 )
{
	if( Key1 < Key2 )
		return plibStdBST_status_LESS ;
	else if( Key1 > Key2 )
		return plibStdBST_status_GREAT ;
	else
		return plibStdBST_status_EQUAL ;
}
bool plibPmem_manager_insert( struct plibPmem_Manager *Manager , void *Address )
{
	struct plibStdBST_Node *NewNode = ( struct plibStdBST_Node* )malloc( sizeof( struct plibStdBST_Node ) ) ;
	bool Flag ;
	
	NewNode->Key = Address ;
	NewNode->Value = NULL ;
	NewNode->Left = NULL ;
	NewNode->Right = NULL ;
		
	Flag = bst_insert( &( Manager->RootMemoryNode ) , NewNode , plibPmem_manager_judge ) ;
	if( Flag == false )
		free( NewNode ) ;
	else
		Manager->Count ++ ;

	return Flag ;
}
bool plibPmem_manager_desert( struct plibPmem_Manager *Manager , void *Address )
{
	struct plibStdBST_Node *OldNode = bst_desert( &( Manager->RootMemoryNode ) , Address , plibPmem_manager_judge ) ;
	
	if( OldNode == NULL )
		return false ;
	else
	{
		free( OldNode ) ;
		Manager->Count -- ;
	}
	
	return true ;
}
