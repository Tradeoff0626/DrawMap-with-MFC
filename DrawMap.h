// DrawMap.h : main header file for the DRAWMAP application
//

#if !defined(AFX_DRAWMAP_H__14253A34_606B_4006_AA80_1F8C6E57FA9B__INCLUDED_)
#define AFX_DRAWMAP_H__14253A34_606B_4006_AA80_1F8C6E57FA9B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDrawMapApp:
// See DrawMap.cpp for the implementation of this class
//

class CDrawMapApp : public CWinApp
{
public:
	CDrawMapApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDrawMapApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDrawMapApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAWMAP_H__14253A34_606B_4006_AA80_1F8C6E57FA9B__INCLUDED_)
