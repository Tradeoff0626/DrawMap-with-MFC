// LinkedList.cpp: implementation of the CLinkedList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawMap.h"
#include "LinkedList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CPointList::CPointList()
{
	m_pointData.x = 0;
	m_pointData.y = 0;
	m_next=NULL;
}
	
CPointList::~CPointList()
{
	
}

void CPointList::NodeInit()
{
	m_pointData.x = 0;
	m_pointData.y = 0;
	m_next=NULL;
}


CPointList* CPointList::AddNode(CPointList* prevNode, CPoint data)
{
	CPointList* newNode = new CPointList;

	newNode->m_pointData = data;

	newNode->m_next = prevNode->m_next;
	prevNode->m_next = newNode;

	return newNode;
}


void CPointList::DeleteList(CPointList* node)
{
	CPointList* nextNode=NULL;
	int i=0;
	
	while(TRUE)
	{		
		nextNode = node->m_next;

		if(i==0)
			node = NULL;
		else
			delete node;

		node = nextNode;
		
		if(NULL==(node->m_next))
		{
			delete node;
			break;
		}

		++i;	
	}
}

void CPointList::GetData(CPointList* node, CPoint* arrPoint)
{
	int i=0;

	node = node->m_next;					//헤더 필터링
	
	while(TRUE)
	{
		arrPoint[i] = node->m_pointData;

		if(NULL==(node->m_next))
			break;
		
		node = node->m_next;
		++i;
	}
}


/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

