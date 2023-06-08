#include "LevelIO.h"
#include <fstream>


dae::LevelLayout dae::LevelIO::LoadLevelLayout(const std::string& path)
{
    std::ifstream inputFile{path, std::ios::binary};
    if (!inputFile.is_open())
    {
        return LevelLayout{};
    }

    LevelLayout layout{};
    inputFile.read(reinterpret_cast<char*>(&layout.columns), sizeof(int));
    inputFile.read(reinterpret_cast<char*>(&layout.rows), sizeof(int));
    layout.levelData.resize(layout.columns * layout.rows);
    inputFile.read(reinterpret_cast<char*>(layout.levelData.data()), layout.columns * layout.rows);
    return layout;
}

void dae::LevelIO::SaveLevelLayout(const LevelLayout& levelLayout, const std::string& path)
{
    std::ofstream outputFile{path, std::ios::binary};
    if (!outputFile.is_open())
    {
        return;
    }

    outputFile.write(reinterpret_cast<const char*>(&levelLayout.columns), sizeof(int));
    outputFile.write(reinterpret_cast<const char*>(&levelLayout.rows), sizeof(int));
    outputFile.write(reinterpret_cast<const char*>(levelLayout.levelData.data()), levelLayout.levelData.size());

    outputFile.close();
}

