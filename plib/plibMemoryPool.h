/*
	plib::Memory::Pool
*/
#pragma once
#include "plibMemory.h"

struct plibMemoryPool
{
	plibCommonCountType UnitSize , MaxCount , Count ;
	plibCommonAnyType *AddressStart , *AddressEnd ;
	plibCommonAnyType **AddressStack ;
} ;

void plibMemoryPool_initialize( struct plibMemoryPool *Pool , struct plibError *Error ) ;

struct plibMemoryPool* plibMemoryPool_create( plibCommonCountType UnitSize , plibCommonCountType MaxCount , struct plibError *Error ) ;
void plibMemoryPool_delete( struct plibMemoryPool **Pool , struct plibError *Error ) ;

plibCommonAnyType* plibMemoryPool_allocate( struct plibMemoryPool *Pool , struct plibError *Error ) ;
void plibMemoryPool_deallocate( struct plibMemoryPool *Pool , plibCommonAnyType **UsedAddress , struct plibError *Error ) ;