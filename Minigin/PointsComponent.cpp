#include "PointsComponent.h"

void dae::PointsComponent::SetPoints(int points)
{
	m_Points = points;
}

int dae::PointsComponent::GetPoints() const
{
	return m_Points;
}
