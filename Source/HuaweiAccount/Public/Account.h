#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include <string>
#include "json98.h"

#define LOGIN_ACTION 0
#define LOGIN_BY_ID_TOKEN_ACTION 1
#define LOGIN_BY_AUTH_CODE_ACTION 2
#define LOGOUT_ACTION 3
#define CANCEL_AUTH_ACTION 4

namespace huawei
{
    struct AccountInfo
    {
        AccountInfo(const json::Json &json);

        FString displayName;
        FString avatarUriString;
        FString email;
        FString openId;
        FString unionId;
    };

    class AccountListener
    {
    public:    
        virtual void onLoggedIn(const AccountInfo account) = 0;
        virtual void onGetIdToken(const FString idToken, const AccountInfo account) = 0;
        virtual void onGetAuthCode(const FString authCode, const AccountInfo account) = 0;
        virtual void onLoggedOut() = 0;
        virtual void onCancelledAuth() = 0;
        virtual void onException(int action, const FString message) = 0;
    };

    class Account
    {
    public:
        static void loginWithoutVerification();
        static void loginWithIdToken();
        static void loginWithAuthorizationCode();
        static void logOut();
        static void cancelAuthorization();

        static void setListener(AccountListener *listener);
        static void removeListener();
        static AccountListener *getListener();
    };
}