#include "AdsBlueprint.h"

using namespace huawei;

FOnBannerAdClosed UHuaweiAdsBlueprint::_onBannerAdClosed;
FOnBannerAdFailed UHuaweiAdsBlueprint::_onBannerAdFailed;
FOnBannerAdLeftApp UHuaweiAdsBlueprint::_onBannerAdLeftApp;
FOnBannerAdOpened UHuaweiAdsBlueprint::_onBannerAdOpened;
FOnBannerAdLoaded UHuaweiAdsBlueprint::_onBannerAdLoaded;
FOnBannerAdClicked UHuaweiAdsBlueprint::_onBannerAdClicked;
FOnBannerAdImpression UHuaweiAdsBlueprint::_onBannerAdImpression;
void UHuaweiAdsBlueprint::loadBannerAd(
	const FString adId,
	const UBannerPosition position,
	const UBannerSize size,
	const FOnBannerAdClosed &onBannerAdClosed,
	const FOnBannerAdFailed &onBannerAdFailed,
	const FOnBannerAdLeftApp &onBannerAdLeftApp,
	const FOnBannerAdOpened &onBannerAdOpened,
	const FOnBannerAdLoaded &onBannerAdLoaded,
	const FOnBannerAdClicked &onBannerAdClicked,
	const FOnBannerAdImpression &onBannerAdImpression)
{
	Ads::loadBannerAd(adId, ((uint8) position) - 1, UEnum::GetValueAsString(size).Replace(TEXT("UBannerSize::"), TEXT("")));
	UHuaweiAdsBlueprint::_onBannerAdClosed = onBannerAdClosed;
	UHuaweiAdsBlueprint::_onBannerAdFailed = onBannerAdFailed;
	UHuaweiAdsBlueprint::_onBannerAdLeftApp = onBannerAdLeftApp;
	UHuaweiAdsBlueprint::_onBannerAdOpened = onBannerAdOpened;
	UHuaweiAdsBlueprint::_onBannerAdLoaded = onBannerAdLoaded;
	UHuaweiAdsBlueprint::_onBannerAdClicked = onBannerAdClicked;
	UHuaweiAdsBlueprint::_onBannerAdImpression = onBannerAdImpression;
}

void UHuaweiAdsBlueprint::showBannerAd()
{
	Ads::showBannerAd();
}

void UHuaweiAdsBlueprint::hideBannerAd()
{
	Ads::hideBannerAd();
}

void UHuaweiAdsBlueprint::destroyBannerAd()
{
	Ads::destroyBannerAd();
}

FOnInterstitialAdClosed UHuaweiAdsBlueprint::_onInterstitialAdClosed;
FOnInterstitialAdFailed UHuaweiAdsBlueprint::_onInterstitialAdFailed;
FOnInterstitialAdLeftApp UHuaweiAdsBlueprint::_onInterstitialAdLeftApp;
FOnInterstitialAdOpened UHuaweiAdsBlueprint::_onInterstitialAdOpened;
FOnInterstitialAdLoaded UHuaweiAdsBlueprint::_onInterstitialAdLoaded;
FOnInterstitialAdClicked UHuaweiAdsBlueprint::_onInterstitialAdClicked;
FOnInterstitialAdImpression UHuaweiAdsBlueprint::_onInterstitialAdImpression;
void UHuaweiAdsBlueprint::loadInterstitialAd(
	const FString adId,
	const FOnInterstitialAdClosed &onInterstitialAdClosed,
	const FOnInterstitialAdFailed &onInterstitialAdFailed,
	const FOnInterstitialAdLeftApp &onInterstitialAdLeftApp,
	const FOnInterstitialAdOpened &onInterstitialAdOpened,
	const FOnInterstitialAdLoaded &onInterstitialAdLoaded,
	const FOnInterstitialAdClicked &onInterstitialAdClicked,
	const FOnInterstitialAdImpression &onInterstitialAdImpression)
{
	Ads::loadInterstitialAd(adId);
	UHuaweiAdsBlueprint::_onInterstitialAdClosed = onInterstitialAdClosed;
	UHuaweiAdsBlueprint::_onInterstitialAdFailed = onInterstitialAdFailed;
	UHuaweiAdsBlueprint::_onInterstitialAdLeftApp = onInterstitialAdLeftApp;
	UHuaweiAdsBlueprint::_onInterstitialAdOpened = onInterstitialAdOpened;
	UHuaweiAdsBlueprint::_onInterstitialAdLoaded = onInterstitialAdLoaded;
	UHuaweiAdsBlueprint::_onInterstitialAdClicked = onInterstitialAdClicked;
	UHuaweiAdsBlueprint::_onInterstitialAdImpression = onInterstitialAdImpression;
}

void UHuaweiAdsBlueprint::showInterstitialAd()
{
	Ads::showInterstitialAd();
}

FOnRewardAdFailedToLoad UHuaweiAdsBlueprint::_onRewardAdFailedToLoad;
FOnRewardedLoaded UHuaweiAdsBlueprint::_onRewardedLoaded;
FOnRewardAdClosed UHuaweiAdsBlueprint::_onRewardAdClosed;
FOnRewardAdFailedToShow UHuaweiAdsBlueprint::_onRewardAdFailedToShow;
FOnRewardAdOpened UHuaweiAdsBlueprint::_onRewardAdOpened;
FOnRewarded UHuaweiAdsBlueprint::_onRewarded;
void UHuaweiAdsBlueprint::loadRewardAd(
	const FString adId,
	const FOnRewardAdFailedToLoad &onRewardAdFailedToLoad,
	const FOnRewardedLoaded &onRewardedLoaded,
	const FOnRewardAdClosed &onRewardAdClosed,
	const FOnRewardAdFailedToShow &onRewardAdFailedToShow,
	const FOnRewardAdOpened &onRewardAdOpened,
	const FOnRewarded &onRewarded)
{
	Ads::loadRewardAd(adId);
	UHuaweiAdsBlueprint::_onRewardAdFailedToLoad = onRewardAdFailedToLoad;
	UHuaweiAdsBlueprint::_onRewardedLoaded = onRewardedLoaded;
	UHuaweiAdsBlueprint::_onRewardAdClosed = onRewardAdClosed;
	UHuaweiAdsBlueprint::_onRewardAdFailedToShow = onRewardAdFailedToShow;
	UHuaweiAdsBlueprint::_onRewardAdOpened = onRewardAdOpened;
	UHuaweiAdsBlueprint::_onRewarded = onRewarded;
}

void UHuaweiAdsBlueprint::showRewardAd()
{
	Ads::showRewardAd();
}

void UHuaweiAdsBlueprint::onBannerAdClosed()
{
	UHuaweiAdsBlueprint::_onBannerAdClosed.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onBannerAdFailed(int errorCode)
{
	UHuaweiAdsBlueprint::_onBannerAdFailed.ExecuteIfBound(errorCode);
}

void UHuaweiAdsBlueprint::onBannerAdLeftApp()
{
	UHuaweiAdsBlueprint::_onBannerAdLeftApp.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onBannerAdOpened()
{
	UHuaweiAdsBlueprint::_onBannerAdOpened.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onBannerAdLoaded()
{
	UHuaweiAdsBlueprint::_onBannerAdLoaded.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onBannerAdClicked()
{
	UHuaweiAdsBlueprint::_onBannerAdClicked.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onBannerAdImpression()
{
	UHuaweiAdsBlueprint::_onBannerAdImpression.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onInterstitialAdClosed()
{
	UHuaweiAdsBlueprint::_onInterstitialAdClosed.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onInterstitialAdFailed(int errorCode)
{
	UHuaweiAdsBlueprint::_onInterstitialAdFailed.ExecuteIfBound(errorCode);
}

void UHuaweiAdsBlueprint::onInterstitialAdLeftApp()
{
	UHuaweiAdsBlueprint::_onInterstitialAdLeftApp.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onInterstitialAdOpened()
{
	UHuaweiAdsBlueprint::_onInterstitialAdOpened.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onInterstitialAdLoaded()
{
	UHuaweiAdsBlueprint::_onInterstitialAdLoaded.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onInterstitialAdClicked()
{
	UHuaweiAdsBlueprint::_onInterstitialAdClicked.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onInterstitialAdImpression()
{
	UHuaweiAdsBlueprint::_onInterstitialAdImpression.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onRewardAdFailedToLoad(int errorCode)
{
	UHuaweiAdsBlueprint::_onRewardAdFailedToLoad.ExecuteIfBound(errorCode);
}

void UHuaweiAdsBlueprint::onRewardedLoaded()
{
	UHuaweiAdsBlueprint::_onRewardedLoaded.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onRewardAdClosed()
{
	UHuaweiAdsBlueprint::_onRewardAdClosed.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onRewardAdFailedToShow(int errorCode)
{
	UHuaweiAdsBlueprint::_onRewardAdFailedToShow.ExecuteIfBound(errorCode);
}

void UHuaweiAdsBlueprint::onRewardAdOpened()
{
	UHuaweiAdsBlueprint::_onRewardAdOpened.ExecuteIfBound();
}

void UHuaweiAdsBlueprint::onRewarded(const FString type, int amount)
{
	UHuaweiAdsBlueprint::_onRewarded.ExecuteIfBound(type, amount);
}
