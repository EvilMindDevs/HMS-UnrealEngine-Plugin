package com.huawei.plugin.push;

import android.util.Log;

import com.huawei.hms.push.HmsMessageService;
import com.huawei.hms.push.RemoteMessage;
import com.huawei.plugin.push.utils.Constants;

import org.json.JSONException;
import org.json.JSONObject;

public class PushPluginService extends HmsMessageService {
    private String TAG = "PushPluginService";

    @Override
    public void onNewToken(String s) {
        super.onNewToken(s);
        HuaweiPushPlugin.handleGetNewToken(s);
        Log.i(TAG, s);
    }

    @Override
    public void onMessageReceived(RemoteMessage message) {
        super.onMessageReceived(message);
        Log.i(TAG, "onMessageReceived is called");

        // Check whether the message is empty.
        if (message == null) {
            Log.e(TAG, "Received message entity is null!");
            HuaweiPushPlugin.handleException(Constants.UNKNOWN_ERROR, Constants.ON_MESSAGE_RECEIVED, "Received null message");
            return;
        }
        String messageData = message.getData();
        HuaweiPushPlugin.handleReceiveMessage(messageData);
    }
}
