/*
	emptydb::Stream
*/
#include "emptydbStream.h"

struct emptydbStream* emptydbStream_create( plibCommonCountType Length , plibCommonCountType Size )
{
	if( Length == 0 || Size == 0 )
		return plibCommonNullPointer ;
	
	// allocating
	struct emptydbStream *NewStream = ( struct emptydbStream* )malloc( sizeof( struct emptydbStream ) ) ;
	if( NewStream == plibCommonNullPointer )
		return plibCommonNullPointer ;
	
	// setting
	NewStream->Length = Length ;
	NewStream->Size = Size ;
	NewStream->Count = 0 ;
	NewStream->Data = ( plibCommonAnyType* )malloc( Size * Length ) ;
	
	return NewStream ;
}
bool emptydbStream_delete( struct emptydbStream **Stream )
{
	if( Stream == plibCommonNullPointer || *Stream == plibCommonNullPointer )
		return false ;
	
	free( ( *Stream )->Data ) ;
	free( *Stream ) ;
	*Stream = plibCommonNullPointer ;
	
	return true ;
}

plibCommonAnyType* emptydbStream_refer( struct emptydbStream *Stream , plibCommonCountType Index )
{
	if( Stream == plibCommonNullPointer || Index >= Stream->Length )
		return plibCommonNullPointer ;
		
	return Stream->Data + ( plibCommonAnyType )( Stream->Size * Index ) ;
}

void emptydbStream_reset( struct emptydbStream *Stream )
{
	if( Stream == plibCommonNullPointer )
		return ;
	
	Stream->Count = 0 ;
}
void emptydbStream_setKey( struct emptydbStream *Stream , emptydbCommonKeyType Key )
{
	emptydbCommonKeyType *KeyPointer = ( emptydbCommonKeyType* )emptydbStream_refer( Stream , Stream->Count ) ;
	

	if( KeyPointer == plibCommonNullPointer )
		return ;
	
	*KeyPointer = Key ;
	Stream->Count ++ ;
}
void emptydbStream_setNode( struct emptydbStream *Stream , struct plibDataHBST *Node )
{
	struct plibDataHBST **NodePointer = ( struct plibDataHBST** )emptydbStream_refer( Stream , Stream->Count ) ;
	
	if( *NodePointer == plibCommonNullPointer )
		return ;
	
	*NodePointer = Node ;
	Stream->Count ++ ;
}