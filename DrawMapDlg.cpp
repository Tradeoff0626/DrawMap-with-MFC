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

	
	//////////////////// ��Ʈ�� ����� ���� ���� ���۸� ����  ///////////////////////////
	//////////+++++++++++++++++++++++++ Memory DC Create +++++++++++++++++///////////////
	CRect rect;
	GetClientRect(rect);

	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);
	m_bmpMem.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	m_pOldBmpMem = m_dcMem.SelectObject(&m_bmpMem);


	/////////+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++///////////////
	
	
	LoadMapFile("map.txt");			//�� ��ǥ ���� ���� �ε�
	DrawMap();						//���� ǥ��

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
	//��ȿ ����  �߻��� ����
	CPaintDC dc(this);

	CRect rect;
	GetClientRect(rect);
	
	//�޸� DC�� ������ ���� DC�� ���(����)
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
		AfxMessageBox("������ �������� �ʽ��ϴ�!");
		return;
	}
	
	char szBuf[1024];							//�� ���� ���� �� �ӽ� ����
	char *pszDelim = ",\n";						//�и��� ����
	char *pszToken;								//��ū ���� ����
	BOOL bObjectStart = FALSE;					//��ǥ ��ü ������ ���� ����

	int type = 0, index = 1;					//��ǥ Ÿ�԰� �ε���(������)
	CString color, fillColor, text;				//��ü�� ������ �Ű������� �ӽ÷� ����� ����
	int penSize;								// ...

	CPointList startNode, *tempNode;			//���Ḯ��Ʈ�� ��ǥ���� �����ϱ� ���� ������ ����

	CPoint		temp;							//��ǥ ���� �ӽ÷� ������ ����

	CObjectList *prevObj = &m_objHead;			//��ü�� ���Ḯ��Ʈ�� �����ϱ� ���� ���� ����


	while( fgets(szBuf, 1024, fp) )
	{
		CString strBuf = szBuf;

		if(strBuf.Left(5) == "START")			//START�� �о����...
		{
			bObjectStart = TRUE;				//Ȱ��ȭ
			
			//�ʱ� ó�� ����
			m_nPointCount = 0;					//��ǥ ī��Ʈ ���� �ʱ�ȭ
			type = 0;							//Ÿ�� �ʱ�ȭ
			tempNode = &startNode;				//�������� ������ ��ǥ ���� ���� �ʱ�ȭ 
			tempNode->NodeInit();				//...ó�� ����Ʈ�� �ʱ�ȭ ����
		}
		else if(strBuf.Left(3) == "END")		//END�� ������...
		{
			bObjectStart = FALSE;				//��Ȱ��
			
			//�Ϸ� ó�� ����

			m_thisObj->SetPointHead(&startNode);		//�� ��ü�� ��ǥ(���Ḯ��Ʈ)�� ��� 
			m_thisObj->SetCount(m_nPointCount);			//�� ��ü�� ��ǥ ������ ���

			CPoint* arr = new CPoint[m_nPointCount];			//polygon()�Լ��� ���ڷ� ����ϱ� ���� ������ŭ �������� �迭 ����
			CPointList* node = m_thisObj->GetPointHead();		//���Ḯ��Ʈ ���� �ּ� ����

			node->GetData(node, arr);							//���Ḯ��Ʈ�� ����� ��ǥ�� ���� �迭�� �ű�

			m_thisObj->SetDynamicPointHead(arr);				//���� �迭�� �����ּҸ� ��ü�� ���
	
			node = m_thisObj->GetPointHead();
			node->DeleteList(node);								//���� ���ʿ�� ���Ḯ��Ʈ ���� (Heap ���� Ȯ��...)

			prevObj = prevObj->AddObject(prevObj, m_thisObj);	//������� ��ü�� ���Ḯ��Ʈ�� ���
		}
		else if(bObjectStart == TRUE)							//Ȱ��ȭ��...
		{
			if(type == 0)										//�� Ÿ�Ը��� ��� ������ �Է� ���
			{
				pszToken = strtok(szBuf, pszDelim);
				type = atoi(pszToken);

				if(type==1)
				{
					pszToken = strtok(NULL, pszDelim);		// y
					color = pszToken;
					
					pszToken = strtok(NULL, pszDelim);
					text = pszToken;
					
					m_thisObj = new CDotObject(type, color, text);		//���� ��� ������ �̿��� �������� ��ü ����
					m_thisObj->SetIndex(index);							//���������� ��ü ������ ī��Ʈ �ؼ� ���
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
					AfxMessageBox("�߸��� �����Ͱ� ���Խ��ϴ�.");
				}
			}
			else
			{
				pszToken = strtok(szBuf, pszDelim);		// x				//��ǥ�� ������ �������� �����Ͽ� ����
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



	GetClientRect(rect);									//Ŭ���̾�Ʈ ���� �ν�
	ptCenter = rect.CenterPoint();							//Ŭ���̾�Ʈ�� �߾��� 

	offsetX = ptCenter.x - point.x;							//�߾����� Ŭ�� ���� ���� ����
	offsetY = ptCenter.y - point.y;

	while(TRUE)
	{	
		thisObj = currentObj->GetObject(currentObj);		//��ü�� ��ϵ� ���Ḯ��Ʈ ��ȸ
		
		dispPt = thisObj->GetDynamicPointHead();			//���� �迭�� ����� �ּ�

		for(int i=0; i<=thisObj->GetCount(); ++i)			//��ǥ�� ��ŭ ���鼭 �����°� ������ ����
		{
			dispPt[i].x += offsetX;
			dispPt[i].y += offsetY;
		}

		currentObj = currentObj->GetNextObject(currentObj);	
		
		if(!currentObj)										//���̻� ������Ʈ ������ ����
			break;
	}

	DrawMap();												//�ٽ� �׸�
	Invalidate(FALSE);										//������� ��������Ƿ� �ٽ� �׸��� �ʰ� ����
	
	CDialog::OnLButtonUp(nFlags, point);
}



void CDrawMapDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_dcMem.SelectObject(m_pOldBmpMem);
	m_bmpMem.DeleteObject();

	//m_objHead.DeleteList(m_objHead.GetNextObject(&m_objHead));
	//��ǥ �̵� �� ������ ���� �߻�
}


void CDrawMapDlg::DrawMap()
{
	CRect rect;
	GetClientRect(rect);
	CObjectList *currentObj = &m_objHead;
	CMapObject *thisObj;

	//������� Ŭ���̾�Ʈ ���� ��ü ä��
	CBrush bkBrush;
	bkBrush.CreateSolidBrush(RGB(255,255,255));
	m_dcMem.FillRect(rect, &bkBrush);
	bkBrush.DeleteObject();

	currentObj = currentObj->GetNextObject(currentObj);			//��ü ��ȸ

	while(TRUE)				
	{
		thisObj = currentObj->GetObject(currentObj);			//����Ʈ���� ��ü ����
		thisObj->DrawMap(m_dcMem, rect);						//�׸���(Call By Address ������� �޸� DC �ּ� �ѱ�)
		currentObj = currentObj->GetNextObject(currentObj);

		if(!currentObj)
			break;
	}
}


/////   thisObj->DrawMap(m_dcMem, rect); ���� Ÿ�Ժ��� DrawMap()�� �������̵��ϰ� �;��µ�,
/////   ����Ʈ�� ��ü�� �����ּҸ� �ٽ� �о�� �ٽ� CMapObject Ŭ�����θ� �νĵǾ� 
////    �������̵��� �ʵǼ� CMapObject�� DrawMap()�� ��� �׷����� ... ��¿�� ���� �����߽��ϴ�;;;;
