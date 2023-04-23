#include "RotatorComponent.h"
#include "GameObject.h"
#include "Time.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

dae::RotatorComponent::RotatorComponent(GameObject* pGameObject)
	:UpdateComponent{ pGameObject }
	,m_RotationSpeed{90.f}
{
}

void dae::RotatorComponent::Init()
{
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>();
	
}

void dae::RotatorComponent::Update()
{
	if (m_pTransform)
	{
		auto vec = m_pTransform->GetLocalPosition();
		glm::mat4 rotationMat{ 1 };
		rotationMat = glm::rotate(rotationMat, glm::radians(m_RotationSpeed * Time::GetInstance().GetElapsedTime()), glm::vec3(0.f, 0.f, 1.f));
		
		m_pTransform->SetLocalPosition(glm::vec3{ rotationMat * glm::vec4{vec, 0.f, 1.f} });
	}
}

void dae::RotatorComponent::SetRotationSpeed(float degPerSec)
{
	m_RotationSpeed = degPerSec;
}
