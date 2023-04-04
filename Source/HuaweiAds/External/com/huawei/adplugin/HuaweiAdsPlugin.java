package com.huawei.adplugin;

import com.huawei.adplugin.adproxy.*;
import com.huawei.adplugin.adlistener.*;
import com.huawei.hms.ads.*;

import android.app.Activity;
import android.util.Log;

public class HuaweiAdsPlugin {
    private static boolean isInit = false;
    private static Activity mActivity = null;
    private static BannerAdProxy bannerAdProxy = null;
    private static InterstitialAdProxy interstitialAdProxy = null;
    private static RewardAdProxy rewardAdProxy = null;
    private static final String TAG = "HuaweiAdsPlugin";

    public static void initialize(Activity activity) {
        if (!isInit) {
            isInit = true;
            mActivity = activity;
        }
    }

    public static void loadBannerAd(String adId, int position, String size, final IAdStatusListener adStatusListener) {
        if (mActivity == null) {
            return;
        }
        if (bannerAdProxy == null) {
            bannerAdProxy = new BannerAdProxy(mActivity, new IAdStatusListener() {
                @Override
                public void onAdClosed() {
                    Log.i(TAG, "on banner ad closed");
                    if (adStatusListener != null) {
                        adStatusListener.onAdClosed();
                    }
                }

                @Override
                public void onAdFailed(int errorCode) {
                    Log.i(TAG, "on banner ad failed with error code " + errorCode);
                    if (adStatusListener != null) {
                        adStatusListener.onAdFailed(errorCode);
                    }
                }

                @Override
                public void onAdLeftApp() {
                    Log.i(TAG, "on banner ad left app");
                    if (adStatusListener != null) {
                        adStatusListener.onAdLeftApp();
                    }
                }

                @Override
                public void onAdOpened() {
                    Log.i(TAG, "on banner ad opened");
                    if (adStatusListener != null) {
                        adStatusListener.onAdOpened();
                    }
                }

                @Override
                public void onAdLoaded() {
                    Log.i(TAG, "on banner ad loaded");
                    //showBannerAd();
                    if (adStatusListener != null) {
                        adStatusListener.onAdLoaded();
                    }
                }

                @Override
                public void onAdClicked() {
                    Log.i(TAG, "on banner ad clicked");
                    if (adStatusListener != null) {
                        adStatusListener.onAdClicked();
                    }
                }

                @Override
                public void onAdImpression() {
                    Log.i(TAG, "on banner ad impression");
                    if (adStatusListener != null) {
                        adStatusListener.onAdImpression();
                    }
                }
            });
        } else {
            bannerAdProxy.destroy();
        }
        Log.i(TAG, "Load banner ad with id " + adId + "; position:" + position + "; size type:" + size);
        bannerAdProxy.setAdId(adId);
        bannerAdProxy.setBannerAdPosition(position);
        bannerAdProxy.setAdSizeType(size);
        AdParam adParam = new AdParam.Builder().build();
        bannerAdProxy.loadAd(adParam);
    }

    public static void showBannerAd() {
        Log.i(TAG, "Show banner ad");
        if (bannerAdProxy != null) {
            bannerAdProxy.show();
        }
    }

    public static void hideBannerAd() {
        Log.i(TAG, "Hide banner ad");
        if (bannerAdProxy != null) {
            bannerAdProxy.hide();
        }
    }

    public static void destroyBannerAd() {
        Log.i(TAG, "Destroy banner ad");
        if (bannerAdProxy != null) {
            bannerAdProxy.destroy();
        }
    }

    public static void loadInterstitialAd(String adId, final IAdStatusListener adStatusListener) {
        if (mActivity == null) {
            return;
        }
        if (interstitialAdProxy == null) {
            interstitialAdProxy = new InterstitialAdProxy(mActivity);
        }
        Log.i(TAG, "Load interstitial ad with id " + adId);
        interstitialAdProxy.setAdId(adId);
        interstitialAdProxy.setAdListener(new IAdStatusListener() {
            @Override
            public void onAdClosed() {
                Log.i(TAG, "on interstitial ad closed");
                if (adStatusListener != null) {
                    adStatusListener.onAdClosed();
                }
            }

            @Override
            public void onAdFailed(int errorCode) {
                Log.i(TAG, "on interstitial ad failed with error code " + errorCode);
                if (adStatusListener != null) {
                    adStatusListener.onAdFailed(errorCode);
                }
            }

            @Override
            public void onAdLeftApp() {
                Log.i(TAG, "on interstitial ad left app");
                if (adStatusListener != null) {
                    adStatusListener.onAdLeftApp();
                }
            }

            @Override
            public void onAdOpened() {
                Log.i(TAG, "on interstitial ad opened");
                if (adStatusListener != null) {
                    adStatusListener.onAdOpened();
                }
            }

            @Override
            public void onAdLoaded() {
                Log.i(TAG, "on interstitial ad loaded");
                //showInterstitialAd();
                if (adStatusListener != null) {
                    adStatusListener.onAdLoaded();
                }
            }

            @Override
            public void onAdClicked() {
                Log.i(TAG, "on interstitial ad clicked");
                if (adStatusListener != null) {
                    adStatusListener.onAdClicked();
                }
            }

            @Override
            public void onAdImpression() {
                Log.i(TAG, "on interstitial ad impression");
                if (adStatusListener != null) {
                    adStatusListener.onAdImpression();
                }
            }
        });
        AdParam adParam = new AdParam.Builder().build();
        interstitialAdProxy.loadAd(adParam);
    }

    public static void showInterstitialAd() {
        Log.i(TAG, "Show interstitial ad");
        if (interstitialAdProxy != null && interstitialAdProxy.isLoaded()) {
            interstitialAdProxy.show();
        }
    }

    public static void loadRewardAd(String adId, final IRewardAdLoadListener rewardLoadListener,
            final IRewardAdStatusListener rewardStatusListener) {
        if (mActivity == null) {
            return;
        }
        if (rewardAdProxy == null) {
            rewardAdProxy = new RewardAdProxy(mActivity, adId);
        }
        Log.i(TAG, "Load reward ad with id " + adId);
        AdParam adParam = new AdParam.Builder().build();
        rewardAdProxy.loadAd(adParam, new IRewardAdLoadListener() {
            @Override
            public void onRewardAdFailedToLoad(final int errorCode) {
                Log.i(TAG, "on reward ad failed to load with error code " + errorCode);
                if (rewardLoadListener != null) {
                    rewardLoadListener.onRewardAdFailedToLoad(errorCode);
                }
            }

            @Override
            public void onRewardedLoaded() {
                Log.i(TAG, "on reward ad loaded");
                //showRewardAd(rewardStatusListener);
                if (rewardLoadListener != null) {
                    rewardLoadListener.onRewardedLoaded();
                }
            }
        });
    }

    public static void showRewardAd(IRewardAdStatusListener adStatusListener) {
        Log.i(TAG, "Show reward ad");
        if (rewardAdProxy != null && rewardAdProxy.isLoaded() && mActivity != null) {
            rewardAdProxy.show(mActivity, adStatusListener);
        }
    }
}
