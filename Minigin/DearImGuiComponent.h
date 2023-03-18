#pragma once
#include "BaseComponent.h"
#include <vector>
#include <string>
#include "imgui.h"
#include "imgui_plot.h"
namespace dae
{
	struct Transform
	{
		float matrix[16]
		{
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		};
	};

	struct GameObject3DAlt
	{
		Transform* transform{};
		int ID{};
	};

	struct GameObject3D
	{
		Transform transform{};
		int ID{};
	};

	class DearImGuiComponent : public BaseComponent
	{
	public:
		DearImGuiComponent(std::shared_ptr<GameObject> pGameObject);
		virtual ~DearImGuiComponent() = default;
		DearImGuiComponent(const DearImGuiComponent& component) = delete;
		DearImGuiComponent(DearImGuiComponent&& component) noexcept = delete;
		DearImGuiComponent& operator=(const DearImGuiComponent& component) = delete;
		DearImGuiComponent& operator=(DearImGuiComponent&& component) noexcept = delete;

		virtual void OnGui() override;

	private:
		
		void RenderIntegerBuffer();
		void RenderGameobjectBuffer();

		void MeasureIntegerBuffer();
		void MeasureGameObjectBuffer();
		void MeasureGameObjectAltBuffer();

		void DrawPlot(const float* data, size_t size, int count, float maxValue, const ImColor& color) const;
		void DrawMultiPlot(const std::vector<std::vector<float>>& measurements, size_t size, int count, float maxValue, const std::vector<ImColor>& colors) const;

		const int m_SampleSize;
		int m_AmountOfIntegerMeasurements;
		int m_AmountOfGameObjectMeasurements;
		std::vector<float> m_IntegerMeasurements{};
		std::vector<float> m_GameObjectMeasurements{};
		std::vector<float> m_GameObjectAltMeasurements{};
	};

}