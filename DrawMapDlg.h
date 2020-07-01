// DrawMapDlg.h : header file
//

#include "MapObject.h"

#if !defined(AFX_DRAWMAPDLG_H__A0DE99BE_41FB_4285_856A_FB3FA515CB22__INCLUDED_)
#define AFX_DRAWMAPDLG_H__A0DE99BE_41FB_4285_856A_FB3FA515CB22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDrawMapDlg dialog



class CDrawMapDlg : public CDialog
{
// Construction
public:
	CDrawMapDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDrawMapDlg)
	enum { IDD = IDD_DRAWMAP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawMapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

	void LoadMapFile(char* pszFileName);
	void DrawMap();
// Implementation
protected:
	HICON m_hIcon;
	
	int m_nPointCount;

	CMapObject *m_thisObj;
	CObjectList m_objHead;
	

	CDC m_dcMem;
	CBitmap m_bmpMem, *m_pOldBmpMem;


	// Generated message map functions
	//{{AFX_MSG(CDrawMapDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWMAPDLG_H__A0DE99BE_41FB_4285_856A_FB3FA515CB22__INCLUDED_)
