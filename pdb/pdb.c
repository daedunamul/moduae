/*
	pdb
*/
#include "pdb.h"

// Query
struct pdbDB* pdbQuery_createDB( size_t QueryKeyMaxCount , size_t ObjectMaxCount , size_t KeyValueMaxCount )
{
	if( QueryKeyMaxCount == 0 || ObjectMaxCount == 0 || KeyValueMaxCount == 0 )
		return plibStdTypeNullPointer ;
		
	struct pdbDB *NewDB = ( struct pdbDB* )malloc( sizeof( struct pdbDB ) ) ;
	
	NewDB->QueryKeyMaxCount = QueryKeyMaxCount ;
	NewDB->QueryKeyCount = 0 ;
	NewDB->QueryResultCount = 0 ;
	NewDB->QueryKeyStack = ( pdbKeyType* )malloc( sizeof( pdbKeyType ) * QueryKeyMaxCount ) ;
	NewDB->QueryResultStack = ( struct plibStdDataBST** )malloc( sizeof( struct plibStdDataBST* ) * QueryKeyMaxCount ) ;
	
	NewDB->ObjectMaxCount = ObjectMaxCount ;
	NewDB->ObjectCount = 0 ;
	NewDB->KeyValueMaxCount = KeyValueMaxCount ;
	NewDB->KeyValueCount = 0 ;
	NewDB->ObjectRootNode = plibStdTypeNullPointer ;
	NewDB->ObjectThisNode = plibStdTypeNullPointer ;
	NewDB->ObjectNodePool = plibStdMemoryPool_createPool
	(
		sizeof( struct plibStdDataBST ) + sizeof( pdbKeyType ) + sizeof( struct pdbObjectValue ) ,
		ObjectMaxCount
	) ;
	NewDB->KeyValueNodePool = plibStdMemoryPool_createPool
	( 
		sizeof( struct plibStdDataBST ) + sizeof( pdbKeyType ) ,
		QueryKeyMaxCount
	) ;
	
	return NewDB ;
}
bool pdbQuery_deleteDB( struct pdbDB **DB )
{
	if( DB == plibStdTypeNullPointer )
		return false ;
	
	plibStdMemoryPool_deletePool( &( *DB )->KeyValueNodePool ) ;
	plibStdMemoryPool_deletePool( &( *DB )->ObjectNodePool ) ;
	free( ( *DB )->QueryResultStack ) ;
	free( ( *DB )->QueryKeyStack ) ;
	free( *DB ) ;
	*DB = plibStdTypeNullPointer ;
	
	return true ;
}

bool pdbQuery_pushStack( struct pdbDB *DB , pdbKeyType Key )
{
	if( DB == plibStdTypeNullPointer || DB->QueryKeyCount == DB->QueryKeyMaxCount )
		return false ;
	
	DB->QueryKeyStack[ DB->QueryKeyCount ] = Key ;
	DB->QueryKeyCount ++ ;
	
	return true ;
}
void pdbQuery_flushStack( struct pdbDB *DB )
{
	if( DB == plibStdTypeNullPointer )
		return ;
		
	DB->QueryKeyCount = 0 ;
}

bool pdbQuery_pointObject( struct pdbDB *DB )
{
	if( DB == plibStdTypeNullPointer )
		return false ;
	
	size_t Index ;
	struct plibStdDataBST *ThisNode ;
	
	for( Index = 0 , ThisNode = DB->ObjectRootNode ; Index < DB->QueryKeyCount ; Index ++ )
	{
		ThisNode = plibStdDataBST_lookup( ThisNode , ( uint8_t* )( DB->QueryKeyStack + Index ) , pdbQuery_compareKey ) ;
		if( ThisNode == plibStdTypeNullPointer )
		{
			DB->ObjectThisNode = plibStdTypeNullPointer ;
			return false ;
		}
		else
		{
			DB->ObjectThisNode = ThisNode ;
			ThisNode = ( ( struct pdbObjectValue* )ThisNode->Value )->MemberObjectRootNode ;
		}
	}
	
	return true ;
}
void pdbQuery_lookupObject( struct pdbDB *DB )
{
	if( DB == plibStdTypeNullPointer || DB->ObjectThisNode == plibStdTypeNullPointer )
		return ;
	
	size_t Index ;
	struct plibStdDataBST *ThisNode ;
	
	for( Index = 0 , DB->QueryResultCount = 0 ; Index < DB->QueryKeyCount ; Index ++ )
	{
		ThisNode = plibStdDataBST_lookup( DB->ObjectThisNode , ( uint8_t* )( DB->QueryKeyStack + Index ) , pdbQuery_compareKey ) ;
		if( ThisNode != plibStdTypeNullPointer )
		{
			DB->QueryResultStack[ DB->QueryResultCount ] = ThisNode ;
			DB->QueryResultCount ++ ;
		}
	}
}
void pdbQuery_createObject( struct pdbDB *DB )
{
	if
	(
		DB == plibStdTypeNullPointer
		||
		( DB->ObjectRootNode != plibStdTypeNullPointer && DB->ObjectThisNode == plibStdTypeNullPointer )
		||
		DB->ObjectCount >= DB->ObjectMaxCount
	)
		return ;
	
	size_t Index ;
	uint8_t *NewMemory ;
	struct plibStdDataBST *NewNode ;
	
	for( Index = 0 ; Index < DB->QueryKeyCount ; Index ++ )
	{
		NewMemory = plbStdMemoryPool_allocate( DB->ObjectNodePool ) ;
		NewNode = ( struct plibStdDataBST* )NewMemory ;
		NewNode->Left = plibStdTypeNullPointer ;
		NewNode->Right = plibStdTypeNullPointer ;
		NewNode->Key = NewMemory + sizeof( struct plibStdDataBST ) ;
		NewNode->Value = NewMemory + sizeof( struct plibStdDataBST ) + sizeof( pdbKeyType ) ;
		( ( struct pdbObjectValue* )NewNode->Value )->MemberObjectRootNode = plibStdTypeNullPointer ;
		( ( struct pdbObjectValue* )NewNode->Value )->MemberKeyValueRootNode = plibStdTypeNullPointer ;
		
		*( pdbKeyType* )NewNode->Key = DB->QueryKeyStack[ Index ] ;
		if( plibStdDataBST_push( &DB->ObjectThisNode , NewNode , pdbQuery_compareKey ) )
		{
			if( DB->ObjectRootNode == plibStdTypeNullPointer )
				DB->ObjectRootNode = DB->ObjectThisNode ;
			DB->ObjectCount ++ ;
		}
		else
			plbStdMemoryPool_deallocate( DB->ObjectNodePool , &NewMemory ) ;
	}
}
void pdbQuery_deleteObject( struct pdbDB *DB )
{
	
}

void pdbQuery_lookupKeyValue( struct pdbDB *DB )
{
	
}
void pdbQuery_createKeyValue( struct pdbDB *DB , uint8_t Type )
{
	
}
void pdbQuery_deleteKeyValue( struct pdbDB *DB )
{
	
}

enum plibStdDataBSTStatus pdbQuery_compareKey( uint8_t *Key1 , uint8_t *Key2 )
{
	if( *( pdbKeyType* )Key1 < *( pdbKeyType* )Key2 )
		return plibStdDataBSTStatusLess ;
	else if( *( pdbKeyType* )Key1 > *( pdbKeyType* )Key2 )
		return plibStdDataBSTStatusGreat ;
	return plibStdDataBSTStatusEqual ;
}
