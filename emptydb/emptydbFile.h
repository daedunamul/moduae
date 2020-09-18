/*
	emptydb::File
*/
#pragma once
#include "emptydbObject.h"
#include <stdio.h>

struct emptydbFileRootHeader
{
	emptydbCommonCountType ObjectMaxCount , ObjectCount , KeyValueMaxCount , KeyValueCount ;
	emptydbCommonKeyType ObjectRootNodeKey , ObjectThisNodeKey , KeyValueThisNodeKey ;
} ;
struct emptydbFileObjectHeader
{
	emptydbCommonKeyType Key ;
	uint8_t Type ;
} ;
struct emptydbFileKeyValueHeader
{
	emptydbCommonKeyType Key ;
	uint8_t Type ;
	emptydbCommonCountType DataSize , DataLength ;
} ;

struct emptydbRoot* emptydbFile_read( char *FileName ) ;
void emptydbFile_readObject( FILE *DBFile , struct plibStdDataBST *Node ) ;

bool emptydbFile_write( struct emptydbRoot *Root , char *FileName ) ;
void emptydbFile_writeObject( struct plibStdDataBST *Node , FILE *DBFile ) ;
void emptydbFile_writeKeyValue( struct plibStdDataBST *Node , FILE *DBFile ) ;

void emptydbFile_countNode( struct plibStdDataBST *Entry , emptydbCommonCountType *Count ) ;