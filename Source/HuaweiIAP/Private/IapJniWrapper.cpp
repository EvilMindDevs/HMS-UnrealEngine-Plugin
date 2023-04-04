#include "IapJniWrapper.h"
#include "HuaweiIapModule.h"
#include "json98.h"
#include "Iap.h"
#include "Async/AsyncWork.h"

using namespace std;
using namespace json98;

DEFINE_LOG_CATEGORY(HuaweiIap_Native);

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

string jstring2string(JNIEnv *env, jstring jstr)
{
    if (jstr == nullptr || !env)
    {
        return "";
    }

    const char *chars = env->GetStringUTFChars(jstr, nullptr);
    string ret(chars);
    env->ReleaseStringUTFChars(jstr, chars);

    return ret;
}

FString jstring2FString(JNIEnv *env, jstring jstr)
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

template<typename T>
TArray<T> convertFromJsonString(const string data)
{
    auto jsonData = Json::parse(data);
    TArray<T> result;

    for (auto &d : jsonData.array_items())
    {
        T p(d);
        result.Add(p);
    }

    return result;
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnCheckEnvironmentSuccess(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::IapJniWrapper::getInstance()->onCheckEnvironmentSuccess(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnException(JNIEnv *env, jobject thiz, int action, jstring message_)
{
    FString message = jstring2FString(env, message_);
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::IapJniWrapper::getInstance()->onException(action, message); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnObtainProductList(JNIEnv *env, jobject thiz, jstring data_, int type)
{
    string data = jstring2string(env, data_);
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::IapJniWrapper::getInstance()->onObtainProductList(data, type); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnPurchaseSuccess(JNIEnv *env, jobject thiz, jstring data_, int type)
{
    FString data = jstring2FString(env, data_);
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::IapJniWrapper::getInstance()->onPurchaseSuccess(data, type); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnObtainPurchases(JNIEnv *env, jobject thiz, jstring purchasedData_, jstring nonPurchasedData_, int type)
{
    string purchasedData = jstring2string(env, purchasedData_);
    string nonPurchasedData = jstring2string(env, nonPurchasedData_);
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::IapJniWrapper::getInstance()->onObtainPurchases(purchasedData, nonPurchasedData, type); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnObtainPurchasedRecords(JNIEnv *env, jobject thiz, jstring data_, int type)
{
    string data = jstring2string(env, data_);
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::IapJniWrapper::getInstance()->onObtainPurchasedRecords(data, type); });
}

namespace huawei
{

    DECLARE_JAVA_METHOD(HuaweiIap_Check_Environment);
    DECLARE_JAVA_METHOD(HuaweiIap_Query_Products);
    DECLARE_JAVA_METHOD(HuaweiIap_Query_Purchases);
    DECLARE_JAVA_METHOD(HuaweiIap_Buy_Product);
    DECLARE_JAVA_METHOD(HuaweiIAP_Get_PurchaseRecords);
    DECLARE_JAVA_METHOD(HuaweiIap_ManageSubscriptions);
    DECLARE_JAVA_METHOD(HuaweiIap_ShowSubscription);

    static IapJniWrapper *s_instance = nullptr;

    IapJniWrapper *IapJniWrapper::getInstance()
    {
        if (!s_instance)
        {
            s_instance = new IapJniWrapper();
        }

        return s_instance;
    }

    IapJniWrapper::IapJniWrapper()
    {
        _listener = nullptr;

        INIT_JAVA_METHOD(HuaweiIap_Check_Environment, "()V");
        INIT_JAVA_METHOD(HuaweiIap_Query_Products, "([Ljava/lang/String;I)V");
        INIT_JAVA_METHOD(HuaweiIap_Query_Purchases, "(I)V");
        INIT_JAVA_METHOD(HuaweiIap_Buy_Product, "(Ljava/lang/String;I)V");
        INIT_JAVA_METHOD(HuaweiIAP_Get_PurchaseRecords, "(I)V");
        INIT_JAVA_METHOD(HuaweiIap_ManageSubscriptions, "()V");
        INIT_JAVA_METHOD(HuaweiIap_ShowSubscription, "(Ljava/lang/String;)V");
    }

    IapJniWrapper::~IapJniWrapper()
    {
    }

    void IapJniWrapper::checkEnvironment()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiIap_Check_Environment);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiIap_Check_Environment\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    void IapJniWrapper::queryProducts(const vector<string> productIds, int type)
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            int size = productIds.size();
            jobjectArray ids = (jobjectArray) Env->NewObjectArray(size, FJavaWrapper::JavaStringClass, nullptr);
            for (int i = 0; i < size; i++)
            {
                Env->SetObjectArrayElement(ids, i, Env->NewStringUTF(productIds[i].c_str()));
            }
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiIap_Query_Products, ids, type);
            Env->DeleteLocalRef(ids);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiIap_Query_Products\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    void IapJniWrapper::queryPurchases(int type)
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiIap_Query_Purchases, type);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiIap_Query_Purchases\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    void IapJniWrapper::buyProduct(const string productId, int type)
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            jstring id = Env->NewStringUTF(productId.c_str());
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiIap_Buy_Product, id, type);
            Env->DeleteLocalRef(id);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiIap_Buy_Product\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    void IapJniWrapper::getPurchasedRecords(int type)
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiIAP_Get_PurchaseRecords, type);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiIAP_Get_PurchaseRecords\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    void IapJniWrapper::showSubscription(const string productId)
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            jstring id = Env->NewStringUTF(productId.c_str());
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiIap_ShowSubscription, id);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiIap_manageSubscriptions\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    void IapJniWrapper::manageSubscriptions()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiIap_ManageSubscriptions);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiIap_manageSubscriptions\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    /********************************************
     * Listener
     ********************************************/

    void IapJniWrapper::setListener(IapListener *listener)
    {
        _listener = listener;
    }

    void IapJniWrapper::removeListener()
    {
        _listener = nullptr;
    }

    IapListener *IapJniWrapper::getListener()
    {
        return _listener;
    }

    /********************************************
     * Callbacks
     ********************************************/

    void IapJniWrapper::onCheckEnvironmentSuccess()
    {
        UE_LOG(HuaweiIap_Native, Log, TEXT("Check environment success"));
        if (_listener != nullptr)
        {
            _listener->onCheckEnvironmentSuccess();
        }
    }

    void IapJniWrapper::onException(int action, const FString message)
    {
        if (_listener != nullptr)
        {
            _listener->onException(action, message);
        }
    }

    void IapJniWrapper::onObtainProductList(const string products, int type)
    {
        if (_listener != nullptr)
        {
            TArray<ProductInfo> productInfos = convertFromJsonString<ProductInfo>(products);
            _listener->onObtainProductList(productInfos, type);
        }
    }

    void IapJniWrapper::onPurchaseSuccess(const FString productId, int type)
    {
        if (_listener != nullptr)
        {
            _listener->onPurchaseSuccess(productId, type);
        }
    }

    void IapJniWrapper::onObtainPurchases(const string purchasedProductIds, const string nonPurchasedProductIds, int type)
    {
        if (_listener != nullptr)
        {
            TArray<InAppPurchaseData> purchasedProductDatas = convertFromJsonString<InAppPurchaseData>(purchasedProductIds);
            TArray<InAppPurchaseData> nonPurchasedProductDatas = convertFromJsonString<InAppPurchaseData>(nonPurchasedProductIds);
            _listener->onObtainPurchases(purchasedProductDatas, nonPurchasedProductDatas, type);
        }
    }

    void IapJniWrapper::onObtainPurchasedRecords(const string purchasedProductIds, int type)
    {
        if (_listener != nullptr)
        {
            TArray<InAppPurchaseData> purchasedProductDatas = convertFromJsonString<InAppPurchaseData>(purchasedProductIds);
            _listener->onObtainPurchasedRecords(purchasedProductDatas, type);
        }
    }

}

#else

// Stub function for other platforms
namespace huawei
{

    static IapJniWrapper *s_instance = nullptr;

    IapJniWrapper *IapJniWrapper::getInstance()
    {
        if (!s_instance)
        {
            s_instance = new IapJniWrapper();
        }

        return s_instance;
    }

    IapJniWrapper::IapJniWrapper()
    {
        _listener = nullptr;
    }

    IapJniWrapper::~IapJniWrapper()
    {
    }

    void IapJniWrapper::checkEnvironment()
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    void IapJniWrapper::queryProducts(const vector<string> productIds, int type)
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    void IapJniWrapper::queryPurchases(int type)
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    void IapJniWrapper::buyProduct(const string productId, int type)
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    void IapJniWrapper::getPurchasedRecords(int type)
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    void IapJniWrapper::manageSubscriptions()
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    void IapJniWrapper::showSubscription(const string productId)
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    /********************************************
     * Listener
     ********************************************/

    void IapJniWrapper::setListener(IapListener *listener)
    {
        _listener = listener;
    }

    void IapJniWrapper::removeListener()
    {
        _listener = nullptr;
    }

    IapListener *IapJniWrapper::getListener()
    {
        return _listener;
    }

    /********************************************
     * Callbacks
     ********************************************/

    void IapJniWrapper::onCheckEnvironmentSuccess()
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    void IapJniWrapper::onException(int action, const FString message)
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    void IapJniWrapper::onObtainProductList(const string products, int type)
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    void IapJniWrapper::onPurchaseSuccess(const FString productId, int type)
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    void IapJniWrapper::onObtainPurchases(const string purchasedProductIds, const string nonPurchasedProductIds, int type)
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

    void IapJniWrapper::onObtainPurchasedRecords(const string purchasedProductIds, int type)
    {
        UE_LOG(HuaweiIap_Native, Warning, TEXT("Huawei IAP is not supported on this platform\n"));
    }

}

#endif
