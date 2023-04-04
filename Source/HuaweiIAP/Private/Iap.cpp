#include "Iap.h"
#include "HuaweiIapModule.h"
#include "IapJniWrapper.h"

using namespace std;
using namespace json98;

namespace huawei
{

    void Iap::checkEnvironment()
    {
        IapJniWrapper::getInstance()->checkEnvironment();
    }

    void Iap::queryProducts(const TArray<FString> productIds, int type)
    {
        vector<string> ids;
        for (auto& productId : productIds)
        {
            ids.push_back(TCHAR_TO_UTF8(*productId));
        }
        IapJniWrapper::getInstance()->queryProducts(ids, type);
    }

    void Iap::queryPurchases(int type)
    {
        IapJniWrapper::getInstance()->queryPurchases(type);
    }

    void Iap::buyProduct(FString productId, int type)
    {
        IapJniWrapper::getInstance()->buyProduct(TCHAR_TO_UTF8(*productId), type);
    }

    void Iap::getPurchasedRecords(int type)
    {
        IapJniWrapper::getInstance()->getPurchasedRecords(type);
    }

    void Iap::setListener(IapListener *listener)
    {
        IapJniWrapper::getInstance()->setListener(listener);
    }

    void Iap::removeListener()
    {
        IapJniWrapper::getInstance()->removeListener();
    }

    IapListener *Iap::getListener()
    {
        return IapJniWrapper::getInstance()->getListener();
    }

    void Iap::manageSubscriptions()
    {
        IapJniWrapper::getInstance()->manageSubscriptions();
    }

    void Iap::showSubscription(FString productId)
    {
        IapJniWrapper::getInstance()->showSubscription(TCHAR_TO_UTF8(*productId));
    }

    /********************************************
     * Data classes
     *******************************************/
    ProductInfo::ProductInfo(const json98::Json &json)
    {
        currency = FString(UTF8_TO_TCHAR(json["currency"].string_value().c_str()));
        microsPrice = json["microsPrice"].long_value();
        offerUsedStatus = json["offerUsedStatus"].int_value();
        originalLocalPrice = FString(UTF8_TO_TCHAR(json["originalLocalPrice"].string_value().c_str()));
        originalMicroPrice = json["originalMicroPrice"].long_value();
        price = FString(UTF8_TO_TCHAR(json["price"].string_value().c_str()));
        priceType = json["priceType"].int_value();
        productDesc = FString(UTF8_TO_TCHAR(json["productDesc"].string_value().c_str()));
        productId = FString(UTF8_TO_TCHAR(json["productId"].string_value().c_str()));
        productName = FString(UTF8_TO_TCHAR(json["productName"].string_value().c_str()));
        status = json["status"].int_value();
        subFreeTrialPeriod = FString(UTF8_TO_TCHAR(json["subFreeTrialPeriod"].string_value().c_str()));
        subGroupId = FString(UTF8_TO_TCHAR(json["subGroupId"].string_value().c_str()));
        subGroupTitle = FString(UTF8_TO_TCHAR(json["subGroupTitle"].string_value().c_str()));
        subPeriod = FString(UTF8_TO_TCHAR(json["subPeriod"].string_value().c_str()));
        subProductLevel = json["subProductLevel"].int_value();
        subSpecialPeriod = FString(UTF8_TO_TCHAR(json["subSpecialPeriod"].string_value().c_str()));
        subSpecialPeriodCycles = json["subSpecialPeriodCycles"].int_value();
        subSpecialPrice = FString(UTF8_TO_TCHAR(json["subSpecialPrice"].string_value().c_str()));
        subSpecialPriceMicros = json["subSpecialPriceMicros"].long_value();
    }

    InAppPurchaseData::InAppPurchaseData(const json98::Json &json)
    {
        accountFlag = json["accountFlag"].int_value();
        appInfo = FString(UTF8_TO_TCHAR(json["appInfo"].string_value().c_str()));
        applicationId = FString(UTF8_TO_TCHAR(json["applicationId"].string_value().c_str()));
        cancelledSubKeepDays = json["cancelledSubKeepDays"].int_value();
        cancellationTime = json["cancellationTime"].long_value();
        cancelReason = json["cancelReason"].int_value();
        cancelTime = json["cancelTime"].long_value();
        cancelWay = json["cancelWay"].int_value();
        consumptionState = json["consumptionState"].int_value();
        country = FString(UTF8_TO_TCHAR(json["country"].string_value().c_str()));
        currency = FString(UTF8_TO_TCHAR(json["currency"].string_value().c_str()));
        daysLasted = json["daysLasted"].long_value();
        deferFlag = json["deferFlag"].int_value();
        developerChallenge = FString(UTF8_TO_TCHAR(json["developerChallenge"].string_value().c_str()));
        developerPayload = FString(UTF8_TO_TCHAR(json["developerPayload"].string_value().c_str()));
        expirationDate = json["expirationDate"].long_value();
        expirationIntent = json["expirationIntent"].int_value();
        graceExpirationTime = json["graceExpirationTime"].int_value();
        introductoryFlag = json["introductoryFlag"].int_value();
        kind = json["kind"].int_value();
        lastOrderId = FString(UTF8_TO_TCHAR(json["lastOrderId"].string_value().c_str()));
        notifyClosed = json["notifyClosed"].int_value();
        numOfDiscount = json["numOfDiscount"].long_value();
        numOfPeriods = json["numOfPeriods"].long_value();
        orderID = FString(UTF8_TO_TCHAR(json["orderID"].string_value().c_str()));
        oriPurchaseTime = json["oriPurchaseTime"].long_value();
        oriSubscriptionId = FString(UTF8_TO_TCHAR(json["oriSubscriptionId"].string_value().c_str()));
        packageName = FString(UTF8_TO_TCHAR(json["packageName"].string_value().c_str()));
        payOrderId = FString(UTF8_TO_TCHAR(json["payOrderId"].string_value().c_str()));
        payType = FString(UTF8_TO_TCHAR(json["payType"].string_value().c_str()));
        price = json["price"].long_value();
        priceConsentStatus = json["priceConsentStatus"].int_value();
        productGroup = FString(UTF8_TO_TCHAR(json["productGroup"].string_value().c_str()));
        productId = FString(UTF8_TO_TCHAR(json["productId"].string_value().c_str()));
        productName = FString(UTF8_TO_TCHAR(json["productName"].string_value().c_str()));
        purchaseState = json["purchaseState"].int_value();
        purchaseTime = json["purchaseTime"].long_value();
        purchaseToken = FString(UTF8_TO_TCHAR(json["purchaseToken"].string_value().c_str()));
        purchaseType = json["purchaseType"].int_value();
        quantity = json["quantity"].int_value();
        renewPrice = json["renewPrice"].long_value();
        renewStatus = json["renewStatus"].int_value();
        resumeTime = json["resumeTime"].long_value();
        retryFlag = json["retryFlag"].int_value();
        subscriptionId = FString(UTF8_TO_TCHAR(json["subscriptionId"].string_value().c_str()));
        trialFlag = json["trialFlag"].int_value();
        isAutoRenewing = json["isAutoRenewing"].bool_value();
        isSubValid = json["isSubValid"].bool_value();
    }
}