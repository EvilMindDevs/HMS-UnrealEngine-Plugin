#include "AdsJniWrapper.h"
#include "HuaweiAdsModule.h"
#include "Ads.h"
#include "Async/AsyncWork.h"

using namespace std;

DEFINE_LOG_CATEGORY(HuaweiAds_Native);

#if PLATFORM_ANDROID

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"

// Initialize JNI context
#define INIT_JAVA_METHOD(name, signature) \
if (JNIEnv *Env = FAndroidApplication::GetJavaEnv()) \
{ \
    name = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, #name, signature, false); \
    check(name != NULL); \
} \
else \
{ \
    check(0); \
} \

#define DECLARE_JAVA_METHOD(name) \
static jmethodID name = NULL;

inline FString jstring2FString(JNIEnv *env, jstring jstr)
{
    if (jstr == nullptr || !env)
    {
        return "";
    }

    const char *chars = env->GetStringUTFChars(jstr, nullptr);
    FString ret = FString(UTF8_TO_TCHAR(chars));
    env->ReleaseStringUTFChars(jstr, chars);

    return ret;
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBannerAdClosed(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onBannerAdClosed(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBannerAdFailed(JNIEnv *env, jobject thiz, int errorCode)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onBannerAdFailed(errorCode); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBannerAdLeftApp(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onBannerAdLeftApp(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBannerAdOpened(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onBannerAdOpened(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBannerAdLoaded(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onBannerAdLoaded(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBannerAdClicked(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onBannerAdClicked(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnBannerAdImpression(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onBannerAdImpression(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnInterstitialAdClosed(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onInterstitialAdClosed(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnInterstitialAdFailed(JNIEnv *env, jobject thiz, int errorCode)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onInterstitialAdFailed(errorCode); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnInterstitialAdLeftApp(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onInterstitialAdLeftApp(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnInterstitialAdOpened(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onInterstitialAdOpened(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnInterstitialAdLoaded(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onInterstitialAdLoaded(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnInterstitialAdClicked(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onInterstitialAdClicked(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnInterstitialAdImpression(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onInterstitialAdImpression(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnRewardAdFailedToLoad(JNIEnv *env, jobject thiz, int errorCode)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onRewardAdFailedToLoad(errorCode); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnRewardedLoaded(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onRewardedLoaded(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnRewardAdClosed(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onRewardAdClosed(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnRewardAdFailedToShow(JNIEnv *env, jobject thiz, int errorCode)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onRewardAdFailedToShow(errorCode); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnRewardAdOpened(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onRewardAdOpened(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnRewarded(JNIEnv *env, jobject thiz, jstring type_, int amount)
{
    FString type = jstring2FString(env, type_);
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AdsJniWrapper::getInstance()->onRewarded(type, amount); });
}

namespace huawei
{

    DECLARE_JAVA_METHOD(HuaweiAds_LoadBannerAd);
    DECLARE_JAVA_METHOD(HuaweiAds_ShowBannerAd);
    DECLARE_JAVA_METHOD(HuaweiAds_HideBannerAd);
    DECLARE_JAVA_METHOD(HuaweiAds_DestroyBannerAd);
    DECLARE_JAVA_METHOD(HuaweiAds_LoadInterstitialAd);
    DECLARE_JAVA_METHOD(HuaweiAds_ShowInterstitialAd);
    DECLARE_JAVA_METHOD(HuaweiAds_LoadRewardAd);
    DECLARE_JAVA_METHOD(HuaweiAds_ShowRewardAd);

    static AdsJniWrapper *s_instance = nullptr;

    AdsJniWrapper *AdsJniWrapper::getInstance()
    {
        if (!s_instance)
        {
            s_instance = new AdsJniWrapper();
        }

        return s_instance;
    }

    AdsJniWrapper::AdsJniWrapper()
    {
        _listener = nullptr;

        INIT_JAVA_METHOD(HuaweiAds_LoadBannerAd, "(Ljava/lang/String;ILjava/lang/String;)V");
        INIT_JAVA_METHOD(HuaweiAds_ShowBannerAd, "()V");
        INIT_JAVA_METHOD(HuaweiAds_HideBannerAd, "()V");
        INIT_JAVA_METHOD(HuaweiAds_DestroyBannerAd, "()V");
        INIT_JAVA_METHOD(HuaweiAds_LoadInterstitialAd, "(Ljava/lang/String;)V");
        INIT_JAVA_METHOD(HuaweiAds_ShowInterstitialAd, "()V");
        INIT_JAVA_METHOD(HuaweiAds_LoadRewardAd, "(Ljava/lang/String;)V");
        INIT_JAVA_METHOD(HuaweiAds_ShowRewardAd, "()V")
    }

    AdsJniWrapper::~AdsJniWrapper()
    {
    }

    void AdsJniWrapper::loadBannerAd(string adId, int position, string size)
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            jstring adIdJstr = Env->NewStringUTF(adId.c_str());
            jstring sizeJstr = Env->NewStringUTF(size.c_str());
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAds_LoadBannerAd, adIdJstr, position, sizeJstr);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAds_LoadBannerAd\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could not get Java ENV\n"));
        }
    }

    void AdsJniWrapper::showBannerAd()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAds_ShowBannerAd);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAds_ShowBannerAd\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could not get Java ENV\n"));
        }
    }

    void AdsJniWrapper::hideBannerAd()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAds_HideBannerAd);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAds_HideBannerAd\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could not get Java ENV\n"));
        }
    }

    void AdsJniWrapper::destroyBannerAd()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAds_DestroyBannerAd);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAds_DestroyBannerAd\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could not get Java ENV\n"));
        }
    }

    void AdsJniWrapper::loadInterstitialAd(string adId)
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            jstring adIdJstr = Env->NewStringUTF(adId.c_str());
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAds_LoadInterstitialAd, adIdJstr);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAds_LoadInterstitialAd\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could not get Java ENV\n"));
        }
    }

    void AdsJniWrapper::showInterstitialAd()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAds_ShowInterstitialAd);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAds_ShowInterstitialAd\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could not get Java ENV\n"));
        }
    }

    void AdsJniWrapper::loadRewardAd(string adId)
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            jstring adIdJstr = Env->NewStringUTF(adId.c_str());
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAds_LoadRewardAd, adIdJstr);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAds_LoadRewardAd\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could not get Java ENV\n"));
        }
    }

    void AdsJniWrapper::showRewardAd()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAds_ShowRewardAd);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAds_ShowRewardAd\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could not get Java ENV\n"));
        }
    }

    /********************************************
     * Listener
     ********************************************/

    void AdsJniWrapper::setListener(AdsListener *listener)
    {
        _listener = listener;
    }

    void AdsJniWrapper::removeListener()
    {
        _listener = nullptr;
    }

    AdsListener *AdsJniWrapper::getListener()
    {
        return _listener;
    }

    /********************************************
     * Callbacks
     ********************************************/

    void AdsJniWrapper::onBannerAdClosed()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Banner ad is closed"));
        if (_listener != nullptr)
        {
            _listener->onBannerAdClosed();
        }
    }

    void AdsJniWrapper::onBannerAdFailed(int errorCode)
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Failed to load banner ad with error code: %d"), errorCode);
        if (_listener != nullptr)
        {
            _listener->onBannerAdFailed(errorCode);
        }
    }

    void AdsJniWrapper::onBannerAdLeftApp()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Banner ad left app"));
        if (_listener != nullptr)
        {
            _listener->onBannerAdLeftApp();
        }
    }

    void AdsJniWrapper::onBannerAdOpened()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Opened banner ad"));
        if (_listener != nullptr)
        {
            _listener->onBannerAdOpened();
        }
    }

    void AdsJniWrapper::onBannerAdLoaded()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Loaded banner ad"));
        if (_listener != nullptr)
        {
            _listener->onBannerAdLoaded();
        }
    }

    void AdsJniWrapper::onBannerAdClicked()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Clicked on banner ad"));
        if (_listener != nullptr)
        {
            _listener->onBannerAdClicked();
        }
    }

    void AdsJniWrapper::onBannerAdImpression()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Impression banner ad"));
        if (_listener != nullptr)
        {
            _listener->onBannerAdImpression();
        }
    }

    void AdsJniWrapper::onInterstitialAdClosed()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Closed interstitial ad"));
        if (_listener != nullptr)
        {
            _listener->onInterstitialAdClosed();
        }
    }

    void AdsJniWrapper::onInterstitialAdFailed(int errorCode)
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Failed to load intertitial ad with error code: %d"), errorCode);
        if (_listener != nullptr)
        {
            _listener->onInterstitialAdFailed(errorCode);
        }
    }


    void AdsJniWrapper::onInterstitialAdLeftApp()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Interstitial ad left app"));
        if (_listener != nullptr)
        {
            _listener->onInterstitialAdLeftApp();
        }
    }

    void AdsJniWrapper::onInterstitialAdOpened()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Opened interstitial ad"));
        if (_listener != nullptr)
        {
            _listener->onInterstitialAdOpened();
        }
    }

    void AdsJniWrapper::onInterstitialAdLoaded()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Loaded intersitial ad"));
        if (_listener != nullptr)
        {
            _listener->onInterstitialAdLoaded();
        }
    }

    void AdsJniWrapper::onInterstitialAdClicked()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Clicked on interstitial ad"));
        if (_listener != nullptr)
        {
            _listener->onInterstitialAdClicked();
        }
    }

    void AdsJniWrapper::onInterstitialAdImpression()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Impression interstitial ad"));
        if (_listener != nullptr)
        {
            _listener->onInterstitialAdImpression();
        }
    }

    void AdsJniWrapper::onRewardAdFailedToLoad(int errorCode)
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Failed to load reward ad with error code: %d"), errorCode);
        if (_listener != nullptr)
        {
            _listener->onRewardAdFailedToLoad(errorCode);
        }
    }

    void AdsJniWrapper::onRewardedLoaded()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Loaded reward ad"));
        if (_listener != nullptr)
        {
            _listener->onRewardedLoaded();
        }
    }

    void AdsJniWrapper::onRewardAdClosed()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Closed reward ad"));
        if (_listener != nullptr)
        {
            _listener->onRewardAdClosed();
        }
    }

    void AdsJniWrapper::onRewardAdFailedToShow(int errorCode)
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Failed to show reward ad with error code: %d"), errorCode);
        if (_listener != nullptr)
        {
            _listener->onRewardAdFailedToShow(errorCode);
        }
    }

    void AdsJniWrapper::onRewardAdOpened()
    {
        UE_LOG(HuaweiAds_Native, Log, TEXT("Opened reward ad"));
        if (_listener != nullptr)
        {
            _listener->onRewardAdOpened();
        }
    }

    void AdsJniWrapper::onRewarded(const FString type, int amount)
    {
        if (_listener != nullptr)
        {
            _listener->onRewarded(type, amount);
        }
    }

}

#else

// Stub function for other platforms
namespace huawei
{

    static AdsJniWrapper *s_instance = nullptr;

    AdsJniWrapper *AdsJniWrapper::getInstance()
    {
        if (!s_instance)
        {
            s_instance = new AdsJniWrapper();
        }

        return s_instance;
    }

    AdsJniWrapper::AdsJniWrapper()
    {
        _listener = nullptr;
    }

    AdsJniWrapper::~AdsJniWrapper()
    {
    }

    void AdsJniWrapper::loadBannerAd(string adId, int position, string size)
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::showBannerAd()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::hideBannerAd()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::destroyBannerAd()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::loadInterstitialAd(string adId)
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::showInterstitialAd()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::loadRewardAd(string adId)
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::showRewardAd()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    /********************************************
     * Listener
     ********************************************/

    void AdsJniWrapper::setListener(AdsListener *listener)
    {
        _listener = listener;
    }

    void AdsJniWrapper::removeListener()
    {
        _listener = nullptr;
    }

    AdsListener *AdsJniWrapper::getListener()
    {
        return _listener;
    }

    /********************************************
     * Callbacks
     ********************************************/

    void AdsJniWrapper::onBannerAdClosed()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onBannerAdFailed(int errorCode)
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onBannerAdLeftApp()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onBannerAdOpened()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onBannerAdLoaded()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onBannerAdClicked()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onBannerAdImpression()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onInterstitialAdClosed()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onInterstitialAdFailed(int errorCode)
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onInterstitialAdLeftApp()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onInterstitialAdOpened()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onInterstitialAdLoaded()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onInterstitialAdClicked()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onInterstitialAdImpression()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onRewardAdFailedToLoad(int errorCode)
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onRewardedLoaded()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onRewardAdClosed()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onRewardAdFailedToShow(int errorCode)
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onRewardAdOpened()
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }

    void AdsJniWrapper::onRewarded(const FString type, int amount)
    {
        UE_LOG(HuaweiAds_Native, Warning, TEXT("Huawei Ads is not supported on this platform\n"));
    }
}

#endif
