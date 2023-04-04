#include "PushJniWrapper.h"
#include "HuaweiPushModule.h"
#include "Async/AsyncWork.h"
#include "push.h"

using namespace std;
DEFINE_LOG_CATEGORY(HuaweiPushPlugin_Native);

#if PLATFORM_ANDROID

#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"

// Initialize JNI context
#define INIT_JAVA_METHOD(name, signature)                                                                 \
	if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())                                                  \
	{                                                                                                     \
		name = FJavaWrapper::FindMethod(Env, FJavaWrapper::GameActivityClassID, #name, signature, false); \
		check(name != NULL);                                                                              \
	}                                                                                                     \
	else                                                                                                  \
	{                                                                                                     \
		check(0);                                                                                         \
	}

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

void checkJavaObject(JNIEnv *env, void *p, const char *desc)
{
	FString str = desc;
	if (!p)
	{
		jthrowable exc = env->ExceptionOccurred();
		if (exc)
		{
			env->ExceptionDescribe();
			env->ExceptionClear();
		}

		UE_LOG(LogAndroid, Error, TEXT("Failed to reference %s"), *str);
	}
	else
	{
		UE_LOG(LogAndroid, Log, TEXT("%s sucessfully referenced"), *str);
	}
}

extern "C"
{
	void Java_com_huawei_plugin_push_HuaweiPushPlugin_nativeOnGetTokenSuccess(JNIEnv *env, jobject thiz, jstring data_)
	{
		FString token = jstring2FString(env, data_);
		AsyncTask(ENamedThreads::GameThread, [=]()
				  { huawei::PushJniWrapper::getInstance()->onGetTokenSuccess(token); });
	}

	void Java_com_huawei_plugin_push_HuaweiPushPlugin_nativeOnSubscribeSuccess(JNIEnv *env, jobject thiz)
	{
		AsyncTask(ENamedThreads::GameThread, [=]()
				  { huawei::PushJniWrapper::getInstance()->onSubscribeSuccess(); });
	}

	void Java_com_huawei_plugin_push_HuaweiPushPlugin_nativeOnUnSubscribeSuccess(JNIEnv *env, jobject thiz)
	{
		AsyncTask(ENamedThreads::GameThread, [=]()
				  { huawei::PushJniWrapper::getInstance()->onUnSubscribeSuccess(); });
	}

	void Java_com_huawei_plugin_push_HuaweiPushPlugin_nativeOnDeleteTokenSuccess(JNIEnv *env, jobject thiz)
	{
		AsyncTask(ENamedThreads::GameThread, [=]()
				  { huawei::PushJniWrapper::getInstance()->onDeleteTokenSuccess(); });
	}

	void Java_com_huawei_plugin_push_HuaweiPushPlugin_nativeOnException(JNIEnv *env, jobject thiz, int error, int action, jstring message_)
	{
		FString message = jstring2FString(env, message_);
		AsyncTask(ENamedThreads::GameThread, [=]()
				  { huawei::PushJniWrapper::getInstance()->onException(error, action, message); });
	}

	void Java_com_huawei_plugin_push_HuaweiPushPlugin_nativeOnNewToken(JNIEnv *env, jobject thiz, jstring data_)
	{
		FString token = jstring2FString(env, data_);
		AsyncTask(ENamedThreads::GameThread, [=]()
				  { huawei::PushJniWrapper::getInstance()->onNewToken(token); });
	}

	void Java_com_huawei_plugin_push_HuaweiPushPlugin_nativeOnMessageReceived(JNIEnv *env, jobject thiz, jstring data_)
	{
		FString data = jstring2FString(env, data_);
		AsyncTask(ENamedThreads::GameThread, [=]()
				  { huawei::PushJniWrapper::getInstance()->onMessageReceived(data); });
	}
}

namespace huawei
{

	DECLARE_JAVA_METHOD(HuaweiPush_Get_Token);
	DECLARE_JAVA_METHOD(HuaweiPush_Delete_Token);
	DECLARE_JAVA_METHOD(HuaweiPush_Set_Auto_Init_Enabled);
	DECLARE_JAVA_METHOD(HuaweiPush_Subscribe);
	DECLARE_JAVA_METHOD(HuaweiPush_Unsubscribe);

	static PushJniWrapper *s_instance = nullptr;

	PushJniWrapper *PushJniWrapper::getInstance()
	{
		if (!s_instance)
		{
			s_instance = new PushJniWrapper();
		}

		return s_instance;
	}

	PushJniWrapper::PushJniWrapper()
	{
		_listener = nullptr;

		INIT_JAVA_METHOD(HuaweiPush_Get_Token, "()V");
		INIT_JAVA_METHOD(HuaweiPush_Delete_Token, "()V");
		INIT_JAVA_METHOD(HuaweiPush_Subscribe, "(Ljava/lang/String;)V");
		INIT_JAVA_METHOD(HuaweiPush_Unsubscribe, "(Ljava/lang/String;)V");
		INIT_JAVA_METHOD(HuaweiPush_Set_Auto_Init_Enabled, "(Z)V");

		if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
		{
			jclass pluginClass = FAndroidApplication::FindJavaClass("com/huawei/plugin/push/HuaweiPushPlugin");
			checkJavaObject(Env, pluginClass, "com/huawei/plugin/push/HuaweiPushPlugin");

			jmethodID androidThunkJava_getInstance = FJavaWrapper::FindStaticMethod(Env, pluginClass, "getInstance", "()Lcom/huawei/plugin/push/HuaweiPushPlugin;", false);
			androidThunkJava_Init = FJavaWrapper::FindMethod(Env, pluginClass, "init", "()V", false);
			jobject localPluginObject = Env->CallStaticObjectMethod(pluginClass, androidThunkJava_getInstance);
			checkJavaObject(Env, localPluginObject, "HuaweiPushPlugin instance");

			pluginObject = Env->NewGlobalRef(localPluginObject);
			Env->DeleteLocalRef(localPluginObject);

			UE_LOG(LogAndroid, Log, TEXT("Java interface initialized"));
		}
		else
		{
			UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
		}
	}

	PushJniWrapper::~PushJniWrapper()
	{
	}

	void PushJniWrapper::init()
	{
		if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
		{
			FJavaWrapper::CallVoidMethod(Env, pluginObject, androidThunkJava_Init);
		}
		else
		{
			UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
		}
	}

	void PushJniWrapper::getToken()
	{
		if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
		{
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiPush_Get_Token);
			UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiPush_Get_Token\n"));
		}
		else
		{
			UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
		}
	}

	void PushJniWrapper::deleteToken()
	{
		if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
		{
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiPush_Delete_Token);
			UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiPush_Delete_Token\n"));
		}
		else
		{
			UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
		}
	}

	void PushJniWrapper::setAutoInitEnabled(bool isEnable)
	{
		if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
		{
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiPush_Set_Auto_Init_Enabled, isEnable);
			UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiPush_Set_Auto_Init_Enabled\n"));
		}
		else
		{
			UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
		}
	}

	void PushJniWrapper::subscribe(const string topic)
	{
		if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
		{
			jstring topic0 = Env->NewStringUTF(topic.c_str());
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiPush_Subscribe, topic0);
			Env->DeleteLocalRef(topic0);
			UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiPush_Subscribe\n"));
		}
		else
		{
			UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
		}
	}

	void PushJniWrapper::unSubscribe(const string topic)
	{
		if (JNIEnv *Env = FAndroidApplication::GetJavaEnv())
		{
			jstring topic0 = Env->NewStringUTF(topic.c_str());
			FJavaWrapper::CallVoidMethod(Env, FJavaWrapper::GameActivityThis, HuaweiPush_Unsubscribe, topic0);
			Env->DeleteLocalRef(topic0);
			UE_LOG(LogAndroid, Warning, TEXT("I found the java method HuaweiPush_Unsubscribe\n"));
		}
		else
		{
			UE_LOG(LogAndroid, Warning, TEXT("ERROR Could note get Java ENV\n"));
		}
	}

	/********************************************
	 * Listener
	 ********************************************/

	void PushJniWrapper::setListener(PushListener *listener)
	{
		_listener = listener;
	}

	void PushJniWrapper::removeListener()
	{
		_listener = nullptr;
	}

	PushListener *PushJniWrapper::getListener()
	{
		return _listener;
	}

	/********************************************
	 * Callbacks
	 ********************************************/

	void PushJniWrapper::onSubscribeSuccess()
	{
		UE_LOG(HuaweiPushPlugin_Native, Log, TEXT("Subscribe Success"));
		if (_listener != nullptr)
		{
			_listener->onSubscribeSuccess();
		}
	}

	void PushJniWrapper::onDeleteTokenSuccess()
	{
		UE_LOG(HuaweiPushPlugin_Native, Log, TEXT("Delete Token Success"));
		if (_listener != nullptr)
		{
			_listener->onDeleteTokenSuccess();
		}
	}

	void PushJniWrapper::onUnSubscribeSuccess()
	{
		UE_LOG(HuaweiPushPlugin_Native, Log, TEXT("unSubscribe Success success"));
		if (_listener != nullptr)
		{
			_listener->onUnSubscribeSuccess();
		}
	}

	void PushJniWrapper::onException(int errorcode, int action, const FString message)
	{
		if (_listener != nullptr)
		{
			_listener->onException(errorcode, action, message);
		}
	}

	void PushJniWrapper::onGetTokenSuccess(const FString token)
	{
		if (_listener != nullptr)
		{
			_listener->onGetTokenSuccess(token);
		}
	}

	void PushJniWrapper::onNewToken(const FString token)
	{
		if (_listener != nullptr)
		{
			_listener->onNewToken(token);
		}
	}

	void PushJniWrapper::onMessageReceived(const FString messageJson)
	{
		if (_listener != nullptr)
		{
			_listener->onMessageReceived(messageJson);
		}
	}

}

#else

// Stub function for other platforms
namespace huawei
{

	static PushJniWrapper *s_instance = nullptr;

	PushJniWrapper *PushJniWrapper::getInstance()
	{
		if (!s_instance)
		{
			s_instance = new PushJniWrapper();
		}

		return s_instance;
	}

	PushJniWrapper::PushJniWrapper()
	{
		_listener = nullptr;
	}

	PushJniWrapper::~PushJniWrapper()
	{
	}

	void PushJniWrapper::init()
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	void PushJniWrapper::getToken()
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	void PushJniWrapper::deleteToken()
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	void PushJniWrapper::setAutoInitEnabled(bool isEnable)
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	void PushJniWrapper::subscribe(const string topic)
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	void PushJniWrapper::unSubscribe(const string topic)
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	/********************************************
	 * Listener
	 ********************************************/

	void PushJniWrapper::setListener(PushListener *listener)
	{
		_listener = listener;
	}

	void PushJniWrapper::removeListener()
	{
		_listener = nullptr;
	}

	PushListener *PushJniWrapper::getListener()
	{
		return _listener;
	}

	/********************************************
	 * Callbacks
	 ********************************************/

	void PushJniWrapper::onGetTokenSuccess(const FString token)
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	void PushJniWrapper::onException(int errorcode, int action, const FString message)
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	void PushJniWrapper::onNewToken(const FString token)
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	void PushJniWrapper::onMessageReceived(const FString messageJson)
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	void PushJniWrapper::onSubscribeSuccess()
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	void PushJniWrapper::onUnSubscribeSuccess()
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}

	void PushJniWrapper::onDeleteTokenSuccess()
	{
		UE_LOG(HuaweiPushPlugin_Native, Warning, TEXT("Huawei Push is not supported on this platform\n"));
	}
}

#endif
