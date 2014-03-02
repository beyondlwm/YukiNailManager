#include "stdafx.h"
#include "../Account/AccountManager.h"
#include "MainWindow.h"
#include "../ShapButton/ShapeButton.h"
#include "../MainApp.h"
#include "../Account/Account.h"
#include "../YukiNailShopManager.h"
#include "../BalanceWindow/BalanceWindow.h"
#include "../SummaryWindow/SummaryWindow.h"
#include "../RegisterWindow/RegisterWindow.h"
#include "../AccountWindow/AccountWindow.h"
#include "../MemberWindow/MemberWindow.h"

IMPLEMENT_CLASS( CMainWindow, wxFrame )

/*
 * CMainWindow constructors
 */

CMainWindow::CMainWindow()
{
    Init();
}

CMainWindow::CMainWindow( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}

/*
 * CMainWindow creator
 */

bool CMainWindow::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin CMainWindow creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end CMainWindow creation
    return true;
}


/*
 * CMainWindow destructor
 */

CMainWindow::~CMainWindow()
{
    BEATS_SAFE_DELETE(m_pBackGroundImage);
}


/*
 * Member initialisation
 */

void CMainWindow::Init()
{
}

/*
 * Control creation for CMainWindow
 */

void CMainWindow::CreateControls()
{
    SetCurrentDirectory(CMainApp::GetMainApp()->GetWorkPath().c_str());
    m_pBackGroundImage = new wxImage(_T("../Resource/MainWindowBackGround.jpg"), wxBITMAP_TYPE_JPEG);
    m_pBackGroundImage->Rescale(SYMBOL_CMAINWINDOW_SIZE.x, SYMBOL_CMAINWINDOW_SIZE.y);

    m_pBackGroundPanel = new wxPanel( this, ID_PANEL, wxDefaultPosition, wxDefaultSize, wxSUNKEN_BORDER|wxTAB_TRAVERSAL );
    wxBoxSizer* itemBoxSizer = new wxBoxSizer(wxHORIZONTAL);

    itemBoxSizer->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pBalanceBtn = new CShapeButton(m_pBackGroundPanel, _T(""));
    wxImage* pImage = new wxImage(_T("../Resource/Balance_Normal.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pBalanceBtn->SetNormalImage(pImage);

    pImage = new wxImage(_T("../Resource/Balance_OnHover.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pBalanceBtn->SetHoverImage(pImage);
    pImage = new wxImage(_T("../Resource/Balance_OnPress.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pBalanceBtn->SetPressedImage(pImage);
    m_pBalanceBtn->SetBackgroundImage(m_pBackGroundImage);

    itemBoxSizer->Add(m_pBalanceBtn, 1, wxALIGN_CENTER_VERTICAL|wxTOP, 400);

    m_pMemeberBtn = new CShapeButton(m_pBackGroundPanel, _T(""));
    pImage = new wxImage(_T("../Resource/Member_Normal.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pMemeberBtn->SetNormalImage(pImage);
    pImage = new wxImage(_T("../Resource/Member_OnHover.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pMemeberBtn->SetHoverImage(pImage);
    pImage = new wxImage(_T("../Resource/Member_OnPress.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pMemeberBtn->SetPressedImage(pImage);
    m_pMemeberBtn->SetBackgroundImage(m_pBackGroundImage);

    itemBoxSizer->Add(m_pMemeberBtn, 1, wxALIGN_CENTER_VERTICAL|wxTOP, 400);


    m_pSummaryBtn = new CShapeButton(m_pBackGroundPanel, _T(""));
    pImage = new wxImage(_T("../Resource/Summary_Normal.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pSummaryBtn->SetNormalImage(pImage);
    pImage = new wxImage(_T("../Resource/Summary_OnHover.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pSummaryBtn->SetHoverImage(pImage);
    pImage = new wxImage(_T("../Resource/Summary_OnPress.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pSummaryBtn->SetPressedImage(pImage);
    m_pSummaryBtn->SetBackgroundImage(m_pBackGroundImage);

    itemBoxSizer->Add(m_pSummaryBtn, 1, wxALIGN_CENTER_VERTICAL|wxTOP, 400);


    m_pAccountBtn = new CShapeButton(m_pBackGroundPanel, _T(""));
    pImage = new wxImage(_T("../Resource/Account_Normal.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pAccountBtn->SetNormalImage(pImage);
    pImage = new wxImage(_T("../Resource/Account_onHover.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pAccountBtn->SetHoverImage(pImage);
    pImage = new wxImage(_T("../Resource/Account_OnPress.Png"), wxBITMAP_TYPE_PNG);
    pImage->Rescale(113, 113);
    m_pAccountBtn->SetPressedImage(pImage);
    m_pAccountBtn->SetBackgroundImage(m_pBackGroundImage);

    itemBoxSizer->Add(m_pAccountBtn, 1,wxALIGN_CENTER_VERTICAL|wxTOP, 400);

    itemBoxSizer->Add(5, 5, 1, wxALIGN_CENTER_VERTICAL|wxALL, 5);

    m_pBackGroundPanel->SetSizerAndFit(itemBoxSizer);

    m_pBalanceBtn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CMainWindow::OnClickBalance), NULL, this);
    m_pSummaryBtn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CMainWindow::OnClickSummary), NULL, this);
    m_pAccountBtn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CMainWindow::OnClickAccount), NULL, this);
    m_pMemeberBtn->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(CMainWindow::OnClickMember), NULL, this);
    m_pBackGroundPanel->Connect(ID_PANEL, wxEVT_PAINT, wxPaintEventHandler(CMainWindow::OnPaint), NULL, this);
}

/*
 * wxEVT_COMMAND_TEXT_ENTER event handler for ID_TEXTCTRL
 */

/*
 * Should we show tooltips?
 */

bool CMainWindow::ShowToolTips()
{
    return true;
}

void CMainWindow::ShowUp(bool bVisible)
{
    if (bVisible)
    {
        CAccount* pAccount = CYukiNailShopManager::GetInstance()->GetCurrentOperatorAccount();
        BEATS_ASSERT(pAccount != NULL);
        if (pAccount)
        {
            m_pBalanceBtn->Show(pAccount->CheckPrivilege(CAccount::eAPT_Balance));
            bool bCanOperatorMember = pAccount->CheckPrivilege(CAccount::eAPT_MemberQuery) || pAccount->CheckPrivilege(CAccount::eAPT_MemberRegister) || pAccount->CheckPrivilege(CAccount::eAPT_MemberManage);
            m_pMemeberBtn->Show(bCanOperatorMember);
            m_pSummaryBtn->Show(pAccount->CheckPrivilege(CAccount::eAPT_Summary));
            m_pAccountBtn->Show(pAccount->CheckPrivilege(CAccount::eAPT_OperateAccount));
            this->Show(true);
        }
    }
    else
    {
        this->Show(false);
    }
}

/*
 * Get bitmap resources
 */

wxBitmap CMainWindow::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin CMainWindow bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end CMainWindow bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon CMainWindow::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin CMainWindow icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end CMainWindow icon retrieval
}

void CMainWindow::OnClickBalance( wxCommandEvent& event )
{
    CBalanceWindow dlg(this);
    dlg.ShowModal();
}

void CMainWindow::OnClickSummary( wxCommandEvent& event )
{
    CSummaryWindow dlg(this);
    dlg.ShowModal();
}

void CMainWindow::OnClickAccount(wxCommandEvent& event)
{
    CAccountWindow dlg(this);
    dlg.ShowModal();
}

void CMainWindow::OnClickMember(wxCommandEvent& event)
{
    CMemberWindow dlg(this);
    dlg.ShowModal();
}

void CMainWindow::OnPaint( wxPaintEvent& event )
{
    wxWindow* window = wxDynamicCast(event.GetEventObject(), wxWindow);
    wxPaintDC dc(window);
    wxRect rect = window->GetClientRect();
    if (m_pBackGroundImage->Ok() && m_pBackGroundImage->GetWidth() > 0 && m_pBackGroundImage->GetHeight() > 0)
    {
        int w = m_pBackGroundImage->GetWidth();
        int h = m_pBackGroundImage->GetHeight();

        wxMemoryDC dcMem;

        dcMem.SelectObjectAsSource(*m_pBackGroundImage);
        int i, j;
        for (i = rect.x; i < rect.x + rect.width; i += w)
        {
            for (j = rect.y; j < rect.y + rect.height; j+= h)
                dc.Blit(i, j, w, h, & dcMem, 0, 0);
        }
        dcMem.SelectObject(wxNullBitmap);
    }
}
