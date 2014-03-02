#ifndef _MAINAPP_H__
#define _MAINAPP_H__

class CLoginWindow;
class CMainWindow;
class CBalanceWindow;
class CSummaryWindow;
class CRegisterWindow;
class CAccountWindow;
class CMainApp : public wxApp
{
    typedef wxApp super;
public:
    CMainApp();
    virtual ~CMainApp();
    virtual bool OnInit();
    virtual bool ProcessIdle();

    CMainWindow* GetMainWindow() const;
    void ShowMainWindow(bool bShow);

    static CMainApp* GetMainApp();
    const TString& GetWorkPath() const;

private:
    CMainWindow* m_pMainWindow;
    TString m_strWorkPath;

};

#endif