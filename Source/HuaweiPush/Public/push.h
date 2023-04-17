#pragma once

#include "CoreMinimal.h"
#include "Engine.h"
#include <string>

namespace huawei
{
	class PushListener
	{
	public:
		virtual void onGetTokenSuccess(const FString token) = 0;
		virtual void onDeleteTokenSuccess() = 0;
		virtual void onNewToken(const FString token) = 0;
		virtual void onMessageReceived(const FString messageJson) = 0;
		virtual void onSubscribeSuccess() = 0;
		virtual void onUnSubscribeSuccess() = 0;
		virtual void onException(int errorcode, int action, const FString message) = 0;
	};

	class HUAWEIPUSH_API Push
	{
	public:
		static void init();
		static void getToken();
		static void deleteToken();
		static void setAutoInitEnabled(bool isEnable);
		static void subscribe(const FString topic);
		static void unSubscribe(const FString topic);

		static void setListener(PushListener *listener);
		static void removeListener();
		static PushListener *getListener();
	};
}