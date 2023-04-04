#pragma once
#include "Iap.h"
#include <string>

DECLARE_LOG_CATEGORY_EXTERN(HuaweiIap_Native, Log, All);
using namespace std;

namespace huawei
{

    class IapJniWrapper
    {

    public:
        static IapJniWrapper *getInstance();

        IapJniWrapper();
        ~IapJniWrapper();

        void checkEnvironment();
        void queryProducts(const vector<string> productIds, int type);
        void queryPurchases(int type);
        void buyProduct(const string productId, int type);
        void getPurchasedRecords(int type);
        void manageSubscriptions();
        void showSubscription(const string productId);

        // Listener
        void setListener(IapListener *listener);
        void removeListener();
        IapListener *getListener();

        // Callbacks
        void onCheckEnvironmentSuccess();
        void onException(int action, const FString message);
        void onObtainProductList(const string products, int type);
        void onPurchaseSuccess(const FString productId, int type);
        void onObtainPurchases(const string purchasedProductIds, const string nonPurchasedProductIds, int type);
        void onObtainPurchasedRecords(const string purchasedProductIds, int type);

    protected:
        IapListener *_listener;
    };
}
