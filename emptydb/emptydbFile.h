/*
	emptydb::File
*/
#pragma once
#include "emptydbObject.h"
#include <stdio.h>

struct emptydbFileHeader
{
	plibCommonCountType ObjectMaxCount , PropertyMaxCount ;
	emptydbCommonKeyType ObjectRootNodeKey ;
} ;

struct emptydbFileNode
{
	plibCommonCountType SuperIndex ;
	emptydbCommonKeyType SuperKey , Key ;
	bool SubFlag ;
} ;
struct emptydbFileValue
{
	plibCommonCountType Type , Size , Length ;
	//// data
} ;

bool emptydbFile_write( struct emptydbDB *DB , char *FileName ) ;
void emptydbFile_writeNode( struct plibDataHBST *TraversedNode , plibCommonCountType Index , plibCommonAnyType *Data ) ;

struct emptydbDB* emptydbFile_read( char *FileName ) ;