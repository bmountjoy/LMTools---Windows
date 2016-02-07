#include "stdafx.h"
#include "resource.h"
#include "TCDDialog.h"
#include "RootTabCtrl.h"

RootTabCtrl::RootTabCtrl(void)
{
	m_nTabs = 1;
	m_Tabs[0] = new TCDDialog();
	m_TabIDs[0] = IDD_TCD_DIALOG;
}

RootTabCtrl::~RootTabCtrl(void)
{
}

void RootTabCtrl::Init()
{
	m_currentTab = 0;

	for (int tabID = 0; tabID < m_nTabs; ++tabID)
	{
		m_Tabs[tabID]->Create(m_TabIDs[tabID], this);
		if (tabID == m_currentTab) {
			m_Tabs[tabID]->ShowWindow(SW_SHOW);
		}
		else {
			m_Tabs[tabID]->ShowWindow(SW_HIDE);
		}
	}

	SetRectangle();
}

void RootTabCtrl::SetRectangle()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX = itemRect.left;
	nY = itemRect.bottom + 1;
	nXc = tabRect.right - itemRect.left - 1;
	nYc = tabRect.bottom - nY - 1;

	for (int tabId = 0; tabId < m_nTabs; ++tabId)
	{
		if (tabId == m_currentTab)
			m_Tabs[tabId]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
		else
			m_Tabs[tabId]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	}
}

BEGIN_MESSAGE_MAP(RootTabCtrl, CTabCtrl)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void RootTabCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// Default behavior
	CTabCtrl::OnLButtonDown(nFlags, point);

	if (m_currentTab != GetCurFocus())
	{
		m_Tabs[m_currentTab]->ShowWindow(SW_HIDE);
		m_currentTab = GetCurFocus();
		m_Tabs[m_currentTab]->ShowWindow(SW_SHOW);
		m_Tabs[m_currentTab]->SetFocus();
	}
}