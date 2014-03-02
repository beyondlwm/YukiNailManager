#ifndef _TRANSPARENTSTATICTEXT_H__INCLUDE
#define _TRANSPARENTSTATICTEXT_H__INCLUDE

#include "wx/stattext.h"

class CTransparentStaticText : public wxStaticText
{
public:
	CTransparentStaticText(wxWindow *parent, wxWindowID id, const wxString& label, wxImage* pImage, const wxPoint& pos = wxDefaultPosition,
							const wxSize& size = wxDefaultSize,
							long style = 0,
							const wxString& name = wxStaticTextNameStr);

	virtual ~CTransparentStaticText();
	virtual void SetLabel(const wxString& label);

    void SetBackgroundImage(wxImage* pImage);

private:
	void OnPaint(wxPaintEvent& evt);
private:
    wxMemoryDC m_backGroundBitmapDC;

};

#endif