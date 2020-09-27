/*
	plib::Memory::Pool
*/
#pragma once
#include "plibMemory.h"

struct plibMemoryPool
{
	plibCommonCountType UnitSize , Count , MaxCount ;
	plibCommonAnyType *AddressStart , *AddressEnd ;
	plibCommonAnyType **AddressStack ;
} ;

void plibMemoryPool_initialize( struct plibMemoryPool *Pool ) ;

struct plibMemoryPool* plibMemoryPool_createPool( plibCommonCountType UnitSize , plibCommonCountType MaxCount ) ;
bool plibMemoryPool_deletePool( struct plibMemoryPool **Pool ) ;

plibCommonAnyType* plibMemoryPool_allocate( struct plibMemoryPool *Pool ) ;
void plibMemoryPool_deallocate( struct plibMemoryPool *Pool , plibCommonAnyType **UsedAddress ) ;