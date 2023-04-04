package com.huawei.adplugin.adlistener;

public interface IRewardAdStatusListener {
    void onRewardAdFailedToLoad(int errorCode);

    void onRewardedLoaded();

    void onRewardAdClosed();

    void onRewardAdFailedToShow(int errorCode);

    void onRewardAdOpened();

    void onRewarded(String type, int amount);
}
