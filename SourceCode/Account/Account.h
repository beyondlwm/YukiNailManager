#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

struct SOperationHistory
{
    SOperationHistory(const SYSTEMTIME* pTime, const TString& strHistory)
    {
        memcpy(&m_time, pTime, sizeof(m_time));
        m_strHistory = strHistory;
    }

    ~SOperationHistory()
    {

    }

    SYSTEMTIME m_time;
    TString m_strHistory;
};
class CAccount
{
public:
    enum EAccountPrivilegeType
    {
        eAPT_OperateAccount,
        eAPT_Balance,
        eAPT_VipView,
        eAPT_MemberQuery,
        eAPT_MemberRegister,
        eAPT_MemberManage,
        eAPT_Summary,

        eAPT_Count,
        eAPT_Force32Bit = 0xFFFFFFFF
    };
    static const TCHAR* pszAccountPrivilegeString[];

public:
    CAccount();
    CAccount(size_t uId, const TString& strAccount, const TString& strPassword, size_t uPrivilege, const SYSTEMTIME* pCreateTime = NULL);
    ~CAccount();

    void SetPassword(const TString& strPassword);
    const TString& GetPassword() const;

    const TString& GetAccountString() const;

    size_t GetId() const;

    const SYSTEMTIME& GetCreateTime() const;
    const SYSTEMTIME& GetLastLoginTime() const;
    void SetLastLoginTime(const SYSTEMTIME& time);

    bool CheckPrivilege(EAccountPrivilegeType uPrivilege) const;
    size_t GetPrivilege() const;
    void SwitchPrivilege(EAccountPrivilegeType type, bool bEnable);
    void SetPrivilege(size_t uPrivilege);

    void WriteToFile(FILE* pFile);
    void ReadFromFile(FILE* pFile);

    void AddOperationHistory(const TString& history);
    void LoadOperationHistory();

private:
    size_t m_uId;
    size_t m_uPrivilege;
    TString m_strAccount;
    TString m_strPassword;
    SYSTEMTIME m_createTime;
    SYSTEMTIME m_lastLoginTime;
    std::vector<SOperationHistory> m_operationHistory;
};

#endif

