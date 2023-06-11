#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
#include <unordered_map>
#include <functional>
#include "Scene.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		dae::Scene& CreateScene(const std::string& name);
		bool LoadScene(const std::string& name);
		void AddScene(const std::string& name, const std::function<void()>& loadFunction, bool setAsDefault = false);

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
