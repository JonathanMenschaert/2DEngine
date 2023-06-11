#include "LoadSceneComponent.h"
#include "SceneManager.h"

dae::LoadSceneComponent::LoadSceneComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
{
}

void dae::LoadSceneComponent::SetDefaultScene(const std::string& scene)
{
	m_DefaultScene = scene;
}

void dae::LoadSceneComponent::SetSceneToLoad(const std::string& scene)
{
	m_SceneToLoad = scene;
}

void dae::LoadSceneComponent::LoadScene()
{
	if (!SceneManager::GetInstance().LoadScene(m_SceneToLoad))
	{
		SceneManager::GetInstance().LoadScene(m_DefaultScene);
	}
}
