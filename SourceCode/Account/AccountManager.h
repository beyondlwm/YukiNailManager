#ifndef _ACCOUNT_MANAGER_H_
#define _ACCOUNT_MANAGER_H_

class CAccount;
class CAccountManager
{
    BEATS_DECLARE_SINGLETON(CAccountManager);
public:

    bool Init();

    CAccount* RegisterAccount(const TString& strAccount, const TString& strPassword, size_t uPrivilege);
    CAccount* Login(const TString& strAccount, const TString& strPassword) const;

    const TCHAR* GetAccountName(size_t uId) const;

    CAccount* GetAccount(const TString& strAccount) const;

    const std::map<size_t, CAccount*>& GetAccountMap() const;

    void AddAccount(CAccount* pAccount);
    void SaveAccountData();

private:
    bool LoadAccountData();


private:
    size_t m_uLastId;
    std::map<const TString, CAccount*> m_accountMap;
    std::map<size_t, CAccount*> m_accountIdMap;

};

#endif
