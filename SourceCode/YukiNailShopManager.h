#ifndef _YUKINAILSHOPMANAGER_H__
#define _YUKINAILSHOPMANAGER_H__

class CAccount;
class CConsumeRecord;

struct SystemTimeSort
{
    bool operator()(const _SYSTEMTIME* _Left, const _SYSTEMTIME* _Right) const
    {
        if (_Left->wYear == _Right->wYear)
        {
            if (_Left->wMonth == _Right->wMonth)
            {
                if (_Left->wDay == _Right->wDay)
                {
                    if (_Left->wHour == _Right->wHour)
                    {
                        if (_Left->wMinute == _Right->wMinute)
                        {
                            if (_Left->wSecond == _Right->wSecond)
                            {
                                return _Left->wMilliseconds < _Right->wMilliseconds;
                            }
                            else
                            {
                                return _Left->wSecond < _Right->wSecond;
                            }
                        }
                        else
                        {
                            return _Left->wMinute < _Right->wMinute;
                        }
                    }
                    else
                    {
                        return _Left->wHour < _Right->wHour;
                    }
                }
                else
                {
                    return _Left->wDay < _Right->wDay;
                }
            }
            else
            {
                return _Left->wMonth < _Right->wMonth;
            }
        }
        else
        {
            return _Left->wYear < _Right->wYear;
        }
    }
};

struct SystemTimeSortByMonth
{
    bool operator()(const _SYSTEMTIME* _Left, const _SYSTEMTIME* _Right) const
    {
        if (_Left->wYear == _Right->wYear)
        {
            return _Left->wMonth < _Right->wMonth;
        }
        else
        {
            return _Left->wYear < _Right->wYear;
        }
    }
};

struct SystemTimeSortByDay
{
    bool operator()(const _SYSTEMTIME* _Left, const _SYSTEMTIME* _Right) const
    {
        if (_Left->wYear == _Right->wYear)
        {
            if (_Left->wMonth == _Right->wMonth)
            {
                return _Left->wDay < _Right->wDay;
            }
            else
            {
                return _Left->wMonth < _Right->wMonth;
            }
        }
        else
        {
            return _Left->wYear < _Right->wYear;
        }
    }

};

typedef std::map<const SYSTEMTIME*, CConsumeRecord*, SystemTimeSort> TDayConsumeRecordMap;
typedef std::map<const SYSTEMTIME*, TDayConsumeRecordMap, SystemTimeSortByDay> TMonthConsumeRecordMap;
typedef std::map<const SYSTEMTIME*, TMonthConsumeRecordMap, SystemTimeSortByMonth> TYearConsumeRecordMap;

class CYukiNailShopManager
{
    BEATS_DECLARE_SINGLETON(CYukiNailShopManager)
public:

    bool Init();

    CAccount* GetCurrentOperatorAccount();
    void Login(CAccount* pAccount);
    void Logout();

    bool LoadConsumeRecord();

    bool SubmitConsumeRecord(float fPayAmount, char consumeType, const TString& strCustomer, const TCHAR* pszDetail);

    const TYearConsumeRecordMap& GetConsumeRecordsMap() const;

    void AddRecord(CConsumeRecord* pRecord);

    void AddOperationHistory(const TString& strHistory);

private:
    CAccount* m_pCurOperatorAccount;

    TYearConsumeRecordMap m_consumeRecordsMap;
    std::vector<CConsumeRecord*> m_allRecords;

};


#endif