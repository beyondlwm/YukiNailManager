#ifndef ERAFABLE_LAUNCHER_SHAPEBUTTON_H__INCLUDE
#define ERAFABLE_LAUNCHER_SHAPEBUTTON_H__INCLUDE

#include "wx/panel.h"

enum EShapeButtonState
{
    eSBS_Normal,
    eSBS_Pressed,
    eSBS_Disable,
    eSBS_Hover,
    
    eSBS_Count,
    eSBS_Force32Bit = 0xFFFFFFFF
};

class CShapeButton : public wxPanel
{
public:
    CShapeButton(wxWindow* pParent, const TCHAR* pszLabel);
    virtual ~CShapeButton();

    void SetNormalImage(wxImage* pImage);
    void SetHoverImage(wxImage* pImage);
    void SetPressedImage(wxImage* pImage);
    void SetDisableImage(wxImage* pImage);
    void SetBackgroundImage(wxImage* pImage);

    void SetCurrentState(EShapeButtonState state);
    void SetLabelOffset(wxPoint& offset);

private:
    void AutomaticConvertImage(wxImage* pImage);
    void RefreshRegion();

    void OnPaint(wxPaintEvent& evt);
    void OnEraseBackground(wxEraseEvent& evt);

    void OnMouseLeftDown(wxMouseEvent& evt);
    void OnMouseLeftUp(wxMouseEvent& evt);
    void OnMouseRightUp(wxMouseEvent& evt);

    void OnResize(wxSizeEvent& evt);

    void OnMouseMotion(wxMouseEvent& evt);
    void OnMouseLeaveWindow(wxMouseEvent& evt);
    wxImage* GetStateImage(EShapeButtonState state);

private:
    wxImage* m_pNormalBitmap;
    wxImage* m_pPressedBitmap;
    wxImage* m_pHoverBitmap;
    wxImage* m_pDisableBitmap;
    wxBitmap m_backBackground;
    wxRegion m_region;
    bool m_bInRegionLastFrame;
    wxPoint m_labelOffset;
    wxColour m_labelColour;

    EShapeButtonState m_state;
};

#endif