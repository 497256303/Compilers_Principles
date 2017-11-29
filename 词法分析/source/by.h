// by.h : main header file for the BY application
//

#if !defined(AFX_BY_H__FC83D73D_8F90_4854_AC34_0EE3CCE8BF40__INCLUDED_)
#define AFX_BY_H__FC83D73D_8F90_4854_AC34_0EE3CCE8BF40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CByApp:
// See by.cpp for the implementation of this class
//

class CByApp : public CWinApp
{
public:
	CByApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CByApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CByApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BY_H__FC83D73D_8F90_4854_AC34_0EE3CCE8BF40__INCLUDED_)
