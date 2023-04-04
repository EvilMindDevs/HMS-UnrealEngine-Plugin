#include "IapBlueprint.h"

using namespace huawei;

FProductInfo convertFromRawData(ProductInfo info)
{
    FProductInfo fInfo;
    fInfo.currency = info.currency;
    fInfo.microsPrice = info.microsPrice;
    fInfo.offerUsedStatus = info.offerUsedStatus;
    fInfo.originalLocalPrice = info.originalLocalPrice;
    fInfo.originalMicroPrice = info.originalMicroPrice;
    fInfo.price = info.price;
    fInfo.priceType = info.priceType;
    fInfo.productDesc = info.productDesc;
    fInfo.productId = info.productId;
    fInfo.productName = info.productName;
    fInfo.status = info.status;
    fInfo.subFreeTrialPeriod = info.subFreeTrialPeriod;
    fInfo.subGroupId = info.subGroupId;
    fInfo.subGroupTitle = info.subGroupTitle;
    fInfo.subPeriod = info.subPeriod;
    fInfo.subProductLevel = info.subProductLevel;
    fInfo.subSpecialPeriod = info.subSpecialPeriod;
    fInfo.subSpecialPeriodCycles = info.subSpecialPeriodCycles;
    fInfo.subSpecialPrice = info.subSpecialPrice;
    fInfo.subSpecialPriceMicros = info.subSpecialPriceMicros;
    return fInfo;
}

FInAppPurchaseData convertFromRawData(InAppPurchaseData data)
{
    FInAppPurchaseData fData;
    fData.accountFlag = data.accountFlag;
    fData.appInfo = data.appInfo;
    fData.applicationId = data.applicationId;
    fData.cancelledSubKeepDays = data.cancelledSubKeepDays;
    fData.cancellationTime = data.cancellationTime;
    fData.cancelReason = data.cancelReason;
    fData.cancelTime = data.cancelTime;
    fData.cancelWay = data.cancelWay;
    fData.consumptionState = data.consumptionState;
    fData.country = data.country;
    fData.currency = data.currency;
    fData.daysLasted = data.daysLasted;
    fData.deferFlag = data.deferFlag;
    fData.developerChallenge = data.developerChallenge;
    fData.developerPayload = data.developerPayload;
    fData.expirationDate = data.expirationDate;
    fData.expirationIntent = data.expirationIntent;
    fData.graceExpirationTime = data.graceExpirationTime;
    fData.introductoryFlag = data.introductoryFlag;
    fData.kind = data.kind;
    fData.lastOrderId = data.lastOrderId;
    fData.notifyClosed = data.notifyClosed;
    fData.numOfDiscount = data.numOfDiscount;
    fData.numOfPeriods = data.numOfPeriods;
    fData.orderID = data.orderID;
    fData.oriPurchaseTime = data.oriPurchaseTime;
    fData.oriSubscriptionId = data.oriSubscriptionId;
    fData.packageName = data.packageName;
    fData.payOrderId = data.payOrderId;
    fData.payType = data.payType;
    fData.price = data.price;
    fData.priceConsentStatus = data.priceConsentStatus;
    fData.productGroup = data.productGroup;
    fData.productId = data.productId;
    fData.productName = data.productName;
    fData.purchaseState = data.purchaseState;
    fData.purchaseTime = data.purchaseTime;
    fData.purchaseToken = data.purchaseToken;
    fData.purchaseType = data.purchaseType;
    fData.quantity = data.quantity;
    fData.renewPrice = data.renewPrice;
    fData.renewStatus = data.renewStatus;
    fData.resumeTime = data.resumeTime;
    fData.retryFlag = data.retryFlag;
    fData.subscriptionId = data.subscriptionId;
    fData.trialFlag = data.trialFlag;
    fData.isAutoRenewing = data.isAutoRenewing;
    fData.isSubValid = data.isSubValid;
    return fData;
}

template <typename T, typename V>
TArray<T> convertFromRawData(TArray<V> datas)
{
    TArray<T> convertedDatas;
    for (auto &data : datas)
    {
        convertedDatas.Add(convertFromRawData(data));
    }
    return convertedDatas;
}

FOnCheckEnvironmentSuccess UHuaweiIapBlueprint::_onCheckEnvironmentSuccess;
FOnCheckEnvironmentException UHuaweiIapBlueprint::_onCheckEnvironmentException;
void UHuaweiIapBlueprint::checkEnvironment(const FOnCheckEnvironmentSuccess &onSuccess, const FOnCheckEnvironmentException &onException)
{
    Iap::checkEnvironment();
    UHuaweiIapBlueprint::_onCheckEnvironmentSuccess = onSuccess;
    UHuaweiIapBlueprint::_onCheckEnvironmentException = onException;
}

FOnObtainProductList UHuaweiIapBlueprint::_onObtainProductList;
FOnObtainProductListException UHuaweiIapBlueprint::_onObtainProductListException;
void UHuaweiIapBlueprint::queryProducts(TArray<FString> productIds, int type, const FOnObtainProductList &onSuccess, const FOnObtainProductListException &onException)
{
    Iap::queryProducts(productIds, type);
    UHuaweiIapBlueprint::_onObtainProductList = onSuccess;
    UHuaweiIapBlueprint::_onObtainProductListException = onException;
}

FOnObtainPurchases UHuaweiIapBlueprint::_onObtainPurchases;
FOnObtainPurchasesException UHuaweiIapBlueprint::_onObtainPurchasesException;
void UHuaweiIapBlueprint::queryPurchases(int type, const FOnObtainPurchases &onSuccess, const FOnObtainPurchasesException &onException)
{
    Iap::queryPurchases(type);
    UHuaweiIapBlueprint::_onObtainPurchases = onSuccess;
    UHuaweiIapBlueprint::_onObtainPurchasesException = onException;
}

FOnPurchaseSuccess UHuaweiIapBlueprint::_onPurchaseSuccess;
FOnPurchaseException UHuaweiIapBlueprint::_onPurchaseException;
void UHuaweiIapBlueprint::buyProduct(FString productId, int type, const FOnPurchaseSuccess &onSuccess, const FOnPurchaseException &onException)
{
    Iap::buyProduct(productId, type);
    UHuaweiIapBlueprint::_onPurchaseSuccess = onSuccess;
    UHuaweiIapBlueprint::_onPurchaseException = onException;
}

FOnObtainPurchasedRecords UHuaweiIapBlueprint::_onObtainPurchasedRecords;
FOnObtainPurchasedRecordsException UHuaweiIapBlueprint::_onObtainPurchasedRecordsException;
void UHuaweiIapBlueprint::getPurchasedRecords(int type, const FOnObtainPurchasedRecords &onSuccess, const FOnObtainPurchasedRecordsException &onException)
{
    Iap::getPurchasedRecords(type);
    UHuaweiIapBlueprint::_onObtainPurchasedRecords = onSuccess;
    UHuaweiIapBlueprint::_onObtainPurchasedRecordsException = onException;
}

void UHuaweiIapBlueprint::onCheckEnvironmentSuccess()
{
    UHuaweiIapBlueprint::_onCheckEnvironmentSuccess.ExecuteIfBound();
}

void UHuaweiIapBlueprint::onException(int action, const FString message)
{
    switch (action)
    {
    case CHECK_ENVIRONMENT:
        UHuaweiIapBlueprint::_onCheckEnvironmentException.ExecuteIfBound(message);
        break;
    case QUERY_PRODUCTS:
        UHuaweiIapBlueprint::_onObtainProductListException.ExecuteIfBound(message);
        break;
    case BUY_PRODUCT:
        UHuaweiIapBlueprint::_onPurchaseException.ExecuteIfBound(message);
        break;
    case QUERY_PURCHASES:
        UHuaweiIapBlueprint::_onObtainPurchasesException.ExecuteIfBound(message);
        break;
    case GET_PURCHASES_RECORDS:
        UHuaweiIapBlueprint::_onObtainPurchasedRecordsException.ExecuteIfBound(message);
    default:
        break;
    }
}

void UHuaweiIapBlueprint::onObtainProductList(const TArray<ProductInfo> products, int type)
{
    UHuaweiIapBlueprint::_onObtainProductList.ExecuteIfBound
    (
        convertFromRawData<FProductInfo, ProductInfo>(products), 
        type
    );
}

void UHuaweiIapBlueprint::onPurchaseSuccess(const FString productId, int type)
{
    UHuaweiIapBlueprint::_onPurchaseSuccess.ExecuteIfBound(productId, type);
}

void UHuaweiIapBlueprint::onObtainPurchases(const TArray<InAppPurchaseData> purchasedProductDatas, const TArray<InAppPurchaseData> nonPurchasedProductDatas, int type)
{
    UHuaweiIapBlueprint::_onObtainPurchases.ExecuteIfBound
    (
        convertFromRawData<FInAppPurchaseData, InAppPurchaseData>(purchasedProductDatas),
        convertFromRawData<FInAppPurchaseData, InAppPurchaseData>(nonPurchasedProductDatas),
        type
    );
}

void UHuaweiIapBlueprint::onObtainPurchasedRecords(const TArray<InAppPurchaseData> purchasedProductDatas, int type)
{
    UHuaweiIapBlueprint::_onObtainPurchasedRecords.ExecuteIfBound
    (
        convertFromRawData<FInAppPurchaseData, InAppPurchaseData>(purchasedProductDatas),
        type
    );
}

void UHuaweiIapBlueprint::manageSubscriptions()
{
    Iap::manageSubscriptions();
}

void UHuaweiIapBlueprint::showSubscription(const FString productId)
{
    Iap::showSubscription(productId);
}



