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
	struct emptydbCommonPropertyValueType *NewValue ;
	
	for( Index = 0 ; Index < Stream->Count ; Index ++ )
	{
		NewMemory = plibMemoryPool_allocate( DB->PropertyNodePool ) ;
		
		if( NewMemory == plibCommonNullPointer )
			return false ;
		
		NewPropertyNode = emptydbCommon_referNode( NewMemory ) ;
		NewPropertyNode->Key = emptydbCommon_referKey( NewMemory ) ;
		NewPropertyNode->Value = emptydbCommon_referPropertyValue( NewMemory ) ;
		NewPropertyNode->Left = plibCommonNullPointer ;
		NewPropertyNode->Right = plibCommonNullPointer ;
		NewPropertyNode->Sub = plibCommonNullPointer ;
		
		*( emptydbCommonKeyType* )NewPropertyNode->Key = *( emptydbCommonKeyType* )emptydbStream_refer( Stream , Index ) ;

		NewValue = ( struct emptydbCommonPropertyValueType* )NewPropertyNode->Value ;
		NewValue->Type = 0 ;
		NewValue->Size = 0 ;
		NewValue->Length = 0 ;
		NewValue->Data = plibCommonNullPointer ;
		
		if( plibDataHBST_push( emptydbCommon_referSubProperty( DB->ObjectThisNode->Sub ) , NewPropertyNode , emptydbCommon_compareKey ) )
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
		PropertyNode = plibDataHBST_pop( emptydbCommon_referSubProperty( DB->ObjectThisNode->Sub ) , emptydbStream_refer( Stream , Index ) , emptydbCommon_compareKey ) ;
		if( PropertyNode == plibCommonNullPointer )
			continue ;
		
		plibMemoryPool_deallocate( DB->PropertyNodePool , ( plibCommonAnyType** )( &PropertyNode ) ) ;
		DB->PropertyCount -- ;
	}
	
	return true ;
}
void emptydbProperty_flush( struct emptydbDB *DB , struct plibDataHBST *PropertyEntryNode )
{
	if( DB == plibCommonNullPointer || PropertyEntryNode == plibCommonNullPointer )
		return ;
	
	emptydbProperty_flush( DB , PropertyEntryNode->Left ) ;
	emptydbProperty_flush( DB , PropertyEntryNode->Right ) ;
		
	plibMemoryPool_deallocate( DB->PropertyNodePool , ( plibCommonAnyType** )( &PropertyEntryNode ) ) ;
	DB->PropertyCount -- ;
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
			*emptydbCommon_referSubProperty( DB->ObjectThisNode->Sub ) , 
			emptydbStream_refer( InputStream , Index ) , 
			emptydbCommon_compareKey 
		) ;
		if( TempNode == plibCommonNullPointer )
			continue ;
		
		emptydbStream_setNode( OutputStream , TempNode ) ;
	}
	
	return ;
}