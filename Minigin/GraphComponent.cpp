#include "GraphComponent.h"
#include <algorithm>
#include <functional>
#include "glm/gtc/epsilon.hpp"

dae::GraphComponent::GraphComponent(GameObject* pGameObject)
	:BaseComponent{pGameObject}
{
}

dae::Node* dae::GraphComponent::CreateNode(const glm::vec2& position)
{
	Node* existingNode{GetNodeFromPosition(position)};
	if (existingNode)
	{
		return existingNode;
	}
	auto node{ std::make_unique<Node>() };
	node->position = position;

	Node* pNode{ node.get() };
	m_Graph.insert(std::move(node));

	return pNode;
}

void dae::GraphComponent::SetConnection(const Node* currentNode, Node* nextNode, float cost)
{
	auto it = std::find_if(m_Graph.begin(), m_Graph.end(), [currentNode](const auto& element)
		{
			return element.get() == currentNode;
		});
	if (it != m_Graph.end())
	{
		(*it)->connections.push_back(Connection{ nextNode, cost });
	}
}

glm::vec2 dae::GraphComponent::GetRandomNextPosition(const glm::vec2& currentPos)
{
	Node* currentNode{ GetNodeFromPosition(currentPos) };
	if (!currentNode)
	{
		return currentPos;
	}

	auto& connections{ currentNode->connections };
	if (connections.size() == 0)
	{
		return currentPos;
	}
	size_t rand{ static_cast<size_t>(std::rand()) };
	auto* nextNode{ connections[rand % connections.size()].endNode };

	return nextNode->position;
}

dae::Node* dae::GraphComponent::GetNodeFromPosition(const glm::vec2& position)
{
	constexpr float posErrorMargin{ 2.f };
	for (auto& element : m_Graph)
	{
		if (glm::all(glm::epsilonEqual(element->position, position, posErrorMargin)))
		{
			return element.get();
		}
	}

	return nullptr;
}


