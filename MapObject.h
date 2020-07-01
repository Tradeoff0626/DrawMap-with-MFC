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
	int				m_nType;					//Ÿ��
	int				m_nCount;					//��ǥ ����
	COLORREF		m_objectColor;				//��ü �⺻ ����
	COLORREF		m_fillColor;				//ä��� ����
	CPointList*		m_PointHead;				//��ǥ ���Ḯ��Ʈ �����ּ�
	CPoint*			m_DPtHead;					//���� �迭 �ּ�
	int				m_penSize;					//�� �β�
	CString			m_text;						//�ؽ�Ʈ

	int				m_index;					//��ü �ε���

	
	
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

	CObjectList* AddObject(CObjectList*, CMapObject*);			//��ü�� ��忡 �߰�
	void DeleteList(CObjectList*);								//��� ��ü ����
	
	BOOL isLastObj(CObjectList*);								//������ ������Ʈ���� �Ǻ�
	

	CObjectList* GetNextObject(CObjectList*);					//���� ������Ʈ ���ϱ�
	CMapObject* GetObject(CObjectList*);						//������ ���ϱ�
	void GetData(CObjectList*, CMapObject*);
};

#endif // !defined(AFX_MAPOBJECT_H__A33786BF_513E_4CFC_B23A_DA85439B2F3F__INCLUDED_)
