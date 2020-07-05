/*
	pdb::Hash
*/
// 임시로 사용할 예정 ... 나중에 plibCrypto로 이동
#pragma once
#include "../plib/plibStdData.h"

uint8_t pdbHash_getBase64( char Ascii ) ;
uint32_t pdbHash_getAdler32( uint8_t *Data ) ;
