/*
	emptydb::File
*/
#pragma once
#include "emptydbObject.h"
#include <stdio.h>

struct emptydbFileDBHeader
{
	plibCommonCountType ObjectMaxCount , ObjectCount , PropertyMaxCount , PropertyCount ;
	emptydbCommonKeyType ObjectRootNodeKey , ObjectThisNodeKey , PropertyThisNodeKey ;
} ;
struct emptydbFilePropertyHeader
{
	emptydbCommonKeyType Key ;
	plibCommonCountType Type , Size , Length ;
} ;

struct emptydbDB* emptydbFile_read( char *FileName ) ;
void emptydbFile_readObject( FILE *DBFile , struct plibDataHBST *Node ) ;

bool emptydbFile_write( struct emptydbDB *DB , char *FileName ) ;
void emptydbFile_writeObject( struct plibDataHBST *Node , FILE *DBFile ) ;
void emptydbFile_writeProperty( struct plibDataHBST *Node , FILE *DBFile ) ;