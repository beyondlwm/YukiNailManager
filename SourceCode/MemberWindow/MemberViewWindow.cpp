
    // _MEMBERVIEWWINDOW_H_
/////////////////////////////////////////////////////////////////////////////
// Name:        memberviewwindow.cpp
// Purpose:     
// Author:      
// Modified by: 
// Created:     14/12/2013 16:55:30
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 14/12/2013 16:55:30

// For compilers that support precompilation, includes "wx/wx.h".
#include "stdafx.h"
#include "wx/wxprec.h"
#include "../Member/Member.h"
#include "../Member/MemberManager.h"
#include "../ConsumeRecordWindow/ConsumeRecordWindow.h"
#include "../YukiNailShopManager.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
#include "wx/imaglist.h"
////@end includes

#include "MemberViewWindow.h"

////@begin XPM images
////@end XPM images


/*
 * CMemberViewWindow type definition
 */

IMPLEMENT_DYNAMIC_CLASS( CMemberViewWindow, wxDialog )


/*
 * CMemberViewWindow event table definition
 */

BEGIN_EVENT_TABLE( CMemberViewWindow, wxDialog )

////@begin CMemberViewWindow event table entries
    EVT_LIST_ITEM_ACTIVATED( ID_LISTCTRL, CMemberViewWindow::OnListctrlItemActivated )
    EVT_LIST_COL_CLICK(ID_LISTCTRL, CMemberViewWindow::OnListctrlColClick)
    EVT_BUTTON( ID_BUTTON11, CMemberViewWindow::OnViewHistoryBtnClick )
    EVT_BUTTON( ID_BUTTON12, CMemberViewWindow::OnCloseClick )
////@end CMemberViewWindow event table entries

END_EVENT_TABLE()


/*
 * CMemberViewWindow constructors
 */

CMemberViewWindow::CMemberViewWindow()
{
    Init();
}

CMemberViewWindow::CMemberViewWindow( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create(parent, id, caption, pos, size, style);
}


/*
 * CMemberViewWindow creator
 */

bool CMemberViewWindow::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CMemberViewWindow creation
    SetExtraStyle(wxWS_EX_BLOCK_EVENTS);
    wxDialog::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end CMemberViewWindow creation
    return true;
}


/*
 * CMemberViewWindow destructor
 */

CMemberViewWindow::~CMemberViewWindow()
{
////@begin CMemberViewWindow destruction
////@end CMemberViewWindow destruction
}


/*
 * Member initialisation
 */

void CMemberViewWindow::Init()
{
////@begin CMemberViewWindow member initialisation
    m_bSortReverse = false;
    m_pMemberCountLabel = NULL;
    m_pAllMoneyLabel = NULL;
    m_pMemberInfoList = NULL;
     m_pViewHistoryBtn = NULL;
    m_pCloseBtn = NULL;
////@end CMemberViewWindow member initialisation
}


/*
 * Control creation for CMemberViewWindow
 */

void CMemberViewWindow::CreateControls()
{    
////@begin CMemberViewWindow content construction
    // Generated by DialogBlocks, 14/12/2013 17:16:51 (unregistered)

    CMemberViewWindow* itemDialog1 = this;

    wxBoxSizer* itemBoxSizer2 = new wxBoxSizer(wxVERTICAL);
    itemDialog1->SetSizer(itemBoxSizer2);

    wxBoxSizer* itemBoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5);

    wxStaticText* itemStaticText4 = new wxStaticText( itemDialog1, wxID_STATIC, wxGetTranslation(wxString() + (wxChar) 0x4F1A + (wxChar) 0x5458 + (wxChar) 0x7BA1 + (wxChar) 0x7406), wxDefaultPosition, wxDefaultSize, 0 );
    itemStaticText4->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false, wxT("����")));
    itemBoxSizer3->Add(itemStaticText4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer5, 0, wxALIGN_LEFT|wxALL, 5);

    m_pMemberCountLabel = new wxStaticText( itemDialog1, wxID_STATIC, wxGetTranslation(wxString() + (wxChar) 0x4F1A + (wxChar) 0x5458 + (wxChar) 0x4EBA + (wxChar) 0x6570 + wxT(": 10000")), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(m_pMemberCountLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pAllMoneyLabel = new wxStaticText( itemDialog1, wxID_STATIC, wxGetTranslation(wxString() + (wxChar) 0x603B + (wxChar) 0x4F59 + (wxChar) 0x989D + wxT(": 1000000")), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer5->Add(m_pAllMoneyLabel, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    wxBoxSizer* itemBoxSizer8 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer8, 1, wxGROW|wxALL, 5);

    m_pMemberInfoList = new wxListCtrl( itemDialog1, ID_LISTCTRL, wxDefaultPosition, wxSize(100, 100), wxLC_REPORT );
    itemBoxSizer8->Add(m_pMemberInfoList, 1, wxGROW|wxALL, 5);
    m_pMemberInfoList->InsertColumn(0, _T("����"));
    m_pMemberInfoList->InsertColumn(1, _T("�绰"));
    m_pMemberInfoList->InsertColumn(2, _T("���"));
    m_pMemberInfoList->InsertColumn(3, _T("�ۿ�����"));
    m_pMemberInfoList->InsertColumn(4, _T("����"));
    m_pMemberInfoList->SetColumnWidth(4, 100);
    m_pMemberInfoList->InsertColumn(5, _T("ע��ʱ��"));
    m_pMemberInfoList->SetColumnWidth(5, 130);

    wxBoxSizer* itemBoxSizer10 = new wxBoxSizer(wxHORIZONTAL);
    itemBoxSizer2->Add(itemBoxSizer10, 0, wxALIGN_RIGHT|wxALL, 5);

     m_pViewHistoryBtn = new wxButton( itemDialog1, ID_BUTTON11, wxGetTranslation(wxString() + (wxChar) 0x67E5 + (wxChar) 0x770B + (wxChar) 0x8BB0 + (wxChar) 0x5F55), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add( m_pViewHistoryBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pCloseBtn = new wxButton( itemDialog1, ID_BUTTON12, wxGetTranslation(wxString() + (wxChar) 0x5173 + (wxChar) 0x95ED), wxDefaultPosition, wxDefaultSize, 0 );
    itemBoxSizer10->Add(m_pCloseBtn, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    UpdateData();
////@end CMemberViewWindow content construction
}


/*
 * Should we show tooltips?
 */

bool CMemberViewWindow::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap CMemberViewWindow::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CMemberViewWindow bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CMemberViewWindow bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon CMemberViewWindow::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CMemberViewWindow icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CMemberViewWindow icon retrieval
}

void CMemberViewWindow::OnListctrlItemActivated( wxListEvent& event )
{
    wxCommandEvent simulateEvent;
    OnViewHistoryBtnClick(simulateEvent);
}


void CMemberViewWindow::OnListctrlColClick( wxListEvent& event )
{
    int iColumnIndex = event.GetColumn();
    switch (iColumnIndex)
    {
    case 2://balance
        m_pMemberInfoList->SortItems(CMemberViewWindow::MemberBalanceCompare, (wxIntPtr)this);
        break;
    case 4://birthday
        m_pMemberInfoList->SortItems(CMemberViewWindow::MemberBirthDayCompare, (wxIntPtr)this);
    	break;
    case 5://register time
        m_pMemberInfoList->SortItems(CMemberViewWindow::MemberRegisterDateCompare, (wxIntPtr)this);
        break;
    default:
        break;
    }
    m_bSortReverse = !m_bSortReverse;
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON11
 */

void CMemberViewWindow::OnViewHistoryBtnClick( wxCommandEvent& event )
{
    long item = m_pMemberInfoList->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (item == -1)
    {
        wxMessageBox(_T("����ѡ��һ����Ա"));
    }
    else
    {
        wxListItem listItem;
        listItem.SetId(item);
        TString strTel = m_pMemberInfoList->GetItemText(listItem, 1);
        CMember* pMember = CMemberManager::GetInstance()->GetMember(strTel);
        BEATS_ASSERT(pMember != NULL);
        if (pMember)
        {
            CConsumeRecordWindow dlg(this);
            dlg.UpdateData(pMember);
            int iRet = dlg.ShowModal();
            if (iRet == 2) // canceled a member
            {
                this->UpdateData();
            }
        }
    }
}

/*
 * wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON12
 */

void CMemberViewWindow::OnCloseClick( wxCommandEvent& event )
{
    EndModal(0);
}

int wxCALLBACK CMemberViewWindow::MemberRegisterDateCompare(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData)
{
    int iRet = 1;
    CMember* pMember1 = (CMember*)item1;
    CMember* pMember2 = (CMember*)item2;
    CMemberViewWindow* pMemberViewWnd = (CMemberViewWindow*)sortData;
    if (pMember1 && pMember2 && pMemberViewWnd)
    {
        SystemTimeSort sortData;
        bool bGreater = sortData(&pMember1->GetRegisterTime(), &pMember2->GetRegisterTime());
        bool bLess = sortData(&pMember2->GetRegisterTime(), &pMember1->GetRegisterTime());
        if (!bGreater && !bLess)
        {
            iRet = 0;
        }
        else
        {
            iRet = bGreater ? -1 : 1;
        }
        if (pMemberViewWnd->m_bSortReverse)
        {
            iRet *= -1;
        }
    }
    return iRet;
}

int wxCALLBACK CMemberViewWindow::MemberBirthDayCompare(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData)
{
    int iRet = 1;
    CMember* pMember1 = (CMember*)item1;
    CMember* pMember2 = (CMember*)item2;
    CMemberViewWindow* pMemberViewWnd = (CMemberViewWindow*)sortData;
    if (pMember1 && pMember2 && pMemberViewWnd)
    {
        const SYSTEMTIME& birthday1 = pMember1->GetBirthday();
        const SYSTEMTIME& birthday2 = pMember2->GetBirthday();
        if (birthday1.wMonth == birthday2.wMonth)
        {
            if (birthday1.wDay == birthday2.wDay)
            {
                iRet = 0;
            }
            else
            {
                iRet = birthday1.wDay > birthday2.wDay ? 1 : -1;
            }
        }
        else
        {
            iRet = birthday1.wMonth > birthday2.wMonth ? 1 : -1;
        }
        if (pMemberViewWnd->m_bSortReverse)
        {
            iRet *= -1;
        }
    }
    return iRet;
}

int wxCALLBACK CMemberViewWindow::MemberBalanceCompare(wxIntPtr item1, wxIntPtr item2, wxIntPtr sortData)
{
    int iRet = 0;
    CMember* pMember1 = (CMember*)item1;
    CMember* pMember2 = (CMember*)item2;
    CMemberViewWindow* pMemberViewWnd = (CMemberViewWindow*)sortData;
    if (pMember1 && pMember2 && pMemberViewWnd)
    {
        float fBalance1 = pMember1->GetBalance();
        float fBalance2 = pMember2->GetBalance();
        if (!BEATS_FLOAT_EQUAL(fBalance1, fBalance2))
        {
            iRet = fBalance1 > fBalance2 ? 1 : -1;
        }
        if (pMemberViewWnd->m_bSortReverse)
        {
            iRet *= -1;
        }
    }
    return iRet;
}

void CMemberViewWindow::UpdateData()
{
    m_pMemberInfoList->DeleteAllItems();
    const std::map<const TString, CMember*>& memberMap = CMemberManager::GetInstance()->GetMemberMap();
    wxListItem listItem;
    size_t uIdCounter = 0;
    float fTotalMoney = 0;
    for (std::map<const TString, CMember*>::const_iterator iter = memberMap.begin(); iter != memberMap.end(); ++iter)
    {
        if (iter->second->GetCancelFlag() == false)
        {
            listItem.SetId(uIdCounter);
            listItem.SetColumn(0);
            listItem.SetText(iter->second->GetName());
            listItem.SetData(iter->second);
            m_pMemberInfoList->InsertItem(listItem);

            listItem.SetColumn(1);
            listItem.SetText(iter->second->GetTelString());
            m_pMemberInfoList->SetItem(listItem);

            listItem.SetColumn(2);
            listItem.SetText(wxString::Format(_T("%.3f"), iter->second->GetBalance()));
            m_pMemberInfoList->SetItem(listItem);

            listItem.SetColumn(3);
            listItem.SetText(iter->second->GetDiscountTypeString());
            m_pMemberInfoList->SetItem(listItem);

            listItem.SetColumn(4);
            const SYSTEMTIME& birthDay = iter->second->GetBirthday();
            listItem.SetText(wxString::Format(_T("%d-%d-%d"), birthDay.wYear, birthDay.wMonth, birthDay.wDay));
            m_pMemberInfoList->SetItem(listItem);

            listItem.SetColumn(5);
            const SYSTEMTIME& registerTime = iter->second->GetRegisterTime();
            listItem.SetText(wxString::Format(_T("%d-%d-%d %d:%.2d"), registerTime.wYear, registerTime.wMonth, registerTime.wDay, registerTime.wHour, registerTime.wMinute));
            m_pMemberInfoList->SetItem(listItem);

            fTotalMoney += iter->second->GetBalance();
            ++uIdCounter;
        }
    }
    m_pMemberInfoList->SortItems(CMemberViewWindow::MemberRegisterDateCompare, (wxIntPtr)this);
    m_pMemberCountLabel->SetLabel(wxString::Format(_T("��Ա����: %d"), uIdCounter));
    m_pAllMoneyLabel->SetLabel(wxString::Format(_T("�����: %.3f"), fTotalMoney));
}

