/*
	plib::Data::BTree
	Balanced Tree
*/
#include "plibDataBTree.h"

void plibDataBTree_swapNode( struct plibDataBTreeNode *Node1 , struct plibDataBTreeNode *Node2 )
{
	if( Node1 == Node2 )
		return ;
	
	struct plibDataBTreeNode TempNode = *Node1 ;
	
	*Node1 = *Node2 ;
	*Node2 = TempNode ;
}
void plibDataBTree_sortNode( struct plibDataBTreeNode *Nodes , plibCommonCountType NodeCount )
{
	struct plibDataBTreeNode *PivotNode ;
	plibCommonCountType LeftIndex , RightIndex , LowIndex , HighIndex , StackCount = 0 , Stack[ plibDataBTreeDegree ][ 2 ] ;
	
	Stack[ StackCount ][ 0 ] = 0 ;
	Stack[ StackCount ][ 1 ] = NodeCount - 1 ;
	StackCount ++ ;
	
	while( StackCount > 0 )
	{
		// popping stack
		StackCount -- ;
		LeftIndex = Stack[ StackCount ][ 0 ] ;
		RightIndex = Stack[ StackCount ][ 1 ] ;
		if( ( RightIndex - LeftIndex + 1 ) < 2 )
			continue ;
		
		// partition
		PivotNode = Nodes + LeftIndex ;
		LowIndex = LeftIndex ;
		HighIndex = RightIndex ;
		while( LowIndex < HighIndex )
		{
			while( LowIndex < HighIndex && plibData_compareKey( PivotNode->Key , Nodes[ HighIndex ].Key ) != plibDataKeyComparisonGreat )
				HighIndex -- ;
			while( LowIndex < HighIndex && plibData_compareKey( PivotNode->Key , Nodes[ LowIndex ].Key ) != plibDataKeyComparisonLess )
				LowIndex ++ ;
			
			// swapping Low for High
			plibDataBTree_swapNode( Nodes + LowIndex , Nodes + HighIndex ) ;
		}
		// swapping Pivot for Low
		plibDataBTree_swapNode( Nodes + LeftIndex , Nodes + LowIndex ) ;
		
		// pushing stack
		if( LowIndex + 1 < RightIndex )
		{
			Stack[ StackCount ][ 0 ] = LowIndex + 1 ;
			Stack[ StackCount ][ 1 ] = RightIndex ;
			StackCount ++ ;
		}
		if( LowIndex - 1 > LeftIndex )
		{
			Stack[ StackCount ][ 0 ] = LeftIndex ;
			Stack[ StackCount ][ 1 ] = LowIndex - 1 ;
			StackCount ++ ;
		}
	}
}

void plibDataBTree_initialize( struct plibDataBTreeUnit *Unit , struct plibError *Error )
{
	// error
	if( Unit == plibCommonNullPointer )
	{
		plibError_report( Error , plibErrorParameter , plibDataBTree_initialize ) ;
		return ;
	}
	
	plibCommonCountType Count ;
	
	Unit->Top = plibCommonNullPointer ;
	for( Count = 0 ; Count < plibDataBTreeDegree + 1 ; Count ++ )
		Unit->Bottoms[ Count ] = plibCommonNullPointer ;
	Unit->BottomCount = 0 ;
	
	for( Count = 0 ; Count < plibDataBTreeDegree ; Count ++ )
	{
		plibData_initializeKey( Unit->Nodes[ Count ].Key ) ;
		Unit->Nodes[ Count ].Value = plibCommonNullPointer ;
	}
	Unit->NodeCount = 0 ;
}