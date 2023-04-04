package com.huawei.adplugin.adlistener;

public interface IRewardAdLoadListener {
    void onRewardAdFailedToLoad(int errorCode);

    void onRewardedLoaded();
}
