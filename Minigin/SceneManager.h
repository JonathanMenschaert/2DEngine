#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include <unordered_map>
#include <functional>
namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& LoadScene(const std::string& name);


		void Init();
		void Update();
		void LateUpdate();
		void Render() const;
		void OnGui();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::unordered_map<std::string, std::function<void()>> m_SceneTemplates;

		std::unique_ptr<Scene> m_pActiveScene{};
		std::unique_ptr<Scene> m_pNewScene{};
	};
}
