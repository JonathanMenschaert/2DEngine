#pragma once
#include "ButtonComponent.h"
namespace dae
{
	class LetterScrollButtonComponent final : public ButtonComponent
	{
	public:
		LetterScrollButtonComponent(GameObject* pGameObject);
		virtual ~LetterScrollButtonComponent() = default;
		LetterScrollButtonComponent(const LetterScrollButtonComponent& component) = delete;
		LetterScrollButtonComponent(LetterScrollButtonComponent&& component) noexcept = delete;
		LetterScrollButtonComponent& operator=(const LetterScrollButtonComponent& component) = delete;
		LetterScrollButtonComponent& operator=(LetterScrollButtonComponent&& component) noexcept = delete;

		void Scroll(int scrollAmount);
		void Init() override;
		const std::string& GetButtonText() const;
	private:
		static std::vector<std::string> m_Letters;

		int m_CurrentLetterIdx{};
	};
}


