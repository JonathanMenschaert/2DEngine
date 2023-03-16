
#include "TrashTheCacheComponent.h"
#include <chrono>
#include <numeric>
#include <algorithm>
#include <functional>



dae::TrashTheCacheComponent::TrashTheCacheComponent(std::shared_ptr<GameObject> pGameObject)
    :BaseComponent{pGameObject}
    ,m_AmountOfIntegerMeasurements{3}
    ,m_AmountOfGameObjectMeasurements{3}
    ,m_SampleSize{ static_cast<int>(powf(2, 26))}
{
}

void dae::TrashTheCacheComponent::OnGui()
{
	RenderIntegerBuffer();
    RenderGameobjectBuffer();
}



void dae::TrashTheCacheComponent::RenderIntegerBuffer()
{
    const ImGuiViewport* pViewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(pViewport->WorkPos);
    ImGui::SetNextWindowSize(ImVec2(300, 180));

    ImGui::Begin("Exercise 1");

    if (ImGui::InputInt("Samples", &m_AmountOfIntegerMeasurements))
    {
        //Make sure there are at least 3 measurements
        if (m_AmountOfIntegerMeasurements < 3)
        {
            m_AmountOfIntegerMeasurements = 3;
        }
    }
    

    if (ImGui::Button("Trash the cache", ImVec2{ 120, 20 }))
    {
        MeasureIntegerBuffer();
    }

    if (!m_IntegerMeasurements.empty())
    {
        auto it{ std::max_element(m_IntegerMeasurements.begin(), m_IntegerMeasurements.end()) };
        DrawPlot(m_IntegerMeasurements.data(), m_IntegerMeasurements.size(), 1, *it, ImColor{1.f, 1.f, 0.f});
    }

    ImGui::End();
}

void dae::TrashTheCacheComponent::RenderGameobjectBuffer()
{
    const ImGuiViewport* pViewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(ImVec2{ pViewport->WorkPos.x + 310, pViewport->WorkPos.y });
    ImGui::SetNextWindowSize(ImVec2(300, 450));

    ImGui::Begin("Exercise 2");

    if (ImGui::InputInt("Samples", &m_AmountOfGameObjectMeasurements))
    {
        //Make sure there are at least 3 measurements
        if (m_AmountOfGameObjectMeasurements < 3)
        {
            m_AmountOfGameObjectMeasurements = 3;
        }
    }


    if (ImGui::Button("Trash the cache with GameObject3D", ImVec2{ 270, 20 }))
    {
        MeasureGameObjectBuffer();
    }

    if (!m_GameObjectMeasurements.empty())
    {
        auto it{ std::max_element(m_GameObjectMeasurements.begin(), m_GameObjectMeasurements.end()) };
        DrawPlot(m_GameObjectMeasurements.data(), m_GameObjectMeasurements.size(), 1, *it, ImColor{ 0.f, 1.f, 0.f });
    }

    if (ImGui::Button("Trash the cache with GameObject3DAlt", ImVec2{ 270, 20 }))
    {
        MeasureGameObjectAltBuffer();
    }

    if (!m_GameObjectAltMeasurements.empty())
    {
        auto it{ std::max_element(m_GameObjectAltMeasurements.begin(), m_GameObjectAltMeasurements.end()) };
        DrawPlot(m_GameObjectAltMeasurements.data(), m_GameObjectAltMeasurements.size(), 1, *it, ImColor{ 0.f, 0.f, 1.f });
    }

    if (!m_GameObjectMeasurements.empty() && !m_GameObjectAltMeasurements.empty())
    {
        auto it{ std::max_element(m_GameObjectMeasurements.begin(), m_GameObjectMeasurements.end()) };
        DrawMultiPlot(m_GameObjectMeasurements.size(), 2, *it, { ImColor{ 0.f, 1.f, 0.f }, ImColor{0.f, 0.f, 1.f} });
    }

    ImGui::End();
}

void dae::TrashTheCacheComponent::DrawPlot(const float* data, size_t size, int count, float maxValue, const ImColor& color) const
{
    const size_t verticalLineIdx{ 4 };
    const int plotAmount{ 1 };
    ImU32 plotColor[plotAmount]{ color };

    ImGui::PlotConfig::Values values{};
    values.ys_list = &data;
    values.count = static_cast<int>(size);
    values.ys_count = count;
    values.colors = plotColor;

    ImGui::PlotConfig::VerticalLines verticalLines{};
    verticalLines.show = true;
    verticalLines.indices = &verticalLineIdx;
    verticalLines.count = 1;

    ImGui::PlotConfig plotConfig{};
    plotConfig.values = values;
    plotConfig.frame_size = ImVec2{ 200, 100 };
    plotConfig.grid_y.show = true;
    plotConfig.grid_y.size = maxValue / 10.f;
    plotConfig.scale.max = maxValue;
    plotConfig.v_lines = verticalLines;


    ImGui::Plot("plotter", plotConfig);
}


void dae::TrashTheCacheComponent::DrawMultiPlot(size_t size, int count, float maxValue, const std::vector<ImColor>& colors) const
{
    const size_t verticalLineIdx{ 4 };
    const int plotAmount{ 2 };
    ImU32 plotColor[plotAmount]{ colors[0], colors[1]};
    const float* data[plotAmount]{ m_GameObjectMeasurements.data(), m_GameObjectAltMeasurements.data() };

    ImGui::PlotConfig::Values values{};
    values.ys_list = data;
    values.count = static_cast<int>(size);
    values.ys_count = count;
    values.colors = plotColor;

    ImGui::PlotConfig::VerticalLines verticalLines{};
    verticalLines.show = true;
    verticalLines.indices = &verticalLineIdx;
    verticalLines.count = 1;

    ImGui::PlotConfig plotConfig{};
    plotConfig.values = values;
    plotConfig.frame_size = ImVec2{ 200, 100 };
    plotConfig.grid_y.show = true;
    plotConfig.grid_y.size = maxValue / 10.f;
    plotConfig.scale.max = maxValue;
    plotConfig.v_lines = verticalLines;

    ImGui::Plot("doubleplotter", plotConfig);
}

void dae::TrashTheCacheComponent::MeasureIntegerBuffer()
{
    m_IntegerMeasurements.clear();
    int* buffer{ new int[m_SampleSize] };

    for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
    {
        std::vector<long long> measurements{};
        for (int i{ 0 }; i < m_AmountOfIntegerMeasurements; ++i)
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (int j = 0; j < m_SampleSize; j += stepSize)
            {
                buffer[j] *= 2;
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

            measurements.push_back(elapsedTime);
        }

        std::sort(measurements.begin(), measurements.end());
        auto average{ std::accumulate(measurements.begin() + 1, measurements.end() - 1, 0.f) / (measurements.size() - 2) };
        m_IntegerMeasurements.push_back(average / 1000.f);
    }
    
    delete[] buffer;
}

void dae::TrashTheCacheComponent::MeasureGameObjectBuffer()
{
    m_GameObjectMeasurements.clear();
    GameObject3D* buffer{ new GameObject3D[m_SampleSize] };

    for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
    {
        std::vector<long long> measurements{};
        for (int i{ 0 }; i < m_AmountOfGameObjectMeasurements; ++i)
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (int j = 0; j < m_SampleSize; j += stepSize)
            {
                buffer[j].ID *= 2;
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            measurements.push_back(elapsedTime);
        }
        std::sort(measurements.begin(), measurements.end());
        auto average{ std::accumulate(measurements.begin() + 1, measurements.end() - 1, 0.f) / (measurements.size() - 2) };
        m_GameObjectMeasurements.push_back(average / 1000.f);
    }
    
    delete[] buffer;
}

void dae::TrashTheCacheComponent::MeasureGameObjectAltBuffer()
{
    m_GameObjectAltMeasurements.clear();
    GameObject3DAlt* buffer{ new GameObject3DAlt[m_SampleSize] };

    for (int stepSize{ 1 }; stepSize <= 1024; stepSize *= 2)
    {
        std::vector<long long> measurements{};
        for (int i{ 0 }; i < m_AmountOfGameObjectMeasurements; ++i)
        {
            auto start = std::chrono::high_resolution_clock::now();

            for (int j = 0; j < m_SampleSize; j += stepSize)
            {
                buffer[j].ID *= 2;
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
            //float elapsedTimeMs = elapsedTime / 1000.f;
            measurements.push_back(elapsedTime);
        }

        std::sort(measurements.begin(), measurements.end());
        auto average{ std::accumulate(measurements.begin() + 1, measurements.end() - 1, 0.f) / (measurements.size() - 2) };
        m_GameObjectAltMeasurements.push_back(average / 1000.f);
    }
    
    delete[] buffer;
}


