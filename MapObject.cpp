// MapObject.cpp: implementation of the CMapObject class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawMap.h"
#include "MapObject.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CObjectList::CObjectList()
{
	m_next = NULL;
}

CObjectList::~CObjectList()
{
	
}


CObjectList* CObjectList::AddObject(CObjectList* prevNode, CMapObject* data)
{
	CObjectList* newNode = new CObjectList;

	newNode->m_mapObj = *data;

	newNode->m_next = prevNode->m_next;
	prevNode->m_next = newNode;

	return newNode;
}


void CObjectList::DeleteList(CObjectList* node)
{
	CObjectList* nextNode=NULL;
	
	while(TRUE)
	{		
		nextNode = node->m_next;

		delete node;

		node = nextNode;
		
		if(!node->m_next)
			break;
	}
}


void CObjectList::GetData(CObjectList* node, CMapObject* arrPoint)
{
	int i=0;

	node = node->m_next;					//헤더 필터링
	
	while(TRUE)
	{
		arrPoint[i] = node->m_mapObj;

		if(NULL==(node->m_next))
			break;
		
		node = node->m_next;
		++i;
	}
}


CObjectList* CObjectList::GetNextObject(CObjectList* object)
{
	return object->m_next;
}

CMapObject* CObjectList::GetObject(CObjectList* object)
{
	return &object->m_mapObj;
}

BOOL CObjectList::isLastObj(CObjectList* object)
{
	if(object->m_next)
		return FALSE;
	else
		return TRUE;
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

CMapObject::CMapObject()
{

}

CMapObject::~CMapObject()
{
	delete []m_DPtHead;
}

void CMapObject::SetType(int type)
{
	m_nType = type;
}
	
int CMapObject::GetType()
{

	return m_nType;
}

void CMapObject::SetCount(int count)
{
	m_nCount = count;
}

int CMapObject::GetCount()
{
	return m_nCount;
}


void CMapObject::SetObjectColor(COLORREF color)
{
	m_objectColor = color;	
}
	
void CMapObject::SetObjectColor(CString color)
{
	if(color=="RED")
		m_objectColor = RGB(255, 0, 0);
	else if(color=="GREEN")
		m_objectColor = RGB(0, 255, 0);
	else if(color=="BLUE")
		m_objectColor = RGB(0, 0, 255);
}

COLORREF CMapObject::GetObjectColor()
{
	return m_objectColor;	
}

void CMapObject::SetFillColor(COLORREF fillColor)
{
	m_fillColor = fillColor;
}

void CMapObject::SetFillColor(CString color)
{
	if(color=="RED")
		m_fillColor = RGB(255, 0, 0);
	else if(color=="GREEN")
		m_fillColor = RGB(0, 255, 0);
	else if(color=="BLUE")
		m_fillColor = RGB(0, 0, 255);
}
	
COLORREF CMapObject::GetFillColor()
{
	return m_fillColor;
}

void CMapObject::SetPointHead(CPointList* head)
{
	m_PointHead = head;
}

CPointList* CMapObject::GetPointHead()
{
	return m_PointHead;
}

void CMapObject::SetDynamicPointHead(CPoint* head)
{
	m_DPtHead = head;
}

CPoint* CMapObject::GetDynamicPointHead()
{
	return m_DPtHead;
}

void CMapObject::SetPenSize(int pSize)
{
	m_penSize = pSize;
}

int CMapObject::GetPenSize()
{
	return m_penSize;
}

void CMapObject::SetText(CString text)
{
	m_text = text;
}

CString CMapObject::GetText()
{
	return m_text;
}


//CMapObject의 DrawMap() 순수 가상함수로 하고 싶었지만 문제가 생겨서 모든 타입별로 그림 가능하게 수정
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMapObject::DrawMap(CDC& dcMem, CRect rect)
{
	CPen pen, *pOldPen;
	CBrush brush, *pOldBrush;
	CFont font, *pOldFont;
	COLORREF crOldTextColor;
	CPoint* temp;
	int x, y, ntype;
	int nOldBkMode;

	ntype = this->GetType();
	
	if(ntype==1)
	{
		pen.CreatePen(PS_SOLID, 1, this->GetObjectColor());
		crOldTextColor = dcMem.SetTextColor(this->GetObjectColor());
	}
	else
	{
		pen.CreatePen(PS_SOLID, this->GetPenSize(), this->GetObjectColor());
		brush.CreateSolidBrush(this->GetFillColor());
	}


	font.CreatePointFont(200, "arial");
	nOldBkMode = dcMem.SetBkMode(TRANSPARENT);
	pOldPen = dcMem.SelectObject(&pen);
	pOldBrush = dcMem.SelectObject(&brush);
	pOldFont = dcMem.SelectObject(&font);
	crOldTextColor = dcMem.SetTextColor(RGB(0, 0, 0));	
	
	if(ntype==1)
	{
		temp = this->GetDynamicPointHead();

		x = temp[0].x;
		y = temp[0].y;

		dcMem.TextOut(x, y, this->GetText());
	}
	else if(ntype==2)
	{
		dcMem.Polyline(this->GetDynamicPointHead(), this->GetCount());			//PolyLine()을 이용해 선 그리기
		/*
		temp = this->GetDynamicPointHead();										//MoveTo(), LineTo()를 이용한 선 그리기

		dcMem.MoveTo(temp[0].x, temp[0].y);

		for(int i=1; i<this->GetCount() ; i++)
		{
			dcMem.LineTo(temp[i].x, temp[i].y);
		}
		*/
	}
	else
	{
		dcMem.Polygon(this->GetDynamicPointHead(), this->GetCount());
	}
	

	dcMem.SelectObject(pOldPen);
	dcMem.SelectObject(pOldBrush);
	dcMem.SelectObject(pOldFont);
	dcMem.SetBkMode(nOldBkMode);
	dcMem.SetTextColor(crOldTextColor);

	pen.DeleteObject();
	font.DeleteObject();
	brush.DeleteObject();
	
}


void CMapObject::SetIndex(int index)
{
	m_index = index;
}

int CMapObject::GetIndex()
{
	return m_index;
}


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////


CDotObject::CDotObject()
{

}

CDotObject::~CDotObject()
{
	CMapObject::~CMapObject();
}

CDotObject::CDotObject(int type, CString color, CString text)
{
	this->SetType(type);

	if(color=="RED")
		this->SetObjectColor(RGB(255, 0, 0));
	else if(color=="GREEN")
		this->SetObjectColor(RGB(0, 255, 0));
	else if(color=="BLUE")
		this->SetObjectColor(RGB(0, 0, 255));
	else
		this->SetObjectColor(atoi(color));

	this->SetText(text);
}




void CDotObject::DrawMap(CDC& dcMem, CRect rect)
{
	CPen pen, *pOldPen;
	CFont font, *pOldFont;
	COLORREF crOldTextColor;
	CPoint* temp;
	int x, y;


	pen.CreatePen(PS_SOLID, 1, this->GetObjectColor());
	font.CreatePointFont(250, "arial");

	pOldPen = dcMem.SelectObject(&pen);
	pOldFont = dcMem.SelectObject(&font);
	crOldTextColor = dcMem.SetTextColor(RGB(0, 0, 0));
	
	temp = this->GetDynamicPointHead();
	x = temp[0].x;
	y = temp[0].y;

	dcMem.TextOut(x, y, this->GetText());

	dcMem.SelectObject(pOldPen);
	dcMem.SelectObject(pOldFont);
	dcMem.SetTextColor(crOldTextColor);

	pen.DeleteObject();
	font.DeleteObject();
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////

CLineObject::CLineObject()
{

}

CLineObject::~CLineObject()
{
	CMapObject::~CMapObject();
}

CLineObject::CLineObject(int type, CString color, int penSize)
{
	this->SetType(type);

	if(color=="RED")
		this->SetObjectColor(RGB(255, 0, 0));
	else if(color=="GREEN")
		this->SetObjectColor(RGB(0, 255, 0));
	else if(color=="BLUE")
		this->SetObjectColor(RGB(0, 0, 255));
	else
		this->SetObjectColor(atoi(color));

	this->SetPenSize(penSize);
}



void CLineObject::DrawMap(CDC& dcMem, CRect rect)
{
	CPen pen, *pOldPen;
	int nOldBkMode;
	COLORREF crOldTextColor;
	//CPoint *temp;


	pen.CreatePen(PS_SOLID, this->GetPenSize(), this->GetObjectColor());

	pOldPen = dcMem.SelectObject(&pen);
	nOldBkMode = dcMem.SetBkMode(TRANSPARENT);
	crOldTextColor = dcMem.SetTextColor(RGB(0, 0, 0));
	
	dcMem.Polyline(this->GetDynamicPointHead(), this->GetCount());

	/*
	temp = this->GetDynamicPointHead();

	dcMem.MoveTo(temp[0].x, temp[0].y);

	for(int i=1; i<this->GetCount() ; i++)
	{
		dcMem.LineTo(temp[i].x, temp[i].y);
	}
	*/

	
	dcMem.SelectObject(pOldPen);
	dcMem.SetBkMode(nOldBkMode);

	dcMem.SetTextColor(crOldTextColor);

	pen.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

CPolyObject::CPolyObject()
{

}

CPolyObject::~CPolyObject()
{
	CMapObject::~CMapObject();
}


CPolyObject::CPolyObject(int type, CString color, CString fillColor, int penSize)
{
	this->SetType(type);

	if(color=="RED")
		this->SetObjectColor(RGB(255, 0, 0));
	else if(color=="GREEN")
		this->SetObjectColor(RGB(0, 255, 0));
	else if(color=="BLUE")
		this->SetObjectColor(RGB(0, 0, 255));
	else
		this->SetObjectColor(atoi(color));

	if(fillColor=="RED")
		this->SetFillColor(RGB(255, 0, 0));
	else if(fillColor=="GREEN")
		this->SetFillColor(RGB(0, 255, 0));
	else if(fillColor=="BLUE")
		this->SetFillColor(RGB(0, 0, 255));
	else
		this->SetFillColor(atoi(fillColor));

	this->SetPenSize(penSize);
}


void CPolyObject::DrawMap(CDC& dcMem, CRect rect)
{
	
	CPen pen, *pOldPen;
	CBrush brush, *pOldBrush;
	int nOldBkMode;
	COLORREF crOldTextColor;

	/*	//Debugging Code//
	CPoint *ttt = this->GetDynamicPointHead();
	CString sss;
	sss.Format("%d %d",ttt[0].x, ttt[0].y);
	AfxMessageBox(sss);	
	*/

	pen.CreatePen(PS_SOLID, this->GetPenSize(), this->GetObjectColor());
	brush.CreateSolidBrush(this->GetFillColor());

	pOldPen = dcMem.SelectObject(&pen);
	pOldBrush = dcMem.SelectObject(&brush);
	nOldBkMode = dcMem.SetBkMode(TRANSPARENT);
	crOldTextColor = dcMem.SetTextColor(RGB(0, 0, 0));
	
	dcMem.Polygon(this->GetDynamicPointHead(), this->GetCount());
	
	dcMem.SelectObject(pOldPen);
	dcMem.SelectObject(pOldBrush);
	dcMem.SetBkMode(nOldBkMode);

	dcMem.SetTextColor(crOldTextColor);

	pen.DeleteObject();
	brush.DeleteObject();
}