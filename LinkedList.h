// LinkedList.h: interface for the CLinkedList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LINKEDLIST_H__85392E9A_1C85_43C4_A20A_DFCAA866DF02__INCLUDED_)
#define AFX_LINKEDLIST_H__85392E9A_1C85_43C4_A20A_DFCAA866DF02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPointList  
{
private:
	CPoint		m_pointData;
	CPointList*		m_next;
	
public:
	CPointList();
	virtual ~CPointList();

	CPointList* AddNode(CPointList*, CPoint);	//���� ��忡 ��� �߰�
	void DeleteList(CPointList*);				//��� ���� ����

	void NodeInit();							//��� �ʱ�ȭ

	void GetData(CPointList*, CPoint*);			//��弭 �����͸� ���ϱ�
};


#endif // !defined(AFX_LINKEDLIST_H__85392E9A_1C85_43C4_A20A_DFCAA866DF02__INCLUDED_)


//���Ḯ��Ʈ�� Ŭ������ ���� �غ��� ó���̶� �����մϴ�...;;
//���������� this Ű���带 ����ص� �ɰ� ������...���ڷ� �ٽ� ��ü�� �����ϰ� ��������ϴ�;;;