#include "stdafx.h"
#include "MainApp.h"
#include "LoginWindow/LoginWindow.h"
#include "Account/AccountManager.h"
#include "MainWindow/MainWindow.h"
#include "YukiNailShopManager.h"
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

IMPLEMENT_APP(CMainApp)

CMainApp::CMainApp()
: m_pMainWindow(NULL)
{

}

CMainApp::~CMainApp()
{
    CYukiNailShopManager::Destroy();
}

bool CMainApp::OnInit()
{
    bool bRet = false;
    wxInitAllImageHandlers();

    HMODULE processModule = GetModuleHandle(NULL);
    TCHAR szModuleFilePath[MAX_PATH];
    GetModuleFileName(processModule, szModuleFilePath, MAX_PATH);
    PathRemoveFileSpec(szModuleFilePath);
    m_strWorkPath = szModuleFilePath;
    m_strWorkPath.append(_T("\\"));

    if (CYukiNailShopManager::GetInstance()->Init())
    {
        CLoginWindow loginDialog(NULL);
        if (loginDialog.ShowModal() == 1)
        {
            m_pMainWindow = new CMainWindow(NULL);
            this->SetTopWindow(m_pMainWindow);
            m_pMainWindow->ShowUp(true);
            bRet = true;
        }
    }

    return bRet;
}

CMainWindow* CMainApp::GetMainWindow() const
{
    return m_pMainWindow;
}

void CMainApp::ShowMainWindow( bool bShow )
{
    m_pMainWindow->ShowUp(bShow);
}

CMainApp* CMainApp::GetMainApp()
{
    return (CMainApp*)(CMainApp::GetInstance());
}

const TString& CMainApp::GetWorkPath() const
{
    return m_strWorkPath;
}

bool CMainApp::ProcessIdle()
{
    LASTINPUTINFO info;
    info.cbSize = sizeof(info);
    GetLastInputInfo(&info);
    size_t curTickCount = GetTickCount();
    if (curTickCount - info.dwTime > (2 * 60 * 1000))
    {
        TerminateProcess(GetCurrentProcess(), 0);
    }
    return super::ProcessIdle();
}
