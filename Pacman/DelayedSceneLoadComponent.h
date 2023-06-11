#include "TimerComponent.h"
#include "Observer.h"
#include "PlayerEvents.h"
#include "Subject.h"
#include "LoadSceneComponent.h"
#include <string>

namespace dae
{
	class DelayedSceneLoadComponent final : public TimerComponent, public Observer<PlayerEvent>
	{
	public:
		DelayedSceneLoadComponent(GameObject* pGameObject);
		~DelayedSceneLoadComponent() = default;
		DelayedSceneLoadComponent(const DelayedSceneLoadComponent& other) = delete;
		DelayedSceneLoadComponent(DelayedSceneLoadComponent&& other) noexcept = delete;
		DelayedSceneLoadComponent& operator=(const DelayedSceneLoadComponent& other) = delete;
		DelayedSceneLoadComponent& operator=(DelayedSceneLoadComponent&& other) noexcept = delete;

		virtual void Update() override;
		void Notify(const Event<PlayerEvent>& e) override;
		void SetScenes(const std::string& nextLevelScene, const std::string& gameOverScene);
		void Init() override;

	private:
		std::string m_NextLevelScene{};
		std::string m_GameOverScene{};

		LoadSceneComponent* m_pLoadScene{};

	};
}