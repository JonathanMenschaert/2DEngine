#include "DelayedSceneLoadComponent.h"
#include "GameObject.h"
#include "GameTime.h"

dae::DelayedSceneLoadComponent::DelayedSceneLoadComponent(GameObject* pGameObject)
	:TimerComponent{pGameObject}
{
}

void dae::DelayedSceneLoadComponent::Update()
{
	if (m_IsTimerActivated)
	{
		m_Timer -= GameTime::GetInstance().GetElapsedTime();
		if (m_Timer <= 0.f)
		{
			m_Timer = 0.f;
			m_IsTimerActivated = false;
			m_pLoadScene->LoadScene();
		}
	}
}

void dae::DelayedSceneLoadComponent::Notify(const Event<PlayerEvent>& e)
{
	if (!m_pLoadScene)
	{
		return;
	}

	switch (e.GetPayload())
	{
	case PlayerEvent::LevelWin:
		m_pLoadScene->SetSceneToLoad(m_NextLevelScene);
		break;
	case PlayerEvent::PacmanDied:
		m_pLoadScene->SetSceneToLoad(m_GameOverScene);
		break;
	}
	m_Timer = m_MaxTime;
	m_IsTimerActivated = true;
}

void dae::DelayedSceneLoadComponent::SetScenes(const std::string& nextLevelScene, const std::string& gameOverScene)
{
	m_NextLevelScene = nextLevelScene;
	m_GameOverScene = gameOverScene;
}

void dae::DelayedSceneLoadComponent::Init()
{
	m_MaxTime = 2.f;
	m_pLoadScene = GetGameObject()->GetComponent<LoadSceneComponent>();
}
