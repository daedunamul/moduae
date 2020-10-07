/*
	emptydb::Common
*/
#include "emptydbCommon.h"

enum plibDataHBSTStatus emptydbCommon_compareKey( plibCommonAnyType *Key1 , plibCommonAnyType *Key2 )
{
	if( *( emptydbCommonKeyType* )Key1 < *( emptydbCommonKeyType* )Key2 )
		return plibDataHBSTStatusLess ;
	else if( *( emptydbCommonKeyType* )Key1 > *( emptydbCommonKeyType* )Key2 )
		return plibDataHBSTStatusGreat ;
	return plibDataHBSTStatusEqual ;
}