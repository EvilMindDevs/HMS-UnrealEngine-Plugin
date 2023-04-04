#include "push.h"
#include "HuaweiPushModule.h"
#include "PushJniWrapper.h"

namespace huawei
{
	void Push::init()
	{
		PushJniWrapper::getInstance()->init();
	}

	void Push::getToken()
	{
		PushJniWrapper::getInstance()->getToken();
	}

	void Push::deleteToken()
	{
		PushJniWrapper::getInstance()->deleteToken();
	}

	void Push::setAutoInitEnabled(bool isEnable)
	{
		PushJniWrapper::getInstance()->setAutoInitEnabled(isEnable);
	}

	void Push::subscribe(const FString topic)
	{
		PushJniWrapper::getInstance()->subscribe(TCHAR_TO_UTF8(*topic));
	}

	void Push::unSubscribe(const FString topic)
	{
		PushJniWrapper::getInstance()->unSubscribe(TCHAR_TO_UTF8(*topic));
	}

	void Push::setListener(PushListener *listener)
	{
		PushJniWrapper::getInstance()->setListener(listener);
	}

	void Push::removeListener()
	{
		PushJniWrapper::getInstance()->removeListener();
	}

	PushListener *Push::getListener()
	{
		return PushJniWrapper::getInstance()->getListener();
	}
}