/*
	emptydb::Object
*/
#include "emptydbObject.h"

bool emptydbObject_createRoot( struct emptydbDB *DB , emptydbCommonKeyType Key )
{
	if( DB == plibCommonNullPointer || DB->ObjectRootNode != plibCommonNullPointer )
		return false ;
	
	// allocating a node
	plibCommonAnyType *NewMemory = plibMemoryPool_allocate( DB->ObjectNodePool ) ;
	if( NewMemory == plibCommonNullPointer )
		return false ;
	
	DB->ObjectRootNode = emptydbDB_referNodeFromMemory( NewMemory ) ;
	
	// initializing
	plibDataHBST_initialize( DB->ObjectRootNode ) ;
	
	// allocating
	DB->ObjectRootNode->Key = emptydbDB_referKeyFromMemory( NewMemory ) ;
	DB->ObjectRootNode->Sub = emptydbDB_referSubFromMemory( NewMemory ) ;
	
	// setting
	*( emptydbCommonKeyType* )DB->ObjectRootNode->Key = Key ;
	
	DB->ObjectRootNode->SubLength = 2 ;
	DB->ObjectRootNode->Sub[ emptydbPropertySubIndex ].Count = 0 ;
	DB->ObjectRootNode->Sub[ emptydbPropertySubIndex ].RootNode = plibCommonNullPointer ;
	DB->ObjectRootNode->Sub[ emptydbObjectSubIndex ].Count = 0 ;
	DB->ObjectRootNode->Sub[ emptydbObjectSubIndex ].RootNode = plibCommonNullPointer ;
	
	DB->ObjectCount = 1 ;
	
	return true ;
}
bool emptydbObject_deleteRoot( struct emptydbDB *DB )
{
	if( DB == plibCommonNullPointer || DB->ObjectRootNode == plibCommonNullPointer )
		return false ;
		
	DB->ObjectRootNode = plibCommonNullPointer ;
	DB->ObjectCount = 0 ;
	plibMemoryPool_initialize( DB->ObjectNodePool ) ;
	
	return true ;
}

struct plibDataHBST* emptydbObject_create( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer )
		return plibCommonNullPointer ;
	
	plibCommonCountType Index ;
	plibCommonAnyType *NewMemory ;
	struct plibDataHBST *NewObjectNode ;
	
	for( Index = 0 ; Index < Stream->Count ; Index ++ )
	{
		// allocating a node
		NewMemory = plibMemoryPool_allocate( DB->ObjectNodePool ) ;
		if( NewMemory == plibCommonNullPointer )
			return plibCommonNullPointer ;
		
		NewObjectNode = emptydbDB_referNodeFromMemory( NewMemory ) ;
		
		// initializing
		plibDataHBST_initialize( NewObjectNode ) ;
		
		// allocating
		NewObjectNode->Key = emptydbDB_referKeyFromMemory( NewMemory ) ;
		
		// setting
		*( emptydbCommonKeyType* )NewObjectNode->Key = *( emptydbCommonKeyType* )emptydbStream_refer( Stream , Index ) ;
		
		NewObjectNode->SubLength = 2 ;
		NewObjectNode->Sub = emptydbDB_referSubFromMemory( NewMemory ) ;
		NewObjectNode->Sub[ emptydbPropertySubIndex ].Count = 0 ;
		NewObjectNode->Sub[ emptydbPropertySubIndex ].RootNode = plibCommonNullPointer ;
		NewObjectNode->Sub[ emptydbObjectSubIndex ].Count = 0 ;
		NewObjectNode->Sub[ emptydbObjectSubIndex ].RootNode = plibCommonNullPointer ;
		
		if( plibDataHBST_pushSub( DB->ObjectThisNode , emptydbObjectSubIndex , NewObjectNode , emptydbCommon_compareKey ) )
			DB->ObjectCount ++ ;
		else
			plibMemoryPool_deallocate( DB->ObjectNodePool , &NewMemory ) ;
	}
	
	return NewObjectNode ;
}
bool emptydbObject_delete( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer )
		return false ;
	
	plibCommonCountType Index ;
	struct plibDataHBST *ObjectNode ;
	
	for( Index = 0 ; Index < Stream->Count ; Index ++ )
	{
		ObjectNode = plibDataHBST_popSub( DB->ObjectThisNode , emptydbObjectSubIndex , emptydbStream_refer( Stream , Index ) , emptydbCommon_compareKey ) ;
		if( ObjectNode == plibCommonNullPointer )
			continue ;
		
		ObjectNode->Left = plibCommonNullPointer ;
		ObjectNode->Right = plibCommonNullPointer ;
		plibDataHBST_traverse( ObjectNode , emptydbObject_flushFx , ( plibCommonAnyType* )DB ) ;
	}
	
	return true ;
}
void emptydbObject_flushFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data )
{
	struct emptydbDB *DB = ( struct emptydbDB* )Data ;
	
	switch( Index )
	{
		case emptydbPropertySubIndex :
			plibMemoryPool_deallocate( DB->PropertyNodePool , ( plibCommonAnyType** )( &TraversedNode ) ) ;
			DB->PropertyCount -- ;
		break ;
		case emptydbObjectSubIndex :
			plibMemoryPool_deallocate( DB->ObjectNodePool , ( plibCommonAnyType** )( &TraversedNode ) ) ;
			DB->ObjectCount -- ;
		break ;
	}
}

bool emptydbObject_point( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( DB == plibCommonNullPointer || DB->ObjectRootNode == plibCommonNullPointer )
	{
		DB->ObjectThisNode = plibCommonNullPointer ;
		return false ;
	}
		
	plibCommonCountType Index ;
	struct plibDataHBST *TempNode ;
	
	for( Index = 0 , TempNode = DB->ObjectRootNode ; Index < Stream->Count ; Index ++ )
	{
		TempNode = plibDataHBST_lookup( TempNode , emptydbStream_refer( Stream , Index ) , emptydbCommon_compareKey ) ;
		
		if( TempNode == plibCommonNullPointer )
		{
			DB->ObjectThisNode = plibCommonNullPointer ;
			return false ;
		}
		DB->ObjectThisNode = TempNode ;
		TempNode = TempNode->Sub[ emptydbObjectSubIndex ].RootNode ;
	}
	
	return true ;
}
void emptydbObject_lookup( struct emptydbDB *DB , struct emptydbStream *InputStream , struct emptydbStream *OutputStream )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer )
		return ;
	
	plibCommonCountType Index ;
	struct plibDataHBST *TempNode ;
	
	emptydbStream_reset( OutputStream ) ;
	for( Index = 0 ; Index < InputStream->Count ; Index ++ )
	{
		TempNode = plibDataHBST_lookup
		(
			DB->ObjectThisNode->Sub[ emptydbObjectSubIndex ].RootNode ,
			emptydbStream_refer( InputStream , Index ) ,
			emptydbCommon_compareKey
		) ;
		if( TempNode == plibCommonNullPointer )
			continue ;
		
		emptydbStream_setNode( OutputStream , TempNode ) ;
	}
}