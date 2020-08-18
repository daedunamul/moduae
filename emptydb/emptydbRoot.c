/*
	emptydb::Root
*/
#include "emptydbRoot.h"

struct emptydbRoot* emptydbRoot_create( size_t ObjectMaxCount , size_t KeyValueMaxCount )
{
	if( ObjectMaxCount == 0 || KeyValueMaxCount == 0 )
		return plibStdTypeNullPointer ;
		
	struct emptydbRoot *NewRoot = ( struct emptydbRoot* )malloc( sizeof( struct emptydbRoot ) ) ;
	
	ObjectMaxCount ++ ; // Root Object
	
	NewRoot->ObjectMaxCount = ObjectMaxCount ;
	NewRoot->ObjectCount = 0 ;
	NewRoot->KeyValueMaxCount = KeyValueMaxCount ;
	NewRoot->KeyValueCount = 0 ;
	NewRoot->ObjectRootNode = plibStdTypeNullPointer ;
	NewRoot->ObjectThisNode = plibStdTypeNullPointer ;
	NewRoot->ObjectNodePool = plibStdMemoryPool_createPool
	(
		sizeof( struct plibStdDataBST ) + sizeof( emptydbCommonKeyType ) + sizeof( struct emptydbCommonObjectValueType ) ,
		ObjectMaxCount
	) ;
	NewRoot->KeyValueNodePool = plibStdMemoryPool_createPool
	( 
		sizeof( struct plibStdDataBST ) + sizeof( emptydbCommonKeyType ) ,
		KeyValueMaxCount
	) ;
	
	return NewRoot ;
}
bool emptydbRoot_delete( struct emptydbRoot **Root )
{
	if( *Root == plibStdTypeNullPointer )
		return false ;
	
	if( ( *Root )->KeyValueNodePool == plibStdTypeNullPointer )
		plibStdMemoryPool_deletePool( &( *Root )->KeyValueNodePool ) ;
	if( ( *Root )->ObjectNodePool == plibStdTypeNullPointer )
		plibStdMemoryPool_deletePool( &( *Root )->ObjectNodePool ) ;
	free( *Root ) ;
	*Root = plibStdTypeNullPointer ;
	
	return true ;
}
