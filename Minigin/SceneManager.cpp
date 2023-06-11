#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Init()
{
	if (!m_pActiveScene)
	{
		if (!m_pNewScene)
		{
			CreateScene("SampleScene");
		}
		
		m_pActiveScene = std::move(m_pNewScene);
	}
	m_pActiveScene->Init();
}

void dae::SceneManager::Update()
{
	if (m_pNewScene)
	{
		m_pNewScene->SetPersistentObjects(m_pActiveScene->GetPersistentObjects());
		m_pActiveScene = std::move(m_pNewScene);
		m_pNewScene = nullptr;
		Init();
	}

	m_pActiveScene->Update();
}

void dae::SceneManager::LateUpdate()
{
	m_pActiveScene->LateUpdate();
}

void dae::SceneManager::Render() const
{
	m_pActiveScene->Render();
}

void dae::SceneManager::OnGui()
{
	m_pActiveScene->OnGui();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	m_pNewScene = std::make_unique<Scene>(name);
	return *m_pNewScene;
}

bool dae::SceneManager::LoadScene(const std::string& name)
{
	if (m_SceneTemplates.find(name) == m_SceneTemplates.end())
	{
		return false;
	}

	m_SceneTemplates[name]();
	return true;
}

void dae::SceneManager::AddScene(const std::string& name, const std::function<void()>& loadFunction, bool setAsDefault)
{
	m_SceneTemplates[name] = loadFunction;

	if (setAsDefault)
	{
		LoadScene(name);
	}
}
