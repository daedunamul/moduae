/*
	plib::Std::Memory::Pool
*/
#include "plibStdMemoryPool.h"

void plbStdMemoryPool_initialize( struct plibStdMemoryPool *Pool )
{
	if( Pool == plibStdTypeNullPointer )
		return ;
		
	uint8_t *Address ;
	
	for( Pool->Count = 0 ; Pool->Count < Pool->MaxCount ; Pool->Count ++ )
	{
		Address = Pool->AddressStart + ( 1 + Pool->UnitSize ) * Pool->Count ;
		*Address = false ;
		Pool->AddressStack[ Pool->Count ] = Address ;
	}
}

struct plibStdMemoryPool* plibStdMemoryPool_createPool( size_t UnitSize , size_t MaxCount )
{
	if( UnitSize == 0 || MaxCount == 0 )
		return plibStdTypeNullPointer ;
		
	struct plibStdMemoryPool *NewPool = ( struct plibStdMemoryPool* )malloc( sizeof( struct plibStdMemoryPool ) ) ;

	NewPool->UnitSize = UnitSize ;
	NewPool->MaxCount = MaxCount ;
	NewPool->AddressStart = ( uint8_t* )malloc( ( 1 + UnitSize ) * MaxCount ) ;
	NewPool->AddressEnd = NewPool->AddressStart + ( 1 + UnitSize ) * ( MaxCount - 1 ) ;
	NewPool->AddressStack = ( uint8_t** )malloc( sizeof( uint8_t* ) * MaxCount ) ;
	plbStdMemoryPool_initialize( NewPool ) ;
	
	return NewPool ;
}
bool plibStdMemoryPool_deletePool( struct plibStdMemoryPool **Pool )
{
	if( *Pool == plibStdTypeNullPointer || ( *Pool )->MaxCount == 0 )
		return false ;
		
	free( ( *Pool )->AddressStack ) ;
	free( ( *Pool )->AddressStart ) ;
	free( *Pool ) ;
	*Pool = plibStdTypeNullPointer ;
	
	return true ;
}

uint8_t* plbStdMemoryPool_allocate( struct plibStdMemoryPool *Pool )
{
	if( Pool == plibStdTypeNullPointer || Pool->Count == 0 )
		return plibStdTypeNullPointer ;
		
	Pool->Count -- ;
	Pool->AddressStack[ Pool->Count ][ 0 ] = true ;
	
	return Pool->AddressStack[ Pool->Count ] + 1 ;
}
void plbStdMemoryPool_deallocate( struct plibStdMemoryPool *Pool , uint8_t **UsedAddress )
{
	if
	(
		Pool == plibStdTypeNullPointer
		||
		*UsedAddress < Pool->AddressStart || *UsedAddress > Pool->AddressEnd
		||
		*( *UsedAddress - 1 ) == false
	)
		return ;
		
	*( *UsedAddress - 1 ) = false ;
	Pool->AddressStack[ Pool->Count ] = *UsedAddress ;
	Pool->Count ++ ;
	*UsedAddress = plibStdTypeNullPointer ;
}
