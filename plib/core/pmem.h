/* 
	pmem
	
	no check for memory validation
*/
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define pmem_NULL NULL

struct pmem_Pool
{
	uint8_t Size , Length , Count ;
	void **Memory ;
} ;

struct pmem_Pool* pmem_create( uint8_t Size , uint8_t Length ) ;
void pmem_delete( struct pmem_Pool **Pool ) ;

void* pmem_allocate( struct pmem_Pool *Pool ) ;
void pmem_deallocate( struct pmem_Pool *Pool , void* Address ) ;
