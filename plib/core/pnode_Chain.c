/*
	pnode
	Chain
*/
#include "pnode_Chain.h"

void pnode_chain_push( struct pnode_Chain *Chain , bool Flag , struct pnode_Node *NewNode )
{
	if( ( Chain == pmem_NULL ) || ( NewNode == pmem_NULL ) )
		return ;
		
	if( Chain->Entry == pmem_NULL )
	{
		// NewNode.Right -> NewNode <- Left.NewNode
		NewNode->Left = NewNode ;
		NewNode->Right = NewNode ;
	}
	else
	{
		if( Flag )
			pnode_linkRight( NewNode , Chain->Entry ) ;
		else
			pnode_linkLeft( NewNode , Chain->Entry ) ;
	}
	Chain->Entry = NewNode ;
}
struct pnode_Node* pnode_chain_pop( struct pnode_Chain *Chain , bool Flag )
{
	if( ( Chain == pmem_NULL ) || ( Chain->Entry == pmem_NULL ) )
		return pmem_NULL ;
		
	struct pnode_Node *OldNode = Chain->Entry ;
	
	if( Chain->Entry == Chain->Entry->Left )
		Chain->Entry = pmem_NULL ;
	else
	{
		pnode_unlink( OldNode ) ;
		if( Flag )
			Chain->Entry = OldNode->Right ;
		else
			Chain->Entry = OldNode->Left ;
	}
	
	return OldNode ;
}
struct pnode_Node* pnode_chain_lookup
( 
	struct pnode_Chain *Chain , bool Flag , void *Data , 
	bool ( *judge )( void* , void* ) 
)
{
	if( ( Chain == pmem_NULL ) || ( Chain->Entry == pmem_NULL ) )
		return pmem_NULL ;
		
	struct pnode_Node *TempNode = Chain->Entry ;
	if( Flag )
	{
		if( judge == pmem_NULL )
		{
			do
			{
				if( TempNode == ( struct pnode_Node* )Data )
					return TempNode ;
				TempNode = TempNode->Right ;
			}
			while( TempNode != Chain->Entry ) ;
		}
		else
		{
			do
			{
				if( judge( TempNode->Value , Data ) )
					return TempNode ;
				TempNode = TempNode->Right ;
			}
			while( TempNode != Chain->Entry ) ;
		}
	}
	else
	{
		if( judge == pmem_NULL )
		{
			do
			{
				if( TempNode == ( struct pnode_Node* )Data )
					return TempNode ;
				TempNode = TempNode->Left ;
			}
			while( TempNode != Chain->Entry ) ;
		}
		else
		{
			do
			{
				if( judge( TempNode->Value , Data ) )
					return TempNode ;
				TempNode = TempNode->Left ;
			}
			while( TempNpde != Chain->Entry ) ;
		}
	}
	
	return pmem_NULL ;
}
