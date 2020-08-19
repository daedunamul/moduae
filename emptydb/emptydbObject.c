/*
	emptydb::Object
*/
#include "emptydbObject.h"

bool emptydbObject_createRootObject( struct emptydbRoot *Root , emptydbCommonKeyType Key )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectRootNode != plibStdTypeNullPointer )
		return false ;
		
	uint8_t *NewMemory = plbStdMemoryPool_allocate( Root->ObjectNodePool ) ;
	
	if( NewMemory == plibStdTypeNullPointer )
		return false ;
	
	Root->ObjectRootNode = ( struct plibStdDataBST* )NewMemory ;
	Root->ObjectRootNode->Left = plibStdTypeNullPointer ;
	Root->ObjectRootNode->Right = plibStdTypeNullPointer ;
	Root->ObjectRootNode->Key = NewMemory + sizeof( struct plibStdDataBST ) ;
	Root->ObjectRootNode->Value = NewMemory + sizeof( struct plibStdDataBST ) + sizeof( emptydbCommonKeyType ) ;
	( ( struct emptydbCommonObjectValueType* )Root->ObjectRootNode->Value )->MemberObjectRootNode = plibStdTypeNullPointer ;
	( ( struct emptydbCommonObjectValueType* )Root->ObjectRootNode->Value )->MemberKeyValueRootNode = plibStdTypeNullPointer ;
	
	*( emptydbCommonKeyType* )Root->ObjectRootNode->Key = Key ;
	Root->ObjectCount = 1 ;
	
	return true ;
}
bool emptydbObject_deleteRootObject( struct emptydbRoot *Root )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectRootNode == plibStdTypeNullPointer )
		return false ;
		
	Root->ObjectRootNode = plibStdTypeNullPointer ;
	Root->ObjectCount = 0 ;
	plbStdMemoryPool_initialize( Root->ObjectNodePool ) ;
	
	return true ;
}

bool emptydbObject_createObject( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer || KeyCount == 0 || KeyArray == plibStdTypeNullPointer )
		return false ;
	
	size_t Index ;
	uint8_t *NewMemory ;
	struct plibStdDataBST *NewObjectNode ;
	
	for( Index = 0 ; Index < KeyCount ; Index ++ )
	{
		NewMemory = plbStdMemoryPool_allocate( Root->ObjectNodePool ) ;
		NewObjectNode = ( struct plibStdDataBST* )NewMemory ;
		NewObjectNode->Left = plibStdTypeNullPointer ;
		NewObjectNode->Right = plibStdTypeNullPointer ;
		NewObjectNode->Key = NewMemory + sizeof( struct plibStdDataBST ) ;
		NewObjectNode->Value = NewMemory + sizeof( struct plibStdDataBST ) + sizeof( emptydbCommonKeyType ) ; ;
		( ( struct emptydbCommonObjectValueType* )NewObjectNode->Value )->MemberObjectRootNode = plibStdTypeNullPointer ;
		( ( struct emptydbCommonObjectValueType* )NewObjectNode->Value )->MemberKeyValueRootNode = plibStdTypeNullPointer ;
		
		*( emptydbCommonKeyType* )NewObjectNode->Key = KeyArray[ Index ] ;
		if( plibStdDataBST_push( &( ( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberObjectRootNode ) , NewObjectNode , emptydbCommon_compareKey ) )
			Root->ObjectCount ++ ;
		else
			plbStdMemoryPool_deallocate( Root->ObjectNodePool , &NewMemory ) ;
	}
	
	return true ;
}
bool emptydbObject_deleteObject( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer || KeyCount == 0 || KeyArray == plibStdTypeNullPointer )
		return false ;
	
	size_t Index ;
	struct plibStdDataBST *ObjectNode ;
	
	for( Index = 0 ; Index < KeyCount ; Index ++ )
	{
		ObjectNode = plibStdDataBST_pop( &( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberObjectRootNode , ( uint8_t* )( KeyArray + Index ) , emptydbCommon_compareKey ) ;
		if( ObjectNode == plibStdTypeNullPointer )
			continue ;
		
		ObjectNode->Left = plibStdTypeNullPointer ;
		ObjectNode->Right = plibStdTypeNullPointer ;
		emptydbObject_flushObject( Root , ObjectNode ) ;
	}
	
	return true ;
}
void emptydbObject_flushObject( struct emptydbRoot *Root , struct plibStdDataBST *ObjectEntryNode )
{
	if( Root == plibStdTypeNullPointer || ObjectEntryNode == plibStdTypeNullPointer )
		return ;
	
	struct plibStdDataBST *TempObjectNode = ObjectEntryNode , *TempObjectMemberNode = ( ( struct emptydbCommonObjectValueType* )TempObjectNode->Value )->MemberObjectRootNode ;
	
	if( TempObjectMemberNode != plibStdTypeNullPointer )
		emptydbObject_flushObject( Root , TempObjectMemberNode ) ;
	else if( TempObjectNode->Left != plibStdTypeNullPointer )
		emptydbObject_flushObject( Root , TempObjectNode->Left ) ;
	else if( TempObjectNode->Right != plibStdTypeNullPointer )
		emptydbObject_flushObject( Root , TempObjectNode->Right ) ;
	
	emptydbKeyValue_flushKeyValue( Root , ( ( struct emptydbCommonObjectValueType* )TempObjectNode->Value )->MemberKeyValueRootNode ) ;
	plbStdMemoryPool_deallocate( Root->ObjectNodePool , ( uint8_t** )( &TempObjectNode ) ) ;
	Root->ObjectCount -- ;
}

bool emptydbObject_pointObject( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectRootNode == plibStdTypeNullPointer || KeyCount == 0 || KeyArray == plibStdTypeNullPointer )
	{
		Root->ObjectThisNode = plibStdTypeNullPointer ;
		return false ;
	}
		
	size_t Index ;
	struct plibStdDataBST *TempNode ;
	
	for( Index = 0 , TempNode = Root->ObjectRootNode ; Index < KeyCount ; Index ++ )
	{
		TempNode = plibStdDataBST_lookup( TempNode , ( uint8_t* )( KeyArray +Index ) , emptydbCommon_compareKey ) ;
		
		if( TempNode == plibStdTypeNullPointer )
		{
			Root->ObjectThisNode = plibStdTypeNullPointer ;
			return false ;
		}
		Root->ObjectThisNode = TempNode ;
		TempNode = ( ( struct emptydbCommonObjectValueType* )TempNode->Value )->MemberObjectRootNode ;
	}
	
	return true ;
}
size_t emptydbObject_lookupObject( struct emptydbRoot *Root , size_t KeyCount , emptydbCommonKeyType *KeyArray , struct plibStdDataBST **ResultObjectArray )
{
	if( Root == plibStdTypeNullPointer || Root->ObjectThisNode == plibStdTypeNullPointer || KeyCount == 0 || KeyArray == plibStdTypeNullPointer )
		return 0 ;
	
	size_t Index , Count ;
	struct plibStdDataBST *TempNode = ( ( struct emptydbCommonObjectValueType* )Root->ObjectThisNode->Value )->MemberObjectRootNode ;

	for( Index = 0 , Count = 0 ; Index < KeyCount ; Index ++ )
	{
		TempNode = plibStdDataBST_lookup( TempNode , ( uint8_t* )( KeyArray + Index ) , emptydbCommon_compareKey ) ;
		if( TempNode == plibStdTypeNullPointer )
			continue ;
		ResultObjectArray[ Count ] = TempNode ;
		Count ++ ;
	}
	
	return Count ;
}
