/*
	emptydb::DB
*/
#include "emptydbDB.h"

struct emptydbDB* emptydbDB_create( plibCommonCountType ObjectMaxCount , plibCommonCountType PropertyMaxCount )
{
	if( ObjectMaxCount == 0 || PropertyMaxCount == 0 )
		return plibCommonNullPointer ;
		
	struct emptydbDB *NewDB = ( struct emptydbDB* )malloc( sizeof( struct emptydbDB ) ) ;
	
	NewDB->ObjectMaxCount = ObjectMaxCount ;
	NewDB->ObjectCount = 0 ;
	NewDB->PropertyMaxCount = PropertyMaxCount ;
	NewDB->PropertyCount = 0 ;
	NewDB->ObjectNodePool = plibMemoryPool_create
	(
		sizeof( struct plibDataHBST ) + sizeof( emptydbCommonKeyType ) + sizeof( struct plibDataHBSTSub ) * 2 ,
		ObjectMaxCount
	) ;
	NewDB->PropertyNodePool = plibMemoryPool_create
	( 
		sizeof( struct plibDataHBST ) + sizeof( emptydbCommonKeyType ) + sizeof( struct emptydbDBPropertyValueType ) ,
		PropertyMaxCount
	) ;
	NewDB->ObjectRootNode = plibCommonNullPointer ;
	NewDB->ObjectThisNode = plibCommonNullPointer ;
	NewDB->PropertyThisNode = plibCommonNullPointer ;
	
	return NewDB ;
}
bool emptydbDB_delete( struct emptydbDB **DB )
{
	if( *DB == plibCommonNullPointer )
		return false ;
	
	if( ( *DB )->PropertyNodePool != plibCommonNullPointer )
		plibMemoryPool_delete( &( *DB )->PropertyNodePool ) ;
	if( ( *DB )->ObjectNodePool != plibCommonNullPointer )
		plibMemoryPool_delete( &( *DB )->ObjectNodePool ) ;
	free( *DB ) ;
	*DB = plibCommonNullPointer ;
	
	return true ;
}