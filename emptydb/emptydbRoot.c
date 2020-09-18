/*
	emptydb::Root
*/
#include "emptydbRoot.h"

struct emptydbRoot* emptydbRoot_create( emptydbCommonCountType ObjectMaxCount , emptydbCommonCountType PropertyMaxCount )
{
	if( ObjectMaxCount == 0 || PropertyMaxCount == 0 )
		return plibStdTypeNullPointer ;
		
	struct emptydbRoot *NewRoot = ( struct emptydbRoot* )malloc( sizeof( struct emptydbRoot ) ) ;
	
	ObjectMaxCount ++ ; // Genesis Object
	
	NewRoot->ObjectMaxCount = ObjectMaxCount ;
	NewRoot->ObjectCount = 0 ;
	NewRoot->PropertyMaxCount = PropertyMaxCount ;
	NewRoot->PropertyCount = 0 ;
	NewRoot->ObjectNodePool = plibStdMemoryPool_createPool
	(
		sizeof( struct plibStdDataBST ) + sizeof( emptydbCommonKeyType ) + sizeof( struct emptydbCommonObjectValueType ) ,
		ObjectMaxCount
	) ;
	NewRoot->PropertyNodePool = plibStdMemoryPool_createPool
	( 
		sizeof( struct plibStdDataBST ) + sizeof( emptydbCommonKeyType ) + sizeof( struct emptydbCommonPropertyValueType ) ,
		PropertyMaxCount
	) ;
	NewRoot->ObjectGenesisNode = plibStdTypeNullPointer ;
	NewRoot->ObjectThisNode = plibStdTypeNullPointer ;
	NewRoot->PropertyThisNode = plibStdTypeNullPointer ;
	
	return NewRoot ;
}
bool emptydbRoot_delete( struct emptydbRoot **Root )
{
	if( *Root == plibStdTypeNullPointer )
		return false ;
	
	if( ( *Root )->PropertyNodePool == plibStdTypeNullPointer )
		plibStdMemoryPool_deletePool( &( *Root )->PropertyNodePool ) ;
	if( ( *Root )->ObjectNodePool == plibStdTypeNullPointer )
		plibStdMemoryPool_deletePool( &( *Root )->ObjectNodePool ) ;
	free( *Root ) ;
	*Root = plibStdTypeNullPointer ;
	
	return true ;
}