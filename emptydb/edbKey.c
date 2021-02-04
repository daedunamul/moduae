/*
	edb::Key
*/
#include "edbKey.h"

enum plibDataHBSTStatus edbKey_compare( plibCommonAnyType *Key1 , plibCommonAnyType *Key2 )
{
	if( *( edbKeyType* )Key1 < *( edbKeyType* )Key2 )
		return plibDataHBSTStatusLess ;
	else if( *( edbKeyType* )Key1 > *( edbKeyType* )Key2 )
		return plibDataHBSTStatusGreat ;
	return plibDataHBSTStatusEqual ;
}