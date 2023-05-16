#include "HowToPlayComponent.h"
#include "imgui.h"
#include "GameObject.h"
#include "glm/glm.hpp"

dae::HowToPlayComponent::HowToPlayComponent(GameObject* pGameObject)
	:BaseComponent{ pGameObject }
{
	
}

void dae::HowToPlayComponent::OnGui()
{
	glm::vec2 windowPos = m_pTransform->GetWorldPosition();
	ImGui::SetNextWindowPos(ImVec2{windowPos.x, windowPos.y});
	ImGui::SetNextWindowSize(ImVec2(600, 250));

	if (ImGui::Begin("How To Play"))
	{
		ImGui::TextWrapped("Move around with WASD on the keyboard or with the DPAD on the controller\n\n");
		ImGui::TextWrapped("Pick up the dots to play the sound\n\n");
	}
	ImGui::End();
}

void dae::HowToPlayComponent::Init()
{
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>();
}
