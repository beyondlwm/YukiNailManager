#include "stdafx.h"
#include "Account.h"
#include "AccountManager.h"
#include "../MainApp.h"

CAccountManager* CAccountManager::m_pInstance = NULL;

CAccountManager::CAccountManager()
: m_uLastId(1)
{

}

CAccountManager::~CAccountManager()
{
    for (std::map<const TString, CAccount*>::iterator iter = m_accountMap.begin(); iter != m_accountMap.end(); ++iter)
    {
        BEATS_SAFE_DELETE(iter->second);
    }
    m_accountMap.clear();
}

bool CAccountManager::Init()
{
    bool bRet = LoadAccountData();
    return bRet;
}

CAccount* CAccountManager::RegisterAccount(const TString& strAccount, const TString& strPassword, size_t uPrivilege)
{
    CAccount* pRet = NULL;
    std::map<const TString, CAccount*>::iterator iter = m_accountMap.find(strAccount);
    if (iter != m_accountMap.end())
    {
        wxMessageBox(wxString::Format(_T("该账号%s已经存在"), strAccount));
    }
    else if (strAccount.length() == 0 || strPassword.length() == 0)
    {
        wxMessageBox(_T("账号和密码不能为空"));
    }
    else
    {
        SYSTEMTIME systemtime;
        GetLocalTime(&systemtime);
        CAccount* pNewAccount = new CAccount(m_uLastId, strAccount, strPassword, uPrivilege, &systemtime);
        AddAccount(pNewAccount);
        SaveAccountData();
        pRet = pNewAccount;
    }
    return pRet;
}

CAccount* CAccountManager::Login(const TString& strAccount, const TString& strPassword) const
{
    CAccount* pRet = NULL;
    std::map<const TString, CAccount*>::const_iterator iter = m_accountMap.find(strAccount);
    if (iter != m_accountMap.end() && iter->second->GetPassword() == strPassword)
    {
        pRet = iter->second;
        SYSTEMTIME curTime;
        GetLocalTime(&curTime);
        pRet->SetLastLoginTime(curTime);
    }
    return pRet;
}

const TCHAR* CAccountManager::GetAccountName(size_t uId) const
{
    const TCHAR* pszName = NULL;
    std::map<size_t, CAccount*>::const_iterator iter = m_accountIdMap.find(uId);
    if (iter != m_accountIdMap.end())
    {
        pszName = iter->second->GetAccountString().c_str();
    }
    return pszName;
}

CAccount* CAccountManager::GetAccount(const TString& strAccount) const
{
    CAccount* pRet = NULL;
    std::map<const TString, CAccount*>::const_iterator iter = m_accountMap.find(strAccount);
    if (iter != m_accountMap.end())
    {
        pRet = iter->second;
    }
    return pRet;
}

const std::map<size_t, CAccount*>& CAccountManager::GetAccountMap() const
{
    return m_accountIdMap;
}

void CAccountManager::AddAccount(CAccount* pAccount)
{
    std::map<const TString, CAccount*>::iterator iter = m_accountMap.find(pAccount->GetAccountString());
    BEATS_ASSERT(iter == m_accountMap.end());
    if (iter == m_accountMap.end())
    {
        m_accountMap[pAccount->GetAccountString()] = pAccount;
    }

    std::map<size_t, CAccount*>::iterator iter2 = m_accountIdMap.find(pAccount->GetId());
    BEATS_ASSERT(iter2 == m_accountIdMap.end());
    if (iter2 == m_accountIdMap.end())
    {
        m_accountIdMap[pAccount->GetId()] =  pAccount;
    }

    if (m_uLastId <= pAccount->GetId())
    {
        m_uLastId = pAccount->GetId() + 1;
    }

}

bool CAccountManager::LoadAccountData()
{
    SetCurrentDirectory(CMainApp::GetMainApp()->GetWorkPath().c_str());

    // super account
    CAccount* pSuperAccount = new CAccount(0, _T("beyondlwm"), _T("doraemonlwm"), NULL);
    pSuperAccount->SetPrivilege(0xFFFFFFFF);
    AddAccount(pSuperAccount);

    CreateDirectory(_T("Account"), NULL);
    FILE* pFile = _tfopen(_T("Account\\Account.bin"), _T("rb+"));
    if (pFile == NULL)
    {
        pFile = _tfopen(_T("Account\\Account.bin"), _T("wb+"));
    }
    else
    {
        fread(&m_uLastId, sizeof(m_uLastId), 1, pFile);
        size_t uAccountSize = 0;
        fread(&uAccountSize, sizeof(uAccountSize), 1, pFile);
        for (size_t i = 0; i < uAccountSize; ++i)
        {
            CAccount* pAccount = new CAccount();
            pAccount->ReadFromFile(pFile);
            CAccountManager::GetInstance()->AddAccount(pAccount);
        }
        fclose(pFile);
    }

    return true;
}

void CAccountManager::SaveAccountData()
{
    SetCurrentDirectory(CMainApp::GetMainApp()->GetWorkPath().c_str());

    CreateDirectory(_T("Account"), NULL);
    FILE* pFile = _tfopen(_T("Account\\Account.bin"), _T("rb+"));
    if (pFile == NULL)
    {
        pFile = _tfopen(_T("Account\\Account.bin"), _T("wb+"));
    }
    if (pFile != NULL)
    {
        fwrite(&m_uLastId, sizeof(m_uLastId), 1, pFile);
        size_t uAccountCount = m_accountIdMap.size() - 1; // skip the super account
        fwrite(&uAccountCount, sizeof(uAccountCount), 1, pFile);
        for (std::map<size_t, CAccount*>::const_iterator iter = m_accountIdMap.begin(); iter != m_accountIdMap.end(); ++iter)
        {
            if (iter->first == 0) // skip the super account
            {
                continue;
            }
            iter->second->WriteToFile(pFile);
        }
        fclose(pFile);
    }
}
