#pragma once
#include "afxcmn.h"
class RootTabCtrl :
	public CTabCtrl
{
public:

	int m_nTabs;
	CDialog* m_Tabs[4];
	int m_TabIDs[4];
	int m_Count;
	int m_currentTab;

	RootTabCtrl();
	~RootTabCtrl();

	void Init();
	void SetRectangle();

protected:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	// Declares that the class defines a message map.Each CCmdTarget -
	// derived class in your program must provide a message map to handle messages.
	DECLARE_MESSAGE_MAP()
};

