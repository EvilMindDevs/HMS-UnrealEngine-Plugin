package com.huawei.plugin.push;

import android.app.Activity;
import android.app.NativeActivity;
import android.content.Intent;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;

import com.huawei.agconnect.AGConnectOptionsBuilder;
import com.huawei.hmf.tasks.OnCompleteListener;
import com.huawei.hmf.tasks.Task;
import com.huawei.hms.aaid.HmsInstanceId;
import com.huawei.hms.common.ApiException;
import com.huawei.hms.push.HmsMessaging;
import com.huawei.plugin.push.utils.ExceptionHandle;

import java.util.Objects;

import static com.huawei.plugin.push.utils.Constants.INIT_FAILED;
import static com.huawei.plugin.push.utils.Constants.DELETE_TOKEN_FAILED;
import static com.huawei.plugin.push.utils.Constants.GET_TOKEN_FAILED;
import static com.huawei.plugin.push.utils.Constants.SUBSCRIBE_FAILED;
import static com.huawei.plugin.push.utils.Constants.UNKNOWN_ERROR;
import static com.huawei.plugin.push.utils.Constants.UN_SUBSCRIBE_FAILED;

public class HuaweiPushPlugin implements HuaweiPushListener {

    private static final String TAG = "HuaweiPushPlugin";
    private static NativeActivity mActivity = null;
    private static String APP_ID = "";
    private static HuaweiPushPlugin mInstance;
    private static String mToken;
    private static String mMessageJson;
    private static int mErrorCode = -1;
    private static int mAction = -1;
    private static String mMessage;

    // native C++ methods
    private static native void nativeOnGetTokenSuccess(String token);
    private static native void nativeOnDeleteTokenSuccess();
    private static native void nativeOnNewToken(String token);
    private static native void nativeOnMessageReceived(String messageJson);
    private static native void nativeOnSubscribeSuccess();
    private static native void nativeOnUnSubscribeSuccess();
    private static native void nativeOnException(int errorCode, int action, String message);

    public static HuaweiPushPlugin getInstance() {
        return mInstance;
    }

    public HuaweiPushPlugin(NativeActivity activity) {
        mInstance = this;
        mActivity = activity;
    }

    public static void handleGetNewToken(String token) {
        if (mInstance == null) {
            synchronized(TAG) {
                mToken = token;
            }
        } else {
            nativeOnNewToken(token);
        }
    }

    public static void handleReceiveMessage(String messageJson) {
        if (mInstance == null) {
            synchronized(TAG) {
                mMessageJson = messageJson;
            }
        } else {
            nativeOnMessageReceived(messageJson);
        }
    }

    public static void handleException(int errorCode, int action, String message) {
        if (mInstance == null) {
            synchronized(TAG) {
                mErrorCode = errorCode;
                mAction = action;
                mMessage = message;
            }
        } else {
            nativeOnException(errorCode, action, message);
        }
    }

    public void init() {
        APP_ID = new AGConnectOptionsBuilder().build(mActivity).getString("client/app_id");
        if (APP_ID == null) {
            onException(UNKNOWN_ERROR, INIT_FAILED, "Cannot get application ID. Please check your agconnect-services.json file");
            return;
        }
        synchronized(TAG) {
            if (mToken != null) {
                onNewToken(mToken);
                mToken = null;
            }
            if (mMessageJson != null) {
                onMessageReceived(mMessageJson);
                mMessageJson = null;
            }
            if (mErrorCode != -1 || mAction != -1 || mMessage != null) {
                nativeOnException(mErrorCode, mAction, mMessage);
                mErrorCode = -1;
                mAction = -1;
                mMessage = null;
            }
        }
    }

    public void getToken() {
        // Create a thread.
        new Thread() {
            @Override
            public void run() {
                try {
                    // Set tokenScope to HCM.
                    String tokenScope = "HCM";
                    String token = HmsInstanceId.getInstance(mActivity).getToken(APP_ID, tokenScope);
                    Log.i(TAG, "get token: " + token);

                    // Check whether the token is null.
                    if (!TextUtils.isEmpty(token)) {
                        onGetTokenSuccess(token);
                    } else {
                        onException(UNKNOWN_ERROR, GET_TOKEN_FAILED, "token is null");
                    }
                } catch (ApiException e) {
                    Log.e(TAG, "get token failed, " + e);
                    ExceptionHandle.handle(mActivity, GET_TOKEN_FAILED, e, HuaweiPushPlugin.this);
                }
            }
        }.start();
    }

    public void deleteToken() {
        // Create a thread.
        new Thread() {
            @Override
            public void run() {
                try {
                    // Set tokenScope to HCM.
                    String tokenScope = "HCM";

                    // Delete the token.
                    HmsInstanceId.getInstance(mActivity).deleteToken(APP_ID, tokenScope);
                    onDeleteTokenSuccess();
                    Log.i(TAG, "token deleted successfully");
                } catch (ApiException e) {
                    Log.e(TAG, "deleteToken failed." + e);
                    ExceptionHandle.handle(mActivity, DELETE_TOKEN_FAILED, e, HuaweiPushPlugin.this);
                }
            }
        }.start();
    }

    public void setAutoInitEnabled(final boolean isEnable) {
        HmsMessaging.getInstance(mActivity).setAutoInitEnabled(isEnable);
    }

    public void subscribe(String topic) {
        try {
            // Subscribe to a topic.
            HmsMessaging.getInstance(mActivity).subscribe(topic)
                    .addOnCompleteListener(new OnCompleteListener<Void>() {
                        @Override
                        public void onComplete(Task<Void> task) {
                            // Obtain the topic subscription result.
                            if (task.isSuccessful()) {
                                Log.i(TAG, "subscribe topic successfully");
                                onSubscribeSuccess();
                            } else {
                                Log.e(TAG,
                                        "subscribe topic failed, return value is " + task.getException().getMessage());
                                ExceptionHandle.handle(mActivity, SUBSCRIBE_FAILED, task.getException(), HuaweiPushPlugin.this);
                            }
                        }
                    });
        } catch (Exception e) {
            Log.e(TAG, "subscribe failed, catch exception : " + e.getMessage());
            onException(UNKNOWN_ERROR, SUBSCRIBE_FAILED, e.getMessage());
        }
    }

    public void unsubscribe(String topic) {
        try {
            // Unsubscribe from a topic.
            HmsMessaging.getInstance(mActivity).unsubscribe(topic)
                    .addOnCompleteListener(new OnCompleteListener<Void>() {
                        @Override
                        public void onComplete(Task<Void> task) {
                            // Obtain the topic unsubscription result.
                            if (task.isSuccessful()) {
                                Log.i(TAG, "unsubscribe topic successfully");
                                onUnSubscribeSuccess();
                            } else {
                                Log.e(TAG, "unsubscribe topic failed, return value is "
                                        + task.getException().getMessage());
                                ExceptionHandle.handle(mActivity, UN_SUBSCRIBE_FAILED, task.getException(), HuaweiPushPlugin.this);
                            }
                        }
                    });
        } catch (Exception e) {
            Log.e(TAG, "unsubscribe failed, catch exception : " + e.getMessage());
            onException(UNKNOWN_ERROR, UN_SUBSCRIBE_FAILED, e.getMessage());
        }
    }

    @Override
    public void onGetTokenSuccess(String token) {
        nativeOnGetTokenSuccess(token);
    }

    @Override
    public void onDeleteTokenSuccess() {
        nativeOnDeleteTokenSuccess();
    }

    @Override
    public void onNewToken(String token) {
        nativeOnNewToken(token);
    }

    @Override
    public void onMessageReceived(String messageJson) {
        nativeOnMessageReceived(messageJson);
    }

    @Override
    public void onSubscribeSuccess() {
        nativeOnSubscribeSuccess();
    }

    @Override
    public void onUnSubscribeSuccess() {
        nativeOnUnSubscribeSuccess();
    }

    @Override
    public void onException(int errorCode, int action, String message) {
        nativeOnException(errorCode, action, message);
    }
}
