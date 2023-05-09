#pragma once
#include "BaseComponent.h"
#include <unordered_map>
#include <vector>


namespace dae
{

	struct Node
	{
		float x{};
		float y{};
		
		std::vector<Connection> m_Connections{};
	};

	struct Connection
	{
		Node* endNode{};
		float cost{};
	};

	class GraphComponent final : public BaseComponent
	{
	public:
		GraphComponent(GameObject* pGameObject);
		virtual ~GraphComponent() = default;
		GraphComponent(const GraphComponent& rectComponent) = delete;
		GraphComponent(GraphComponent&& rectComponent) noexcept = delete;
		GraphComponent& operator=(const GraphComponent& rectComponent) = delete;
		GraphComponent& operator=(GraphComponent&& rectComponent) noexcept = delete;

		Node& CreateNode();
		void SetConnection(const Node& currentNode, const Node& nextNode, float cost, bool isBidirectional = false);

	private:
		std::unordered_map<Node*, std::vector<Node*>> m_Graph;
	};
}

