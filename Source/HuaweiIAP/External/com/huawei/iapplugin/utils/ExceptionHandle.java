/**
 * Copyright 2020. Huawei Technologies Co., Ltd. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

package com.huawei.iapplugin.utils;

import android.app.Activity;
import android.util.Log;
import com.huawei.hms.iap.IapApiException;
import com.huawei.hms.iap.entity.OrderStatusCode;
import com.huawei.iapplugin.HuaweiIapListener;

import static android.content.ContentValues.TAG;

/**
 *  Handles the exception returned from the iap api.
 *
 * @since 2019/12/9
 */
public class ExceptionHandle {
    /**
     * The exception is solved.
     */
    public static final int SOLVED = 0;

    /**
     * Handles the exception returned from the IAP API.
     *
     * @param activity The Activity to call the IAP API.
     * @param e The exception returned from the IAP API.
     * @return int
     */
    public static int handle(Activity activity, int action, Exception e, HuaweiIapListener listener) {

        if (e instanceof IapApiException) {
            IapApiException iapApiException = (IapApiException) e;
            Log.i(TAG, "returnCode: " + iapApiException.getStatusCode());
            switch (iapApiException.getStatusCode()) {
                case OrderStatusCode.ORDER_STATE_CANCEL:
                    listener.onException(action, "Order has been canceled!");
                    return SOLVED;
                case OrderStatusCode.ORDER_STATE_PARAM_ERROR:
                    listener.onException(action, "Order state param error!");
                    return SOLVED;
                case OrderStatusCode.ORDER_STATE_NET_ERROR:
                    listener.onException(action, "Order state net error!");
                    return SOLVED;
                case OrderStatusCode.ORDER_VR_UNINSTALL_ERROR:
                    listener.onException(action, "Order vr uninstall error!");
                    return SOLVED;
                case OrderStatusCode.ORDER_HWID_NOT_LOGIN:
                    IapRequestHelper.startResolutionForResult(activity, iapApiException.getStatus(), Constants.REQ_CODE_LOGIN);
                    return SOLVED;
                case OrderStatusCode.ORDER_PRODUCT_OWNED:
                    listener.onException(action, "Product already owned error!");
                    return OrderStatusCode.ORDER_PRODUCT_OWNED;
                case OrderStatusCode.ORDER_PRODUCT_NOT_OWNED:
                    listener.onException(action, "Product not owned error!");
                    return SOLVED;
                case OrderStatusCode.ORDER_PRODUCT_CONSUMED:
                    listener.onException(action, "Product consumed error!");
                    return SOLVED;
                case OrderStatusCode.ORDER_ACCOUNT_AREA_NOT_SUPPORTED:
                    listener.onException(action, "Order account area not supported error!");
                    return SOLVED;
                case OrderStatusCode.ORDER_NOT_ACCEPT_AGREEMENT:
                    listener.onException(action, "User does not agree the agreement");
                    return SOLVED;
                default:
                    // Handle other error scenarios.
                    listener.onException(action, "Order unknown error!");
                    return SOLVED;
            }
        } else {
            listener.onException(action, e.getMessage());
            return SOLVED;
        }
    }
}