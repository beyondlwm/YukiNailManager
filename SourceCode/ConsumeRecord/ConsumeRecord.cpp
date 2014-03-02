#include "stdafx.h"
#include "ConsumeRecord.h"
#include "../Account/AccountManager.h"
#include "../Member/MemberManager.h"

CConsumeRecord::CConsumeRecord()
{

}

CConsumeRecord::~CConsumeRecord()
{

}

void CConsumeRecord::Create( const SYSTEMTIME& sysTime, size_t uOperatorId, char uConsumeType, const TString& strCustomer, float fPayAmount, const TString& strDetail )
{
    m_uOperatorId = uOperatorId;
    m_uConsumeType = uConsumeType;
    m_consumeAmount = fPayAmount;
    m_createTime = sysTime;
    m_strDetail = strDetail;
    m_fAccountBalance = 0;
    m_strCustomer = strCustomer;
    if (uConsumeType == eCT_Member || uConsumeType == eCT_Recharge)
    {
        m_fAccountBalance = CMemberManager::GetInstance()->OnConsume(m_strCustomer, fPayAmount, m_uConsumeType == eCT_Recharge);
    }
}

void CConsumeRecord::WriteToFile( FILE* pFile ) const
{
    fwrite(&m_uOperatorId, sizeof(m_uOperatorId), 1, pFile);
    fwrite(&m_uConsumeType, sizeof(m_uConsumeType), 1, pFile);
    fwrite(&m_consumeAmount, sizeof(m_consumeAmount), 1, pFile);
    fwrite(&m_fAccountBalance, sizeof(m_fAccountBalance), 1, pFile);
    fwrite(&m_createTime, sizeof(m_createTime), 1, pFile);
    size_t uStringSize = (m_strDetail.length() + 1) * sizeof(TCHAR);
    fwrite(&uStringSize, sizeof(uStringSize), 1, pFile);
    fwrite(m_strDetail.c_str(), uStringSize, 1, pFile);
    uStringSize = (m_strCustomer.length() + 1) * sizeof(TCHAR);
    fwrite(&uStringSize, sizeof(uStringSize), 1, pFile);
    fwrite(m_strCustomer.c_str(), uStringSize, 1, pFile);
}

void CConsumeRecord::LoadFromFile(FILE* pFile)
{
    fread(&m_uOperatorId, sizeof(m_uOperatorId), 1, pFile);
    fread(&m_uConsumeType, sizeof(m_uConsumeType), 1, pFile);
    fread(&m_consumeAmount, sizeof(m_consumeAmount), 1, pFile);
    fread(&m_fAccountBalance, sizeof(m_fAccountBalance), 1, pFile);
    fread(&m_createTime, sizeof(m_createTime), 1, pFile);
    size_t uStringSize = 0;
    fread(&uStringSize, sizeof(uStringSize), 1, pFile);
    BEATS_ASSERT(uStringSize < MAX_PATH * 5, _T("Data out of bound!"));
    TCHAR szBuffer[MAX_PATH * 5];
    fread(szBuffer, uStringSize, 1, pFile);
    m_strDetail = szBuffer;

    fread(&uStringSize, sizeof(uStringSize), 1, pFile);
    BEATS_ASSERT(uStringSize < MAX_PATH * 5, _T("Data out of bound!"));
    fread(szBuffer, uStringSize, 1, pFile);
    m_strCustomer = szBuffer;
}

const SYSTEMTIME& CConsumeRecord::GetConsumeRecordTime() const
{
    return m_createTime;
}

size_t CConsumeRecord::GetOperatorId() const
{
    return m_uOperatorId;
}

const TCHAR* CConsumeRecord::GetOperatorName() const
{
    return CAccountManager::GetInstance()->GetAccountName(m_uOperatorId);
}

float CConsumeRecord::GetConsumeAmount() const
{
    return m_consumeAmount;
}

const TString& CConsumeRecord::GetDetailString() const
{
    return m_strDetail;
}

const TCHAR* CConsumeRecord::GetConsumeTypeString() const
{
    return pszConsumeTypeString[m_uConsumeType];
}

char CConsumeRecord::GetConsumeType() const
{
    return m_uConsumeType;
}

const TString& CConsumeRecord::GetCustomerString() const
{
    return m_strCustomer;
}

float CConsumeRecord::GetAccountBalance() const
{
    return m_fAccountBalance;
}
