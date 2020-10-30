/*
	plib::Memory::Pool
*/
#include "plibMemoryPool.h"

void plibMemoryPool_initialize( struct plibMemoryPool *Pool )
{
	// plibError
	if( Pool == plibCommonNullPointer )
	{
		plibError = plibErrorParameterNull ;
		return ;
	}
	else
		plibError = plibErrorNull ;
	
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
	// plibError
	if( UnitSize == 0 || MaxCount == 0 )
	{
		plibError = plibErrorParameterViolation ;
		return plibCommonNullPointer ;
	}
	else
		plibError = plibErrorNull ;
	
	struct plibMemoryPool *NewPool ;
	
	// allocating
	NewPool = ( struct plibMemoryPool* )malloc( sizeof( struct plibMemoryPool ) ) ;
	if( NewPool == plibCommonNullPointer )
	{
		// plibError
		plibError = plibMemoryErrorAllocation ;
		return plibCommonNullPointer ;
	}
	NewPool->AddressStart = ( plibCommonAnyType* )malloc( ( 1 + UnitSize ) * MaxCount ) ;
	if( NewPool->AddressStart == plibCommonNullPointer )
	{
		// plibError
		free( NewPool ) ;
		plibError = plibMemoryErrorAllocation ;
		return plibCommonNullPointer ;
	}
	NewPool->AddressStack = ( plibCommonAnyType** )malloc( sizeof( plibCommonAnyType* ) * MaxCount ) ;
	if( NewPool->AddressStack == plibCommonNullPointer )
	{
		// plibError
		free( NewPool->AddressStart ) ;
		free( NewPool ) ;
		plibError = plibMemoryErrorAllocation ;
		return plibCommonNullPointer ;
	}
	
	// initializing
	NewPool->UnitSize = UnitSize ;
	NewPool->MaxCount = MaxCount ;
	NewPool->AddressEnd = NewPool->AddressStart + ( 1 + UnitSize ) * ( MaxCount - 1 ) ;
	plibMemoryPool_initialize( NewPool ) ;
	
	return NewPool ;
}
void plibMemoryPool_delete( struct plibMemoryPool **Pool )
{
	// plibError
	if( Pool == plibCommonNullPointer || *Pool == plibCommonNullPointer )
	{
		plibError = plibErrorParameterNull ;
		return ;
	}
	else
		plibError = plibErrorNull ;
	
	free( ( *Pool )->AddressStack ) ;
	free( ( *Pool )->AddressStart ) ;
	free( *Pool ) ;
	*Pool = plibCommonNullPointer ;
	
	return ;
}

plibCommonAnyType* plibMemoryPool_allocate( struct plibMemoryPool *Pool )
{
	// plibError
	if( Pool == plibCommonNullPointer )
	{
		plibError = plibErrorParameterNull ;
		return plibCommonNullPointer ;
	}	
	else if( Pool->Count == 0 )
	{
		plibError = plibMemoryErrorOutOfCount ;
		return plibCommonNullPointer ;
	}
	else
		plibError = plibErrorNull ;
	
	Pool->Count -- ;
	Pool->AddressStack[ Pool->Count ][ 0 ] = true ;
	
	return Pool->AddressStack[ Pool->Count ] + 1 ;
}
void plibMemoryPool_deallocate( struct plibMemoryPool *Pool , plibCommonAnyType **UsedAddress )
{
	// plibError
	if( Pool == plibCommonNullPointer || UsedAddress == plibCommonNullPointer )
	{
		plibError = plibErrorParameterNull ;
		return ;
	}	
	else if( *UsedAddress < Pool->AddressStart || *UsedAddress > Pool->AddressEnd )
	{
		plibError = plibErrorReferenceViolation ;
		return ;
	}
	else if( *( *UsedAddress - 1 ) == false )
	{
		plibError = plibMemoryErrorDoubleFreeing ;
		return ;
	}
	else
		plibError = plibErrorNull ;
	
	*( *UsedAddress - 1 ) = false ;
	Pool->AddressStack[ Pool->Count ] = *UsedAddress ;
	Pool->Count ++ ;
	*UsedAddress = plibCommonNullPointer ;
}