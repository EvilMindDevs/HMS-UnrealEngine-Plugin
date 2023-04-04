/**
 * Copyright 2020. Huawei Technologies Co., Ltd. All rights reserved.
 * <p>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.huawei.plugin.push.utils;

import android.app.Activity;
import android.util.Log;

import com.huawei.hms.adapter.internal.AvailableCode;
import com.huawei.hms.adapter.internal.BaseCode;
import com.huawei.hms.common.ApiException;
import com.huawei.hms.support.api.entity.auth.AuthCode;
import com.huawei.hms.support.api.entity.core.CommonCode;
import com.huawei.plugin.push.HuaweiPushListener;

import static com.huawei.plugin.push.utils.Constants.UNKNOWN_ERROR;

/**
 *  Handles the exception returned from the iap api.
 *
 * @since 2019/12/9
 */
public class ExceptionHandle {
    private static String TAG = "ExceptionHandle";
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
    public static int handle(Activity activity, int action, Exception e, HuaweiPushListener listener) {
        if (e instanceof ApiException) {
            ApiException apiException = (ApiException) e;
            Log.i(TAG, "returnCode: " + apiException.getStatusCode());
            switch (apiException.getStatusCode()) {
                case CommonCode.ErrorCode.ARGUMENTS_INVALID:
                    listener.onException(CommonCode.ErrorCode.ARGUMENTS_INVALID, action, "Incorrect input parameters.");
                    return SOLVED;
                case CommonCode.ErrorCode.INTERNAL_ERROR:
                    listener.onException(CommonCode.ErrorCode.INTERNAL_ERROR, action, "An internal error occurred and cannot be rectified.");
                    return SOLVED;
                case CommonCode.ErrorCode.NAMING_INVALID:
                    listener.onException(CommonCode.ErrorCode.NAMING_INVALID, action, "Failed to query the specified service API, because the API does not exist or the API instance failed to be created.");
                    return SOLVED;
                case CommonCode.ErrorCode.CLIENT_API_INVALID:
                    listener.onException(CommonCode.ErrorCode.CLIENT_API_INVALID, action, "Invalid ApiClient object.");
                    return SOLVED;
                case CommonCode.ErrorCode.EXECUTE_TIMEOUT:
                    listener.onException(CommonCode.ErrorCode.EXECUTE_TIMEOUT, action, "AIDL call timed out.");
                    return SOLVED;
                case CommonCode.ErrorCode.NOT_IN_SERVICE:
                    listener.onException(CommonCode.ErrorCode.NOT_IN_SERVICE, action, "This service is unavailable in this region.");
                    return SOLVED;
                case CommonCode.ErrorCode.SESSION_INVALID:
                    listener.onException(CommonCode.ErrorCode.SESSION_INVALID, action, "HMS Core SDK internal error. The AIDL connection session is invalid.");
                    return SOLVED;
                case AuthCode.ErrorCode.GET_SCOPE_ERROR:
                    listener.onException(AuthCode.ErrorCode.GET_SCOPE_ERROR, action, "Failed to call the gateway to query Scope of the app.");
                    return SOLVED;
                case AuthCode.ErrorCode.SCOPE_LIST_EMPTY:
                    listener.onException(AuthCode.ErrorCode.SCOPE_LIST_EMPTY, action, "Scope of OpenGW is not configured.");
                    return SOLVED;
                case AuthCode.ErrorCode.CERT_FINGERPRINT_EMPTY:
                    listener.onException(AuthCode.ErrorCode.CERT_FINGERPRINT_EMPTY, action, "No certificate fingerprint is configured for OpenGW.");
                    return SOLVED;
                case AuthCode.ErrorCode.PERMISSION_LIST_EMPTY:
                    listener.onException(AuthCode.ErrorCode.PERMISSION_LIST_EMPTY, action, "The permission of OpenGW is not configured");
                    return SOLVED;
                case AuthCode.StatusCode.AUTH_INFO_NOT_EXIST:
                    listener.onException(AuthCode.StatusCode.AUTH_INFO_NOT_EXIST, action, "The app's authentication information does not exist");
                    return SOLVED;
                case AuthCode.StatusCode.CERT_FINGERPRINT_ERROR:
                    listener.onException(AuthCode.StatusCode.CERT_FINGERPRINT_ERROR, action, "Certificate fingerprint verification: Incorrect signing certificate fingerprint.");
                    return SOLVED;
                case AuthCode.StatusCode.PERMISSION_NOT_EXIST:
                    listener.onException(AuthCode.StatusCode.PERMISSION_NOT_EXIST, action, "API authentication: Permission not granted from HUAWEI Developers.");
                    return SOLVED;
                case AuthCode.StatusCode.PERMISSION_NOT_AUTHORIZED:
                    listener.onException(AuthCode.StatusCode.PERMISSION_NOT_AUTHORIZED, action, "API authentication: Permission not granted.");
                    return SOLVED;
                case AuthCode.StatusCode.PERMISSION_EXPIRED:
                    listener.onException(AuthCode.StatusCode.PERMISSION_EXPIRED, action, "API authentication: Permission expired.");
                    return SOLVED;
                case BaseCode.PARAM_ERROR:
                    listener.onException(BaseCode.PARAM_ERROR, action, "The input parameter is set to null.");
                    return SOLVED;
                case BaseCode.ACTIVITY_NULL:
                    listener.onException(BaseCode.ACTIVITY_NULL, action, "The reference of the passed Activity object is null.");
                    return SOLVED;
                case BaseCode.NO_SOLUTION:
                    listener.onException(AuthCode.StatusCode.PERMISSION_NOT_EXIST, action, "The service side does not return Intent or PendingIntent.");
                    return SOLVED;

                case BaseCode.DATA_NULL_IN_INTENT:
                    listener.onException(BaseCode.DATA_NULL_IN_INTENT, action, "The data field in the intent returned by onActivityResult is set to null, or the intent does not record the update result.");
                    return SOLVED;
                case BaseCode.NO_AVAILABLE_LIB_ERROR:
                    listener.onException(BaseCode.NO_AVAILABLE_LIB_ERROR, action, "The update failed because you have not integrated the availableupdate SDK.");
                    return SOLVED;
                case BaseCode.KPMS_UPDATE_FAILED:
                    listener.onException(BaseCode.KPMS_UPDATE_FAILED, action, "The kit failed to be updated using the KPMS.");
                    return SOLVED;
                case AvailableCode.CANCELED:
                    listener.onException(AvailableCode.CANCELED, action, "The operation is canceled by the user.");
                    return SOLVED;
                case AvailableCode.ERROR_NO_ACTIVITY:
                    listener.onException(AvailableCode.ERROR_NO_ACTIVITY, action, "The page cannot be displayed because no Activity object is passed.");
                    return SOLVED;
                case AvailableCode.APP_IS_BACKGROUND_OR_LOCKED:
                    listener.onException(AvailableCode.APP_IS_BACKGROUND_OR_LOCKED, action, "The update page failed to be displayed because the app is running in the background or the screen of the device is locked.");
                    return SOLVED;
                case AvailableCode.HMS_IS_SPOOF:
                    listener.onException(AvailableCode.ERROR_NO_ACTIVITY, action, "HMS Core (APK) is spoofed.");
                    return SOLVED;
                case -5:
                    listener.onException(-5, action, "Failed to obtain the token.");
                    return SOLVED;
                case 907122030:
                    listener.onException(907122030, action, "No token.");
                    return SOLVED;
                case 907122031:
                    listener.onException(907122031, action, "The network is unavailable.");
                    return SOLVED;
                case 907122032:
                    listener.onException(907122032, action, "The token has expired.");
                    return SOLVED;
                case 907122034:
                    listener.onException(907122034, action, "The number of topics to be subscribed to exceeds the threshold (2000).");
                    return SOLVED;
                case 907122035:
                    listener.onException(907122035, action, "Failed to subscribe to the topic.");
                    return SOLVED;
                case 907122036:
                    listener.onException(907122036, action, "Push Kit is not enabled.");
                    return SOLVED;
                case 907122037:
                    listener.onException(907122037, action, "Failed to obtain the token.");
                    return SOLVED;
                case 907122038:
                    listener.onException(907122038, action, "No storage location is selected for the app, or the storage location is invalid.");
                    return SOLVED;
                case 907122041:
                    listener.onException(907122041, action, "The message body size exceeds the maximum (1 KB).");
                    return SOLVED;
                case 907122042:
                    listener.onException(907122042, action, "The message contains invalid parameters.");
                    return SOLVED;
                case 907122043:
                    listener.onException(907122043, action, "This message is discarded because the number of sent messages reaches the upper limit.");
                    return SOLVED;
                case 907122044:
                    listener.onException(907122044, action, "Before being sent to your server, the message is discarded due to expiration.");
                    return SOLVED;
                case 907122045:
                    listener.onException(907122045, action, "Unknown error.");
                    return SOLVED;
                case 907122047:
                    listener.onException(907122047, action, "Common Push Kit error.");
                    return SOLVED;
                case 907122048:
                    listener.onException(907122048, action, "HMS Core (APK) cannot connect to Push Kit.");
                    return SOLVED;
                case 907122049:
                    listener.onException(907122049, action, "EMUI is not in the required version, or Push Kit is not in the required version.");
                    return SOLVED;
                case 907122050:
                    listener.onException(907122050, action, "The operation cannot be performed in the main thread.");
                    return SOLVED;
                case 907122051:
                    listener.onException(907122051, action, "Failed to authenticate the device certificate.");
                    return SOLVED;
                case 907122052:
                    listener.onException(907122052, action, "Failed to bind the service.");
                    return SOLVED;
                case 907122053:
                    listener.onException(907122053, action, "Failed to obtain the token. Cross-location application is not allowed.");
                    return SOLVED;
                case 907122054:
                    listener.onException(907122054, action, "The HMS Core Push SDK is being automatically initialized.");
                    return SOLVED;
                case 907122055:
                    listener.onException(907122055, action, "The system is busy.");
                    return SOLVED;
                case 907122056:
                    listener.onException(907122056, action, "Failed to send an uplink message.");
                    return SOLVED;
                case 907122057:
                    listener.onException(907122057, action, "Incorrect input parameter for constructing an object for sending uplink messages.");
                    return SOLVED;
                case 907122058:
                    listener.onException(907122058, action, "The message is discarded because the number of cached uplink messages to be sent by the app exceeds the threshold (20).");
                    return SOLVED;
                case 907122059:
                    listener.onException(907122059, action, "The uplink message sent by the app is cached due to a cause such as network unavailability.");
                    return SOLVED;
                case 907122060:
                    listener.onException(907122060, action, "Your server is offline.");
                    return SOLVED;
                case 907122061:
                    listener.onException(907122061, action, "Flow control is performed because the frequency for the app to send uplink messages is too high.");
                    return SOLVED;
                case 907122064:
                    listener.onException(907122064, action, "The agconnect-services.json file does not contain the projectId field.");
                    return SOLVED;
                case 907122065:
                    listener.onException(907122065, action, "Failed to obtain a token for the apps on smart watches, VR devices, or routers.");
                    return SOLVED;
                case 907122066:
                    listener.onException(907122066, action, "Failed to obtain HUAWEI ID information.");
                    return SOLVED;
                case 907122067:
                    listener.onException(907122067, action, "The number of added user-app relationships exceeds the maximum (10).");
                    return SOLVED;
                case 907122101:
                    listener.onException(907122101, action, "Failed to obtain the token of the third-party push service.");
                    return SOLVED;
                case 907122102:
                    listener.onException(907122102, action, "Failed to delete the token of the third-party push service.");
                    return SOLVED;
                case 907122103:
                    listener.onException(907122103, action, "An internal error occurs in the third-party push SDK.");
                    return SOLVED;
                case 907122104:
                    listener.onException(907122104, action, "Failed to obtain the domain name.");
                    return SOLVED;
                case 907122105:
                    listener.onException(907122105, action, "Failed to construct the JSON message body for obtaining a token.");
                    return SOLVED;
                default:
                    // Handle other error scenarios.
                    listener.onException(apiException.getStatusCode(), action, "unknown error!");
                    return SOLVED;
            }
        } else {
            listener.onException(UNKNOWN_ERROR, action, e.getMessage());
            return SOLVED;
        }
    }
}