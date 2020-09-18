/*
	emptydb::File
*/
#include "emptydbFile.h"

struct emptydbRoot* emptydbFile_read( char *FileName )
{
	if( FileName == plibStdTypeNullPointer )
		return plibStdTypeNullPointer ;
	
	FILE *DBFile = fopen( FileName , "rb" ) ;
	if( DBFile == plibStdTypeNullPointer )
		return plibStdTypeNullPointer ;
	
	struct emptydbFileRootHeader RootHeader ;
	struct emptydbRoot *NewRoot ;
	
	// reading Root
	fread( &RootHeader , sizeof( struct emptydbFileRootHeader ) , 1 , DBFile ) ;
	NewRoot = emptydbRoot_create( RootHeader.ObjectMaxCount , RootHeader.KeyValueMaxCount ) ;
	NewRoot->ObjectCount = RootHeader.ObjectCount ;
	NewRoot->KeyValueCount = RootHeader.KeyValueCount ;
	if( RootHeader.ObjectRootNodeKey != 0 )
	{
		emptydbObject_createRootObject( NewRoot , RootHeader.ObjectRootNodeKey ) ;
		
		// reading Objects and KeyValues
		emptydbFile_readObject( DBFile , NewRoot->ObjectRootNode ) ;
	}
		
	fclose( DBFile ) ;
	return NewRoot ;
}
void emptydbFile_readObject( FILE *DBFile , struct plibStdDataBST *Node )
{
	emptydbCommonCountType Counter ;
	
	fread( &Counter , sizeof( emptydbCommonCountType ) , 1 , DBFile ) ;
	if( Counter == 0 )
		return ;
	
	struct emptydbFileObjectHeader ObjectHeader ;
	struct emptydbFileKeyValueHeader KeyValueHeader ;
	struct emptydbCommonObjectValueType *ObjectValue = ( struct emptydbCommonObjectValueType* )Node->Value ;
	
	// read Object Header
	fread( &ObjectHeader , sizeof( struct emptydbFileObjectHeader ) , 1 , DBFile ) ;
	emptydbObject_createObject( ObjectValue->MemberObjectRootNode , 1 , &ObjectHeader.Key ) ;
	
	// read Member KeyValue
	fread( &Counter , sizeof( emptydbCommonCountType ) , 1 , DBFile ) ;
	while( Counter > 0 )
	{
		fread( &KeyValueHeader , sizeof( struct emptydbFileKeyValueHeader ) , 1 , DBFile ) ;
		emptydbKeyValue_createKeyValue( ObjectValue->MemberKeyValueRootNode , 1 , &KeyValueHeader.Key , KeyValueHeader.DataSize , KeyValueHeader.DataLength ) ;
		
		Counter -- ;
	}
	
	// read Member Object
	fread( &Counter , sizeof( emptydbCommonCountType ) , 1 , DBFile ) ;
	if( Counter != 0 )
		emptydbFile_readObject( DBFile , ObjectValue->MemberObjectRootNode ) ;
	
	emptydbFile_readObject( DBFile , Node ) ;
}

bool emptydbFile_write( struct emptydbRoot *Root , char *FileName )
{
	if( Root == plibStdTypeNullPointer || FileName == plibStdTypeNullPointer )
		return false ;

	FILE *DBFile = fopen( FileName , "wb" ) ;
	if( DBFile == plibStdTypeNullPointer )
		return false ;
	
	struct emptydbFileRootHeader RootHeader ;
	
	// writing Root
	RootHeader.ObjectMaxCount = Root->ObjectMaxCount ; 
	RootHeader.ObjectCount = Root->ObjectCount ;
	RootHeader.KeyValueMaxCount = Root->KeyValueMaxCount ;
	RootHeader.KeyValueCount = Root->KeyValueCount ;
	RootHeader.ObjectRootNodeKey = Root->ObjectRootNode == plibStdTypeNullPointer ? 0 : *( emptydbCommonKeyType* )Root->ObjectRootNode->Key ;
	RootHeader.ObjectThisNodeKey = Root->ObjectThisNode == plibStdTypeNullPointer ? 0 : *( emptydbCommonKeyType* )Root->ObjectThisNode->Key ;
	RootHeader.KeyValueThisNodeKey = Root->KeyValueThisNode == plibStdTypeNullPointer ? 0 : *( emptydbCommonKeyType* )Root->KeyValueThisNode->Key ;
	fwrite( &RootHeader , sizeof( struct emptydbFileRootHeader ) , 1 , DBFile ) ;
	
	// writing Objects and KeyValues
	emptydbFile_writeObject( ( struct emptydbCommonObjectValueType* )( Root->ObjectRootNode->Value )->MemberObjectRootNode , DBFile ) ;
	
	fclose( DBFile ) ;
	return true ;
}
void emptydbFile_writeObject( struct plibStdDataBST *Node , FILE *DBFile )
{
	emptydbCommonCountType Counter = 0 ;
	
	if( Node == plibStdTypeNullPointer )
	{
		fwrite( &Counter , sizeof( emptydbCommonCountType ) , 1 , DBFile ) ;
		return ;
	}
	else
	{
		Counter = 1 ;
		fwrite( &Counter , sizeof( emptydbCommonCountType ) , 1 , DBFile ) ;
	}
	
	struct emptydbFileObjectHeader ObjectHeader ;
	
	// write Object Header
	ObjectHeader.Key = *( emptydbCommonKeyType* )Node->Key ;
	ObjectHeader.Type = Node->Type ;
	fwrite( &ObjectHeader , sizeof( struct emptydbFileObjectHeader ) , 1 , DBFile ) ;
	
	// write Member KeyValue
	Counter = 0 ;
	emptydbFile_countNode( ( struct emptydbCommonObjectValueType* )( Node->Value )->MemberKeyValueRootNode , &Counter ) ;
	fwrite( &Counter , sizeof( emptydbCommonCountType ) , 1 , DBFile ) ;
	emptydbFile_writeKeyValue( ( struct emptydbCommonObjectValueType* )( Node->Value )->MemberKeyValueRootNode , DBFile ) ;
	
	// write Member Object
	emptydbFile_writeObject( ( struct emptydbCommonObjectValueType* )( Node->Value )->MemberObjectRootNode , DBFile ) ;
	
	emptydbFile_writeObject( Node->Left , DBFile ) ;
	emptydbFile_writeObject( Node->Right , DBFile ) ;
}
void emptydbFile_writeKeyValue( struct plibStdDataBST *Node , FILE *DBFile )
{
	if( Node == plibStdTypeNullPointer )
		return ;
	
	struct emptydbFileKeyValueHeader KeyValueHeader ;
	KeyValueHeader.Key = Node->Key ;
	KeyValueHeader.Type = Node->Type ;
	KeyValueHeader.DataSize = ( ( struct emptydbCommonKeyValueType* )Node->Value )->DataSize ;
	KeyValueHeader.DataLength = ( ( struct emptydbCommonKeyValueType* )Node->Value )->DataLength ;
	
	fwrite( &KeyValueHeader , sizeof( struct emptydbFileKeyValueHeader ) , 1 , DBFile ) ;
	if( Node->Left != plibStdTypeNullPointer )
		emptydbFile_writeKeyValue( Node->Left , DBFile ) ;
	else if( Node->Right != plibStdTypeNullPointer )
		emptydbFile_writeKeyValue( Node->Right , DBFile ) ;
}

void emptydbFile_countNode( struct plibStdDataBST *Entry , emptydbCommonCountType *Count )
{
	if( Entry == plibStdTypeNullPointer )
		return ;
	
	( *Count ) ++ ;
	if( Entry->Left != plibStdTypeNullPointer )
		emptydbFile_countNode( Entry->Left , Count ) ;
	else if( Entry->Right != plibStdTypeNullPointer )
		emptydbFile_countNode( Entry->Right , Count ) ;
}