#pragma once

#include "Components/ActorComponent.h"
#include "push.h"
#include "PushComponent.generated.h"

#define INIT_FAILED 99
#define UN_SUBSCRIBE_FAILED 100
#define SUBSCRIBE_FAILED 101
#define DELETE_TOKEN_FAILED 102
#define GET_TOKEN_FAILED 103
#define ON_MESSAGE_RECEIVED 104

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetTokenSuccess, FString, token);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeleteTokenSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnSubscribeSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUnSubscribeSuccess);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewToken, FString, token);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageReceived, FString, messageJson);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetTokenException, FString, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeleteTokenException, FString, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSubscribeException, FString, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUnSubscribeException, FString, message);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMessageReceivedException, FString, message);

UCLASS(ClassGroup = (HuaweiPushPlugin), meta = (BlueprintSpawnableComponent))
class UPushComponent : public UActorComponent,
                       public huawei::PushListener
{
    GENERATED_BODY()

public:
    UPushComponent();

    UPROPERTY(BlueprintAssignable, Category = "HuaweiPush Category")
    FOnGetTokenSuccess onGetTokenSuccessEvent;

    UPROPERTY(BlueprintAssignable, Category = "HuaweiPush Category")
    FOnGetTokenException onGetTokenExceptionEvent;

    UPROPERTY(BlueprintAssignable, Category = "HuaweiPush Category")
    FOnDeleteTokenSuccess onDeleteTokenSuccessEvent;

    UPROPERTY(BlueprintAssignable, Category = "HuaweiPush Category")
    FOnDeleteTokenException onDeleteTokenExceptionEvent;

    UPROPERTY(BlueprintAssignable, Category = "HuaweiPush Category")
    FOnSubscribeSuccess onSubscribeSuccessEvent;

    UPROPERTY(BlueprintAssignable, Category = "HuaweiPush Category")
    FOnSubscribeException onSubscribeExceptionEvent;

    UPROPERTY(BlueprintAssignable, Category = "HuaweiPush Category")
    FOnUnSubscribeSuccess onUnSubscribeSuccessEvent;

    UPROPERTY(BlueprintAssignable, Category = "HuaweiPush Category")
    FOnUnSubscribeException onUnSubscribeExceptionEvent;

    UPROPERTY(BlueprintAssignable, Category = "HuaweiPush Category")
    FOnMessageReceived onMessageReceivedEvent;

    UPROPERTY(BlueprintAssignable, Category = "HuaweiPush Category")
    FOnMessageReceivedException onMessageReceivedExceptionEvent;

    UPROPERTY(BlueprintAssignable, Category = "HuaweiPush Category")
    FOnNewToken onNewTokenEvent;

    UFUNCTION(BlueprintCallable, Category = "HuaweiPush Category")
    void init();

    UFUNCTION(BlueprintCallable, Category = "HuaweiPush Category")
    void getToken();

    UFUNCTION(BlueprintCallable, Category = "HuaweiPush Category")
    void deleteToken();

    UFUNCTION(BlueprintCallable, Category = "HuaweiPush Category")
    void subscribe(FString topic);

    UFUNCTION(BlueprintCallable, Category = "HuaweiPush Category")
    void unSubscribe(FString topic);

    UFUNCTION(BlueprintCallable, Category = "HuaweiPush Category")
    void setAutoInitEnabled(bool isEnable);

    void InitializeComponent() override;

    // callbacks
    void onGetTokenSuccess(const FString token) override;
    void onDeleteTokenSuccess() override;
    void onNewToken(const FString token) override;
    void onMessageReceived(const FString messageJson) override;
    void onSubscribeSuccess() override;
    void onUnSubscribeSuccess() override;
    void onException(int errorcode, int action, const FString message) override;
};
