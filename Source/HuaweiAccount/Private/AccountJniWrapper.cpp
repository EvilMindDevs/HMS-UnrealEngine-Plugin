#include "AccountJniWrapper.h"
#include "HuaweiAccountModule.h"
#include "json98.h"
#include "Account.h"
#include "Async/AsyncWork.h"

using namespace std;
using namespace json;

DEFINE_LOG_CATEGORY(HuaweiAccount_Native);

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

inline string jstring2string(JNIEnv *env, jstring jstr)
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

AccountInfo convertFromJsonString(const string data)
{
    auto jsonData = Json::parse(data);
    return AccountInfo(jsonData);
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnLoggedIn(JNIEnv *env, jobject thiz, jstring data_)
{
    string data = jstring2string(env, data_);
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AccountJniWrapper::getInstance()->onLoggedIn(data); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnGetIdToken(JNIEnv *env, jobject thiz, jstring token_, jstring data_)
{
    FString token = jstring2FString(env, token_);
    string data = jstring2string(env, data_);
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AccountJniWrapper::getInstance()->onGetIdToken(token, data); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnGetAuthCode(JNIEnv *env, jobject thiz, jstring code_, jstring data_)
{
    FString code = jstring2FString(env, code_);
    string data = jstring2string(env, data_);
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AccountJniWrapper::getInstance()->onGetAuthCode(code, data); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnLoggedOut(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AccountJniWrapper::getInstance()->onLoggedOut(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnCancelledAuth(JNIEnv *env, jobject thiz)
{
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AccountJniWrapper::getInstance()->onCancelledAuth(); });
}

extern "C" void Java_com_epicgames_ue4_GameActivity_nativeOnAccountException(JNIEnv *env, jobject thiz, int action, jstring message_)
{
    FString message = jstring2FString(env, message_);
    AsyncTask(ENamedThreads::GameThread, [=]()
              { huawei::AccountJniWrapper::getInstance()->onException(action, message); });
}

namespace huawei
{

    DECLARE_JAVA_METHOD(HuaweiAccount_Login_Without_Verification);
    DECLARE_JAVA_METHOD(HuaweiAccount_Login_With_Id_Token);
    DECLARE_JAVA_METHOD(HuaweiAccount_Login_With_Authorization_Code);
    DECLARE_JAVA_METHOD(HuaweiAccount_Logout);
    DECLARE_JAVA_METHOD(HuaweiAccount_CancelAuthorization);

    static AccountJniWrapper *s_instance = nullptr;

    AccountJniWrapper *AccountJniWrapper::getInstance()
    {
        if (!s_instance)
        {
            s_instance = new AccountJniWrapper();
        }

        return s_instance;
    }

    AccountJniWrapper::AccountJniWrapper()
    {
        _listener = nullptr;

        INIT_JAVA_METHOD(HuaweiAccount_Login_Without_Verification, "()V");
        INIT_JAVA_METHOD(HuaweiAccount_Login_With_Id_Token, "()V");
        INIT_JAVA_METHOD(HuaweiAccount_Login_With_Authorization_Code, "()V");
        INIT_JAVA_METHOD(HuaweiAccount_Logout, "()V");
        INIT_JAVA_METHOD(HuaweiAccount_CancelAuthorization, "()V");
    }

    AccountJniWrapper::~AccountJniWrapper()
    {
    }

    void AccountJniWrapper::loginWithoutVerification()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAccount_Login_Without_Verification);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAccount_Login_Without_Verification\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    void AccountJniWrapper::loginWithIdToken()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAccount_Login_With_Id_Token);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAccount_Login_With_Id_Token\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    void AccountJniWrapper::loginWithAuthorizationCode()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAccount_Login_With_Authorization_Code);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAccount_Login_With_Authorization_Code\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    void AccountJniWrapper::logOut()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAccount_Logout);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAccount_Logout\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    void AccountJniWrapper::cancelAuthorization()
    {
        if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
        {
            FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiAccount_CancelAuthorization);
            UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiAccount_CancelAuthorization\n"));
        }
        else
        {
            UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
        }
    }

    

    /********************************************
     * Listener
     ********************************************/

    void AccountJniWrapper::setListener(AccountListener *listener)
    {
        _listener = listener;
    }

    void AccountJniWrapper::removeListener()
    {
        _listener = nullptr;
    }

    AccountListener *AccountJniWrapper::getListener()
    {
        return _listener;
    }

    /********************************************
     * Callbacks
     ********************************************/

    void AccountJniWrapper::onLoggedIn(const string account)
    {
        UE_LOG(HuaweiAccount_Native, Log, TEXT("Log in success"));
        if (_listener != nullptr)
        {
            _listener->onLoggedIn(convertFromJsonString(account));
        }
    }

    void AccountJniWrapper::onGetIdToken(const FString idToken, const string account)
    {
        UE_LOG(HuaweiAccount_Native, Log, TEXT("Get id token success"));
        if (_listener != nullptr)
        {
            _listener->onGetIdToken(idToken, convertFromJsonString(account));
        }
    }


    void AccountJniWrapper::onGetAuthCode(const FString authCode, const string account)
    {
        UE_LOG(HuaweiAccount_Native, Log, TEXT("Get authozation code success"));
        if (_listener != nullptr)
        {
            _listener->onGetAuthCode(authCode, convertFromJsonString(account));
        }
    }

    void AccountJniWrapper::onLoggedOut()
    {
        UE_LOG(HuaweiAccount_Native, Log, TEXT("Log out success"));
        if (_listener != nullptr)
        {
            _listener->onLoggedOut();
        }
    }

    void AccountJniWrapper::onCancelledAuth()
    {
        UE_LOG(HuaweiAccount_Native, Log, TEXT("Cancel authorization success"));
        if (_listener != nullptr)
        {
            _listener->onCancelledAuth();
        }
    }


    void AccountJniWrapper::onException(int action, const FString message)
    {
        if (_listener != nullptr)
        {
            _listener->onException(action, message);
        }
    }

}

#else

// Stub function for other platforms
namespace huawei
{

    static AccountJniWrapper *s_instance = nullptr;

    AccountJniWrapper *AccountJniWrapper::getInstance()
    {
        if (!s_instance)
        {
            s_instance = new AccountJniWrapper();
        }

        return s_instance;
    }

    AccountJniWrapper::AccountJniWrapper()
    {
        _listener = nullptr;
    }

    AccountJniWrapper::~AccountJniWrapper()
    {
    }

    void AccountJniWrapper::loginWithoutVerification()
    {
        UE_LOG(HuaweiAccount_Native, Warning, TEXT("Huawei Account is not supported on this platform\n"));
    }

    void AccountJniWrapper::loginWithIdToken()
    {
        UE_LOG(HuaweiAccount_Native, Warning, TEXT("Huawei Account is not supported on this platform\n"));
    }

    void AccountJniWrapper::loginWithAuthorizationCode()
    {
        UE_LOG(HuaweiAccount_Native, Warning, TEXT("Huawei Account is not supported on this platform\n"));
    }

    void AccountJniWrapper::logOut()
    {
        UE_LOG(HuaweiAccount_Native, Warning, TEXT("Huawei Account is not supported on this platform\n"));
    }

    void AccountJniWrapper::cancelAuthorization()
    {
        UE_LOG(HuaweiAccount_Native, Warning, TEXT("Huawei Account is not supported on this platform\n"));
    }

    /********************************************
     * Listener
     ********************************************/

    void AccountJniWrapper::setListener(AccountListener *listener)
    {
        _listener = listener;
    }

    void AccountJniWrapper::removeListener()
    {
        _listener = nullptr;
    }

    AccountListener *AccountJniWrapper::getListener()
    {
        return _listener;
    }

    /********************************************
     * Callbacks
     ********************************************/

    void AccountJniWrapper::onLoggedIn(const string account)
    {
        UE_LOG(HuaweiAccount_Native, Warning, TEXT("Huawei Account is not supported on this platform\n"));
    }

    void AccountJniWrapper::onGetIdToken(const FString idToken, const string account)
    {
        UE_LOG(HuaweiAccount_Native, Warning, TEXT("Huawei Account is not supported on this platform\n"));
    }

    void AccountJniWrapper::onGetAuthCode(const FString authCode, const string account)
    {
        UE_LOG(HuaweiAccount_Native, Warning, TEXT("Huawei Account is not supported on this platform\n"));
    }

    void AccountJniWrapper::onLoggedOut()
    {
        UE_LOG(HuaweiAccount_Native, Warning, TEXT("Huawei Account is not supported on this platform\n"));
    }

    void AccountJniWrapper::onCancelledAuth()
    {
        UE_LOG(HuaweiAccount_Native, Warning, TEXT("Huawei Account is not supported on this platform\n"));
    }

    void AccountJniWrapper::onException(int action, const FString message)
    {
        UE_LOG(HuaweiAccount_Native, Warning, TEXT("Huawei Account is not supported on this platform\n"));
    }

}

#endif
