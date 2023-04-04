#pragma once
#include "Account.h"
#include <string>

DECLARE_LOG_CATEGORY_EXTERN(HuaweiAccount_Native, Log, All);
using namespace std;

namespace huawei
{

    class AccountJniWrapper
    {

    public:
        static AccountJniWrapper *getInstance();

        AccountJniWrapper();
        ~AccountJniWrapper();

        void loginWithoutVerification();
        void loginWithIdToken();
        void loginWithAuthorizationCode();
        void logOut();
        void cancelAuthorization();

        // Listener
        void setListener(AccountListener *listener);
        void removeListener();
        AccountListener *getListener();

        // Callbacks
        void onLoggedIn(const string account);
        void onGetIdToken(const FString idToken, const string account);
        void onGetAuthCode(const FString authCode, const string account);
        void onLoggedOut();
        void onCancelledAuth();
        void onException(int action, const FString message);

    protected:
        AccountListener *_listener;
    };
}
