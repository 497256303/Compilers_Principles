
// byDlg.h : header file
//

#if !defined(AFX_BYDLG_H__B1839D0D_A081_4791_8F8A_05AC926E5C51__INCLUDED_)
#define AFX_BYDLG_H__B1839D0D_A081_4791_8F8A_05AC926E5C51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CByDlg dialog
#include<iostream>
#include<string.h>
#include<ctype.h>
#include<conio.h>
#include<fstream>
#include<stdio.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;
#define  MAX 18			//分析表的最大容量
#define  MAXBUF 255
#define WORD_LENGTH 130 // 单词最大长度
#define WORD_OF_PROGRAM 1000 //最大单词数
#include"link.h"


class CByDlg : public CDialog
{
// Construction
public:
	void analyse(FILE *fpin,FILE *fpout);
	CByDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CByDlg)
	enum { IDD = IDD_BY_DIALOG };
	CLink	m_me;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CByDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
		
	
	CString m_strFileName;


	// Generated message map functions
	//{{AFX_MSG(CByDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnOpen();
	afx_msg void OnFenxi();
	afx_msg void OnSave();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CFont m_font;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BYDLG_H__B1839D0D_A081_4791_8F8A_05AC926E5C51__INCLUDED_)
