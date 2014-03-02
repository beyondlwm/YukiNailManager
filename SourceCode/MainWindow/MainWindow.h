#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_
/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
////@end includes
#define ID_CMAINWINDOW 10000
#define ID_PANEL 10044
#define SYMBOL_CMAINWINDOW_STYLE wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX
#define SYMBOL_CMAINWINDOW_TITLE _("°¢»¨ÃÀ¼×")
#define SYMBOL_CMAINWINDOW_IDNAME ID_CMAINWINDOW
#define SYMBOL_CMAINWINDOW_SIZE wxSize(1120, 630)
#define SYMBOL_CMAINWINDOW_POSITION wxDefaultPosition

class CShapeButton;

class CMainWindow: public wxFrame
{    
    DECLARE_CLASS( CMainWindow )

public:
    /// Constructors
    CMainWindow();
    CMainWindow( wxWindow* parent, wxWindowID id = SYMBOL_CMAINWINDOW_IDNAME, const wxString& caption = SYMBOL_CMAINWINDOW_TITLE, const wxPoint& pos = SYMBOL_CMAINWINDOW_POSITION, const wxSize& size = SYMBOL_CMAINWINDOW_SIZE, long style = SYMBOL_CMAINWINDOW_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CMAINWINDOW_IDNAME, const wxString& caption = SYMBOL_CMAINWINDOW_TITLE, const wxPoint& pos = SYMBOL_CMAINWINDOW_POSITION, const wxSize& size = SYMBOL_CMAINWINDOW_SIZE, long style = SYMBOL_CMAINWINDOW_STYLE );

    /// Destructor
    ~CMainWindow();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();


////@begin CLoginWindow member function declarations
    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// wxEVT_PAINT event handler for ID_PANEL
    void OnPaint( wxPaintEvent& event );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CLoginWindow member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    void ShowUp(bool bVisible);

private:
    void OnClickBalance(wxCommandEvent& event);
    void OnClickSummary(wxCommandEvent& event);
    void OnClickAccount(wxCommandEvent& event);
    void OnClickMember(wxCommandEvent& event);

private:
    CShapeButton* m_pBalanceBtn;
    CShapeButton* m_pMemeberBtn;
    CShapeButton* m_pSummaryBtn;
    CShapeButton* m_pAccountBtn;
    wxImage* m_pBackGroundImage;
    wxPanel* m_pBackGroundPanel;
};

#endif
    // _CLOGINWINDOW_H_
