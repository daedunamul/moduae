/*
	emptydb::Property
*/
#include "emptydbProperty.h"

struct plibDataHBST* emptydbProperty_create( struct emptydbDB *DB , plibCommonAnyType *Key )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer || Key == plibCommonNullPointer )
		return plibCommonNullPointer ;
	
	plibCommonAnyType *NewMemory ;
	struct plibDataHBST *NewPropertyNode ;
	struct emptydbDBPropertyValueType *NewValue ;
	
	// allocating memory
	NewMemory = plibMemoryPool_allocate( DB->PropertyNodePool ) ;
	if( plibError != plibErrorNull )
		return plibCommonNullPointer ;
	
	// allocating node
	NewPropertyNode = emptydbDB_referNodeFromMemory( NewMemory ) ;
	
	// initializing
	plibDataHBST_initialize( NewPropertyNode ) ;
	
	// allocating key and value
	NewPropertyNode->Key = emptydbDB_referKeyFromMemory( NewMemory ) ;
	NewPropertyNode->Value = emptydbDB_referPropertyValueFromMemory( NewMemory ) ;
	
	// setting
	*( emptydbCommonKeyType* )NewPropertyNode->Key = *( emptydbCommonKeyType* )Key ;
	
	NewValue = ( struct emptydbDBPropertyValueType* )NewPropertyNode->Value ;
	NewValue->Type = 0 ;
	NewValue->Size = 0 ;
	NewValue->Length = 0 ;
	NewValue->Data = plibCommonNullPointer ;
	
	// pushing
	plibDataHBST_pushSub( DB->ObjectThisNode , emptydbPropertySubIndex , NewPropertyNode , emptydbCommon_compareKey ) ;
	if( plibError == plibErrorNull )
		DB->PropertyCount ++ ;
	else
	{
		plibMemoryPool_deallocate( DB->PropertyNodePool , &NewMemory ) ;
		return plibCommonNullPointer ;
	}
	
	return NewPropertyNode ;
}
void emptydbProperty_createStream( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( Stream == plibCommonNullPointer )
		return ;
	
	plibCommonCountType Index ;

	for( Index = 0 ; Index < Stream->Count ; Index ++ )
		emptydbProperty_create( DB , emptydbStream_refer( Stream , Index ) ) ;
}

bool emptydbProperty_delete( struct emptydbDB *DB , plibCommonAnyType *Key )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer )
		return false ;
	
	struct plibDataHBST *PropertyNode = plibDataHBST_popSub( DB->ObjectThisNode , emptydbPropertySubIndex , Key , emptydbCommon_compareKey ) ;
	if( plibError != plibErrorNull )
		return false ;
	
	plibMemoryPool_deallocate( DB->PropertyNodePool , ( plibCommonAnyType** )( &PropertyNode ) ) ;
	DB->PropertyCount -- ;
	
	return true ;
}
void emptydbProperty_deleteStream( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( Stream == plibCommonNullPointer )
		return ;
	
	plibCommonCountType Index ;
	
	for( Index = 0 ; Index < Stream->Count ; Index ++ )
		emptydbProperty_delete( DB , emptydbStream_refer( Stream , Index ) ) ;
}

struct plibDataHBST* emptydbProperty_lookup( struct emptydbDB *DB , plibCommonAnyType *Key )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer )
		return plibCommonNullPointer ;
	
	struct plibDataHBST *Node = plibDataHBST_lookup( DB->ObjectThisNode->Sub[ emptydbPropertySubIndex ].RootNode , Key , emptydbCommon_compareKey ) ;
	if( plibError != plibErrorNull )
		return plibCommonNullPointer ;
	
	return Node ;
}
void emptydbProperty_lookupStream( struct emptydbDB *DB , struct emptydbStream *InputStream , struct emptydbStream *OutputStream )
{
	if( InputStream == plibCommonNullPointer || OutputStream == plibCommonNullPointer )
		return ;
	
	plibCommonCountType Index ;
	struct plibDataHBST *Node ;
	
	emptydbStream_reset( OutputStream ) ;
	for( Index = 0 ; Index < InputStream->Count ; Index ++ )
	{
		Node = emptydbProperty_lookup( DB , emptydbStream_refer( InputStream , Index ) ) ;
		if( Node != plibCommonNullPointer )
			emptydbStream_setNode( OutputStream , Node ) ;
	}
}