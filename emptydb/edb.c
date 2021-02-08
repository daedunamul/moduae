/*
	edb
	emptydb
*/
#include "edb.h"

void edb_initializeError( struct edbError *Error )
{
	if( Error == plibCommonNullPointer )
		return ;
	
	Error->Error = edbErrorNull ;
	plibError_initialize( &Error->InternalError ) ;
}
void edb_reportError( struct edbError *Error , enum edbErrorType ErrorConstant )
{
	if( Error == plibCommonNullPointer )
		return ;
	
	Error->Error = ErrorConstant ;
}

struct edbDB* edb_createDB( plibCommonCountType ObjectMaxCount , plibCommonCountType PropertyMaxCount , struct edbError *Error )
{
	// error
	if( ObjectMaxCount == 0 || PropertyMaxCount == 0 )
	{
		edb_reportError( Error , edbErrorDBCreationParameter ) ;
		return plibCommonNullPointer ;
	}
	
	// allocating
	// DB
	struct edbDB *NewDB = ( struct edbDB* )malloc( sizeof( struct edbDB ) ) ;
	if( NewDB == plibCommonNullPointer )
	{
		edb_reportError( Error , edbErrorDBCreationAllocation ) ;
		return plibCommonNullPointer ;
	}
	
	// NodePool
	NewDB->ObjectNodePool = plibMemoryPool_create( sizeof( struct plibDataHBST ) + sizeof( edbKeyType ) + sizeof( struct plibDataHBSTSub ) * 2 , ObjectMaxCount , &Error->InternalError ) ;
	if( NewDB->ObjectNodePool == plibCommonNullPointer )
	{
		edb_reportError( Error , edbErrorDBCreationAllocationObjectNodePool ) ;
		edb_deleteDB( &NewDB , Error ) ;
		return plibCommonNullPointer ;
	}
	NewDB->PropertyNodePool = plibMemoryPool_create( sizeof( struct plibDataHBST ) + sizeof( edbKeyType ) + sizeof( struct edbPropertyValue ) , PropertyMaxCount , &Error->InternalError ) ;
	if( NewDB->PropertyNodePool == plibCommonNullPointer )
	{
		edb_reportError( Error , edbErrorDBCreationAllocationPropertyNodePool ) ;
		edb_deleteDB( &NewDB , Error ) ;
		return plibCommonNullPointer ;
	}
	
	// setting
	// MaxCount
	NewDB->ObjectMaxCount = ObjectMaxCount ;
	NewDB->PropertyMaxCount = PropertyMaxCount ;
	NewDB->PropertyCount = 0 ;
	
	// allocating root object
	plibCommonAnyType *NewMemory = plibMemoryPool_allocate( NewDB->ObjectNodePool , &Error->InternalError ) ;
	
	// pointing root object
	NewDB->ObjectRootNode = ( struct plibDataHBST* )NewMemory ;
	
	// initializing root object
	plibDataHBST_initialize( NewDB->ObjectRootNode , &Error->InternalError ) ;
	
	// pointing root object
	NewDB->ObjectRootNode->Key = NewMemory + sizeof( struct plibDataHBST ) ;
	NewDB->ObjectRootNode->Sub = ( struct plibDataHBSTSub* )( NewMemory + sizeof( struct plibDataHBST ) + sizeof( edbKeyType ) ) ;
	
	// setting root object
	*( edbKeyType* )NewDB->ObjectRootNode->Key = 0 ;
	
	NewDB->ObjectRootNode->SubLength = 2 ;
	NewDB->ObjectRootNode->Sub[ edbNodeObject ].Count = 0 ;
	NewDB->ObjectRootNode->Sub[ edbNodeObject ].RootNode = plibCommonNullPointer ;
	NewDB->ObjectRootNode->Sub[ edbNodeProperty ].Count = 0 ;
	NewDB->ObjectRootNode->Sub[ edbNodeProperty ].RootNode = plibCommonNullPointer ;
	
	// ObjectCount
	NewDB->ObjectCount = 1 ;
	
	return NewDB ;
}
void edb_deleteDB( struct edbDB **DB , struct edbError *Error )
{
	// error
	if( DB == plibCommonNullPointer || *DB == plibCommonNullPointer )
	{
		edb_reportError( Error , edbErrorDBDeletionParameter ) ;
		return ;
	}
	
	// pool
	if( &( *DB )->PropertyNodePool != plibCommonNullPointer )
		plibMemoryPool_delete( &( *DB )->PropertyNodePool , &Error->InternalError ) ;
	if( &( *DB )->ObjectNodePool != plibCommonNullPointer )
		plibMemoryPool_delete( &( *DB )->ObjectNodePool , &Error->InternalError ) ;
	free( *DB ) ;
	*DB = plibCommonNullPointer ;
}

struct plibDataHBST* edb_createNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbError *Error )
{
	// error
	if( DB == plibCommonNullPointer || SuperObject == plibCommonNullPointer || SubNodeKey == plibCommonNullPointer )
	{
		edb_reportError( Error , edbErrorNodeCreationParameter ) ;
		return plibCommonNullPointer ;
	}
	
	plibCommonAnyType *NewMemory ;
	struct plibDataHBST *NewNode ;
	struct edbPropertyValue *NewValue ;
	time_t TempTime ;
	struct tm *TempTimeInfo ;
	
	// allocating memory
	NewMemory = SubNodeType ? plibMemoryPool_allocate( DB->PropertyNodePool , &Error->InternalError ) : plibMemoryPool_allocate( DB->ObjectNodePool , &Error->InternalError ) ;
	if( NewMemory == plibCommonNullPointer )
	{
		edb_reportError( Error , edbErrorNodeCreationAllocation ) ;
		return plibCommonNullPointer ;
	}
	
	// pointing node
	NewNode = ( struct plibDataHBST* )NewMemory ;
	
	// initializing
	plibDataHBST_initialize( NewNode , &Error->InternalError ) ;
	
	// pointing and setting key
	NewNode->Key = NewMemory + sizeof( struct plibDataHBST ) ;
	*( edbKeyType* )NewNode->Key = *( edbKeyType* )SubNodeKey ;
		
	if( SubNodeType )
	{
		// pointing and setting value
		NewNode->Value = NewMemory + sizeof( struct plibDataHBST ) + sizeof( edbKeyType ) ;
		NewValue = ( struct edbPropertyValue* )NewNode->Value ;
		NewValue->Type = 0 ;
		NewValue->Data = plibCommonNullPointer ;
		
		// setting value name
		TempTime = time( plibCommonNullPointer ) ;
		TempTimeInfo = localtime( &TempTime ) ;
		sprintf( NewValue->Name , "%d%02d%02d_%02d%02d%02d_%03d" , TempTimeInfo->tm_year + 1900 , TempTimeInfo->tm_mon + 1 , TempTimeInfo->tm_mday , TempTimeInfo->tm_hour , TempTimeInfo->tm_min , TempTimeInfo->tm_sec , DB->PropertyCount ) ;
		
		// pushing property
		if( plibDataHBST_pushSub( SuperObject , edbNodeProperty , NewNode , edbKey_compare , &Error->InternalError ) == true )
			DB->PropertyCount ++ ;
		else
		{
			edb_reportError( Error , edbErrorNodeCreationPushing ) ;
			plibMemoryPool_deallocate( DB->PropertyNodePool , &NewMemory , &Error->InternalError ) ;
			return plibCommonNullPointer ;
		}
	}
	else
	{
		// pointing and setting sub
		NewNode->SubLength = 2 ;
		NewNode->Sub = ( struct plibDataHBSTSub* )( NewMemory + sizeof( struct plibDataHBST ) + sizeof( edbKeyType ) ) ;
		NewNode->Sub[ edbNodeObject ].Count = 0 ;
		NewNode->Sub[ edbNodeObject ].RootNode = plibCommonNullPointer ;
		NewNode->Sub[ edbNodeProperty ].Count = 0 ;
		NewNode->Sub[ edbNodeProperty ].RootNode = plibCommonNullPointer ;
		
		// pushing object
		if( plibDataHBST_pushSub( SuperObject , edbNodeObject , NewNode , edbKey_compare , &Error->InternalError ) == true )
			DB->ObjectCount ++ ;
		else
		{
			edb_reportError( Error , edbErrorNodeCreationPushing ) ;
			plibMemoryPool_deallocate( DB->ObjectNodePool , &NewMemory , &Error->InternalError ) ;
			return plibCommonNullPointer ;
		}
	}
	
	return NewNode ;
}
void edb_deleteNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbError *Error )
{
	// error : do not delete root object from the sub of which the super node has root object
	if( DB == plibCommonNullPointer || SuperObject == plibCommonNullPointer || SubNodeKey == plibCommonNullPointer )
	{
		edb_reportError( Error , edbErrorNodeDeletionParameter ) ;
		return ;
	}
	
	struct plibDataHBST *Node ;
	
	switch( SubNodeType )
	{
		case false : 
			Node = plibDataHBST_popSub( SuperObject , edbNodeObject , SubNodeKey , edbKey_compare , &Error->InternalError ) ;
			if( Node == plibCommonNullPointer )
			{
				edb_reportError( Error , edbErrorNodeDeletionDeallocation ) ;
				return ;
			}
			
			Node->Left = plibCommonNullPointer ;
			Node->Right = plibCommonNullPointer ;
			plibDataHBST_traverse( Node , edb_flushNodeFx , ( plibCommonAnyType* )DB , &Error->InternalError ) ;
		break ;
		case true : 
			Node = plibDataHBST_popSub( SuperObject , edbNodeProperty , SubNodeKey , edbKey_compare , &Error->InternalError ) ;
			if( Node == plibCommonNullPointer )
			{
				edb_reportError( Error , edbErrorNodeDeletionDeallocation ) ;
				return ;
			}
			
			plibMemoryPool_deallocate( DB->PropertyNodePool , ( plibCommonAnyType** )( &Node ) , &Error->InternalError ) ;
			DB->PropertyCount -- ;
		break ;
	}
}
void edb_flushNodeFx( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data , struct plibErrorType *Error )
{
	struct edbDB *DB = ( struct edbDB* )Data ;
	
	switch( Index )
	{
		case edbNodeObject :
			plibMemoryPool_deallocate( DB->ObjectNodePool , ( plibCommonAnyType** )( &TraversedNode ) , Error ) ;
			DB->ObjectCount -- ;
		break ;
		case edbNodeProperty :
			plibMemoryPool_deallocate( DB->PropertyNodePool , ( plibCommonAnyType** )( &TraversedNode ) , Error ) ;
			DB->PropertyCount -- ;
		break ;
	}
}
struct plibDataHBST* edb_lookupNode( struct edbDB *DB , struct plibDataHBST *SuperObject , bool SubNodeType , plibCommonAnyType *SubNodeKey , struct edbError *Error )
{
	// error
	if( DB == plibCommonNullPointer || SuperObject == plibCommonNullPointer || SubNodeKey == plibCommonNullPointer )
	{
		edb_reportError( Error , edbErrorNodeDeletionParameter ) ;
		return plibCommonNullPointer ;
	}
	
	struct plibDataHBST *Node ;
	
	if( SubNodeType )
		Node = plibDataHBST_lookup( SuperObject->Sub[ edbNodeProperty ].RootNode , SubNodeKey , edbKey_compare , &Error->InternalError ) ;
	else
		Node = plibDataHBST_lookup( SuperObject->Sub[ edbNodeObject ].RootNode , SubNodeKey , edbKey_compare , &Error->InternalError ) ;
	if( Node == plibCommonNullPointer )
	{
		edb_reportError( Error , edbErrorNodeLookingupNothing ) ;
		return plibCommonNullPointer ;
	}
	
	return Node ;
}