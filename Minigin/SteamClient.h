#pragma once
#include "Singleton.h"
#include <unordered_map>
#include "Achievement.h"
namespace dae
{
	class SteamClient : public Singleton<SteamClient>
	{
	public:
		SteamClient() = default;
		~SteamClient() = default;
		SteamClient(const SteamClient& other) = delete;
		SteamClient(SteamClient&& other) noexcept = delete;
		SteamClient& operator=(const SteamClient& other) = delete;
		SteamClient& operator=(SteamClient&& other) noexcept = delete;

		void ResetAchievements();
		void ResetAchievement(AchievementId id);
		void SetAchievements(const std::unordered_map<AchievementId, Achievement>& achievements);
		void UnlockAchievement(AchievementId Id);

	private:
		std::unordered_map<AchievementId, Achievement> m_Achievements;
	};
}

