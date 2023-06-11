#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class LoadSceneComponent final : public BaseComponent
	{
	public:
		LoadSceneComponent(GameObject* pGameObject);
		virtual ~LoadSceneComponent() = default;
		LoadSceneComponent(const LoadSceneComponent& other) = delete;
		LoadSceneComponent(LoadSceneComponent&& other) noexcept = delete;
		LoadSceneComponent& operator=(const LoadSceneComponent& other) = delete;
		LoadSceneComponent& operator=(LoadSceneComponent&& other) noexcept = delete;

		void SetDefaultScene(const std::string& scene);
		void SetSceneToLoad(const std::string& scene);

		void LoadScene();

	private:
		std::string m_DefaultScene{};
		std::string m_SceneToLoad{};
	};
}

