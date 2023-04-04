#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include <string>

namespace huawei
{
	enum BannerPosition
	{
		POSITION_CUSTOM = -1,
		POSITION_TOP = 0,
		POSITION_BOTTOM = 1,
		POSITION_TOP_LEFT = 2,
		POSITION_TOP_RIGHT = 3,
		POSITION_BOTTOM_LEFT = 4,
		POSITION_BOTTOM_RIGHT = 5,
		POSITION_CENTER = 6
	};

	enum BannerSize
	{
		USER_DEFINED,
		BANNER_SIZE_320_50,
		BANNER_SIZE_320_100,
		BANNER_SIZE_468_60,
		BANNER_SIZE_DYNAMIC,
		BANNER_SIZE_728_90,
		BANNER_SIZE_300_250,
		BANNER_SIZE_SMART,
		BANNER_SIZE_160_600,
		BANNER_SIZE_360_57,
		BANNER_SIZE_360_144
	};

	class AdsListener
	{
	public:
		virtual void onBannerAdClosed() = 0;
		virtual void onBannerAdFailed(int errorCode) = 0;
		virtual void onBannerAdLeftApp() = 0;
		virtual void onBannerAdOpened() = 0;
		virtual void onBannerAdLoaded() = 0;
		virtual void onBannerAdClicked() = 0;
		virtual void onBannerAdImpression() = 0;
		virtual void onInterstitialAdClosed() = 0;
		virtual void onInterstitialAdFailed(int errorCode) = 0;
		virtual void onInterstitialAdLeftApp() = 0;
		virtual void onInterstitialAdOpened() = 0;
		virtual void onInterstitialAdLoaded() = 0;
		virtual void onInterstitialAdClicked() = 0;
		virtual void onInterstitialAdImpression() = 0;
		virtual void onRewardAdFailedToLoad(int errorCode) = 0;
		virtual void onRewardedLoaded() = 0;
		virtual void onRewardAdClosed() = 0;
		virtual void onRewardAdFailedToShow(int errorCode) = 0;
		virtual void onRewardAdOpened() = 0;
		virtual void onRewarded(const FString type, int amount) = 0;
	};

	class Ads
	{
	public:
		static constexpr const char* bannerSizeToString(BannerSize size);
		static void loadBannerAd(FString adId, int position, BannerSize size);
		static void loadBannerAd(FString adId, int position, FString size);
		static void showBannerAd();
		static void hideBannerAd();
		static void destroyBannerAd();
		static void loadInterstitialAd(FString adId);
		static void showInterstitialAd();
		static void loadRewardAd(FString adId);
		static void showRewardAd();

		static void setListener(AdsListener* listener);
		static void removeListener();
		static AdsListener* getListener();
	};
}