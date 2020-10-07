/*
	plib::Memory::Pool
*/
#include "plibMemoryPool.h"

void plibMemoryPool_initialize( struct plibMemoryPool *Pool )
{
	if( Pool == plibCommonNullPointer )
		return ;
		
	plibCommonAnyType *Address ;
	
	for( Pool->Count = 0 ; Pool->Count < Pool->MaxCount ; Pool->Count ++ )
	{
		Address = Pool->AddressStart + ( 1 + Pool->UnitSize ) * Pool->Count ;
		*Address = false ;
		Pool->AddressStack[ Pool->Count ] = Address ;
	}
}

struct plibMemoryPool* plibMemoryPool_create( plibCommonCountType UnitSize , plibCommonCountType MaxCount )
{
	if( UnitSize == 0 || MaxCount == 0 )
		return plibCommonNullPointer ;
		
	struct plibMemoryPool *NewPool = ( struct plibMemoryPool* )malloc( sizeof( struct plibMemoryPool ) ) ;

	NewPool->UnitSize = UnitSize ;
	NewPool->MaxCount = MaxCount ;
	NewPool->AddressStart = ( plibCommonAnyType* )malloc( ( 1 + UnitSize ) * MaxCount ) ;
	NewPool->AddressEnd = NewPool->AddressStart + ( 1 + UnitSize ) * ( MaxCount - 1 ) ;
	NewPool->AddressStack = ( plibCommonAnyType** )malloc( sizeof( plibCommonAnyType* ) * MaxCount ) ;
	plibMemoryPool_initialize( NewPool ) ;
	
	return NewPool ;
}
bool plibMemoryPool_delete( struct plibMemoryPool **Pool )
{
	if( *Pool == plibCommonNullPointer )
		return false ;
		
	free( ( *Pool )->AddressStack ) ;
	free( ( *Pool )->AddressStart ) ;
	free( *Pool ) ;
	*Pool = plibCommonNullPointer ;
	
	return true ;
}

plibCommonAnyType* plibMemoryPool_allocate( struct plibMemoryPool *Pool )
{
	if( Pool == plibCommonNullPointer || Pool->Count == 0 )
		return plibCommonNullPointer ;
		
	Pool->Count -- ;
	Pool->AddressStack[ Pool->Count ][ 0 ] = true ;
	
	return Pool->AddressStack[ Pool->Count ] + 1 ;
}
void plibMemoryPool_deallocate( struct plibMemoryPool *Pool , plibCommonAnyType **UsedAddress )
{
	if
	(
		Pool == plibCommonNullPointer
		||
		*UsedAddress < Pool->AddressStart || *UsedAddress > Pool->AddressEnd
		||
		*( *UsedAddress - 1 ) == false
	)
		return ;
		
	*( *UsedAddress - 1 ) = false ;
	Pool->AddressStack[ Pool->Count ] = *UsedAddress ;
	Pool->Count ++ ;
	*UsedAddress = plibCommonNullPointer ;
}