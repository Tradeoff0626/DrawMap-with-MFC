// DrawMapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DrawMap.h"
#include "DrawMapDlg.h"
#include "LinkedList.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawMapDlg dialog

CDrawMapDlg::CDrawMapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDrawMapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDrawMapDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDrawMapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDrawMapDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDrawMapDlg, CDialog)
	//{{AFX_MSG_MAP(CDrawMapDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDrawMapDlg message handlers

BOOL CDrawMapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	
	//////////////////// 비트맵 사용을 위한 더블 퍼퍼링 선언  ///////////////////////////
	//////////+++++++++++++++++++++++++ Memory DC Create +++++++++++++++++///////////////
	CRect rect;
	GetClientRect(rect);

	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_bmpMem.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	m_pOldBmpMem = m_dcMem.SelectObject(&m_bmpMem);


	/////////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///////////////
	
	
	LoadMapFile("map.txt");			//맵 좌표 샘플 파일 로딩
	DrawMap();						//최초 표시

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDrawMapDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDrawMapDlg::OnPaint() 
{
	//무효 영역  발생시 수행
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(rect);
	
	//메모리 DC의 내용을 메인 DC에 출력(복사)
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_dcMem, 0, 0, SRCCOPY);
 
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDrawMapDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CDrawMapDlg::LoadMapFile(char* pszFileName)
{
	FILE *fp = fopen(pszFileName, "rt");
	if(fp==NULL)
	{
		AfxMessageBox("파일이 존재하지 않습니다!");
		return;
	}
	
	char szBuf[1024];							//한 줄을 저장 할 임시 버퍼
	char *pszDelim = ",\n";						//분리자 설정
	char *pszToken;								//토큰 문자 버퍼
	BOOL bObjectStart = FALSE;					//좌표 객체 구분자 설정 변수

	int type = 0, index = 1;					//좌표 타입과 인덱스(디버깅용)
	CString color, fillColor, text;				//객체에 저장할 매개변수를 임시로 기억할 변수
	int penSize;								// ...

	CPointList startNode, *tempNode;			//연결리스트로 좌표값을 저장하기 위해 선언한 변수

	CPoint		temp;							//좌표 값을 임시로 저장할 변수

	CObjectList *prevObj = &m_objHead;			//객체를 연결리스트로 저장하기 위해 만든 변수


	while( fgets(szBuf, 1024, fp) )
	{
		CString strBuf = szBuf;

		if(strBuf.Left(5) == "START")			//START를 읽어오면...
		{
			bObjectStart = TRUE;				//활성화
			
			//초기 처리 구현
			m_nPointCount = 0;					//좌표 카운트 갯수 초기화
			type = 0;							//타입 초기화
			tempNode = &startNode;				//동적으로 저장할 좌표 시작 변수 초기화 
			tempNode->NodeInit();				//...처음 리스트의 초기화 수행
		}
		else if(strBuf.Left(3) == "END")		//END를 읽으면...
		{
			bObjectStart = FALSE;				//비활성
			
			//완료 처리 구현

			m_thisObj->SetPointHead(&startNode);		//그 객체의 좌표(연결리스트)를 등록 
			m_thisObj->SetCount(m_nPointCount);			//그 객체의 좌표 갯수를 등록

			CPoint* arr = new CPoint[m_nPointCount];			//polygon()함수의 인자로 사용하기 위해 갯수만큼 동적으로 배열 선언
			CPointList* node = m_thisObj->GetPointHead();		//연결리스트 시작 주소 받음

			node->GetData(node, arr);							//연결리스트로 저장된 좌표를 동적 배열에 옮김

			m_thisObj->SetDynamicPointHead(arr);				//동적 배열의 시작주소를 객체에 등록
	
			node = m_thisObj->GetPointHead();
			node->DeleteList(node);								//원본 불필요시 연결리스트 제거 (Heap 영역 확보...)

			prevObj = prevObj->AddObject(prevObj, m_thisObj);	//만들어진 객체를 연결리스트에 등록
		}
		else if(bObjectStart == TRUE)							//활성화시...
		{
			if(type == 0)										//각 타입마다 헤더 정보를 입력 기억
			{
				pszToken = strtok(szBuf, pszDelim);
				type = atoi(pszToken);

				if(type==1)
				{
					pszToken = strtok(NULL, pszDelim);		// y
					color = pszToken;
					
					pszToken = strtok(NULL, pszDelim);
					text = pszToken;
					
					m_thisObj = new CDotObject(type, color, text);		//받은 헤더 정보를 이용해 동적으로 객체 생성
					m_thisObj->SetIndex(index);							//디버깅용으로 객체 갯수를 카운트 해서 기억
					++index;

				}
				else if(type==2)
				{
					pszToken = strtok(NULL, pszDelim);		// y
					color = pszToken;

					pszToken = strtok(NULL, pszDelim);
					penSize = atoi(pszToken);

					m_thisObj = new CLineObject(type, color, penSize);
					m_thisObj->SetIndex(index);
					++index;
				}
				else if(type==3)
				{
					pszToken = strtok(NULL, pszDelim);		// y
					color = pszToken;
					
					pszToken = strtok(NULL, pszDelim);
					fillColor = pszToken;

					pszToken = strtok(NULL, pszDelim);
					penSize = atoi(pszToken);

					m_thisObj = new CPolyObject(type, color, fillColor, penSize);
					m_thisObj->SetIndex(index);
					++index;
				}
				else
				{
					AfxMessageBox("잘못된 데이터가 들어왔습니다.");
				}
			}
			else
			{
				pszToken = strtok(szBuf, pszDelim);		// x				//좌표가 있으면 동적으로 생성하여 저장
				temp.x = atoi(pszToken);

				pszToken = strtok(NULL, pszDelim);		// y
				temp.y = atoi(pszToken);

				tempNode = tempNode->AddNode(tempNode, temp);

				++m_nPointCount;
			}
			
		}
	}
	fclose(fp);
}

void CDrawMapDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	CPoint ptCenter;
	CRect rect;
	int offsetX, offsetY;
	CPoint* dispPt;

	CObjectList *currentObj = &m_objHead;
	CMapObject *thisObj;



	GetClientRect(rect);									//클라이언트 영역 인식
	ptCenter = rect.CenterPoint();							//클라이언트의 중앙점 

	offsetX = ptCenter.x - point.x;							//중앙점과 클릭 영역 차이 저장
	offsetY = ptCenter.y - point.y;

	while(TRUE)
	{	
		thisObj = currentObj->GetObject(currentObj);		//객체가 등록된 연결리스트 순회
		
		dispPt = thisObj->GetDynamicPointHead();			//동적 배열이 저장된 주소

		for(int i=0; i<=thisObj->GetCount(); ++i)			//좌표수 만큼 돌면서 오프셋값 연산후 저장
		{
			dispPt[i].x += offsetX;
			dispPt[i].y += offsetY;
		}

		currentObj = currentObj->GetNextObject(currentObj);	
		
		if(!currentObj)										//더이상 오브젝트 없을시 종료
			break;
	}

	DrawMap();												//다시 그림
	Invalidate(FALSE);										//흰색으로 덮어쓰여지므로 다시 그리지 않고 갱신
	
	CDialog::OnLButtonUp(nFlags, point);
}



void CDrawMapDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_dcMem.SelectObject(m_pOldBmpMem);
	m_bmpMem.DeleteObject();

	//m_objHead.DeleteList(m_objHead.GetNextObject(&m_objHead));
	//좌표 이동 후 삭제시 문제 발생
}


void CDrawMapDlg::DrawMap()
{
	CRect rect;
	GetClientRect(rect);
	CObjectList *currentObj = &m_objHead;
	CMapObject *thisObj;

	//흰색으로 클라이언트 영역 전체 채움
	CBrush bkBrush;
	bkBrush.CreateSolidBrush(RGB(255,255,255));
	m_dcMem.FillRect(rect, &bkBrush);
	bkBrush.DeleteObject();

	currentObj = currentObj->GetNextObject(currentObj);			//객체 순회

	while(TRUE)				
	{
		thisObj = currentObj->GetObject(currentObj);			//리스트에서 객체 추출
		thisObj->DrawMap(m_dcMem, rect);						//그리기(Call By Address 방식으로 메모리 DC 주소 넘김)
		currentObj = currentObj->GetNextObject(currentObj);

		if(!currentObj)
			break;
	}
}


/////   thisObj->DrawMap(m_dcMem, rect); 에서 타입별로 DrawMap()을 오버라이딩하고 싶었는데,
/////   연결트로 객체의 시작주소만 다시 읽어보니 다시 CMapObject 클래스로만 인식되어 
////    오버라이딩이 않되서 CMapObject의 DrawMap()을 모두 그려지게 ... 어쩔수 없이 수정했습니다;;;;
