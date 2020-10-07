/*
	emptydb::Stream
*/
#pragma once
#include "emptydbCommon.h"

struct emptydbStream
{
	plibCommonCountType Length , Size , Count ;
	plibCommonAnyType *Data ;
} ;

struct emptydbStream* emptydbStream_create( plibCommonCountType Length , plibCommonCountType Size ) ;
bool emptydbStream_delete( struct emptydbStream **Stream ) ;

plibCommonAnyType* emptydbStream_refer( struct emptydbStream *Stream , plibCommonCountType Index ) ;

void emptydbStream_reset( struct emptydbStream *Stream ) ;
bool emptydbStream_setKey( struct emptydbStream *Stream , emptydbCommonKeyType Key ) ;
bool emptydbStream_setNode( struct emptydbStream *Stream , struct plibDataHBST *Node ) ;