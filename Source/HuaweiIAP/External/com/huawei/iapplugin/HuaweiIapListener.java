package com.huawei.iapplugin;

import com.huawei.hms.iap.entity.ProductInfo;
import com.huawei.hms.iap.entity.InAppPurchaseData;
import java.util.List;

public interface HuaweiIapListener {
    void onCheckEnvironmentSuccess();
    void onException(int action, String message);
    void onObtainProductList(List<ProductInfo> products, int type);
    void onPurchaseSuccess(String productId, int type);
    void onObtainPurchases(List<InAppPurchaseData> purchasedProducts, List<InAppPurchaseData> nonPurchasedProducts, int type);
    void onObtainPurchasedRecords(List<InAppPurchaseData> purchasedProducts, int type);
}
