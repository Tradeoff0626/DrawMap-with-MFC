#include "LinkedList.h"


// MapObject.h: interface for the CMapObject class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_MAPOBJECT_H__A33786BF_513E_4CFC_B23A_DA85439B2F3F__INCLUDED_)
#define AFX_MAPOBJECT_H__A33786BF_513E_4CFC_B23A_DA85439B2F3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CMapObject  
{
private:
	int				m_nType;					//타입
	int				m_nCount;					//좌표 갯수
	COLORREF		m_objectColor;				//객체 기본 색상
	COLORREF		m_fillColor;				//채우기 색상
	CPointList*		m_PointHead;				//좌표 연결리스트 시작주소
	CPoint*			m_DPtHead;					//동적 배열 주소
	int				m_penSize;					//펜 두께
	CString			m_text;						//텍스트

	int				m_index;					//객체 인덱스

	
	
public:
	CMapObject();
	virtual ~CMapObject();

	virtual void SetType(int);
	virtual int GetType();

	virtual void SetCount(int);
	virtual int GetCount();

	virtual void SetObjectColor(COLORREF);
	virtual void SetObjectColor(CString);
	virtual COLORREF GetObjectColor();

	virtual void SetFillColor(COLORREF);
	virtual void SetFillColor(CString);
	virtual COLORREF GetFillColor();

	virtual void SetPointHead(CPointList*);
	virtual CPointList* GetPointHead();

	virtual void SetDynamicPointHead(CPoint*);
	virtual CPoint* GetDynamicPointHead();

	virtual void SetPenSize(int);
	virtual int GetPenSize();

	virtual void SetText(CString);
	virtual CString GetText();


	virtual void DrawMap(CDC&, CRect);
	
	virtual void SetIndex(int);
	virtual int GetIndex();

};




class CDotObject : public CMapObject
{
public:
	CDotObject();
	CDotObject(int, CString, CString);
	~CDotObject();

	virtual void DrawMap(CDC&, CRect);
}; 



class CLineObject : public CMapObject
{
public:
	CLineObject();
	CLineObject(int, CString, int);
	~CLineObject();

	virtual void DrawMap(CDC&, CRect);
};


class CPolyObject : public CMapObject
{
public:
	CPolyObject();
	CPolyObject(int, CString, CString, int);
	~CPolyObject();

	virtual void DrawMap(CDC&, CRect);
};






class CObjectList  
{
private:
	CMapObject		m_mapObj;
	CObjectList*	m_next;
	
public:
	CObjectList();
	virtual ~CObjectList();

	CObjectList* AddObject(CObjectList*, CMapObject*);			//객체를 노드에 추가
	void DeleteList(CObjectList*);								//모든 객체 샂게
	
	BOOL isLastObj(CObjectList*);								//마지막 오브젝트인지 판별
	

	CObjectList* GetNextObject(CObjectList*);					//다음 오브젝트 구하기
	CMapObject* GetObject(CObjectList*);						//데이터 구하기
	void GetData(CObjectList*, CMapObject*);
};

#endif // !defined(AFX_MAPOBJECT_H__A33786BF_513E_4CFC_B23A_DA85439B2F3F__INCLUDED_)
