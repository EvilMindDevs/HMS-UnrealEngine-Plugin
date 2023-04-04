package com.huawei.accountplugin;

import com.huawei.hms.support.account.result.AuthAccount;

public interface HuaweiAccountListener {
    void onLoggedIn(AuthAccount account);
    void onGetIdToken(AuthAccount account);
    void onGetAuthCode(AuthAccount account);
    void onLoggedOut();
    void onCancelledAuth();
    void onException(int action, String message);
}