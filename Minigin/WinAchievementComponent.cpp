#include "WinAchievementComponent.h"
#include "SteamClient.h"
dae::WinAchievementComponent::WinAchievementComponent(std::shared_ptr<GameObject> pGameObject)
	:BaseComponent(pGameObject)
	,m_WinScore{500}
{
}
void dae::WinAchievementComponent::Notify(const Event<int>& e)
{
	if (e.GetPayload() >= m_WinScore)
	{
		SteamClient::GetInstance().UnlockAchievement(AchievementId::ACH_WIN_ONE_GAME);
	}
}
