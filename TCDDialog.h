#pragma once

#include <gdal_priv.h>
#include <ogrsf_frmts.h>

// TCDDialog dialog

class TCDDialog : public CDialogEx
{
	DECLARE_DYNAMIC(TCDDialog)

public:
	TCDDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~TCDDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TCD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
