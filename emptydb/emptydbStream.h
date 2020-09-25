/*
	emptydb::Stream
*/
#pragma once
#include "emptydbCommon.h"

bool emptydbStream_verify( uint8_t *Stream ) ;
uint8_t emptydbStream_getTag( uint8_t *Stream , bool Flag ) ;
void emptydbStream_setTag( uint8_t *Stream , uint8_t Value , bool Flag ) ;
uint8_t* emptydbStream_pointData( uint8_t *Stream , uint8_t Index ) ;

uint8_t* emptydbStream_create( uint8_t Length , uint8_t Size ) ;
bool emptydbStream_delete( uint8_t **Stream ) ;