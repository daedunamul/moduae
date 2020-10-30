/*
	emptydb::DB
*/
#include "emptydbDB.h"

struct emptydbDB* emptydbDB_create( plibCommonCountType ObjectMaxCount , plibCommonCountType PropertyMaxCount )
{
	if( ObjectMaxCount == 0 || PropertyMaxCount == 0 )
		return plibCommonNullPointer ;
		
	// allocating
	struct emptydbDB *NewDB = ( struct emptydbDB* )malloc( sizeof( struct emptydbDB ) ) ;
	if( NewDB == plibCommonNullPointer )
		return plibCommonNullPointer ;
	NewDB->ObjectNodePool = plibMemoryPool_create
	(
		sizeof( struct plibDataHBST ) + sizeof( emptydbCommonKeyType ) + sizeof( struct plibDataHBSTSub ) * 2 ,
		ObjectMaxCount
	) ;
	if( plibError != plibErrorNull )
	{
		free( NewDB ) ;
		return plibCommonNullPointer ;
	}
	NewDB->PropertyNodePool = plibMemoryPool_create
	( 
		sizeof( struct plibDataHBST ) + sizeof( emptydbCommonKeyType ) + sizeof( struct emptydbDBPropertyValueType ) ,
		PropertyMaxCount
	) ;
	if( plibError != plibErrorNull )
	{
		free( NewDB->ObjectNodePool ) ;
		free( NewDB ) ;
		return plibCommonNullPointer ;
	}
	
	// setting
	NewDB->ObjectMaxCount = ObjectMaxCount ;
	NewDB->ObjectCount = 0 ;
	NewDB->PropertyMaxCount = PropertyMaxCount ;
	NewDB->PropertyCount = 0 ;
	NewDB->ObjectRootNode = plibCommonNullPointer ;
	NewDB->ObjectThisNode = plibCommonNullPointer ;
	
	return NewDB ;
}
bool emptydbDB_delete( struct emptydbDB **DB )
{
	if( DB == plibCommonNullPointer || *DB == plibCommonNullPointer )
		return false ;
	
	if( ( *DB )->PropertyNodePool != plibCommonNullPointer )
		plibMemoryPool_delete( &( *DB )->PropertyNodePool ) ;
	if( ( *DB )->ObjectNodePool != plibCommonNullPointer )
		plibMemoryPool_delete( &( *DB )->ObjectNodePool ) ;
	free( *DB ) ;
	*DB = plibCommonNullPointer ;
	
	return true ;
}