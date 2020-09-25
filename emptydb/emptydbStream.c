/*
	emptydb::Stream
*/
#include "emptydbStream.h"

bool emptydbStream_verify( uint8_t *Stream )
{
	if( Stream == plibStdTypeNullPointer )
		return false ;
	
	// Null Tag = Stream Address + 2 + Length * Size
	if( Stream + 2 + *Stream * *( Stream + 1 ) != 0 )
		return false ;
	return true ;
}
uint8_t emptydbStream_getTag( uint8_t *Stream , bool Flag )
{
	// stream should be verified before get some data
	return Flag ? *( Stream + 1 ) : *Stream ; // False : Length , True : Size
}
void emptydbStream_setTag( uint8_t *Stream , uint8_t Value , bool Flag )
{
	// stream should be verified before set some data
	if( Flag )
		*( Stream + 1 ) = Value ; // True : Size
	else
		*Stream = Value ; // False : Length
}
uint8_t* emptydbStream_pointData( uint8_t *Stream , uint8_t Index )
{
	if( Index >= *Stream )
		return plibStdTypeNullPointer ;
	
	// stream should be verified before point a data
	return Stream + 2 + *( Stream + 1 ) * Index ;
}

uint8_t* emptydbStream_create( uint8_t Length , uint8_t Size )
{
	uint8_t *NewStream = ( uint8_t* )malloc( 2 + Length * Size + 1 ) ;
	*NewStream = Length ;
	*( NewStream + 1 ) = Size ;
	*( NewStream + 2 + Length * Size ) = 0 ;
	
	return NewStream ;
}
bool emptydbStream_delete( uint8_t **Stream )
{
	if( *Stream == plibStdTypeNullPointer )
		return false ;
	
	free( *Stream ) ;
	*Stream = plibStdTypeNullPointer ;
	return true ;
}