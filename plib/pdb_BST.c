/*
	pdb
	BST
*/
#include "pdb_BST.h"

struct pdb_bst_Parameter pdb_bst_search( struct pdb_bst_Node *TopNode , uint64_t Key )
{
	struct pdb_bst_Parameter Parameter = { .ParentNode = TopNode , .Node = TopNode , .Status = pdb_bst_status_NULL } ;
	
	if( Parameter.Node != pmem_NULL )
	{
		Parameter.Status = pdb_bst_status_NONEOFPARENT ;
		
		while( true )
		{
			if( Key == Parameter.Node->Key )
				break ;
			else if( Key < Parameter.Node->Key )
			{
				if( Parameter.Node->Left == pmem_NULL )
				{
					Parameter.Status = pdb_bst_status_NONEOFLEFT ;
					break ;
				}
					
				Parameter.Status = pdb_bst_status_LEFTOFPARENT ;
				Parameter.ParentNode = Parameter.Node ;
				Parameter.Node = Parameter.Node->Left ;
			}
			else
			{
				if( Parameter.Node->Right == pmem_NULL )
				{
					Parameter.Status = pdb_bst_status_NONEOFRIGHT ;
					break ;
				}
				
				Parameter.Status = pdb_bst_status_RIGHTOFPARENT ;
				Parameter.ParentNode = Parameter.Node ;
				Parameter.Node = Parameter.Node->Right ;
			}
		}
	}
	
	return Parameter ;
}
struct pdb_bst_Parameter pdb_bst_getCandidate( struct pdb_bst_Node *Node )
{
	struct pdb_bst_Parameter Parameter = { .ParentNode = Node , .Node = Node , .Status = pdb_bst_status_NULL } ;
	
	if( Parameter.Node != pmem_NULL )
	{
		if( ( Parameter.Node->Left != pmem_NULL ) && ( Parameter.Node->Right != pmem_NULL ) )
		{
			for( Parameter.Node = Parameter.Node->Right ; Parameter.Node->Left != pmem_NULL ; Parameter.ParentNode = Parameter.Node , Parameter.Node = Parameter.Node->Left ) ;
			Parameter.Status = pdb_bst_status_BOTHOFPARENT ;
		}
		else if( Parameter.Node->Left != pmem_NULL )
		{
			Parameter.Node = Parameter.Node->Left ;
			Parameter.Status = pdb_bst_status_LEFTOFPARENT ;
		}
		else if( Parameter.Node->Right != pmem_NULL )
		{
			Parameter.Node = Parameter.Node->Right ;
			Parameter.Status = pdb_bst_status_RIGHTOFPARENT ;
		}
		else
			Parameter.Status = pdb_bst_status_NONEOFPARENT ;
	}
	
	return Parameter ;
}
bool pdb_bst_insert( struct pdb_bst_Node **TopNode , struct pdb_bst_Node *NewNode )
{
	struct pdb_bst_Parameter Parameter = pdb_bst_search( *TopNode , NewNode->Key ) ;
	

	switch( Parameter.Status )
	{
		case pdb_bst_status_NONEOFPARENT :
		case pdb_bst_status_LEFTOFPARENT : 
		case pdb_bst_status_RIGHTOFPARENT : 
			return false ;
			
		case pdb_bst_status_NULL :
			*TopNode = NewNode ;
		break ;
		case pdb_bst_status_NONEOFLEFT :
			Parameter.Node->Left = NewNode ;
		break ;
		case pdb_bst_status_NONEOFRIGHT :
			Parameter.Node->Right = NewNode ;
		break ;
	}
	
	return true ;
}
struct pdb_bst_Node* pdb_bst_desert( struct pdb_bst_Node **TopNode , uint64_t Key )
{
	struct pdb_bst_Parameter Parameter = pdb_bst_search( *TopNode , Key ) , ChildParameter ;
	struct pdb_bst_Node **TempNode ;
	
	switch( Parameter.Status )
	{
		case pdb_bst_status_NULL :
		case pdb_bst_status_NONEOFLEFT :
		case pdb_bst_status_NONEOFRIGHT :
			return pmem_NULL ;
		
		case pdb_bst_status_NONEOFPARENT : 
			TempNode = TopNode ;
		break ;
		case pdb_bst_status_LEFTOFPARENT :
			TempNode = &( Parameter.ParentNode->Left ) ;
		break ;
		case pdb_bst_status_RIGHTOFPARENT :
			TempNode = &( Parameter.ParentNode->Right ) ;
		break ;
	}

	ChildParameter = pdb_bst_getCandidate( Parameter.Node ) ;
	switch( ChildParameter.Status )
	{
		case pdb_bst_status_NONEOFPARENT : 
			*TempNode = pmem_NULL ;
		break ;
		case pdb_bst_status_LEFTOFPARENT : 
		case pdb_bst_status_RIGHTOFPARENT : 
			*TempNode = ChildParameter.Node ;
		break ;
		
		case pdb_bst_status_BOTHOFPARENT : 
			ChildParameter.Node->Left = Parameter.Node->Left ;
			if( ChildParameter.ParentNode != Parameter.Node )
				ChildParameter.Node->Right = Parameter.Node->Right ;
			
			ChildParameter.ParentNode->Left = pmem_NULL ;
			*TempNode = ChildParameter.Node ;
		break ;
	}
			
	return Parameter.Node ;
}
