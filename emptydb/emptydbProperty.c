/*
	emptydb::Property
*/
#include "emptydbProperty.h"

bool emptydbKeyValue_createKeyValue( struct emptydbRoot *Root , emptydbCommonCountType KeyCount , emptydbCommonKeyType *KeyArray , emptydbCommonCountType DataSize , emptydbCommonCountType DataLength )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer || KeyCount == 0 || KeyArray == plibStdTypeNullPointer || DataSize == 0 || DataLength == 0 )
		return false ;
	
	emptydbCommonCountType Index ;
	uint8_t *NewMemory ;
	struct plibStdDataBST *NewKeyValueNode ;
	struct emptydbCommonKeyValueType *NewValue ;
	
	for( Index = 0 ; Index < KeyCount ; Index ++ )
	{
		NewMemory = plbStdMemoryPool_allocate( Root->KeyValueNodePool ) ;
		NewKeyValueNode = ( struct plibStdDataBST* )NewMemory ;
		NewKeyValueNode->Key = NewMemory + sizeof( struct plibStdDataBST ) ;
		*( emptydbCommonKeyType* )NewKeyValueNode->Key = KeyArray[ Index ] ;
		NewKeyValueNode->Type = emptydbCommonNodeTypeKeyValue ;
		NewKeyValueNode->Value = NewMemory + sizeof( struct plibStdDataBST ) + sizeof( emptydbCommonKeyType ) ; ;
		NewKeyValueNode->Left = plibStdTypeNullPointer ;
		NewKeyValueNode->Right = plibStdTypeNullPointer ;

		NewValue = ( struct emptydbCommonKeyValueType* )NewKeyValueNode->Value ;
		NewValue->DataSize = DataSize ;
		NewValue->DataLength = DataLength ;
		//NewValue->Data = plibStdTypeNullPointer ;
		
		if( plibStdDataBST_push( &( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberKeyValueRootNode , NewKeyValueNode , emptydbCommon_compareKey ) )
			Root->KeyValueCount ++ ;
		else
			plbStdMemoryPool_deallocate( Root->KeyValueNodePool , &NewMemory ) ;
	}
	
	return true ;
}
bool emptydbKeyValue_deleteKeyValue( struct emptydbRoot *Root , emptydbCommonCountType KeyCount , emptydbCommonKeyType *KeyArray )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer || KeyCount == 0 || KeyArray == plibStdTypeNullPointer )
		return false ;
	
	emptydbCommonCountType Index ;
	struct plibStdDataBST *KeyValueNode ;
	
	for( Index = 0 ; Index < KeyCount ; Index ++ )
	{
		KeyValueNode = plibStdDataBST_pop( &( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberKeyValueRootNode , ( uint8_t* )( KeyArray + Index ) , emptydbCommon_compareKey ) ;
		if( KeyValueNode == plibStdTypeNullPointer )
			continue ;
		plbStdMemoryPool_deallocate( Root->KeyValueNodePool , ( uint8_t** )( &KeyValueNode ) ) ;
		Root->KeyValueCount -- ;
	}
	
	return true ;
}
void emptydbKeyValue_flushKeyValue( struct emptydbRoot *Root , struct plibStdDataBST *KeyValueEntryNode )
{
	if( Root == plibStdTypeNullPointer || KeyValueEntryNode == plibStdTypeNullPointer )
		return ;
	
	if( KeyValueEntryNode->Left != plibStdTypeNullPointer )
		emptydbKeyValue_flushKeyValue( Root , KeyValueEntryNode->Left ) ;
	else if( KeyValueEntryNode->Right != plibStdTypeNullPointer )
		emptydbKeyValue_flushKeyValue( Root , KeyValueEntryNode->Right ) ;
		
	plbStdMemoryPool_deallocate( Root->KeyValueNodePool , ( uint8_t** )( &KeyValueEntryNode ) ) ;
	Root->KeyValueCount -- ;
}

emptydbCommonCountType emptydbKeyValue_lookupKeyValue( struct emptydbRoot *Root , emptydbCommonCountType KeyCount , emptydbCommonKeyType *KeyArray , struct plibStdDataBST **ResultKeyValueArray )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer || KeyCount == 0 || KeyArray == plibStdTypeNullPointer )
		return 0 ;
		
	emptydbCommonCountType Index , Count ;
	struct plibStdDataBST *KeyValueRootNode = ( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberKeyValueRootNode , *KeyValueThisNode ;
	
	for( Index = 0 , Count = 0 ; Index < KeyCount ; Index ++ )
	{
		KeyValueThisNode = plibStdDataBST_lookup( KeyValueRootNode , ( uint8_t* )( KeyArray + Index ) , emptydbCommon_compareKey ) ;
		if( KeyValueThisNode == plibStdTypeNullPointer )
			continue ;
		ResultKeyValueArray[ Count ] = KeyValueThisNode ;
		Count ++ ;
	}
	
	return Count ;
}