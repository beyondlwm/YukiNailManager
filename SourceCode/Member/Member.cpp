#include "stdafx.h"
#include "Member.h"

CMember::CMember()
: m_bCanceled(false)
, m_fBalance(0)
, m_discountType(eDT_NoDiscount)
{
    ZeroMemory(&m_birthDay, sizeof(m_birthDay));
    ZeroMemory(&m_registerTime, sizeof(m_registerTime));
}

CMember::CMember(EDiscountType discountType, const TCHAR* pszTel, const TCHAR* pszName, const SYSTEMTIME& birthday, const SYSTEMTIME& registerTime )
: m_bCanceled(false)
, m_fBalance(0)
, m_discountType(discountType)
, m_strTel(pszTel)
, m_strName(pszName)
{
    memcpy(&m_birthDay, &birthday, sizeof(m_birthDay));
    memcpy(&m_registerTime, &registerTime, sizeof(m_registerTime));
}

CMember::~CMember()
{

}

void CMember::LoadFromFile(FILE* pFile)
{
    fread(&m_fBalance, sizeof(m_fBalance), 1, pFile);
    fread(&m_discountType, sizeof(m_discountType), 1, pFile);
    size_t uStringSize = 0;
    fread(&uStringSize, sizeof(uStringSize), 1, pFile);
    TCHAR szBuffer[MAX_PATH];
    fread(&szBuffer, uStringSize, 1, pFile);
    m_strTel = szBuffer;

    fread(&uStringSize, sizeof(uStringSize), 1, pFile);
    fread(&szBuffer, uStringSize, 1, pFile);
    m_strName = szBuffer;

    fread(&m_birthDay, sizeof(m_birthDay), 1, pFile);
    fread(&m_registerTime, sizeof(m_registerTime), 1, pFile);
    fread(&m_bCanceled, sizeof(m_bCanceled), 1, pFile);
}

void CMember::SaveToFile(FILE* pFile)
{
    fwrite(&m_fBalance, sizeof(m_fBalance), 1, pFile);
    fwrite(&m_discountType, sizeof(m_discountType), 1, pFile);
    size_t uStringSize = (m_strTel.length() + 1) * sizeof(TCHAR);
    fwrite(&uStringSize, sizeof(uStringSize), 1, pFile);
    fwrite(m_strTel.c_str(), uStringSize, 1, pFile);

    uStringSize = (m_strName.length() + 1) * sizeof(TCHAR);
    fwrite(&uStringSize, sizeof(uStringSize), 1, pFile);
    fwrite(m_strName.c_str(), uStringSize, 1, pFile);


    fwrite(&m_birthDay, sizeof(m_birthDay), 1, pFile);
    fwrite(&m_registerTime, sizeof(m_registerTime), 1, pFile);
    fwrite(&m_bCanceled, sizeof(m_bCanceled), 1, pFile);
}

float CMember::GetBalance() const
{
    return m_fBalance;
}

void CMember::SetBalance(float fBalance)
{
    m_fBalance = fBalance;
}

EDiscountType CMember::GetDiscountType() const
{
    return m_discountType;
}

void CMember::SetDiscountType(EDiscountType type)
{
    m_discountType = type;
}

const TCHAR* CMember::GetDiscountTypeString() const
{
    return pszDiscountTypeString[m_discountType];
}

const TCHAR* CMember::GetTelString() const
{
    return m_strTel.c_str();
}

const TCHAR* CMember::GetName() const
{
    return m_strName.c_str();
}

const SYSTEMTIME& CMember::GetBirthday() const
{
    return m_birthDay;
}

const SYSTEMTIME& CMember::GetRegisterTime() const
{
    return m_registerTime;
}

void CMember::SetCancelFlag( bool bCancelFlag )
{
    m_bCanceled = bCancelFlag;
}

bool CMember::GetCancelFlag() const
{
    return m_bCanceled;
}
