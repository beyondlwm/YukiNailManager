#ifndef _MEMBER__H
#define _MEMBER__H

enum EDiscountType
{
    eDT_Five,
    eDT_Six,
    eDT_Seven,

    eDT_NoDiscount,

    eDT_Count,
    eDT_Force32Bit = 0xFFFFFFFF
};

static const TCHAR* pszDiscountTypeString[] =
{
    _T("ŒÂ’€"),
    _T("¡˘’€"),
    _T("∆ﬂ’€"),
    _T("Œﬁ’€ø€")
};

class CMember
{
public:
    CMember();
    CMember(EDiscountType discountType, const TCHAR* pszTel, const TCHAR* pszName, const SYSTEMTIME& birthday, const SYSTEMTIME& registerTime);
    ~CMember();

    void LoadFromFile(FILE* pFile);
    void SaveToFile(FILE* pFile);

    float GetBalance() const;
    void SetBalance(float fBalance);

    void SetCancelFlag(bool bCancelFlag);
    bool GetCancelFlag() const;
    EDiscountType GetDiscountType() const;
    void SetDiscountType(EDiscountType type);
    const TCHAR* GetDiscountTypeString() const;
    const TCHAR* GetTelString() const;
    const TCHAR* GetName() const;
    const SYSTEMTIME& GetBirthday() const;
    const SYSTEMTIME& GetRegisterTime() const;

private:
    bool m_bCanceled;
    float m_fBalance;
    EDiscountType m_discountType;
    TString m_strTel;
    TString m_strName;
    SYSTEMTIME m_birthDay;
    SYSTEMTIME m_registerTime;
};

#endif