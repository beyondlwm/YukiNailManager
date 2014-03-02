/////////////////////////////////////////////////////////////////////////////
// Name:        registerwindow.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     13/12/2013 12:22:56
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 13/12/2013 12:22:56

#ifndef _REGISTERWINDOW_H_
#define _REGISTERWINDOW_H_


/*!
 * Includes
 */

////@begin includes
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_CREGISTERWINDOW 10015
#define ID_TEXTCTRL4 10016
#define ID_TEXTCTRL5 10017
#define ID_TEXTCTRL6 10021
#define ID_CHECKLISTBOX 10020
#define ID_BUTTON5 10018
#define ID_BUTTON6 10019
#define SYMBOL_CREGISTERWINDOW_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CREGISTERWINDOW_TITLE _("�˺�")
#define SYMBOL_CREGISTERWINDOW_IDNAME ID_CREGISTERWINDOW
#define SYMBOL_CREGISTERWINDOW_SIZE wxSize(200, 300)
#define SYMBOL_CREGISTERWINDOW_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CRegisterWindow class declaration
 */
class CAccount;

class CRegisterWindow: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CRegisterWindow )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CRegisterWindow();
    CRegisterWindow( wxWindow* parent, wxWindowID id = SYMBOL_CREGISTERWINDOW_IDNAME, const wxString& caption = SYMBOL_CREGISTERWINDOW_TITLE, const wxPoint& pos = SYMBOL_CREGISTERWINDOW_POSITION, const wxSize& size = SYMBOL_CREGISTERWINDOW_SIZE, long style = SYMBOL_CREGISTERWINDOW_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CREGISTERWINDOW_IDNAME, const wxString& caption = SYMBOL_CREGISTERWINDOW_TITLE, const wxPoint& pos = SYMBOL_CREGISTERWINDOW_POSITION, const wxSize& size = SYMBOL_CREGISTERWINDOW_SIZE, long style = SYMBOL_CREGISTERWINDOW_STYLE );

    /// Destructor
    ~CRegisterWindow();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CRegisterWindow event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON5
    void OnRegisterAccountBtnClick( wxCommandEvent& event );

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON6
    void OnRegisterCloseBtnClick( wxCommandEvent& event );

////@end CRegisterWindow event handler declarations

////@begin CRegisterWindow member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CRegisterWindow member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    void ChangeToModifyWindow(const CAccount* pAccount);

////@begin CRegisterWindow member variables
    wxTextCtrl* m_pRegisterAccountText;
    wxTextCtrl* m_pRegisterPasswordText;
    wxTextCtrl* m_pRegisterRecheckPasswordText;
    wxCheckListBox* m_pPrivilegeCheckBox;
    wxButton* m_pRegisterSubmitBtn;
    wxButton* m_pRegisterCloseBtn;
    wxStaticText* m_pTitleLabel;
    wxStaticText* m_pRepasswordLabel;
    bool m_bModifyFlag;
////@end CRegisterWindow member variables
};

#endif
    // _REGISTERWINDOW_H_
