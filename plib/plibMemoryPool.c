/*
	plib::Memory::Pool
*/
#include "plibMemoryPool.h"

void plibMemoryPool_initialize( struct plibMemoryPool *Pool , struct plibErrorType *Error )
{
	// error
	if( Pool == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorTypeParameter , plibMemoryPool_initialize ) ;
		return ;
	}
	
	plibCommonAnyType *Address ;
	
	for( Pool->Count = 0 ; Pool->Count < Pool->MaxCount ; Pool->Count ++ )
	{
		Address = Pool->AddressStart + ( 1 + Pool->UnitSize ) * Pool->Count ;
		*Address = false ;
		Pool->AddressStack[ Pool->Count ] = Address ;
	}
}

struct plibMemoryPool* plibMemoryPool_create( plibCommonCountType UnitSize , plibCommonCountType MaxCount , struct plibErrorType *Error )
{
	// error
	if( UnitSize == 0 || MaxCount == 0 )
	{
		plibError_report( Error , plibErrorTypeParameter , plibMemoryPool_create ) ;
		return plibCommonNullPointer ;
	}
	
	struct plibMemoryPool *NewPool ;
	
	// allocating
	NewPool = ( struct plibMemoryPool* )malloc( sizeof( struct plibMemoryPool ) ) ;
	if( NewPool == plibCommonNullPointer )
	{
		// error
		plibError_report( Error , plibErrorTypeProcess , plibMemoryPool_create ) ;
		return plibCommonNullPointer ;
	}
	NewPool->AddressStart = ( plibCommonAnyType* )malloc( ( 1 + UnitSize ) * MaxCount ) ;
	if( NewPool->AddressStart == plibCommonNullPointer )
	{
		// error
		free( NewPool ) ;
		plibError_report( Error , plibErrorTypeProcess , plibMemoryPool_create ) ;
		return plibCommonNullPointer ;
	}
	NewPool->AddressStack = ( plibCommonAnyType** )malloc( sizeof( plibCommonAnyType* ) * MaxCount ) ;
	if( NewPool->AddressStack == plibCommonNullPointer )
	{
		// error
		free( NewPool->AddressStart ) ;
		free( NewPool ) ;
		plibError_report( Error , plibErrorTypeProcess , plibMemoryPool_create ) ;
		return plibCommonNullPointer ;
	}
	
	// initializing
	NewPool->UnitSize = UnitSize ;
	NewPool->MaxCount = MaxCount ;
	NewPool->AddressEnd = NewPool->AddressStart + ( 1 + UnitSize ) * ( MaxCount - 1 ) ;
	plibMemoryPool_initialize( NewPool , Error ) ;
	
	return NewPool ;
}
void plibMemoryPool_delete( struct plibMemoryPool **Pool , struct plibErrorType *Error )
{
	// error
	if( Pool == plibCommonNullPointer || *Pool == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorTypeParameter , plibMemoryPool_delete ) ;
		return ;
	}
	
	free( ( *Pool )->AddressStack ) ;
	free( ( *Pool )->AddressStart ) ;
	free( *Pool ) ;
	*Pool = plibCommonNullPointer ;
	
	return ;
}

plibCommonAnyType* plibMemoryPool_allocate( struct plibMemoryPool *Pool , struct plibErrorType *Error )
{
	// error
	if( Pool == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorTypeParameter , plibMemoryPool_allocate ) ;
		return plibCommonNullPointer ;
	}	
	else if( Pool->Count == 0 )
	{
		plibError_report( Error , plibErrorTypeParameter , plibMemoryPool_allocate ) ;
		return plibCommonNullPointer ;
	}
	
	Pool->Count -- ;
	Pool->AddressStack[ Pool->Count ][ 0 ] = true ;
	
	return Pool->AddressStack[ Pool->Count ] + 1 ;
}
void plibMemoryPool_deallocate( struct plibMemoryPool *Pool , plibCommonAnyType **UsedAddress , struct plibErrorType *Error )
{
	// error
	if( Pool == plibCommonNullPointer || UsedAddress == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorTypeParameter , plibMemoryPool_deallocate ) ;
		return ;
	}	
	else if( *UsedAddress < Pool->AddressStart || *UsedAddress > Pool->AddressEnd )
	{
		plibError_report( Error , plibErrorTypeParameter , plibMemoryPool_deallocate ) ;
		return ;
	}
	else if( *( *UsedAddress - 1 ) == false )
	{
		plibError_report( Error , plibErrorTypeParameter , plibMemoryPool_deallocate ) ;
		return ;
	}
	
	*( *UsedAddress - 1 ) = false ;
	Pool->AddressStack[ Pool->Count ] = *UsedAddress ;
	Pool->Count ++ ;
	*UsedAddress = plibCommonNullPointer ;
}