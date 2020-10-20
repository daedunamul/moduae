/*
	emptydb::File
*/
#include "emptydbFile.h"

struct emptydbDB* emptydbFile_read( char *FileName ) ;
{
	if( FileName == plibCommonNullPointer )
		return plibCommonNullPointer ;
	
	FILE *DBFile = fopen( FileName , "rb" ) ;
	if( DBFile == plibCommonNullPointer )
		return plibCommonNullPointer ;
	
	struct emptydbFileDBHeader DBHeader ;
	struct emptydbDB *NewDB ;
	
	// reading DB
	fread( &DBHeader , sizeof( struct emptydbFileDBHeader ) , 1 , DBFile ) ;
	NewDB = emptydbDB_create( DBHeader.ObjectMaxCount , DBHeader.PropertyMaxCount ) ;
	NewDB->ObjectCount = DBHeader.ObjectCount ;
	NewDB->PropertyCount = DBHeader.PropertyCount ;
	if( DBHeader.ObjectRootNodeKey != 0 )
	{
		emptydbObject_createRoot( NewDB , DBHeader.ObjectRootNodeKey ) ;
		
		// reading Objects and Properties
		emptydbFile_readObject( DBFile , NewDB->ObjectRootNode ) ;
	}
		
	fclose( DBFile ) ;
	return NewDB ;
}
void emptydbFile_readObject( FILE *DBFile , struct plibDataHBST *Node )
{

}

bool emptydbFile_write( struct emptydbDB *DB , char *FileName )
{
	if( DB == plibCommonNullPointer || FileName == plibCommonNullPointer )
		return false ;

	FILE *DBFile = fopen( FileName , "wb" ) ;
	if( DBFile == plibCommonNullPointer )
		return false ;
	
	struct emptydbFileDBHeader DBHeader ;
	
	// writing DB
	DBHeader.ObjectMaxCount = DB->ObjectMaxCount ; 
	DBHeader.ObjectCount = DB->ObjectCount ;
	DBHeader.PropertyMaxCount = DB->PropertyMaxCount ;
	DBHeader.PropertyCount = DB->PropertyCount ;
	DBHeader.ObjectRootNodeKey = DB->ObjectRootNode == plibCommonNullPointer ? 0 : *( emptydbCommonKeyType* )DB->ObjectRootNode->Key ;
	DBHeader.ObjectThisNodeKey = DB->ObjectThisNode == plibCommonNullPointer ? 0 : *( emptydbCommonKeyType* )DB->ObjectThisNode->Key ;
	DBHeader.PropertyThisNodeKey = DB->PropertyThisNode == plibCommonNullPointer ? 0 : *( emptydbCommonKeyType* )DB->PropertyThisNode->Key ;
	fwrite( &DBHeader , sizeof( struct emptydbFileDBHeader ) , 1 , DBFile ) ;
	
	// writing Objects and Properties
	emptydbFile_writeObject( DB->ObjectRootNode , DBFile ) ;
	
	fclose( DBFile ) ;
	return true ;
}
void emptydbFile_writeObject( struct plibDataHBST *Node , FILE *DBFile )
{
	if( Node == plibCommonNullPointer )
		return ;
	
	// This Node Key
	fwrite( ( emptydbCommonKeyType* )Node->Key , sizeof( emptydbCommonKeyType ) , 1 , DBFile ) ;
	
	// Left
	
	
	
	
	
	
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
void emptydbFile_writeProperty( struct plibDataHBST *Node , FILE *DBFile )
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