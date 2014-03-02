#ifndef _CONSUMERECORD_H_
#define _CONSUMERECORD_H_

enum EConsumeType
{
    eCT_Normal,
    eCT_Member,
    eCT_VIP,
    eCT_Recharge,
    eCT_Other,

    eCT_Count,
    eCT_Force32Bit = 0xFFFFFFFF
};

static const TCHAR* pszConsumeTypeString[] = 
{
    _T("普通"),
    _T("会员"),
    _T("VIP"),
    _T("会员充值"),
    _T("其他")
};

class CConsumeRecord
{
public:
    CConsumeRecord();
    virtual ~CConsumeRecord();

    void Create(const SYSTEMTIME& sysTime, size_t uOperatorId, char m_uConsumeType, const TString& strCustomer, float fPayAmount, const TString& strDetail);
    void WriteToFile(FILE* pFile) const;
    void LoadFromFile(FILE* pFile);
    const SYSTEMTIME& GetConsumeRecordTime() const;
    size_t GetOperatorId() const;
    const TCHAR* GetOperatorName() const;
    float GetConsumeAmount() const;
    float GetAccountBalance() const;
    const TString& GetDetailString() const;
    const TCHAR* GetConsumeTypeString() const;
    char GetConsumeType() const;
    const TString& GetCustomerString() const;

private:
    char m_uConsumeType;
    size_t m_uOperatorId;
    float m_consumeAmount;
    float m_fAccountBalance;
    SYSTEMTIME m_createTime;
    TString m_strDetail;
    TString m_strCustomer;
};

#endif