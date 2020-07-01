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

	CPointList* AddNode(CPointList*, CPoint);	//이전 노드에 노드 추가
	void DeleteList(CPointList*);				//모든 도드 삭제

	void NodeInit();							//노드 초기화

	void GetData(CPointList*, CPoint*);			//노드서 데이터만 구하기
};


#endif // !defined(AFX_LINKEDLIST_H__85392E9A_1C85_43C4_A20A_DFCAA866DF02__INCLUDED_)


//연결리스트를 클래스로 구현 해본건 처음이라 허접합니다...;;
//내부적으로 this 키워드를 사용해도 될것 같은데...인자로 다시 객체를 지정하게 만들었습니다;;;