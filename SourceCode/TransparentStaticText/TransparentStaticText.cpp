#include "stdafx.h"
#include "TransparentStaticText.h"
#include "wx/dcbuffer.h"

CTransparentStaticText::CTransparentStaticText( wxWindow *parent, wxWindowID id, const wxString& label, wxImage* pImage, const wxPoint& pos /*= wxDefaultPosition*/, const wxSize& size /*= wxDefaultSize*/, long style /*= 0*/, const wxString& name /*= wxStaticTextNameStr*/ )
: wxStaticText(parent, id, label, pos, size, style, name)
{
	this->SetBackgroundColour(*wxBLACK);
	this->SetBackgroundStyle(wxBG_STYLE_PAINT);
    this->SetBackgroundImage(pImage);
	this->Connect(wxEVT_PAINT, wxPaintEventHandler( CTransparentStaticText::OnPaint ), NULL, this );
}

CTransparentStaticText::~CTransparentStaticText()
{

}

void CTransparentStaticText::OnPaint( wxPaintEvent& evt )
{
    if (m_backGroundBitmapDC.GetSelectedBitmap().IsOk())
    {
        int i = GetBackgroundStyle();
        wxAutoBufferedPaintDC dc(this);
        dc.SetBackgroundMode(wxTRANSPARENT);
        dc.Blit(wxPoint(0,0), this->GetSize(), &m_backGroundBitmapDC, this->GetPosition());
        dc.SetFont(GetFont());
        dc.DrawText(this->GetLabel(), wxPoint(0, 0));
    }
}

void CTransparentStaticText::SetLabel( const wxString& label )
{
	if (label != this->GetLabel())
	{
		wxStaticText::SetLabel(label);
	}
}

void CTransparentStaticText::SetBackgroundImage( wxImage* pImage )
{
    m_backGroundBitmapDC.SelectObjectAsSource(*pImage);
}
