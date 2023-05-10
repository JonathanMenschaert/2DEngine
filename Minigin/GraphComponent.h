#pragma once
#include "BaseComponent.h"
#include <unordered_set>
#include <vector>
#include "glm/glm.hpp"
#include <memory>

namespace dae
{
	struct Node;
	struct Connection
	{

		Node* endNode{};
		float cost{};
	};

	struct Node
	{
		glm::vec2 position{};
		
		std::vector<Connection> connections{};

		inline bool operator==(const Node& rhs)
		{
			return position == rhs.position;
		}
	};

	

	class GraphComponent final : public BaseComponent
	{
	public:
		GraphComponent(GameObject* pGameObject);
		virtual ~GraphComponent() noexcept = default;
		GraphComponent(const GraphComponent& graphComponent) = delete;
		GraphComponent(GraphComponent&& graphComponent) noexcept = delete;
		GraphComponent& operator=(const GraphComponent& graphComponent) = delete;
		GraphComponent& operator=(GraphComponent&& graphComponent) noexcept = delete;

		Node* CreateNode(const glm::vec2& position);
		void SetConnection(const Node* currentNode, Node* nextNode, float cost);
		glm::vec2 GetRandomNextPosition(const glm::vec2& currentPos);
		

	private:

		Node* GetNodeFromPosition(const glm::vec2& position);
		std::unordered_set<std::unique_ptr<Node>> m_Graph;
	};
}

