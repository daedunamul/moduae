/* 
	pmem
	
	no check for memory validation
*/ 

#include "pmem.h"

struct pmem_Pool* pmem_create( uint8_t Size , uint8_t Length )
{	
	struct pmem_Pool *Pool = ( struct pmem_Pool* )malloc( sizeof( struct pmem_Pool ) ) ;
	Pool->Size = Size ; 
	Pool->Length = Length ;
	Pool->Memory = ( void** )malloc( sizeof( void* ) * Length ) ;
	for( Pool->Count = 0 ; Pool->Count < Length ; Pool->Count ++ )
		Pool->Memory[ Pool->Count ] = malloc( Size ) ;
	Pool->Count = 0 ;
	
	return Pool ;
}
void pmem_delete( struct pmem_Pool **Pool )
{	
	for( ( *Pool )->Count = 0 ; ( *Pool )->Count < ( *Pool )->Length ; ( *Pool )->Count ++ )
		free( ( *Pool )->Memory[ ( *Pool )->Count ] ) ;
	free( ( *Pool )->Memory ) ;
	free( *Pool ) ;
	*Pool = pmem_NULL ;
}

void* pmem_allocate( struct pmem_Pool *Pool )
{
	if( Pool->Count >= Pool->Length )
		return pmem_NULL ;
		
	return Pool->Memory[ Pool->Count ++ ] ;
}
void pmem_deallocate( struct pmem_Pool *Pool , void* Address )
{
	if( Pool->Count == 0 )
		return ;
		
	Pool->Memory[ -- Pool->Count ] = Address ;
}
