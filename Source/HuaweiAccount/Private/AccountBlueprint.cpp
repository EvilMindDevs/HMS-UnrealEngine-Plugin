#include "AccountBlueprint.h"

using namespace huawei;

FAccountInfo convertFromRawData(AccountInfo info)
{
    FAccountInfo fInfo;
    fInfo.displayName = info.displayName;
    fInfo.avatarUriString = info.avatarUriString;
    fInfo.email = info.email;
    fInfo.openId = info.openId;
    fInfo.unionId = info.unionId;
    return fInfo;
}

FOnLogInSuccess UHuaweiAccountBlueprint::_onLogInSuccess;
FOnLogInException UHuaweiAccountBlueprint::_onLogInException;
void UHuaweiAccountBlueprint::loginWithoutVerification(const FOnLogInSuccess &onSuccess, const FOnLogInException &onException)
{
    Account::loginWithoutVerification();
    UHuaweiAccountBlueprint::_onLogInSuccess = onSuccess;
    UHuaweiAccountBlueprint::_onLogInException = onException;
}

FOnLogInByIdTokenSuccess UHuaweiAccountBlueprint::_onLogInByIdTokenSuccess;
FOnLogInByIdTokenException UHuaweiAccountBlueprint::_onLogInByIdTokenException;
void UHuaweiAccountBlueprint::loginWithIdToken(const FOnLogInByIdTokenSuccess &onSuccess, const FOnLogInByIdTokenException &onException)
{
    Account::loginWithIdToken();
    UHuaweiAccountBlueprint::_onLogInByIdTokenSuccess = onSuccess;
    UHuaweiAccountBlueprint::_onLogInByIdTokenException = onException;
}

FOnLogInByAuthCodeSuccess UHuaweiAccountBlueprint::_onLogInByAuthCodeSuccess;
FOnLogInByAuthCodeException UHuaweiAccountBlueprint::_onLogInByAuthCodeException;
void UHuaweiAccountBlueprint::loginWithAuthorizationCode(const FOnLogInByAuthCodeSuccess &onSuccess, const FOnLogInByAuthCodeException &onException)
{
    Account::loginWithAuthorizationCode();
    UHuaweiAccountBlueprint::_onLogInByAuthCodeSuccess = onSuccess;
    UHuaweiAccountBlueprint::_onLogInByAuthCodeException = onException;
}

FOnLogOutSuccess UHuaweiAccountBlueprint::_onLogOutSuccess;
FOnLogOutException UHuaweiAccountBlueprint::_onLogOutException;
void UHuaweiAccountBlueprint::logout(const FOnLogOutSuccess &onSuccess, const FOnLogOutException &onException)
{
    Account::logOut();
    UHuaweiAccountBlueprint::_onLogOutSuccess = onSuccess;
    UHuaweiAccountBlueprint::_onLogOutException = onException;
}

FOnCancelAuthSuccess UHuaweiAccountBlueprint::_onCancelAuthSuccess;
FOnCancelAuthException UHuaweiAccountBlueprint::_onCancelAuthException;
void UHuaweiAccountBlueprint::cancelAuthorization(const FOnCancelAuthSuccess &onSuccess, const FOnCancelAuthException &onException)
{
    Account::cancelAuthorization();
    UHuaweiAccountBlueprint::_onCancelAuthSuccess = onSuccess;
    UHuaweiAccountBlueprint::_onCancelAuthException = onException;
}

void UHuaweiAccountBlueprint::onLoggedIn(const AccountInfo account)
{
    UHuaweiAccountBlueprint::_onLogInSuccess.ExecuteIfBound(convertFromRawData(account));
}

void UHuaweiAccountBlueprint::onGetIdToken(const FString idToken, const AccountInfo account)
{
    UHuaweiAccountBlueprint::_onLogInByIdTokenSuccess.ExecuteIfBound
    (
        idToken,
        convertFromRawData(account)
    );
}

void UHuaweiAccountBlueprint::onGetAuthCode(const FString authCode, const AccountInfo account)
{
    UHuaweiAccountBlueprint::_onLogInByAuthCodeSuccess.ExecuteIfBound
    (
        authCode,
        convertFromRawData(account)
    );
}

void UHuaweiAccountBlueprint::onLoggedOut()
{
    UHuaweiAccountBlueprint::_onLogOutSuccess.ExecuteIfBound();
}

void UHuaweiAccountBlueprint::onCancelledAuth()
{
    UHuaweiAccountBlueprint::_onCancelAuthSuccess.ExecuteIfBound();
}

void UHuaweiAccountBlueprint::onException(int action, const FString message)
{
    switch (action)
    {
    case LOGIN_ACTION:
        UHuaweiAccountBlueprint::_onLogInException.ExecuteIfBound(message);
        break;
    case LOGIN_BY_ID_TOKEN_ACTION:
        UHuaweiAccountBlueprint::_onLogInByIdTokenException.ExecuteIfBound(message);
        break;
    case LOGIN_BY_AUTH_CODE_ACTION:
        UHuaweiAccountBlueprint::_onLogInByAuthCodeException.ExecuteIfBound(message);
        break;
    case LOGOUT_ACTION:
        UHuaweiAccountBlueprint::_onLogOutException.ExecuteIfBound(message);
        break;
    case CANCEL_AUTH_ACTION:
        UHuaweiAccountBlueprint::_onCancelAuthException.ExecuteIfBound(message);
        break;
    default:
        break;
    }
}
