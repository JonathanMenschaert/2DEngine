#pragma once
namespace dae
{
	class GameObject;
	class Command
	{
	public:
		Command(GameObject* pActor);
		virtual ~Command() = default;
		virtual void Execute() = 0;
	protected:
		GameObject* GetActor() const;
	private:
		GameObject* m_pActor{ nullptr };
	};
}
