#include "Ads.h"
#include "HuaweiAdsModule.h"
#include "AdsJniWrapper.h"

using namespace std;

namespace huawei
{
    constexpr const char* Ads::bannerSizeToString(BannerSize size)
    {
        switch (size)
        {
            case BannerSize::USER_DEFINED: return "USER_DEFINED";
            case BannerSize::BANNER_SIZE_320_50: return "BANNER_SIZE_320_50";
            case BannerSize::BANNER_SIZE_320_100: return "BANNER_SIZE_320_100";
            case BannerSize::BANNER_SIZE_468_60: return "BANNER_SIZE_468_60";
            case BannerSize::BANNER_SIZE_DYNAMIC: return "BANNER_SIZE_DYNAMIC";
            case BannerSize::BANNER_SIZE_728_90: return "BANNER_SIZE_728_90";
            case BannerSize::BANNER_SIZE_300_250: return "BANNER_SIZE_300_250";
            case BannerSize::BANNER_SIZE_SMART: return "BANNER_SIZE_SMART";
            case BannerSize::BANNER_SIZE_160_600: return "BANNER_SIZE_160_600";
            case BannerSize::BANNER_SIZE_360_57: return "BANNER_SIZE_360_57";
            case BannerSize::BANNER_SIZE_360_144: return "BANNER_SIZE_360_144";
            default: return "Invalid Size";
        }        
    }

    void Ads::loadBannerAd(FString adId, int position, BannerSize size)
    {
        AdsJniWrapper::getInstance()->loadBannerAd(TCHAR_TO_UTF8(*adId), position, bannerSizeToString(size));
    }

    void Ads::loadBannerAd(FString adId, int position, FString size)
    {
        AdsJniWrapper::getInstance()->loadBannerAd(TCHAR_TO_UTF8(*adId), position, TCHAR_TO_UTF8(*size));
    }

    void Ads::showBannerAd()
    {
        AdsJniWrapper::getInstance()->showBannerAd();
    }

    void Ads::hideBannerAd()
    {
        AdsJniWrapper::getInstance()->hideBannerAd();    
    }

    void Ads::destroyBannerAd()
    {
        AdsJniWrapper::getInstance()->destroyBannerAd();
    }

    void Ads::loadInterstitialAd(FString adId)
    {
        AdsJniWrapper::getInstance()->loadInterstitialAd(TCHAR_TO_UTF8(*adId));
    }

    void Ads::showInterstitialAd()
    {
        AdsJniWrapper::getInstance()->showInterstitialAd();
    }

    void Ads::loadRewardAd(FString adId)
    {
        AdsJniWrapper::getInstance()->loadRewardAd(TCHAR_TO_UTF8(*adId));
    }

    void Ads::showRewardAd()
    {
        AdsJniWrapper::getInstance()->showRewardAd();
    }


    void Ads::setListener(AdsListener *listener)
    {
        AdsJniWrapper::getInstance()->setListener(listener);
    }

    void Ads::removeListener()
    {
        AdsJniWrapper::getInstance()->removeListener();
    }

    AdsListener *Ads::getListener()
    {
        return AdsJniWrapper::getInstance()->getListener();
    }

}