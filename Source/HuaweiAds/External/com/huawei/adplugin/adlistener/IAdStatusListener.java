package com.huawei.adplugin.adlistener;

public interface IAdStatusListener {
    void onAdClosed();

    void onAdFailed(int errorCode);

    void onAdLeftApp();

    void onAdOpened();

    void onAdLoaded();

    void onAdClicked();

    void onAdImpression();
}
