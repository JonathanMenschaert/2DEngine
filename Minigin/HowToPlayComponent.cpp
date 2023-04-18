#include "HowToPlayComponent.h"
#include "imgui.h"
#include "GameObject.h"
#include "glm/glm.hpp"
dae::HowToPlayComponent::HowToPlayComponent(std::shared_ptr<GameObject> pGameObject)
	:BaseComponent(pGameObject)
{
	
}

void dae::HowToPlayComponent::OnGui()
{
	glm::vec2 windowPos = m_pTransform->GetWorldPosition();
	ImGui::SetNextWindowPos(ImVec2{windowPos.x, windowPos.y});
	ImGui::SetNextWindowSize(ImVec2(600, 250));

	if (ImGui::Begin("How To Play"))
	{
		ImGui::TextWrapped("Player 1:\nMove around with WASD on the keyboard or with the DPAD on the first controller\n\n");
		ImGui::TextWrapped("Player 2:\nMove around with the DPAD on the second controller\n\n");
		ImGui::TextWrapped("Lives:\nManually take life from Player 1 with the E on the keyboard or A button on the controller.");
		ImGui::TextWrapped("Use the same button on the second controller to take life from Player 2\n\n");
		ImGui::TextWrapped("Scoring:\nManually add score to Player 1 with O (+10) and P (+50) on the keyboard or the X (+10) and Y (+50) button on the controller.");
		ImGui::TextWrapped("Use the same buttons on the second controller to add score to Player 2\n\n");
	}
	ImGui::End();
}

void dae::HowToPlayComponent::Init()
{
	m_pTransform = GetGameObject()->GetComponent<TransformComponent>().lock().get();
}
