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
	if( plibError != plibErrorNull )
		// plibError
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

struct plibDataHBST* emptydbObject_create( struct emptydbDB *DB , plibCommonAnyType *Key )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer || Key == plibCommonNullPointer )
		return plibCommonNullPointer ;
	
	plibCommonAnyType *NewMemory ;
	struct plibDataHBST *NewObjectNode ;
	
	// allocating memory
	NewMemory = plibMemoryPool_allocate( DB->ObjectNodePool ) ;
	if( NewMemory == plibCommonNullPointer )
		return plibCommonNullPointer ;
	
	// allocating node
	NewObjectNode = emptydbDB_referNodeFromMemory( NewMemory ) ;
	
	// initializing
	plibDataHBST_initialize( NewObjectNode ) ;
	
	// allocating key
	NewObjectNode->Key = emptydbDB_referKeyFromMemory( NewMemory ) ;
	
	// setting
	*( emptydbCommonKeyType* )NewObjectNode->Key = *( emptydbCommonKeyType* )Key ;
	
	NewObjectNode->SubLength = 2 ;
	NewObjectNode->Sub = emptydbDB_referSubFromMemory( NewMemory ) ;
	NewObjectNode->Sub[ emptydbPropertySubIndex ].Count = 0 ;
	NewObjectNode->Sub[ emptydbPropertySubIndex ].RootNode = plibCommonNullPointer ;
	NewObjectNode->Sub[ emptydbObjectSubIndex ].Count = 0 ;
	NewObjectNode->Sub[ emptydbObjectSubIndex ].RootNode = plibCommonNullPointer ;
	
	// pushing
	plibDataHBST_pushSub( DB->ObjectThisNode , emptydbObjectSubIndex , NewObjectNode , emptydbCommon_compareKey ) ;
	if( plibError == plibErrorNull )
		DB->ObjectCount ++ ;
	else
	{
		plibMemoryPool_deallocate( DB->ObjectNodePool , &NewMemory ) ;
		return plibCommonNullPointer ;
	}
	
	return NewObjectNode ;
}
void emptydbObject_createStream( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( Stream == plibCommonNullPointer )
		return ;
	
	plibCommonCountType Index ;
	
	for( Index = 0 ; Index < Stream->Count ; Index ++ )
		emptydbObject_create( DB , emptydbStream_refer( Stream , Index ) ) ;
}

bool emptydbObject_delete( struct emptydbDB *DB , plibCommonAnyType *Key )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer )
		return false ;
		
	struct plibDataHBST *ObjectNode = plibDataHBST_popSub( DB->ObjectThisNode , emptydbObjectSubIndex , Key , emptydbCommon_compareKey ) ;
	if( plibError != plibErrorNull )
		return false ;
	
	ObjectNode->Left = plibCommonNullPointer ;
	ObjectNode->Right = plibCommonNullPointer ;
	plibDataHBST_traverse( ObjectNode , emptydbObject_flushFx , ( plibCommonAnyType* )DB ) ;
	
	return true ;
}
void emptydbObject_deleteStream( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( Stream == plibCommonNullPointer )
		return ;
	
	plibCommonCountType Index ;
	
	for( Index = 0 ; Index < Stream->Count ; Index ++ )
		emptydbObject_delete( DB , emptydbStream_refer( Stream , Index ) ) ;
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

bool emptydbObject_pointStream( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( DB == plibCommonNullPointer || DB->ObjectRootNode == plibCommonNullPointer || Stream == plibCommonNullPointer )
	{
		DB->ObjectThisNode = plibCommonNullPointer ;
		return false ;
	}
		
	plibCommonCountType Index ;
	struct plibDataHBST *TempNode ;
	
	for( Index = 0 , TempNode = DB->ObjectRootNode ; Index < Stream->Count ; Index ++ )
	{
		TempNode = plibDataHBST_lookup( TempNode , emptydbStream_refer( Stream , Index ) , emptydbCommon_compareKey ) ;
		if( plibError != plibErrorNull )
		{
			DB->ObjectThisNode = plibCommonNullPointer ;
			return false ;
		}
		
		DB->ObjectThisNode = TempNode ;
		TempNode = TempNode->Sub[ emptydbObjectSubIndex ].RootNode ;
	}
	
	return true ;
}

struct plibDataHBST* emptydbObject_lookup( struct emptydbDB *DB , plibCommonAnyType *Key )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer )
		return plibCommonNullPointer ;
	
	struct plibDataHBST *Node = plibDataHBST_lookup( DB->ObjectThisNode->Sub[ emptydbObjectSubIndex ].RootNode , Key , emptydbCommon_compareKey ) ;
	if( plibError != plibErrorNull )
		return plibCommonNullPointer ;
	
	return Node ;
}
void emptydbObject_lookupStream( struct emptydbDB *DB , struct emptydbStream *InputStream , struct emptydbStream *OutputStream )
{
	if( InputStream == plibCommonNullPointer || OutputStream == plibCommonNullPointer )
		return ;
	
	plibCommonCountType Index ;
	struct plibDataHBST *Node ;
	
	emptydbStream_reset( OutputStream ) ;
	for( Index = 0 ; Index < InputStream->Count ; Index ++ )
	{
		Node = emptydbObject_lookup( DB , emptydbStream_refer( InputStream , Index ) ) ;
		if( Node != plibCommonNullPointer )
			emptydbStream_setNode( OutputStream , Node ) ;
	}
}