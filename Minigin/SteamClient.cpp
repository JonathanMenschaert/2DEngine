#include "SteamClient.h"
#include "isteamuserstats.h"



void dae::SteamClient::ResetAchievements()
{
	for (auto& achievement : m_Achievements)
	{
		auto pUserStats{ SteamUserStats() };
		pUserStats->ClearAchievement(achievement.second.m_ApiName.c_str());
	}
}

void dae::SteamClient::ResetAchievement(AchievementId id)
{
	auto pUserStats{ SteamUserStats() };
	pUserStats->ClearAchievement(m_Achievements[id].m_ApiName.c_str());
}

void dae::SteamClient::SetAchievements(const std::unordered_map<AchievementId, Achievement>& achievements)
{
	m_Achievements = achievements;
}

void dae::SteamClient::UnlockAchievement(AchievementId Id)
{
	auto pUserStats{ SteamUserStats() };
	pUserStats->SetAchievement(m_Achievements[Id].m_ApiName.c_str());
	pUserStats->StoreStats();
}
