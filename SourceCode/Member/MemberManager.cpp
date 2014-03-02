#include "stdafx.h"
#include "MemberManager.h"
#include "../MainApp.h"

CMemberManager* CMemberManager::m_pInstance = NULL;

CMemberManager::CMemberManager()
{

}

CMemberManager::~CMemberManager()
{
    for (std::map<const TString, CMember*>::iterator iter = m_memberTelMap.begin(); iter != m_memberTelMap.end(); ++iter)
    {
        BEATS_SAFE_DELETE(iter->second);
    }
    m_memberTelMap.clear();
}

bool CMemberManager::Init()
{
    LoadMemberData();
    return true;
}

void CMemberManager::LoadMemberData()
{
    FILE* pMemberInfoFile = _tfopen(_T("Member\\MemberInfo.bin"), _T("rb+"));
    if (pMemberInfoFile == NULL)
    {
        pMemberInfoFile = _tfopen(_T("Member\\MemberInfo.bin"), _T("wb+"));
    }
    if (pMemberInfoFile != NULL)
    {
        size_t uMemberInfoCount = 0;
        fread(&uMemberInfoCount, sizeof(uMemberInfoCount), 1, pMemberInfoFile);
        for (size_t i = 0; i < uMemberInfoCount; ++i)
        {
            CMember* pMember = new CMember;
            pMember->LoadFromFile(pMemberInfoFile);
            TString strTel(pMember->GetTelString());
            std::map<const TString, CMember*>::iterator iter = m_memberTelMap.find(strTel);
            if (iter == m_memberTelMap.end())
            {
                m_memberTelMap[strTel] = pMember;
            }
        }
    }
}

void CMemberManager::SaveMemberData()
{
    SetCurrentDirectory(CMainApp::GetMainApp()->GetWorkPath().c_str());
    CreateDirectory(_T("Member"), NULL);
    FILE* pMemberInfoFile = _tfopen(_T("Member\\MemberInfo.bin"), _T("rb+"));
    if (pMemberInfoFile == NULL)
    {
        pMemberInfoFile = _tfopen(_T("Member\\MemberInfo.bin"), _T("wb+"));
    }
    if (pMemberInfoFile != NULL)
    {
        size_t uMemberInfoCount = m_memberTelMap.size();
        fwrite(&uMemberInfoCount, sizeof(uMemberInfoCount), 1, pMemberInfoFile);
        for (std::map<const TString, CMember*>::iterator iter = m_memberTelMap.begin(); iter != m_memberTelMap.end(); ++iter)
        {
            iter->second->SaveToFile(pMemberInfoFile);
        }
        fclose(pMemberInfoFile);
    }
}

CMember* CMemberManager::RegisterMember( EDiscountType discountType, const TCHAR* pszTel, const TCHAR* pszName, const SYSTEMTIME& birthday, const SYSTEMTIME& registerTime )
{
    CMember* pMember = NULL;
    std::map<const TString, CMember*>::iterator iter = m_memberTelMap.find(TString(pszTel));
    if (iter != m_memberTelMap.end())
    {
        wxMessageBox(wxString::Format(_T("电话 %s 已经存在! 无法再次注册!"), pszTel));
    }
    else
    {
        pMember = new CMember(discountType, pszTel, pszName, birthday, registerTime);
        m_memberTelMap[TString(pszTel)] = pMember;
        SaveMemberData();
    }
    return pMember;
}

const std::map<const TString, CMember*>& CMemberManager::GetMemberMap() const
{
    return m_memberTelMap;
}

float CMemberManager::OnConsume( const TString& tel, float fConsumeAmount, bool bRecharge /*= false*/ )
{
    std::map<const TString, CMember*>::iterator iter = m_memberTelMap.find(tel);
    if (iter == m_memberTelMap.end())
    {
        wxMessageBox(_T("修改账户余额失败！请联系开发人员并停止使用该软件！"));
    }
    else
    {
        CMember* pMember = iter->second;
        pMember->SetBalance(bRecharge ? iter->second->GetBalance() + fConsumeAmount : iter->second->GetBalance() - fConsumeAmount);
        SaveMemberData();
        wxMessageBox(wxString::Format(_T("修改账户余额成功!\n账户: %s\n号码: %s\n操作金额: %f\n当前余额: %f"), pMember->GetName(), pMember->GetTelString(), fConsumeAmount, pMember->GetBalance()));
    }
    return iter->second->GetBalance();
}

CMember* CMemberManager::GetMember( const TString& tel ) const
{
    CMember* pMember = NULL;
    std::map<const TString, CMember*>::const_iterator iter = m_memberTelMap.find(tel);
    if (iter != m_memberTelMap.end())
    {
        pMember = iter->second;
    }
    return pMember;
}
