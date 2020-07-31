/*
	emptydb::DB
*/
#include "emptydbDB.h"

struct emptydbDB* emptydbDB_createDB( size_t ObjectMaxCount , size_t KeyValueMaxCount )
{
	if( ObjectMaxCount < 0 || KeyValueMaxCount < 0 )
		return plibStdTypeNullPointer ;
		
	struct emptydbDB *NewDB = ( struct emptydbDB* )malloc( sizeof( struct emptydbDB ) ) ;
	
	ObjectMaxCount ++ ; // Root Object
	
	NewDB->ObjectMaxCount = ObjectMaxCount ;
	NewDB->ObjectCount = 0 ;
	NewDB->KeyValueMaxCount = KeyValueMaxCount ;
	NewDB->KeyValueCount = 0 ;
	NewDB->ObjectRootNode = plibStdTypeNullPointer ;
	NewDB->ObjectThisNode = plibStdTypeNullPointer ;
	NewDB->ObjectNodePool = plibStdMemoryPool_createPool
	(
		sizeof( struct emptydbDB ) + sizeof( emptydbCommonKeyType ) + sizeof( struct emptydbDBObjectValueType ) ,
		ObjectMaxCount
	) ;
	NewDB->KeyValueNodePool = plibStdMemoryPool_createPool
	( 
		sizeof( struct emptydbDB ) + sizeof( emptydbCommonKeyType ) ,
		KeyValueMaxCount
	) ;
	
	return NewDB ;
}
bool emptydbDB_deleteDB( struct emptydbDB **DB )
{
	if( *DB == plibStdTypeNullPointer )
		return false ;
	
	if( ( *DB )->KeyValueNodePool == plibStdTypeNullPointer )
		plibStdMemoryPool_deletePool( &( *DB )->KeyValueNodePool ) ;
	if( ( *DB )->ObjectNodePool == plibStdTypeNullPointer )
		plibStdMemoryPool_deletePool( &( *DB )->ObjectNodePool ) ;
	free( *DB ) ;
	*DB = plibStdTypeNullPointer ;
	
	return true ;
}
