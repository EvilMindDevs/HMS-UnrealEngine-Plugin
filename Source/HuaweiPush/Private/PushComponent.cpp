#include "PushComponent.h"

using namespace std;
using namespace huawei;

UPushComponent::UPushComponent()
{
    bWantsInitializeComponent = true;
}

void UPushComponent::InitializeComponent()
{
    Super::InitializeComponent();
    Push::setListener(this);
}

void UPushComponent::init()
{
    Push::init();
}

void UPushComponent::getToken()
{
	Push::getToken();
}

void UPushComponent::deleteToken()
{
	Push::deleteToken();
}

void UPushComponent::setAutoInitEnabled(bool isEnable)
{
	Push::setAutoInitEnabled(isEnable);
}

void UPushComponent::subscribe(FString topic)
{
	Push::subscribe(topic);
}

void UPushComponent::unSubscribe(FString topic)
{
	Push::unSubscribe(topic);
}

void UPushComponent::onException(int errorcode, int action, const FString message)
{
	switch (action)
	{
	case UN_SUBSCRIBE_FAILED:
		onUnSubscribeExceptionEvent.Broadcast(message);
		break;
	case SUBSCRIBE_FAILED:
		onSubscribeExceptionEvent.Broadcast(message);
		break;
	case DELETE_TOKEN_FAILED:
		onDeleteTokenExceptionEvent.Broadcast(message);
		break;
	case GET_TOKEN_FAILED:
		onGetTokenExceptionEvent.Broadcast(message);
		break;
	case ON_MESSAGE_RECEIVED:
		onMessageReceivedExceptionEvent.Broadcast(message);
	default:
		break;
	}
}

void UPushComponent::onSubscribeSuccess()
{
	onSubscribeSuccessEvent.Broadcast();
}

void UPushComponent::onUnSubscribeSuccess()
{
	onUnSubscribeSuccessEvent.Broadcast();
}

void UPushComponent::onDeleteTokenSuccess()
{
	onDeleteTokenSuccessEvent.Broadcast();
}

void UPushComponent::onGetTokenSuccess(const FString token)
{
	onGetTokenSuccessEvent.Broadcast(token);
}

void UPushComponent::onNewToken(const FString token)
{
	onNewTokenEvent.Broadcast(token);
}

void UPushComponent::onMessageReceived(const FString messageJson)
{
	onMessageReceivedEvent.Broadcast(messageJson);
}