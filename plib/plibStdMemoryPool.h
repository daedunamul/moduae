/*
	plib::Std::Memory::Pool
*/
#pragma once
#include "plibStdMemory.h"

struct plibStdMemoryPool
{
	plibStdTypeCount UnitSize , Count , MaxCount ;
	plibStdTypeAddress AddressStart , AddressEnd ;
	plibStdTypeAddress *AddressStack ;
} ;

void plbStdMemoryPool_initialize( struct plibStdMemoryPool *Pool ) ;

struct plibStdMemoryPool* plibStdMemoryPool_createPool( plibStdTypeCount UnitSize , plibStdTypeCount MaxCount ) ;
bool plibStdMemoryPool_deletePool( struct plibStdMemoryPool **Pool ) ;

plibStdTypeAddress plbStdMemoryPool_allocate( struct plibStdMemoryPool *Pool ) ;
void plbStdMemoryPool_deallocate( struct plibStdMemoryPool *Pool , plibStdTypeAddress *UsedAddress ) ;