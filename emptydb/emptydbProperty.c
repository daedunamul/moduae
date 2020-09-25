/*
	emptydb::Property
*/
#include "emptydbProperty.h"

bool emptydbProperty_create( struct emptydbRoot *Root , uint8_t *Stream )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer )
		return false ;
		
	emptydbCommonCountType Index ;
	uint8_t *NewMemory ;
	struct plibStdDataBST *NewPropertyNode ;
	struct emptydbCommonPropertyValueType *NewValue ;
	
	for( Index = 0 ; Index < emptydbStream_getTag( Stream , false ) ; Index ++ )
	{
		NewMemory = plbStdMemoryPool_allocate( Root->PropertyNodePool ) ;
		NewPropertyNode = emptydbCommon_referNode( NewMemory ) ;
		NewPropertyNode->Key = emptydbCommon_referKey( NewMemory ) ;
		NewPropertyNode->Value = emptydbCommon_referValue( NewMemory ) ;
		
		*( emptydbCommonKeyType* )NewPropertyNode->Key = *( emptydbCommonKeyType* )emptydbStream_pointData( Stream , Index ) ;
		NewPropertyNode->Left = plibStdTypeNullPointer ;
		NewPropertyNode->Right = plibStdTypeNullPointer ;
		
		NewValue = ( struct emptydbCommonPropertyValueType* )NewPropertyNode->Value ;
		NewValue->DataType = 0 ;
		NewValue->DataSize = 0 ;
		NewValue->DataLength = 0 ;
		NewValue->Data = plibStdTypeNullPointer ;
		
		if( plibStdDataBST_push( &( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberPropertyGenesisNode , NewPropertyNode , emptydbCommon_compareKey ) )
			Root->PropertyCount ++ ;
		else
			plbStdMemoryPool_deallocate( Root->PropertyNodePool , &NewMemory ) ;
	}
	
	return true ;
}
bool emptydbProperty_delete( struct emptydbRoot *Root , uint8_t *Stream )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer )
		return false ;
	
	emptydbCommonCountType Index ;
	struct plibStdDataBST *PropertyNode ;
	
	for( Index = 0 ; Index < emptydbStream_getTag( Stream , false ) ; Index ++ )
	{
		PropertyNode = plibStdDataBST_pop( &( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberPropertyGenesisNode , emptydbStream_pointData( Stream , Index ) , emptydbCommon_compareKey ) ;
		if( PropertyNode == plibStdTypeNullPointer )
			continue ;
		
		plbStdMemoryPool_deallocate( Root->PropertyNodePool , ( uint8_t** )( &PropertyNode ) ) ;
		Root->PropertyCount -- ;
	}
	
	return true ;
}
void emptydbProperty_flush( struct emptydbRoot *Root , struct plibStdDataBST *PropertyEntryNode )
{
	if( Root == plibStdTypeNullPointer || PropertyEntryNode == plibStdTypeNullPointer )
		return ;
	
	if( PropertyEntryNode->Left != plibStdTypeNullPointer )
		emptydbProperty_flush( Root , PropertyEntryNode->Left ) ;
	else if( PropertyEntryNode->Right != plibStdTypeNullPointer )
		emptydbProperty_flush( Root , PropertyEntryNode->Right ) ;
		
	plbStdMemoryPool_deallocate( Root->PropertyNodePool , ( uint8_t** )( &PropertyEntryNode ) ) ;
	Root->PropertyCount -- ;
}

emptydbCommonCountType emptydbProperty_lookup( struct emptydbRoot *Root , uint8_t *InputStream , uint8_t *OutputStream )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer )
		return 0 ;
		
	emptydbCommonCountType Index , Count ;
	struct plibStdDataBST *PropertThisNode ;
	
	for( Index = 0 , Count = 0 ; Index < emptydbStream_getTag( InputStream , false ) ; Index ++ )
	{
		PropertThisNode = plibStdDataBST_lookup
		( 
			( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberPropertyGenesisNode , 
			emptydbStream_pointData( InputStream , Index ) , 
			emptydbCommon_compareKey 
		) ;
		if( PropertThisNode == plibStdTypeNullPointer )
			continue ;
			
		*( struct plibStdDataBST** )( emptydbStream_pointData( OutputStream , Count ) ) = PropertThisNode ;
		Count ++ ;
	}
	
	return Count ;
}