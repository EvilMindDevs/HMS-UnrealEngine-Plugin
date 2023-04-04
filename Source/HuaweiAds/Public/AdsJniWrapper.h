#pragma once
#include "Ads.h"
#include <string>

DECLARE_LOG_CATEGORY_EXTERN(HuaweiAds_Native, Log, All);
using namespace std;

namespace huawei
{

    class AdsJniWrapper
    {

    public:
        static AdsJniWrapper *getInstance();

        AdsJniWrapper();
        ~AdsJniWrapper();

        void loadBannerAd(string adId, int position, string size);
        void showBannerAd();
        void hideBannerAd();
        void destroyBannerAd();
        void loadInterstitialAd(string adId);
        void showInterstitialAd();
        void loadRewardAd(string adId);
        void showRewardAd();

        // Listener
        void setListener(AdsListener *listener);
        void removeListener();
        AdsListener *getListener();

        // Callbacks
        void onBannerAdClosed();
        void onBannerAdFailed(int errorCode);
        void onBannerAdLeftApp();
        void onBannerAdOpened();
        void onBannerAdLoaded();
        void onBannerAdClicked();
        void onBannerAdImpression();
        void onInterstitialAdClosed();
        void onInterstitialAdFailed(int errorCode);
        void onInterstitialAdLeftApp();
        void onInterstitialAdOpened();
        void onInterstitialAdLoaded();
        void onInterstitialAdClicked();
        void onInterstitialAdImpression();
        void onRewardAdFailedToLoad(int errorCode);
        void onRewardedLoaded();
        void onRewardAdClosed();
        void onRewardAdFailedToShow(int errorCode);
        void onRewardAdOpened();
        void onRewarded(const FString type, int amount);

    protected:
        AdsListener *_listener;
    };
}
