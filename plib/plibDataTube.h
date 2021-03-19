/*
	plib::Data::Tube
*/
#pragma once
#include "plibData.h"

struct plibDataTube
{
	struct plibDataNode *EntryNode ;
	plibCommonCountType Count ;
} ;

typedef void ( plibDataTubeIterationFxType )( plibCommonCountType Count , struct plibDataNode *VistedNode ) ;

void plibDataTube_initialize( struct plibDataTube *Tube , struct plibError *Error ) ;

void plibDataTube_push( bool Direction , struct plibDataTube *Tube , struct plibDataNode *NewNode , struct plibError *Error ) ;
struct plibDataNode* plibDataTube_pop( bool Direction , struct plibDataTube *Tube , struct plibError *Error ) ;

void plibDataTube_iterate( bool Direction , struct plibDataTube *Tube , plibDataTubeIterationFxType IterationFx , struct plibError *Error ) ;
struct plibDataNode* plibDataTube_index( struct plibDataTube *Tube , plibCommonCountType Index , struct plibError *Error ) ;