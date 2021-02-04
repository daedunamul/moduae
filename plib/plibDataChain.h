/*
	plib::Data::Chain
*/
#pragma once
#include "plibData.h"

struct plibDataChain
{
	struct plibDataChain *Left , *Right ;
	plibCommonAnyType *Value ;
} ;

void plibDataChain_push( bool Direction , struct plibDataChain **EntryNode , struct plibDataChain *NewNode , struct plibErrorType *Error ) ;
struct plibDataChain* plibDataChain_pop( bool Direction , struct plibDataChain **EntryNode , struct plibErrorType *Error ) ;
struct plibDataChain* plibDataChain_lookup( bool Direction , plibCommonCountType Index , struct plibDataChain *ThisNode , struct plibErrorType *Error ) ;