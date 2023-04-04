#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Engine.h"
#include "Ads.h"
#include "Delegates/DelegateCombinations.h"
#include "AdsBlueprint.generated.h"

using namespace huawei;

DECLARE_DYNAMIC_DELEGATE(FOnBannerAdClosed);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnBannerAdFailed, int, errorCode);
DECLARE_DYNAMIC_DELEGATE(FOnBannerAdLeftApp);
DECLARE_DYNAMIC_DELEGATE(FOnBannerAdOpened);
DECLARE_DYNAMIC_DELEGATE(FOnBannerAdLoaded);
DECLARE_DYNAMIC_DELEGATE(FOnBannerAdClicked);
DECLARE_DYNAMIC_DELEGATE(FOnBannerAdImpression);
DECLARE_DYNAMIC_DELEGATE(FOnInterstitialAdClosed);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnInterstitialAdFailed, int, errorCode);
DECLARE_DYNAMIC_DELEGATE(FOnInterstitialAdLeftApp);
DECLARE_DYNAMIC_DELEGATE(FOnInterstitialAdOpened);
DECLARE_DYNAMIC_DELEGATE(FOnInterstitialAdLoaded);
DECLARE_DYNAMIC_DELEGATE(FOnInterstitialAdClicked);
DECLARE_DYNAMIC_DELEGATE(FOnInterstitialAdImpression);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnRewardAdFailedToLoad, int, errorCode);
DECLARE_DYNAMIC_DELEGATE(FOnRewardedLoaded);
DECLARE_DYNAMIC_DELEGATE(FOnRewardAdClosed);
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnRewardAdFailedToShow, int, errorCode);
DECLARE_DYNAMIC_DELEGATE(FOnRewardAdOpened);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnRewarded, FString, type, int, amount);

UENUM(BlueprintType)
enum class UBannerPosition : uint8
{
    POSITION_CUSTOM = 0 UMETA(DisplayName="POSITION_CUSTOM"),
    POSITION_TOP = 1 UMETA(DisplayName="POSITION_TOP"),
    POSITION_BOTTOM = 2 UMETA(DisplayName="POSITION_BOTTOM"),
    POSITION_TOP_LEFT = 3 UMETA(DisplayName="POSITION_TOP_LEFT"),
    POSITION_TOP_RIGHT = 4 UMETA(DisplayName="POSITION_TOP_RIGHT"),
    POSITION_BOTTOM_LEFT = 5 UMETA(DisplayName="POSITION_BOTTOM_LEFT"),
    POSITION_BOTTOM_RIGHT = 6 UMETA(DisplayName="POSITION_BOTTOM_RIGHT"),
    POSITION_CENTER = 7 UMETA(DisplayName="POSITION_CENTER")
};

UENUM(BlueprintType)
enum class UBannerSize : uint8
{
    //USER_DEFINED  UMETA(DisplayName="USER_DEFINED"),
    BANNER_SIZE_320_50 UMETA(DisplayName="BANNER_SIZE_320_50"),
    BANNER_SIZE_320_100 UMETA(DisplayName="BANNER_SIZE_320_100"),
    //BANNER_SIZE_468_60 UMETA(DisplayName="BANNER_SIZE_468_60"),
    BANNER_SIZE_DYNAMIC UMETA(DisplayName="BANNER_SIZE_DYNAMIC"),
    //BANNER_SIZE_728_90 UMETA(DisplayName="BANNER_SIZE_728_90"),
    BANNER_SIZE_300_250 UMETA(DisplayName="BANNER_SIZE_300_250"),
    BANNER_SIZE_SMART UMETA(DisplayName="BANNER_SIZE_SMART"),
    //BANNER_SIZE_160_600 UMETA(DisplayName="BANNER_SIZE_160_600"),
    BANNER_SIZE_360_57 UMETA(DisplayName="BANNER_SIZE_360_57"),
    BANNER_SIZE_360_144 UMETA(DisplayName="BANNER_SIZE_360_144")
};

UCLASS()
class HUAWEIADS_API UHuaweiAdsBlueprint : public UBlueprintFunctionLibrary, public AdsListener
{
    GENERATED_BODY()

    UHuaweiAdsBlueprint(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
    {
        huawei::Ads::setListener(this);
    };

    static FOnBannerAdClosed _onBannerAdClosed;
    static FOnBannerAdFailed _onBannerAdFailed;
    static FOnBannerAdLeftApp _onBannerAdLeftApp;
    static FOnBannerAdOpened _onBannerAdOpened;
    static FOnBannerAdLoaded _onBannerAdLoaded;
    static FOnBannerAdClicked _onBannerAdClicked;
    static FOnBannerAdImpression _onBannerAdImpression;
    static FOnInterstitialAdClosed _onInterstitialAdClosed;
    static FOnInterstitialAdFailed _onInterstitialAdFailed;
    static FOnInterstitialAdLeftApp _onInterstitialAdLeftApp;
    static FOnInterstitialAdOpened _onInterstitialAdOpened;
    static FOnInterstitialAdLoaded _onInterstitialAdLoaded;
    static FOnInterstitialAdClicked _onInterstitialAdClicked;
    static FOnInterstitialAdImpression _onInterstitialAdImpression;
    static FOnRewardAdFailedToLoad _onRewardAdFailedToLoad;
    static FOnRewardedLoaded _onRewardedLoaded;
    static FOnRewardAdClosed _onRewardAdClosed;
    static FOnRewardAdFailedToShow _onRewardAdFailedToShow;
    static FOnRewardAdOpened _onRewardAdOpened;
    static FOnRewarded _onRewarded;

    UFUNCTION(BlueprintCallable, Category = "HuaweiAds Category")
    static void loadBannerAd(
        const FString adId,
        const UBannerPosition position,
        const UBannerSize size,
        const FOnBannerAdClosed &onBannerAdClosed,
        const FOnBannerAdFailed &onBannerAdFailed,
        const FOnBannerAdLeftApp &onBannerAdLeftApp,
        const FOnBannerAdOpened &onBannerAdOpened,
        const FOnBannerAdLoaded &onBannerAdLoaded,
        const FOnBannerAdClicked &onBannerAdClicked,
        const FOnBannerAdImpression &onBannerAdImpression);

    UFUNCTION(BlueprintCallable, Category = "HuaweiAds Category")
    static void showBannerAd();

    UFUNCTION(BlueprintCallable, Category = "HuaweiAds Category")
    static void hideBannerAd();

    UFUNCTION(BlueprintCallable, Category = "HuaweiAds Category")
    static void destroyBannerAd();

    UFUNCTION(BlueprintCallable, Category = "HuaweiAds Category")
    static void loadInterstitialAd(
        const FString adId,
        const FOnInterstitialAdClosed &onInterstitialAdClosed,
        const FOnInterstitialAdFailed &onInterstitialAdFailed,
        const FOnInterstitialAdLeftApp &onInterstitialAdLeftApp,
        const FOnInterstitialAdOpened &onInterstitialAdOpened,
        const FOnInterstitialAdLoaded &onInterstitialAdLoaded,
        const FOnInterstitialAdClicked &onInterstitialAdClicked,
        const FOnInterstitialAdImpression &onInterstitialAdImpression);

    UFUNCTION(BlueprintCallable, Category = "HuaweiAds Category")
    static void showInterstitialAd();

    UFUNCTION(BlueprintCallable, Category = "HuaweiAds Category")
    static void loadRewardAd(
        const FString adId,
        const FOnRewardAdFailedToLoad &onRewardAdFailedToLoad,
        const FOnRewardedLoaded &onRewardedLoaded,
        const FOnRewardAdClosed &onRewardAdClosed,
        const FOnRewardAdFailedToShow &onRewardAdFailedToShow,
        const FOnRewardAdOpened &onRewardAdOpened,
        const FOnRewarded &onRewarded);

    UFUNCTION(BlueprintCallable, Category = "HuaweiAds Category")
    static void showRewardAd();

    virtual void onBannerAdClosed() override;
    virtual void onBannerAdFailed(int errorCode) override;
    virtual void onBannerAdLeftApp() override;
    virtual void onBannerAdOpened() override;
    virtual void onBannerAdLoaded() override;
    virtual void onBannerAdClicked() override;
    virtual void onBannerAdImpression() override;
    virtual void onInterstitialAdClosed() override;
    virtual void onInterstitialAdFailed(int errorCode) override;
    virtual void onInterstitialAdLeftApp() override;
    virtual void onInterstitialAdOpened() override;
    virtual void onInterstitialAdLoaded() override;
    virtual void onInterstitialAdClicked() override;
    virtual void onInterstitialAdImpression() override;
    virtual void onRewardAdFailedToLoad(int errorCode) override;
    virtual void onRewardedLoaded() override;
    virtual void onRewardAdClosed() override;
    virtual void onRewardAdFailedToShow(int errorCode) override;
    virtual void onRewardAdOpened() override;
    virtual void onRewarded(const FString type, int amount) override;
};
