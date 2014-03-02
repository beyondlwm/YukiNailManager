#include "stdafx.h"
#include "Account.h"
#include "../MainApp.h"

const TCHAR* CAccount::pszAccountPrivilegeString[] =
{
    _T("管理账号"),
    _T("普通结算"),
    _T("VIP操作"),
    _T("会员查询"),
    _T("会员注册"),
    _T("会员统计"),
    _T("统计"),
};

CAccount::CAccount(size_t uId, const TString& strAccount, const TString& strPassword, size_t uPrivilege, const SYSTEMTIME* pCreateTime/* = NULL*/)
: m_uId(uId)
, m_uPrivilege(uPrivilege)
, m_strAccount(strAccount)
, m_strPassword(strPassword)
{
    BEATS_ASSERT(strAccount.length() > 0, _T("Account can't be Empty!"));
    BEATS_ASSERT(strPassword.length() > 0, _T("Password can't be Empty!"));
    if (pCreateTime != NULL)
    {
        memcpy(&m_createTime, pCreateTime, sizeof(SYSTEMTIME));
    }
    else
    {
        ZeroMemory(&m_createTime, sizeof(m_createTime));
    }
    ZeroMemory(&m_lastLoginTime, sizeof(m_lastLoginTime));
}

CAccount::CAccount()
: m_uId(0)
, m_uPrivilege(0)
{
    ZeroMemory(&m_createTime, sizeof(m_createTime));
    ZeroMemory(&m_lastLoginTime, sizeof(m_lastLoginTime));
}

CAccount::~CAccount()
{

}

const TString& CAccount::GetPassword() const
{
    return m_strPassword;
}

void CAccount::SetPassword( const TString& strPassword )
{
    m_strPassword = strPassword;
}

const TString& CAccount::GetAccountString() const
{
    return m_strAccount;
}

size_t CAccount::GetId() const
{
    return m_uId;
}

const SYSTEMTIME& CAccount::GetCreateTime() const
{
    return m_createTime;
}

const SYSTEMTIME& CAccount::GetLastLoginTime() const
{
    return m_lastLoginTime;
}

void CAccount::SetLastLoginTime(const SYSTEMTIME& time)
{
    memcpy(&m_lastLoginTime, &time, sizeof(m_lastLoginTime));
}

bool CAccount::CheckPrivilege(EAccountPrivilegeType uPrivilege) const
{
    return (m_uPrivilege & (1 << uPrivilege)) > 0;
}

size_t CAccount::GetPrivilege() const
{
    return m_uPrivilege;
}

void CAccount::SwitchPrivilege(EAccountPrivilegeType type, bool bEnable)
{
    if (bEnable)
    {
        m_uPrivilege |= (1 << type);
    }
    else
    {
        m_uPrivilege &= ~(1 << type);
    }
}

void CAccount::SetPrivilege(size_t uPrivilege)
{
    m_uPrivilege = uPrivilege;
}

void CAccount::WriteToFile(FILE* pFile)
{
    BEATS_ASSERT(pFile != NULL);
    fwrite(&m_uId, sizeof(m_uId), 1, pFile);
    fwrite(&m_uPrivilege, sizeof(m_uPrivilege), 1, pFile);
    size_t uStrSize = sizeof(TCHAR) * (m_strAccount.length() + 1);
    fwrite(&uStrSize, sizeof(uStrSize), 1, pFile);
    fwrite(m_strAccount.c_str(), uStrSize, 1, pFile);

    uStrSize = sizeof(TCHAR) * (m_strPassword.length() + 1);
    fwrite(&uStrSize, sizeof(uStrSize), 1, pFile);
    fwrite(m_strPassword.c_str(), uStrSize, 1, pFile);
    fwrite(&m_createTime, sizeof(m_createTime), 1, pFile);
    fwrite(&m_lastLoginTime, sizeof(m_createTime), 1, pFile);
}

void CAccount::ReadFromFile(FILE* pFile)
{
    BEATS_ASSERT(pFile != NULL);
    fread(&m_uId, sizeof(m_uId), 1, pFile);
    fread(&m_uPrivilege, sizeof(m_uPrivilege), 1, pFile);

    size_t uStrSize = 0;
    fread(&uStrSize, sizeof(uStrSize), 1, pFile);
    TCHAR szBuffer[MAX_PATH];
    fread(szBuffer, uStrSize, 1, pFile);
    m_strAccount = szBuffer;

    fread(&uStrSize, sizeof(uStrSize), 1, pFile);
    fread(szBuffer, uStrSize, 1, pFile);
    m_strPassword = szBuffer;

    fread(&m_createTime, sizeof(m_createTime), 1, pFile);
    fread(&m_lastLoginTime, sizeof(m_createTime), 1, pFile);
}

void CAccount::AddOperationHistory( const TString& strHistory )
{
    SetCurrentDirectory(CMainApp::GetMainApp()->GetWorkPath().c_str());
    if (m_uId != 0)
    {
        SYSTEMTIME systemTime;
        GetLocalTime(&systemTime);
        SOperationHistory history(&systemTime, strHistory);
        m_operationHistory.push_back(history);
        wxString strHistoryDirectoryName = wxString::Format(_T("Account\\%s_%d"), m_strAccount, m_uId);
        CreateDirectory(strHistoryDirectoryName, NULL);
        strHistoryDirectoryName.append(_T("\\history.bin"));
        FILE* pFile = _tfopen(strHistoryDirectoryName, _T("rb+"));
        if (pFile == NULL)
        {
            pFile = _tfopen(strHistoryDirectoryName, _T("wb+"));
        }
        if (pFile)
        {
            fseek(pFile, 0, SEEK_END);
            fwrite(&systemTime, sizeof(systemTime), 1, pFile);
            size_t uStringSize = (strHistory.length() + 1) * sizeof(TCHAR);
            fwrite(&uStringSize, sizeof(uStringSize), 1, pFile);
            fwrite(strHistory.c_str(), uStringSize, 1, pFile);
            fclose(pFile);
        }
    }
}

void CAccount::LoadOperationHistory()
{
    SetCurrentDirectory(CMainApp::GetMainApp()->GetWorkPath().c_str());
    m_operationHistory.clear();
    wxString strHistoryFileName;
    strHistoryFileName = wxString::Format(_T("Account\\%s_%d\\history.bin"), m_strAccount, m_uId);
    FILE* pFile = _tfopen(strHistoryFileName, _T("rb+"));
    if (pFile != NULL)
    {
        SYSTEMTIME systime;
        while(fread(&systime, sizeof(systime), 1, pFile) != 0)
        {
            size_t uStringSize = 0;
            fread(&uStringSize, sizeof(uStringSize), 1, pFile);
            TCHAR szBuffer[MAX_PATH * 5];
            fread(szBuffer, uStringSize, 1, pFile);
            SOperationHistory history(&systime, szBuffer);
            m_operationHistory.push_back(history);
        }
        fclose(pFile);
    }
}
