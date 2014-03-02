#include "stdafx.h"
#include "YukiNailShopManager.h"
#include "ConsumeRecord/ConsumeRecord.h"
#include "Account/Account.h"
#include "Account/AccountManager.h"
#include "Member/MemberManager.h"
#include "MainApp.h"

CYukiNailShopManager* CYukiNailShopManager::m_pInstance = NULL;


CYukiNailShopManager::CYukiNailShopManager()
: m_pCurOperatorAccount(NULL)
{

}

CYukiNailShopManager::~CYukiNailShopManager()
{
    for (size_t i = 0; i < m_allRecords.size(); ++i)
    {
        BEATS_SAFE_DELETE(m_allRecords[i]);
    }
    m_allRecords.clear();
    CAccountManager::Destroy();
    CMemberManager::Destroy();
}

bool CYukiNailShopManager::Init()
{
    bool bRet = CAccountManager::GetInstance()->Init() && CMemberManager::GetInstance()->Init() && LoadConsumeRecord();
    return bRet;
}

CAccount* CYukiNailShopManager::GetCurrentOperatorAccount()
{
    return m_pCurOperatorAccount;
}

void CYukiNailShopManager::Login(CAccount* pAccount)
{
    BEATS_ASSERT(m_pCurOperatorAccount == NULL, _T("Can't login twice!"));
    m_pCurOperatorAccount = pAccount;
}

void CYukiNailShopManager::Logout()
{
    m_pCurOperatorAccount = NULL;
}

bool CYukiNailShopManager::SubmitConsumeRecord(float fPayAmount, char consumeType, const TString& strCustomer, const TCHAR* pszDetail)
{
    SetCurrentDirectory(CMainApp::GetMainApp()->GetWorkPath().c_str());
    CreateDirectory(_T("ConsumeRecord"), NULL);
    SYSTEMTIME sysTime;
    GetLocalTime(&sysTime);
    TCHAR szFileName[MAX_PATH];
    _stprintf(szFileName, _T("ConsumeRecord/yuki_record_%d_%.2d.rec"), sysTime.wYear, sysTime.wMonth);
    FILE* pFile = _tfopen(szFileName, _T("rb+"));
    if (pFile == NULL)
    {
        pFile = _tfopen(szFileName, _T("wb+"));
    }
    if (pFile != NULL)
    {
        size_t uCount = 0;
        fread(&uCount, sizeof(uCount), 1, pFile);
        fseek(pFile, 0, SEEK_SET);
        ++uCount;
        fwrite(&uCount, sizeof(uCount), 1, pFile);
        CConsumeRecord* pConsumeRecord = new CConsumeRecord;
        pConsumeRecord->Create(sysTime, m_pCurOperatorAccount->GetId(), consumeType, strCustomer, fPayAmount, pszDetail);
        fseek(pFile, 0, SEEK_END);
        pConsumeRecord->WriteToFile(pFile);
        AddRecord(pConsumeRecord);
        BEATS_ASSERT(m_pCurOperatorAccount->GetAccountString() == pConsumeRecord->GetOperatorName());
        AddOperationHistory(_T("添加消费记录"));
        fclose(pFile);
    }
    return true;
}

const TYearConsumeRecordMap& CYukiNailShopManager::GetConsumeRecordsMap()const
{
    return m_consumeRecordsMap;
}

bool CYukiNailShopManager::LoadConsumeRecord()
{
    SetCurrentDirectory(CMainApp::GetMainApp()->GetWorkPath().c_str());
    WIN32_FIND_DATA FindFileData;
    HANDLE hFind = FindFirstFile(_T("ConsumeRecord\\*"), &FindFileData);
    BOOL bFindFile = hFind != INVALID_HANDLE_VALUE;
    while (bFindFile) 
    {
        FILE* pFile = _tfopen(wxString::Format(_T("ConsumeRecord\\%s"), FindFileData.cFileName), _T("rb+"));
        if (pFile != NULL)
        {
            size_t uCount = 0;
            fread(&uCount, sizeof(uCount), 1, pFile);
            for (size_t i = 0; i < uCount; ++i)
            {
                CConsumeRecord* pRecord = new CConsumeRecord();
                pRecord->LoadFromFile(pFile);
                AddRecord(pRecord);
            }
            fclose(pFile);
        }
        bFindFile = FindNextFile(hFind, &FindFileData);
        if (!bFindFile)
        {
            FindClose(hFind);
        }
    }
    return true;
}

void CYukiNailShopManager::AddRecord( CConsumeRecord* pRecord )
{
    BEATS_ASSERT(pRecord != NULL);
    const SYSTEMTIME* pRecordTime = &pRecord->GetConsumeRecordTime();
    TYearConsumeRecordMap::iterator iter = m_consumeRecordsMap.find(pRecordTime);
    if (iter == m_consumeRecordsMap.end())
    {
        m_consumeRecordsMap[pRecordTime] = TMonthConsumeRecordMap();
        iter = m_consumeRecordsMap.find(pRecordTime);
    }
    TMonthConsumeRecordMap::iterator subIter = iter->second.find(pRecordTime);
    if (subIter == iter->second.end())
    {
        iter->second[pRecordTime] = TDayConsumeRecordMap();
        subIter = iter->second.find(pRecordTime);
    }
    TDayConsumeRecordMap::iterator dayIter = subIter->second.find(pRecordTime);
    BEATS_ASSERT(dayIter == subIter->second.end(), _T("Record time can't be the same!"));
    if (dayIter == subIter->second.end())
    {
        subIter->second[pRecordTime] = pRecord;
        m_allRecords.push_back(pRecord);
    }
}

void CYukiNailShopManager::AddOperationHistory(const TString& strHistory)
{
    m_pCurOperatorAccount->AddOperationHistory(strHistory);
}


