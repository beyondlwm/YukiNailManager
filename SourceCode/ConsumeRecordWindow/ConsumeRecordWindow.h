/////////////////////////////////////////////////////////////////////////////
// Name:        consumerecordwindow.h
// Purpose:     
// Author:      
// Modified by: 
// Created:     15/12/2013 00:39:14
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 15/12/2013 00:39:14

#ifndef _CONSUMERECORDWINDOW_H_
#define _CONSUMERECORDWINDOW_H_


/*!
 * Includes
 */

////@begin includes
////@end includes

#include "wx/listctrl.h"
////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_CCONSUMERECORDWINDOW 10040
#define ID_BUTTON13 10042
#define ID_LISTCTRL1 10043
#define ID_BUTTON14 10044
#define ID_BUTTON15 10045
#define SYMBOL_CCONSUMERECORDWINDOW_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX|wxTAB_TRAVERSAL
#define SYMBOL_CCONSUMERECORDWINDOW_TITLE _("���Ѽ�¼")
#define SYMBOL_CCONSUMERECORDWINDOW_IDNAME ID_CCONSUMERECORDWINDOW
#define SYMBOL_CCONSUMERECORDWINDOW_SIZE wxSize(600, 600)
#define SYMBOL_CCONSUMERECORDWINDOW_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * CConsumeRecordWindow class declaration
 */
class CMember;
class CConsumeRecord;

class CConsumeRecordWindow: public wxDialog
{    
    DECLARE_DYNAMIC_CLASS( CConsumeRecordWindow )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    CConsumeRecordWindow();
    CConsumeRecordWindow( wxWindow* parent, wxWindowID id = SYMBOL_CCONSUMERECORDWINDOW_IDNAME, const wxString& caption = SYMBOL_CCONSUMERECORDWINDOW_TITLE, const wxPoint& pos = SYMBOL_CCONSUMERECORDWINDOW_POSITION, const wxSize& size = SYMBOL_CCONSUMERECORDWINDOW_SIZE, long style = SYMBOL_CCONSUMERECORDWINDOW_STYLE );

    /// Creation
    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_CCONSUMERECORDWINDOW_IDNAME, const wxString& caption = SYMBOL_CCONSUMERECORDWINDOW_TITLE, const wxPoint& pos = SYMBOL_CCONSUMERECORDWINDOW_POSITION, const wxSize& size = SYMBOL_CCONSUMERECORDWINDOW_SIZE, long style = SYMBOL_CCONSUMERECORDWINDOW_STYLE );

    /// Destructor
    ~CConsumeRecordWindow();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin CConsumeRecordWindow event handler declarations

    /// wxEVT_COMMAND_BUTTON_CLICKED event handler for ID_BUTTON13
    void OnCloseBtnClick( wxCommandEvent& event );
    void OnCancelBtnClick( wxCommandEvent& event );
    void OnChangeDiscountType( wxCommandEvent& event );

////@end CConsumeRecordWindow event handler declarations

////@begin CConsumeRecordWindow member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end CConsumeRecordWindow member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

    void UpdateData(const CMember* pMember);

    void ShowRecord(const CConsumeRecord* pRecord);

////@begin CConsumeRecordWindow member variables
    wxStaticText* m_pNameLabel;
    wxStaticText* m_pTelLabel;
    wxStaticText* m_pAccountBalanceLabel;
    wxStaticText* m_pDiscountTypeLabel;

    wxListCtrl* m_pConsumeRecordList;
    wxButton* m_pCancelBtn;
    wxButton* m_pCloseBtn;
    wxButton* m_pChangeDiscountBtn;
    CMember* m_pCurrentMember;
////@end CConsumeRecordWindow member variables
};

#endif
    // _CONSUMERECORDWINDOW_H_
