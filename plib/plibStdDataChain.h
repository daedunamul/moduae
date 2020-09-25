/*
	plib::Std::Data::Chain
*/
#pragma once
#include "plibStdType.h"

struct plibStdDataChain
{
	struct plibStdDataChain *Left , *Right ;
	plibStdTypeAddress *Value ;
} ;

void plibStdDataChain_push( bool Direction , struct plibStdDataChain **EntryNode , struct plibStdDataChain *NewNode ) ;
struct plibStdDataChain* plibStdDataChain_pop( bool Direction , struct plibStdDataChain **EntryNode ) ;
struct plibStdDataChain* plibStdDataChain_lookup( bool Direction , unsigned int Index , struct plibStdDataChain *ThisNode ) ;