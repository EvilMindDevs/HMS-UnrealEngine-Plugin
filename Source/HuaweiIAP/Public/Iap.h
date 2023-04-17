#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include <string>
#include "json98.h"

#define IN_APP_CONSUMABLE 0
#define IN_APP_NONCONSUMABLE 1
#define IN_APP_SUBSCRIPTION 2
#define CHECK_ENVIRONMENT 0
#define QUERY_PRODUCTS 1
#define BUY_PRODUCT 2
#define QUERY_PURCHASES 3
#define GET_PURCHASES_RECORDS 4

namespace huawei
{
    struct ProductInfo
    {
        ProductInfo(const json98::Json &json);

        FString currency;
        long microsPrice;
        int offerUsedStatus;
        FString originalLocalPrice;
        long originalMicroPrice;
        FString price;
        int priceType;
        FString productDesc;
        FString productId;
        FString productName;
        int status;
        FString subFreeTrialPeriod;
        FString subGroupId;
        FString subGroupTitle;
        FString subPeriod;
        int subProductLevel;
        FString subSpecialPeriod;
        int subSpecialPeriodCycles;
        FString subSpecialPrice;
        long subSpecialPriceMicros;
    };

    struct InAppPurchaseData
    {
        InAppPurchaseData(const json98::Json &json);

        int accountFlag;
        FString appInfo;
        FString applicationId;
        int cancelledSubKeepDays;
        long cancellationTime;
        int cancelReason;
        long cancelTime;
        int cancelWay;
        int consumptionState;
        FString country;
        FString currency;
        long daysLasted;
        int deferFlag;
        FString developerChallenge;
        FString developerPayload;
        long expirationDate;
        int expirationIntent;
        long graceExpirationTime;
        int introductoryFlag;
        int kind;
        FString lastOrderId;
        int notifyClosed;
        long numOfDiscount;
        long numOfPeriods;
        FString orderID;
        long oriPurchaseTime;
        FString oriSubscriptionId;
        FString packageName;
        FString payOrderId;
        FString payType;
        long price;
        int priceConsentStatus;
        FString productGroup;
        FString productId;
        FString productName;
        int purchaseState;
        long purchaseTime;
        FString purchaseToken;
        int purchaseType;
        int quantity;
        long renewPrice;
        int renewStatus;
        long resumeTime;
        int retryFlag;
        FString subscriptionId;
        int trialFlag;
        bool isAutoRenewing;
        bool isSubValid;
    };

    class IapListener
    {
    public:    
        virtual void onCheckEnvironmentSuccess() = 0;
        virtual void onException(int action, const FString message) = 0;
        virtual void onObtainProductList(const TArray<ProductInfo> products, int type) = 0;
        virtual void onPurchaseSuccess(const FString productId, int type) = 0;
        virtual void onObtainPurchases(const TArray<InAppPurchaseData> purchasedProductIds, const TArray<InAppPurchaseData> nonPurchasedProductIds, int type) = 0;
        virtual void onObtainPurchasedRecords(const TArray<InAppPurchaseData> purchasedProductIds, int type) = 0;
    };

    class HUAWEIIAP_API Iap
    {
    public:
        static void checkEnvironment();
        static void queryProducts(const TArray<FString> productIds, int type);
        static void queryPurchases(int type);
        static void buyProduct(FString productId, int type);
        static void getPurchasedRecords(int type);

        static void setListener(IapListener *listener);
        static void removeListener();
        static IapListener *getListener();
        static void manageSubscriptions();
        static void showSubscription(FString productId);
    };
}