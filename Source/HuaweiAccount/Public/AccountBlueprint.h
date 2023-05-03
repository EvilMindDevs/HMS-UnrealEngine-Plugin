#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine.h"
#include "Account.h"
#include "AccountBlueprint.generated.h"

using namespace huawei;

USTRUCT(Blueprintable, BlueprintType)
struct HUAWEIACCOUNT_API FAccountInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiAccount")
    FString displayName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiAccount")
    FString avatarUriString;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiAccount")
    FString email;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiAccount")
    FString openId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiAccount")
    FString unionId;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLogInSuccess, FAccountInfo, account);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLogInException, FString, message);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLogInByIdTokenSuccess, FString, idToken, FAccountInfo, account);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLogInByIdTokenException, FString, message);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnLogInByAuthCodeSuccess, FString, authCode, FAccountInfo, account);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLogInByAuthCodeException, FString, message);
DECLARE_DYNAMIC_DELEGATE(FOnLogOutSuccess);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLogOutException, FString, message);
DECLARE_DYNAMIC_DELEGATE(FOnCancelAuthSuccess);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCancelAuthException, FString, message);

UCLASS()
class HUAWEIACCOUNT_API UHuaweiAccountBlueprint : public UBlueprintFunctionLibrary,
                                                  public AccountListener
{
    GENERATED_BODY()

public:
    UHuaweiAccountBlueprint(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
    {
        Account::setListener(this);
    };

    static FOnLogInSuccess _onLogInSuccess;
    static FOnLogInByIdTokenSuccess _onLogInByIdTokenSuccess;
    static FOnLogInByAuthCodeSuccess _onLogInByAuthCodeSuccess;
    static FOnLogOutSuccess _onLogOutSuccess;
    static FOnCancelAuthSuccess _onCancelAuthSuccess;
    static FOnLogInException _onLogInException;
    static FOnLogInByIdTokenException _onLogInByIdTokenException;
    static FOnLogInByAuthCodeException _onLogInByAuthCodeException;
    static FOnLogOutException _onLogOutException;
    static FOnCancelAuthException _onCancelAuthException;

    UFUNCTION(BlueprintCallable, Category = "HuaweiAccount Category")
    static void loginWithoutVerification(const FOnLogInSuccess &onSuccess, const FOnLogInException &onException);

    UFUNCTION(BlueprintCallable, Category = "HuaweiAccount Category")
    static void loginWithIdToken(const FOnLogInByIdTokenSuccess &onSuccess, const FOnLogInByIdTokenException &onException);

    UFUNCTION(BlueprintCallable, Category = "HuaweiAccount Category")
    static void loginWithAuthorizationCode(const FOnLogInByAuthCodeSuccess &onSuccess, const FOnLogInByAuthCodeException &onException);

    UFUNCTION(BlueprintCallable, Category = "HuaweiAccount Category")
    static void logout(const FOnLogOutSuccess &onSuccess, const FOnLogOutException &onException);

    UFUNCTION(BlueprintCallable, Category = "HuaweiAccount Category")
    static void cancelAuthorization(const FOnCancelAuthSuccess &onSuccess, const FOnCancelAuthException &onException);

    void onLoggedIn(const huawei::AccountInfo account);
    void onGetIdToken(const FString idToken, const huawei::AccountInfo account);
    void onGetAuthCode(const FString authCode, const huawei::AccountInfo account);
    void onLoggedOut();
    void onCancelledAuth();
    void onException(int action, const FString message);
};
