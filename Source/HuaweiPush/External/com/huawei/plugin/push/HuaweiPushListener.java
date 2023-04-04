package com.huawei.plugin.push;

public interface HuaweiPushListener {
    void onGetTokenSuccess(String token);
    void onDeleteTokenSuccess();
    void onNewToken(String token);
    void onMessageReceived(String messageJson);
    void onSubscribeSuccess();
    void onUnSubscribeSuccess();
    void onException(int errorCode, int action, String message);
}
