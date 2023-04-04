// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine.h"
#include "Iap.h"
#include "IapBlueprint.generated.h"

#define CHECK_ENVIRONMENT 0
#define QUERY_PRODUCTS 1
#define BUY_PRODUCT 2
#define QUERY_PURCHASES 3
#define GET_PURCHASES_RECORDS 4

USTRUCT(Blueprintable, BlueprintType)
struct HUAWEIIAP_API FProductInfo
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString currency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 microsPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 offerUsedStatus;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString originalLocalPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 originalMicroPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString price;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 priceType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString productDesc;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString productId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString productName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 status;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString subFreeTrialPeriod;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString subGroupId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString subGroupTitle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString subPeriod;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 subProductLevel;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString subSpecialPeriod;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 subSpecialPeriodCycles;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString subSpecialPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 subSpecialPriceMicros;
};

USTRUCT(Blueprintable, BlueprintType)
struct HUAWEIIAP_API FInAppPurchaseData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 accountFlag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString appInfo;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString applicationId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 cancelledSubKeepDays;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 cancellationTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 cancelReason;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 cancelTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 cancelWay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 consumptionState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString country;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString currency;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 daysLasted;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 deferFlag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString developerChallenge;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString developerPayload;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 expirationDate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 expirationIntent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 graceExpirationTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 introductoryFlag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 kind;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString lastOrderId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 notifyClosed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 numOfDiscount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 numOfPeriods;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString orderID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 oriPurchaseTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString oriSubscriptionId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString packageName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString payOrderId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString payType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 price;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 priceConsentStatus;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString productGroup;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString productId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString productName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 purchaseState;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 purchaseTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString purchaseToken;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 purchaseType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 quantity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 renewPrice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 renewStatus;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int64 resumeTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 retryFlag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    FString subscriptionId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    int32 trialFlag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    bool isAutoRenewing;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HuaweiIAP")
    bool isSubValid;
};

DECLARE_DYNAMIC_DELEGATE(FOnCheckEnvironmentSuccess);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnCheckEnvironmentException, FString, message);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnObtainProductListException, FString, message);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnPurchaseException, FString, message);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnObtainPurchasesException, FString, message);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnObtainPurchasedRecordsException, FString, message);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObtainProductList, const TArray<FProductInfo> &, products, int, type);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPurchaseSuccess, FString, productId, int, type);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnObtainPurchases, const TArray<FInAppPurchaseData> &, purchasedProductDatas, const TArray<FInAppPurchaseData> &, nonPurchasedProductDatas, int, type);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnObtainPurchasedRecords, const TArray<FInAppPurchaseData> &, purchasedProductDatas, int, type);

UCLASS()
class HUAWEIIAP_API UHuaweiIapBlueprint : public UBlueprintFunctionLibrary,
                                          public huawei::IapListener
{
    GENERATED_BODY()

public:
    UHuaweiIapBlueprint(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
    {
        huawei::Iap::setListener(this);
    };

    static FOnCheckEnvironmentSuccess _onCheckEnvironmentSuccess;
    static FOnObtainProductList _onObtainProductList;
    static FOnPurchaseSuccess _onPurchaseSuccess;
    static FOnObtainPurchases _onObtainPurchases;
    static FOnObtainPurchasedRecords _onObtainPurchasedRecords;
    static FOnCheckEnvironmentException _onCheckEnvironmentException;
    static FOnObtainProductListException _onObtainProductListException;
    static FOnPurchaseException _onPurchaseException;
    static FOnObtainPurchasesException _onObtainPurchasesException;
    static FOnObtainPurchasedRecordsException _onObtainPurchasedRecordsException;

    UFUNCTION(BlueprintCallable, Category = "HuaweiIAP Category")
    static void checkEnvironment(const FOnCheckEnvironmentSuccess &onSuccess, const FOnCheckEnvironmentException &onException);

    UFUNCTION(BlueprintCallable, Category = "HuaweiIAP Category")
    static void queryProducts(TArray<FString> productIds, int type, const FOnObtainProductList &onSuccess, const FOnObtainProductListException &onException);

    UFUNCTION(BlueprintCallable, Category = "HuaweiIAP Category")
    static void queryPurchases(int type, const FOnObtainPurchases &onSuccess, const FOnObtainPurchasesException &onException);

    UFUNCTION(BlueprintCallable, Category = "HuaweiIAP Category")
    static void buyProduct(FString productId, int type, const FOnPurchaseSuccess &onSuccess, const FOnPurchaseException &onException);

    UFUNCTION(BlueprintCallable, Category = "HuaweiIAP Category")
    static void getPurchasedRecords(int type, const FOnObtainPurchasedRecords &onSucceess, const FOnObtainPurchasedRecordsException &onException);

    UFUNCTION(BlueprintCallable, Category = "HuaweiIAP Category")
    static void showSubscription(FString productId);

    UFUNCTION(BlueprintCallable, Category = "HuaweiIAP Category")
    static void manageSubscriptions();

    void onCheckEnvironmentSuccess();
    void onException(int action, const FString message);
    void onObtainProductList(const TArray<huawei::ProductInfo> products, int type);
    void onPurchaseSuccess(const FString productId, int type);
    void onObtainPurchases(const TArray<huawei::InAppPurchaseData> purchasedProductDatas, const TArray<huawei::InAppPurchaseData> nonPurchasedProductDatas, int type);
    void onObtainPurchasedRecords(const TArray<huawei::InAppPurchaseData> purchasedProductDatas, int type);
};
