package com.huawei.iapplugin;

import com.huawei.iapplugin.utils.IapApiCallback;
import com.huawei.iapplugin.utils.Constants;
import com.huawei.iapplugin.utils.ExceptionHandle;
import com.huawei.iapplugin.utils.IapRequestHelper;
import com.huawei.iapplugin.utils.CipherUtil;

import com.huawei.hms.iap.Iap;
import com.huawei.hms.iap.IapClient;
import com.huawei.hms.iap.entity.IsEnvReadyResult;
import com.huawei.hms.iap.entity.OrderStatusCode;
import com.huawei.hms.iap.util.IapClientHelper;
import com.huawei.hms.iap.entity.InAppPurchaseData;
import com.huawei.hms.iap.entity.OwnedPurchasesResult;
import com.huawei.hms.iap.entity.ProductInfo;
import com.huawei.hms.iap.entity.ProductInfoResult;
import com.huawei.hms.iap.entity.PurchaseIntentResult;
import com.huawei.hms.iap.entity.PurchaseResultInfo;
import com.huawei.hms.support.api.client.Status;

import android.app.NativeActivity;
import android.text.TextUtils;
import android.util.Base64;
import android.util.Log;
import android.util.Pair;
import android.content.Intent;

import org.json.JSONException;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class HuaweiIapPlugin {
    private static boolean isInit = false;
    private static NativeActivity mActivity = null;
    private static HuaweiIapListener mListener = null;
    private static String mPublicKey = null;
    private static IapClient client = null;
    private static final String TAG = "HuaweiIapPlugin";
    private static int currentType = -1;
    private static String currentProductId;

    public static int CHECK_ENVIRONMENT = 0;
    public static int QUERY_PRODUCTS = 1;
    public static int BUY_PRODUCT = 2;
    public static int QUERY_PURCHASES = 3;
    public static int GET_PURCHASES_RECORDS = 4;

    public static void initialize(NativeActivity activity, HuaweiIapListener listener) {
        if (!isInit) {
            mActivity = activity;
            client = Iap.getIapClient(mActivity);
            mListener = listener;
            isInit = true;
        }
    }

    public static void setPublicKey(String publicKey) {
        mPublicKey = publicKey;
    }

    public static void registerOnActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case Constants.REQ_CODE_LOGIN:
                int returnCode = IapClientHelper.parseRespCodeFromIntent(data);
                switch (returnCode) {
                    case OrderStatusCode.ORDER_STATE_SUCCESS:
                        mListener.onCheckEnvironmentSuccess();
                        break;
                    case OrderStatusCode.ORDER_ACCOUNT_AREA_NOT_SUPPORTED:
                        mListener.onException(CHECK_ENVIRONMENT, "This is unavailable in your country/region");  
                        break;
                    default:
                        mListener.onException(CHECK_ENVIRONMENT, "User cancel login.");
                        break;      
                }
                break;
            case Constants.REQ_CODE_BUY:
                PurchaseResultInfo purchaseResultInfo = client.parsePurchaseResultInfoFromIntent(data);
                switch(purchaseResultInfo.getReturnCode()) {
                    case OrderStatusCode.ORDER_STATE_CANCEL:
                        mListener.onException(BUY_PRODUCT, "Order with " + currentProductId + " has been canceled!");
                        break;
                    case OrderStatusCode.ORDER_STATE_FAILED:
                    case OrderStatusCode.ORDER_STATE_DEFAULT_CODE:
                        // Default value returned by parsePurchaseResultInfoFromIntent when no return code is received from the IAP.
                    case OrderStatusCode.ORDER_PRODUCT_OWNED:
                        if (currentType != -1) {
                            queryPurchases(currentType);
                        }
                        break;
                    case OrderStatusCode.ORDER_STATE_SUCCESS:
                        Pair<Boolean, InAppPurchaseData> verifyResult = verifyPurchaseStatus(currentType, purchaseResultInfo.getInAppPurchaseData(), purchaseResultInfo.getInAppDataSignature());
                        boolean isSuccess = verifyResult.first;
                        String productId = verifyResult.second.getProductId();
                        if (isSuccess&& currentType != -1) {
                            mListener.onPurchaseSuccess(productId, currentType);
                        } else {
                            mListener.onException(BUY_PRODUCT, "Failed to verify order with " + productId + " !");     
                        }
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }   
    }

    public static void checkEnvironment() {
        IapRequestHelper.isEnvReady(client, new IapApiCallback<IsEnvReadyResult>() {
            @Override
            public void onSuccess(IsEnvReadyResult result) {
                mListener.onCheckEnvironmentSuccess();
            }

            @Override
            public void onFail(Exception e) {
                Log.e(TAG, "isEnvReady fail, " + e.getMessage());
                ExceptionHandle.handle(mActivity, CHECK_ENVIRONMENT, e, mListener);
            }
        });
    }

    public static void queryProducts(String[] productIds, final int type) {
        IapRequestHelper.obtainProductInfo(client, new ArrayList<>(Arrays.asList(productIds)), type, new IapApiCallback<ProductInfoResult>() {
            @Override
            public void onSuccess(ProductInfoResult result) {
                Log.i(TAG, "obtainProductInfo, success");
                if (result == null) {
                    return;
                }
                List<ProductInfo> productInfos = result.getProductInfoList();
                if (productInfos != null) {
                    mListener.onObtainProductList(productInfos, type);
                }
            }

            @Override
            public void onFail(Exception e) {
                Log.e(TAG, "obtainProductInfo: " + e.getMessage());
                ExceptionHandle.handle(mActivity, QUERY_PRODUCTS, e, mListener);
            }
        });   
    }

    public static void queryPurchases(int type) {
        queryPurchases(type, null);
    }

    public static void buyProduct(final String productId, final int type) {
        currentProductId = productId;
        currentType = type;
        IapRequestHelper.createPurchaseIntent(client, productId, type, new IapApiCallback<PurchaseIntentResult>() {
            @Override
            public void onSuccess(PurchaseIntentResult result) {
                if (result == null) {
                    Log.e(TAG, "result is null");
                    return;
                }
                Status status = result.getStatus();
                if (status == null) {
                    Log.e(TAG, "status is null");
                    return;
                }
                // You should pull up the page to complete the payment process.
                IapRequestHelper.startResolutionForResult(mActivity, status, Constants.REQ_CODE_BUY);
            }

            @Override
            public void onFail(Exception e) {
                int errorCode = ExceptionHandle.handle(mActivity, BUY_PRODUCT, e, mListener);
                if (errorCode != ExceptionHandle.SOLVED) {
                    Log.e(TAG, "createPurchaseIntent, returnCode: " + errorCode);
                    switch (errorCode) {
                        case OrderStatusCode.ORDER_PRODUCT_OWNED:
                            if (type != IapClient.PriceType.IN_APP_SUBSCRIPTION) {
                                queryPurchases(type);
                            } else {
                                IapRequestHelper.showSubscription(mActivity, productId, BUY_PRODUCT, mListener);
                            }
                            break;
                        default:
                            break;
                    }
                }
            }
        });
    }

    public static void getPurchasedRecords(int type) {
        getPurchasedRecords(type, null);
    }

    private static void queryPurchases(final int type, String continuationToken) {
        IapRequestHelper.obtainOwnedPurchases(client, type, continuationToken, new IapApiCallback<OwnedPurchasesResult>() {
            @Override
            public void onSuccess(OwnedPurchasesResult result) {
                if (result == null) {
                    mListener.onException(QUERY_PURCHASES, "result is null");
                    return;
                }
                String token = result.getContinuationToken();
                if (!TextUtils.isEmpty(token)) {
                    queryPurchases(type, token);
                    return;
                }
                Log.i(TAG, "obtainOwnedPurchases, success");

                List<String> inAppPurchaseDataList = result.getInAppPurchaseDataList();
                if (inAppPurchaseDataList != null) {
                    List<String> inAppSignature= result.getInAppSignature();
                    List<InAppPurchaseData> purchasedProductDatas = new ArrayList<>();
                    List<InAppPurchaseData> nonPurchasedProductDatas = new ArrayList<>();
                    for (int i = 0; i < inAppPurchaseDataList.size(); i++) {
                        final String inAppPurchaseData = inAppPurchaseDataList.get(i);
                        final String inAppPurchaseDataSignature = inAppSignature.get(i);
                        Pair<Boolean, InAppPurchaseData> verifyResult = verifyPurchaseStatus(type, inAppPurchaseData, inAppPurchaseDataSignature);
                        boolean isPurchased = verifyResult.first;
                        InAppPurchaseData productData = verifyResult.second;
                        if (productData != null) {
                            if (isPurchased) {
                                purchasedProductDatas.add(productData);
                            } else {
                                nonPurchasedProductDatas.add(productData);
                            }
                        }
                    }
                    mListener.onObtainPurchases(purchasedProductDatas, nonPurchasedProductDatas, type);
                }
            }

            @Override
            public void onFail(Exception e) {
                Log.e(TAG, "obtainOwnedPurchases, type=" + IapClient.PriceType.IN_APP_CONSUMABLE + ", " + e.getMessage());
                ExceptionHandle.handle(mActivity, QUERY_PURCHASES, e, mListener);
            }
        });
    }

    private static Pair<Boolean, InAppPurchaseData> verifyPurchaseStatus(int type, final String inAppPurchaseDataStr, final String inAppPurchaseDataSignature) {
        // Check whether the signature of the purchase data is valid.
        if (CipherUtil.doCheck(inAppPurchaseDataStr, inAppPurchaseDataSignature, mPublicKey)) {
            try {
                InAppPurchaseData inAppPurchaseDataBean = new InAppPurchaseData(inAppPurchaseDataStr);
                String purchaseToken = inAppPurchaseDataBean.getPurchaseToken();
                String productId = inAppPurchaseDataBean.getProductId();
                boolean isValid = type == IapClient.PriceType.IN_APP_SUBSCRIPTION ? inAppPurchaseDataBean.isSubValid() : inAppPurchaseDataBean.getPurchaseState() == InAppPurchaseData.PurchaseState.PURCHASED;
                if (type == IapClient.PriceType.IN_APP_CONSUMABLE && isValid) {
                    IapRequestHelper.consumeOwnedPurchase(client, purchaseToken);
                }
                return Pair.create(isValid, inAppPurchaseDataBean);
            } catch (JSONException e) {
                Log.e(TAG, "delivery:" + e.getMessage());
                return Pair.create(false, null);
            }
        } else {
            return Pair.create(false, null);
        }
    }

    private static void getPurchasedRecords(final int type, String continuationToken) {
        if (type == IapClient.PriceType.IN_APP_NONCONSUMABLE) {
            mListener.onException(GET_PURCHASES_RECORDS, "For non-consumables, please use queryPurchases API");
        }
        IapRequestHelper.obtainOwnedPurchaseRecord(client, type, continuationToken, new IapApiCallback<OwnedPurchasesResult>() {
            @Override
            public void onSuccess(OwnedPurchasesResult result) {
                List<String> inAppPurchaseDataList = result.getInAppPurchaseDataList();
                List<String> signatureList = result.getInAppSignature();
                List<InAppPurchaseData> purchasedProductDatas = new ArrayList<>();
                if (inAppPurchaseDataList == null) {
                    return;
                }

                // If the continuationToken is not empty, you need to continue the query to get all purchase data.
                String token = result.getContinuationToken();
                if (!TextUtils.isEmpty(token)) {
                    getPurchasedRecords(type, token);
                    return;
                }

                Log.i(TAG, "obtainOwnedPurchaseRecord, success");
                try {
                    for (int i = 0; i < signatureList.size(); i++) {
                        String inAppPurchaseDataStr = inAppPurchaseDataList.get(i);
                        // Check whether the signature of the purchase data is valid.
                        boolean success = CipherUtil.doCheck(inAppPurchaseDataStr, signatureList.get(i), mPublicKey);
                        if (success) {
                            purchasedProductDatas.add(new InAppPurchaseData(inAppPurchaseDataStr));
                        }
                    }
                } catch (JSONException ex) {
                    mListener.onException(GET_PURCHASES_RECORDS, "Error when parsing data");
                }
                mListener.onObtainPurchasedRecords(purchasedProductDatas, type); 
            }

            @Override
            public void onFail(Exception e) {
                Log.e(TAG, "obtainOwnedPurchaseRecord, " + e.getMessage());
                ExceptionHandle.handle(mActivity, GET_PURCHASES_RECORDS, e, mListener);          
            }
        });
    }
  
    public static void showSubscription(String productId)
    {
       IapRequestHelper.showSubscription(mActivity,productId);
    }  

    public static void manageSubscriptions()
    {
       IapRequestHelper.manageSubscriptions(mActivity);
    }

}

