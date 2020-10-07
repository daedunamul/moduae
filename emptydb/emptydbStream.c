/*
	emptydb::Stream
*/
#include "emptydbStream.h"

struct emptydbStream* emptydbStream_create( plibCommonCountType Length , plibCommonCountType Size )
{
	struct emptydbStream *NewStream = ( struct emptydbStream* )malloc( sizeof( struct emptydbStream ) ) ;
	NewStream->Length = Length ;
	NewStream->Size = Size ;
	NewStream->Count = 0 ;
	NewStream->Data = ( plibCommonAnyType* )malloc( Size * Length ) ;
	
	return NewStream ;
}
bool emptydbStream_delete( struct emptydbStream **Stream )
{
	if( *Stream == plibCommonNullPointer )
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
	if( Stream != plibCommonNullPointer )
		Stream->Count = 0 ;
}
bool emptydbStream_setKey( struct emptydbStream *Stream , emptydbCommonKeyType Key )
{
	emptydbCommonKeyType *KeyPointer = ( emptydbCommonKeyType* )emptydbStream_refer( Stream , Stream->Count ) ;
	if( KeyPointer == plibCommonNullPointer )
		return false ;
	
	*KeyPointer = Key ;
	Stream->Count ++ ;
	return true ;
}
bool emptydbStream_setNode( struct emptydbStream *Stream , struct plibDataHBST *Node )
{
	struct plibDataHBST **NodePointer = ( struct plibDataHBST** )emptydbStream_refer( Stream , Stream->Count ) ;
	if( NodePointer == plibCommonNullPointer )
		return false ;
	
	*NodePointer = Node ;
	Stream->Count ++ ;
	return true ;
}