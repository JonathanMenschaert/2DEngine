#include "LetterScrollButtonComponent.h"
#include "GameObject.h"
#include "TextureRenderComponent.h"
std::vector<std::string> dae::LetterScrollButtonComponent::m_Letters {
	"_", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
	"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", " "
};

dae::LetterScrollButtonComponent::LetterScrollButtonComponent(GameObject* pGameObject)
	:ButtonComponent{pGameObject}
	,m_CurrentLetterIdx{0}
{
}

void dae::LetterScrollButtonComponent::Scroll(int scrollAmount)
{
	if (!m_IsSelected)
	{
		return;
	}
	const int size{ static_cast<int>(m_Letters.size()) };
	if (scrollAmount <= -size)
	{
		int amount{ std::abs(scrollAmount) / size };
		scrollAmount += (size * amount);
	}

	m_CurrentLetterIdx = (m_CurrentLetterIdx + scrollAmount + size) % size;

	SetButtonText(m_Letters[static_cast<size_t>(m_CurrentLetterIdx)]);
}

void dae::LetterScrollButtonComponent::Init()
{
	ButtonComponent::Init();
	SetButtonText(m_Letters[m_CurrentLetterIdx]);
	GameObject* pGameObj{ GetGameObject() };

	auto pArrowUp{ std::make_shared<GameObject>() };

	auto pUpTrans{ pArrowUp->AddComponent<TransformComponent>() };
	auto pUpRender{ pArrowUp->AddComponent<TextureRenderComponent>() };
	pUpTrans->SetLocalPosition(glm::vec2{0, -40.f});
	pUpRender->SetTexture("arrowup.png");
	pArrowUp->SetParent(pGameObj, false);

	auto pArrowDown{ std::make_shared<GameObject>() };
	auto pDownTrans{ pArrowDown->AddComponent<TransformComponent>() };
	auto pDownRender{ pArrowDown->AddComponent<TextureRenderComponent>() };
	pDownTrans->SetLocalPosition(glm::vec2{0, 40.f});
	pArrowDown->SetParent(pGameObj,false);
	pDownRender->SetTexture("arrowdown.png");
}

const std::string& dae::LetterScrollButtonComponent::GetButtonText() const
{
	return m_Letters[m_CurrentLetterIdx];
}
