#include "Account.h"
#include "HuaweiAccountModule.h"
#include "AccountJniWrapper.h"

using namespace std;
using namespace json;

namespace huawei
{

    void Account::loginWithoutVerification()
    {
        AccountJniWrapper::getInstance()->loginWithoutVerification();
    }

    void Account::loginWithIdToken()
    {
        AccountJniWrapper::getInstance()->loginWithIdToken();
    }

    void Account::loginWithAuthorizationCode()
    {
        AccountJniWrapper::getInstance()->loginWithAuthorizationCode();
    }

    void Account::logOut()
    {
        AccountJniWrapper::getInstance()->logOut();
    }

    void Account::cancelAuthorization()
    {
        AccountJniWrapper::getInstance()->cancelAuthorization();
    }
    
    void Account::setListener(AccountListener *listener)
    {
        AccountJniWrapper::getInstance()->setListener(listener);
    }

    void Account::removeListener()
    {
        AccountJniWrapper::getInstance()->removeListener();
    }

    AccountListener *Account::getListener()
    {
        return AccountJniWrapper::getInstance()->getListener();
    }

    /********************************************
     * Data classes
     *******************************************/
    AccountInfo::AccountInfo(const json::Json &json)
    {
        displayName = FString(UTF8_TO_TCHAR(json["displayName"].string_value().c_str()));
        avatarUriString = FString(UTF8_TO_TCHAR(json["avatarUriString"].string_value().c_str()));
        email = FString(UTF8_TO_TCHAR(json["email"].string_value().c_str()));
        openId = FString(UTF8_TO_TCHAR(json["openId"].string_value().c_str()));
        unionId = FString(UTF8_TO_TCHAR(json["unionId"].string_value().c_str()));
    }
}