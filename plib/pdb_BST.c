/*
	pdb
	BST
*/
#include "pdb_BST.h"

struct pdb_bst_Node* pdb_bst_search( struct pdb_bst_Node *RootNode , char *Key )
{
	struct pdb_bst_Node *TempNode = RootNode ;
	uint8_t Count ;
	
	while( TempNode != pmem_NULL )
	{
		for( Count = 0 ; Count < pdb_bst_key_LENGTH ; Count ++ )
		{
			if( Key[ Count ] < TempNode->Key[ Count ] )
			{
				TempNode = TempNode->Left ;
				break ;
			}
			else if( Key[ Count ] > TempNode->Key[ Count ] )
			{
				TempNode = TempNode->Right ;
				break ;
			}
		}
		
		if( Count == pdb_bst_key_LENGTH )
			break ;
	}
	
	return TempNode ;
}

bool pdb_bst_insert( struct pdb_bst_Node **RootNode , struct pdb_bst_Node *NewNode )
{
	struct pdb_bst_Node *TempNode = *RootNode ;
	uint8_t Count ;

	while( TempNode != pmem_NULL )
	{
		for( Count = 0 ; Count < pdb_bst_key_LENGTH ; Count ++ )
		{
			if( NewNode->Key[ Count ] < TempNode->Key[ Count ] )
			{
				if( TempNode->Left == pmem_NULL )
				{
					TempNode->Left = NewNode ;
					return true ;
				}
				
				TempNode = TempNode->Left ;
				break ;
			}
			else if( NewNode->Key[ Count ] > TempNode->Key[ Count ] )
			{
				if( TempNode->Right == pmem_NULL )
				{
					TempNode->Right = NewNode ;
					return true ;
				}
				
				TempNode = TempNode->Right ;
				break ;
			}
		}
		
		if( Count == pdb_bst_key_LENGTH )
			return false ;
	}
	
	*RootNode = NewNode ;
	return true ;
}
struct pdb_bst_Node* pdb_bst_desert( struct pdb_bst_Node **RootNode , char *Key )
{
	struct pdb_bst_Node *ChildNode = *RootNode , *ParentNode = ChildNode , *TempParentNode , *TempChildNode ;
	uint8_t Count ;
	bool Flag ;
	
	while( ChildNode != pmem_NULL )
	{
		 for( Count = 0 ; Count < pdb_bst_key_LENGTH ; Count ++ )
		 {
			if( Key[ Count ] < ChildNode->Key[ Count ] )
			{
				ParentNode = ChildNode ;
				ChildNode = ChildNode->Left ;
				Flag = false ;
				break ;
			}
			else if( Key[ Count ] > ChildNode->Key[ Count ] )
			{
				ParentNode = ChildNode ;
				ChildNode = ChildNode->Right ;
				Flag = true ;
				break ;
			}
		}
		
		if( Count == pdb_bst_key_LENGTH )
		{
			if( ChildNode == *RootNode )
			{
				if( ChildNode->Left == pmem_NULL && ChildNode->Right == pmem_NULL )
					*RootNode = pmem_NULL ;
				else if( ChildNode->Left != pmem_NULL && ChildNode->Right == pmem_NULL )
					*RootNode = ( *RootNode )->Left ;
				else if( ChildNode->Left == pmem_NULL && ChildNode->Right != pmem_NULL )
					*RootNode = ( *RootNode )->Right ;
				else
				{
					for
					(
						TempChildNode = ChildNode->Right , TempParentNode = TempChildNode ; 
						TempChildNode->Left != pmem_NULL ; 
						TempParentNode = TempChildNode , TempChildNode = TempChildNode->Left 
					) ;
				
					if( TempChildNode == TempParentNode )
						TempChildNode->Left = ChildNode->Left ;
					else
					{
						TempParentNode->Left = TempChildNode->Right ;
						TempChildNode->Left = ChildNode->Left ;
						TempChildNode->Right = ChildNode->Right ;
					}
					
					*RootNode = TempChildNode ;
				}
			}
			else
			{
				if( ChildNode->Left == pmem_NULL && ChildNode->Right == pmem_NULL )
				{
					if( Flag )
						ParentNode->Right = pmem_NULL ;
					else
						ParentNode->Left = pmem_NULL ;
				}
				else if( ChildNode->Left != pmem_NULL && ChildNode->Right == pmem_NULL )
				{
					if( Flag )
						ParentNode->Right = ChildNode->Left ;
					else
						ParentNode->Left = ChildNode->Left ;
				}
				else if( ChildNode->Left == pmem_NULL && ChildNode->Right != pmem_NULL )
				{
					if( Flag )
						ParentNode->Right = ChildNode->Right ;
					else
						ParentNode->Left = ChildNode->Right ;
				}
				else
				{
					for
					(
						TempChildNode = ChildNode->Right , TempParentNode = TempChildNode ; 
						TempChildNode->Left != pmem_NULL ; 
						TempParentNode = TempChildNode , TempChildNode = TempChildNode->Left 
					) ;
				
					if( TempChildNode == TempParentNode )
						TempChildNode->Left = ChildNode->Left ;
					else
					{
						TempParentNode->Left = TempChildNode->Right ;
						TempChildNode->Left = ChildNode->Left ;
						TempChildNode->Right = ChildNode->Right ;
					}
				
					if( Flag )
						ParentNode->Right = TempChildNode ;
					else
						ParentNode->Left = TempChildNode ;
				}
			}
			
			break ;
		}
	}
	
	return ChildNode ;
}
