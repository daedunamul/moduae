/*
	plib::Std::Memory::Pool
*/
#include "plibStdMemoryPool.h"

struct plibStdMemoryPool* plibStdMemoryPool_createPool( size_t UnitSize , size_t MaxCount )
{
	if( UnitSize == 0 || MaxCount == 0 )
		return plibStdTypeNullPointer ;
		
	struct plibStdMemoryPool *NewPool = ( struct plibStdMemoryPool* )malloc( sizeof( struct plibStdMemoryPool ) ) ;
	
	NewPool->UnitSize = UnitSize ;
	NewPool->MaxCount = MaxCount ;
	NewPool->UsageCount = 0 ;
	NewPool->Data = ( uint8_t* )malloc( UnitSize * MaxCount ) ;
	
	return NewPool ;
}
bool plibStdMemoryPool_deletePool( struct plibStdMemoryPool **Pool )
{
	if( *Pool == plibStdTypeNullPointer )
		return false ;
		
	free( ( *Pool )->Data ) ;
	free( *Pool ) ;
	*Pool = plibStdTypeNullPointer ;
	
	return true ;
}

uint8_t* plbStdMemoryPool_allocate( struct plibStdMemoryPool *Pool )
{
	if( Pool == plibStdTypeNullPointer || Pool->UsageCount == Pool->MaxCount )
		return plibStdTypeNullPointer ;
	Pool->UsageCount ++ ;
	
	return Pool->Data + ( Pool->UsageCount - 1 ) * Pool->UnitSize ;
}
void plbStdMemoryPool_flush( struct plibStdMemoryPool *Pool )
{
	if( Pool == plibStdTypeNullPointer )
		return ;
	
	Pool->UsageCount = 0 ;
}
