#include "stdafx.h"
#include "ShapeButton.h"

CShapeButton::CShapeButton(wxWindow* pParent, const TCHAR* pszLabel)
: wxPanel(pParent)
, m_pNormalBitmap(NULL)
, m_pPressedBitmap(NULL)
, m_pHoverBitmap(NULL)
, m_pDisableBitmap(NULL)
, m_state(eSBS_Normal)
, m_bInRegionLastFrame(false)
{
    m_labelOffset.x = m_labelOffset.y = 0;
    this->SetLabel(pszLabel);
    this->SetBackgroundStyle(wxBG_STYLE_ERASE);
    this->Connect(wxEVT_PAINT, wxPaintEventHandler( CShapeButton::OnPaint ), NULL, this );
    this->Connect(wxEVT_MOTION, wxMouseEventHandler(CShapeButton::OnMouseMotion), NULL, this);
    this->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(CShapeButton::OnMouseLeaveWindow), NULL, this);
    this->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CShapeButton::OnMouseLeftDown), NULL, this);
    this->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(CShapeButton::OnMouseLeftUp), NULL, this);
    this->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(CShapeButton::OnMouseRightUp), NULL, this);
    this->Connect(wxEVT_SIZE, wxSizeEventHandler(CShapeButton::OnResize), NULL, this);
    this->Connect(wxEVT_ERASE_BACKGROUND, wxEraseEventHandler(CShapeButton::OnEraseBackground), NULL, this);
}

CShapeButton::~CShapeButton()
{
    this->Disconnect(wxEVT_PAINT, wxPaintEventHandler( CShapeButton::OnPaint ), NULL, this );
    this->Disconnect(wxEVT_MOTION, wxMouseEventHandler(CShapeButton::OnMouseMotion), NULL, this);
    this->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(CShapeButton::OnMouseLeaveWindow), NULL, this);
    this->Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(CShapeButton::OnMouseLeftDown), NULL, this);
    this->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(CShapeButton::OnMouseLeftUp), NULL, this);
    this->Disconnect(wxEVT_RIGHT_UP, wxMouseEventHandler(CShapeButton::OnMouseRightUp), NULL, this);
    this->Disconnect(wxEVT_SIZE, wxSizeEventHandler(CShapeButton::OnResize), NULL, this);

    BEATS_SAFE_DELETE(m_pNormalBitmap);
    BEATS_SAFE_DELETE(m_pPressedBitmap);
    BEATS_SAFE_DELETE(m_pHoverBitmap);
    BEATS_SAFE_DELETE(m_pDisableBitmap);

}

void CShapeButton::SetNormalImage(wxImage* pImage)
{
    AutomaticConvertImage(pImage);
    if (m_state == eSBS_Normal)
    {
        m_region = wxRegion(*pImage);
    }
    m_pNormalBitmap = pImage;
}

void CShapeButton::SetHoverImage(wxImage* pImage)
{
    AutomaticConvertImage(pImage);
    if (m_state == eSBS_Hover)
    {
        m_region = wxRegion(*pImage);
    }

    m_pHoverBitmap = pImage;
}

void CShapeButton::SetPressedImage(wxImage* pImage)
{
    AutomaticConvertImage(pImage);
    if (m_state == eSBS_Pressed)
    {
        m_region = wxRegion(*pImage);
    }

    m_pPressedBitmap = pImage;
}

void CShapeButton::SetDisableImage(wxImage* pImage)
{
    AutomaticConvertImage(pImage);
    if (m_state == eSBS_Disable)
    {
        m_region = wxRegion(*pImage);
    }

    m_pDisableBitmap = pImage;
}

void CShapeButton::SetBackgroundImage(wxImage* pImage)
{
    wxBitmap background(*pImage);
    m_backBackground = background;
}

void CShapeButton::AutomaticConvertImage(wxImage* pImage)
{
    BEATS_ASSERT(pImage->HasAlpha(), _T("This Image doesn't contain a alpha chanel!"));
    if (pImage->HasAlpha() && !pImage->HasMask())
    {
        pImage->ConvertAlphaToMask();
        pImage->SetMask(true);
    }
    wxSize minSize = this->GetMinSize();
    if (minSize.GetX() < pImage->GetSize().GetX() ||
        minSize.GetY() < pImage->GetSize().GetY())
    {
        this->SetMinSize(pImage->GetSize());
    }
}

void CShapeButton::RefreshRegion()
{
    wxImage* pImage = GetStateImage(m_state);
    if (pImage == NULL)
    {
        pImage = m_pNormalBitmap;
    }
    if (pImage)
    {
        m_region = wxRegion(*pImage);
        wxSize curSize = this->GetSize();
        wxSize minSize = this->GetMinSize();
        wxSize offsetPos = (curSize - minSize) * 0.5f;
        m_region.Offset(offsetPos.x, offsetPos.y);
    }
    this->Refresh(false);
}

void CShapeButton::OnPaint( wxPaintEvent& evt )
{
    wxSize curSize = this->GetSize();
    wxSize minSize = this->GetMinSize();
    wxSize offsetPos = (curSize - minSize) * 0.5f;
    
    wxImage* pRenderImage = GetStateImage(m_state);
    if (pRenderImage)
    {
        wxPaintDC dc(this);
        dc.DrawBitmap(*pRenderImage, offsetPos.x, offsetPos.y , true);
        wxFont font = this->GetFont();
        dc.SetFont(font);
        wxSize fontSize = font.GetPixelSize();
        wxSize btnSize = this->GetSize();
        int heightStart = (int)((btnSize.GetY() - fontSize.GetY()) * 0.5F);
        wxPoint startPos = m_labelOffset;
        startPos.y += heightStart;
        dc.DrawText(this->GetLabel(), startPos);
    }
    evt.Skip(true);
}

void CShapeButton::OnEraseBackground(wxEraseEvent& evt)
{
    if (m_backBackground.IsOk())
    {
        wxDC* dc = evt.GetDC();
        static wxMemoryDC memDC(m_backBackground);
        dc->Blit(wxPoint(0,0), this->GetSize(), &memDC, this->GetPosition());
    }
    else
    {
        evt.Skip();
    }
}

void CShapeButton::SetCurrentState( EShapeButtonState state )
{
    if (!this->IsEnabled())
    {
        state = eSBS_Disable;
    }
    if (m_state != state)
    {
        if (state == eSBS_Hover)
        {
            m_labelColour = this->GetForegroundColour();
            this->SetForegroundColour(*wxWHITE);
        }
        else
        {
            this->SetForegroundColour(m_labelColour);
        }
        m_state = state;
        RefreshRegion();
    }
}

void CShapeButton::SetLabelOffset(wxPoint& offset)
{
    m_labelOffset = offset;
}

wxImage* CShapeButton::GetStateImage( EShapeButtonState state )
{
    wxImage* pRenderBitmap = m_pNormalBitmap;

    switch (state)
    {
    case eSBS_Normal:
        {
            if (m_pNormalBitmap)
            {
                pRenderBitmap = m_pNormalBitmap;
            }
        }
        break;
    case eSBS_Pressed:
        {
            if (m_pPressedBitmap)
            {
                pRenderBitmap = m_pPressedBitmap;
            }
        }
        break;
    case eSBS_Disable:
        {
            if (m_pDisableBitmap)
            {
                pRenderBitmap = m_pDisableBitmap;
            }
        }
        break;
    case eSBS_Hover:
        {
            if (m_pHoverBitmap)
            {
                pRenderBitmap = m_pHoverBitmap;
            }
        }
        break;
    default:
        break;

    }
    return pRenderBitmap;
}

void CShapeButton::OnMouseLeftDown( wxMouseEvent& /*evt*/ )
{
    if (m_bInRegionLastFrame)
    {
        SetCurrentState(eSBS_Pressed);
    }
}

void CShapeButton::OnMouseLeftUp(wxMouseEvent& /*evt*/)
{
    if (m_bInRegionLastFrame)
    {
        SetCurrentState(eSBS_Hover);
        wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, GetId());
        evt.SetEventObject(this);
        evt.SetInt(wxMOUSE_BTN_LEFT);
        GetEventHandler()->AddPendingEvent(evt);
    }
}

void CShapeButton::OnMouseRightUp(wxMouseEvent& /*evt*/)
{
    if (m_bInRegionLastFrame)
    {
        wxCommandEvent evt(wxEVT_COMMAND_BUTTON_CLICKED, GetId());
        evt.SetEventObject(this);
        evt.SetInt(wxMOUSE_BTN_RIGHT);
        GetEventHandler()->AddPendingEvent(evt);
    }
}

void CShapeButton::OnResize(wxSizeEvent& evt)
{
    this->Refresh();
    RefreshRegion();
}

void CShapeButton::OnMouseMotion( wxMouseEvent& evt )
{
    wxPoint pos = evt.GetPosition();
    wxRegionContain contain = m_region.Contains(pos);
    bool bInRegion = contain == wxInRegion || contain == wxPartRegion;
    if(!m_bInRegionLastFrame && bInRegion)
    {
        m_bInRegionLastFrame = true;
        SetCurrentState(eSBS_Hover);
    }
    else if (m_bInRegionLastFrame && !bInRegion)
    {
        m_bInRegionLastFrame = false;
        SetCurrentState(eSBS_Normal);
    }
}

void CShapeButton::OnMouseLeaveWindow(wxMouseEvent& /*evt*/)
{
    m_bInRegionLastFrame = false;
    SetCurrentState(eSBS_Normal);
}
