#pragma once
#include "push.h"
#include <string>

#if PLATFORM_ANDROID
#include "Android/AndroidApplication.h"
#include "Android/AndroidJNI.h"
#include "Android/AndroidJava.h"
#endif

DECLARE_LOG_CATEGORY_EXTERN(HuaweiPushPlugin_Native, Log, All);
using namespace std;

namespace huawei
{

	class PushJniWrapper
	{

	public:
		static PushJniWrapper *getInstance();

		PushJniWrapper();
		~PushJniWrapper();

		void init();
		void getToken();
		void deleteToken();
		void setAutoInitEnabled(bool isEnable);
		void subscribe(const string topic);
		void unSubscribe(const string topic);

		// Listener
		void setListener(PushListener *listener);
		void removeListener();
		PushListener *getListener();

		// Callbacks
		void onGetTokenSuccess(const FString token);
		void onDeleteTokenSuccess();
		void onNewToken(const FString token);
		void onMessageReceived(const FString messageJson);
		void onSubscribeSuccess();
		void onUnSubscribeSuccess();
		void onException(int errorcode, int action, const FString message);

	protected:
		PushListener *_listener;
		#if PLATFORM_ANDROID
		jobject pluginObject;
		jmethodID androidThunkJava_Init;
		#endif
	};
}
