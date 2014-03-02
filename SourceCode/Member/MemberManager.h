#ifndef _MEMBERMANAGER__H
#define _MEMBERMANAGER__H

#include "Member.h"

class CMemberManager
{
    BEATS_DECLARE_SINGLETON(CMemberManager)
public:
    bool Init();
    void LoadMemberData();
    void SaveMemberData();

    CMember* RegisterMember(EDiscountType discountType, const TCHAR* pszTel, const TCHAR* pszName, const SYSTEMTIME& birthday, const SYSTEMTIME& registerTime);

    const std::map<const TString, CMember*>& GetMemberMap() const;

    float OnConsume(const TString& tel, float fConsumeAmount, bool bRecharge = false);

    CMember* GetMember(const TString& tel) const;


private:
    std::map<const TString, CMember*> m_memberTelMap;
};

#endif
