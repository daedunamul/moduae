/*
	emptydb::Common
*/
#include "emptydbCommon.h"

enum plibStdDataBSTStatus emptydbCommon_compareKey( uint8_t *Key1 , uint8_t *Key2 )
{
	if( *( emptydbCommonKeyType* )Key1 < *( emptydbCommonKeyType* )Key2 )
		return plibStdDataBSTStatusLess ;
	else if( *( emptydbCommonKeyType* )Key1 > *( emptydbCommonKeyType* )Key2 )
		return plibStdDataBSTStatusGreat ;
	return plibStdDataBSTStatusEqual ;
}
