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

void plibMemoryPool_initialize( struct plibMemoryPool *Pool , struct plibErrorType *Error ) ;

struct plibMemoryPool* plibMemoryPool_create( plibCommonCountType UnitSize , plibCommonCountType MaxCount , struct plibErrorType *Error ) ;
void plibMemoryPool_delete( struct plibMemoryPool **Pool , struct plibErrorType *Error ) ;

plibCommonAnyType* plibMemoryPool_allocate( struct plibMemoryPool *Pool , struct plibErrorType *Error ) ;
void plibMemoryPool_deallocate( struct plibMemoryPool *Pool , plibCommonAnyType **UsedAddress , struct plibErrorType *Error ) ;