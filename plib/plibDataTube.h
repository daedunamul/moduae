/*
	plib::Data::Tube
*/
#pragma once
#include "plibData.h"

struct plibDataTube
{
	struct plibDataTube *Left , *Right ;
	plibCommonAnyType *Value ;
} ;

typedef void ( plibDataTubeIterationFxType )( plibCommonCountType Count , struct plibDataTube *VistedNode ) ;

void plibDataTube_push( bool Direction , struct plibDataTube **EntryNode , struct plibDataTube *NewNode , struct plibErrorType *Error ) ;
struct plibDataTube* plibDataTube_pop( bool Direction , struct plibDataTube **EntryNode , struct plibErrorType *Error ) ;

void plibDataTube_iterate( bool Direction , struct plibDataTube *EntryNode , plibDataTubeIterationFxType IterationFx , struct plibErrorType *Error ) ;