#pragma once
#include "BaseComponent.h"
namespace dae
{
	class PointsComponent final : public BaseComponent
	{
	public:
		virtual ~PointsComponent() = default;
		PointsComponent(const PointsComponent& baseComponent) = delete;
		PointsComponent(PointsComponent&& baseComponent) noexcept = delete;
		PointsComponent& operator=(const PointsComponent& baseComponent) = delete;
		PointsComponent& operator=(PointsComponent&& baseComponent) noexcept = delete;

		void SetPoints(int points);
		int GetPoints() const;

	private:
		int m_Points;
	};
}

