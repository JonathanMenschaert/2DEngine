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
	ImGui::SetNextWindowSize(ImVec2(700, 250));

	if (ImGui::Begin("How To Play"))
	{
		ImGui::TextWrapped("Menu navigation:\n\n");
		ImGui::TextWrapped("Keyboard: WASD and ENTER\n");
		ImGui::TextWrapped("Controller: DPAD and A Button\n\n");

		ImGui::TextWrapped("Ingame Controls:\n\n");
		ImGui::TextWrapped("Player1: \n");
		ImGui::TextWrapped("Keyboard: WASD to move \n");
		ImGui::TextWrapped("Controller: DPAD to move \n\n");

		ImGui::TextWrapped("Player2: \n");
		ImGui::TextWrapped("Controller: DPAD to move \n\n");
	}
	ImGui::End();
}

void dae::HowToPlayComponent::Init()
{
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>();
}
