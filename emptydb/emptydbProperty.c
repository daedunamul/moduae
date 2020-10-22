/*
	emptydb::Property
*/
#include "emptydbProperty.h"

bool emptydbProperty_create( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer )
		return false ;
		
	plibCommonCountType Index ;
	plibCommonAnyType *NewMemory ;
	struct plibDataHBST *NewPropertyNode ;
	struct emptydbDBPropertyValueType *NewValue ;
	
	for( Index = 0 ; Index < Stream->Count ; Index ++ )
	{
		// allocating a node
		NewMemory = plibMemoryPool_allocate( DB->PropertyNodePool ) ;
		if( NewMemory == plibCommonNullPointer )
			return false ;
		
		NewPropertyNode = emptydbDB_referNodeFromMemory( NewMemory ) ;
		
		// initializing
		plibDataHBST_initialize( NewPropertyNode ) ;
		
		// allocating
		NewPropertyNode->Key = emptydbDB_referKeyFromMemory( NewMemory ) ;
		NewPropertyNode->Value = emptydbDB_referPropertyValueFromMemory( NewMemory ) ;
		
		// setting
		*( emptydbCommonKeyType* )NewPropertyNode->Key = *( emptydbCommonKeyType* )emptydbStream_refer( Stream , Index ) ;
		
		NewValue = ( struct emptydbDBPropertyValueType* )NewPropertyNode->Value ;
		NewValue->Type = 0 ;
		NewValue->Size = 0 ;
		NewValue->Length = 0 ;
		NewValue->Data = plibCommonNullPointer ;
		
		if( plibDataHBST_pushSub( DB->ObjectThisNode , emptydbPropertySubIndex , NewPropertyNode , emptydbCommon_compareKey ) )
			DB->PropertyCount ++ ;
		else
			plibMemoryPool_deallocate( DB->PropertyNodePool , &NewMemory ) ;
	}
	
	return true ;
}
bool emptydbProperty_delete( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer )
		return false ;
	
	plibCommonCountType Index ;
	struct plibDataHBST *PropertyNode ;
	
	for( Index = 0 ; Index < Stream->Count ; Index ++ )
	{
		PropertyNode = plibDataHBST_popSub( DB->ObjectThisNode , emptydbPropertySubIndex , emptydbStream_refer( Stream , Index ) , emptydbCommon_compareKey ) ;
		if( PropertyNode == plibCommonNullPointer )
			continue ;
		
		plibMemoryPool_deallocate( DB->PropertyNodePool , ( plibCommonAnyType** )( &PropertyNode ) ) ;
		DB->PropertyCount -- ;
	}
	
	return true ;
}

void emptydbProperty_lookup( struct emptydbDB *DB , struct emptydbStream *InputStream , struct emptydbStream *OutputStream )
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
			DB->ObjectThisNode->Sub[ emptydbPropertySubIndex ].RootNode ,
			emptydbStream_refer( InputStream , Index ) , 
			emptydbCommon_compareKey 
		) ;
		if( TempNode == plibCommonNullPointer )
			continue ;
		
		emptydbStream_setNode( OutputStream , TempNode ) ;
	}
	
	return ;
}