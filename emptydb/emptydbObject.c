/*
	emptydb::Object
*/
#include "emptydbObject.h"

bool emptydbObject_createRoot( struct emptydbDB *DB , emptydbCommonKeyType Key )
{
	if( DB == plibCommonNullPointer || DB->ObjectRootNode != plibCommonNullPointer )
		return false ;
	
	plibCommonAnyType *NewMemory = plibMemoryPool_allocate( DB->ObjectNodePool ) ;
	
	if( NewMemory == plibCommonNullPointer )
		return false ;
	
	DB->ObjectRootNode = emptydbCommon_referNode( NewMemory ) ;
	DB->ObjectRootNode->Key = emptydbCommon_referKey( NewMemory ) ;
	DB->ObjectRootNode->Left = plibCommonNullPointer ;
	DB->ObjectRootNode->Right = plibCommonNullPointer ;
	DB->ObjectRootNode->Sub = emptydbCommon_referSub( NewMemory ) ;
	DB->ObjectRootNode->Sub->RootNodeArray = emptydbCommon_referSubRootArray( NewMemory ) ;
	
	*( emptydbCommonKeyType* )DB->ObjectRootNode->Key = Key ;
	DB->ObjectRootNode->Sub->Count = 0 ;
	DB->ObjectRootNode->Sub->Length = 2 ;
	*emptydbCommon_referSubProperty( DB->ObjectRootNode->Sub ) = plibCommonNullPointer ;
	*emptydbCommon_referSubObject( DB->ObjectRootNode->Sub ) = plibCommonNullPointer ;
	
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

bool emptydbObject_create( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer )
		return false ;
	
	plibCommonCountType Index ;
	plibCommonAnyType *NewMemory ;
	struct plibDataHBST *NewObjectNode ;
	
	for( Index = 0 ; Index < Stream->Count ; Index ++ )
	{
		NewMemory = plibMemoryPool_allocate( DB->ObjectNodePool ) ;
		
		if( NewMemory == plibCommonNullPointer )
			return false ;
		
		NewObjectNode = emptydbCommon_referNode( NewMemory ) ;
		NewObjectNode->Key = emptydbCommon_referKey( NewMemory ) ;
		NewObjectNode->Value = plibCommonNullPointer ;
		NewObjectNode->Left = plibCommonNullPointer ;
		NewObjectNode->Right = plibCommonNullPointer ;
		NewObjectNode->Sub = emptydbCommon_referSub( NewMemory ) ;
		NewObjectNode->Sub->RootNodeArray = emptydbCommon_referSubRootArray( NewMemory ) ;
		
		*( emptydbCommonKeyType* )NewObjectNode->Key = *( emptydbCommonKeyType* )emptydbStream_refer( Stream , Index ) ;
		NewObjectNode->Sub->Count = 0 ;
		NewObjectNode->Sub->Length = 2 ;
		*emptydbCommon_referSubProperty( NewObjectNode->Sub ) = plibCommonNullPointer ;
		*emptydbCommon_referSubObject( NewObjectNode->Sub ) = plibCommonNullPointer ;
		
		if( plibDataHBST_push( emptydbCommon_referSubObject( DB->ObjectThisNode->Sub ) , NewObjectNode , emptydbCommon_compareKey ) )
		{
			DB->ObjectCount ++ ;
			DB->ObjectThisNode->Sub->Count ++ ;
		}
		else
			plibMemoryPool_deallocate( DB->ObjectNodePool , &NewMemory ) ;
	}
	
	return true ;
}
bool emptydbObject_delete( struct emptydbDB *DB , struct emptydbStream *Stream )
{
	if( DB == plibCommonNullPointer || DB->ObjectThisNode == plibCommonNullPointer )
		return false ;
	
	plibCommonCountType Index ;
	struct plibDataHBST *ObjectNode ;
	
	for( Index = 0 ; Index < Stream->Count ; Index ++ )
	{
		ObjectNode = plibDataHBST_pop( emptydbCommon_referSubObject( DB->ObjectThisNode->Sub ) , emptydbStream_refer( Stream , Index ) , emptydbCommon_compareKey ) ;
		if( ObjectNode == plibCommonNullPointer )
			continue ;
		
		ObjectNode->Left = plibCommonNullPointer ;
		ObjectNode->Right = plibCommonNullPointer ;
		emptydbObject_flush( DB , ObjectNode ) ;
	}
	
	return true ;
}
void emptydbObject_flush( struct emptydbDB *DB , struct plibDataHBST *ObjectEntryNode )
{
	if( DB == plibCommonNullPointer || ObjectEntryNode == plibCommonNullPointer )
		return ;
	
	emptydbObject_flush( DB , *emptydbCommon_referSubObject( ObjectEntryNode->Sub ) ) ;
	emptydbObject_flush( DB , ObjectEntryNode->Left ) ;
	emptydbObject_flush( DB , ObjectEntryNode->Right ) ;
	
	emptydbProperty_flush( DB , *emptydbCommon_referSubProperty( ObjectEntryNode->Sub ) ) ;
	plibMemoryPool_deallocate( DB->ObjectNodePool , ( plibCommonAnyType** )( &ObjectEntryNode ) ) ;
	DB->ObjectCount -- ;
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
		TempNode = *emptydbCommon_referSubObject( TempNode->Sub ) ;
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
			*emptydbCommon_referSubObject( DB->ObjectThisNode->Sub ) ,
			emptydbStream_refer( InputStream , Index ) ,
			emptydbCommon_compareKey
		) ;
		if( TempNode == plibCommonNullPointer )
			continue ;
		
		emptydbStream_setNode( OutputStream , TempNode ) ;
	}
}