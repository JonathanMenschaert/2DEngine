#include "HighScoreIO.h"
#include <fstream>

std::vector<dae::HighScoreData> dae::HighScoreIO::LoadHighScoreTable(const std::string& path)
{
    std::ifstream inputFile{path, std::ios::binary};
    if (!inputFile.is_open())
    {
        return std::vector<HighScoreData>{};
    }
    unsigned int amount{};
    inputFile.read(reinterpret_cast<char*>(&amount), sizeof(unsigned int));
    
    std::vector<HighScoreData> highScores{amount};
    inputFile.read(reinterpret_cast<char*>(highScores.data()), sizeof(HighScoreData) * amount);

    return highScores;
}

void dae::HighScoreIO::SaveLevelLayout(const std::vector<HighScoreData>& highscores, const std::string& path)
{
    std::ofstream outputFile{path, std::ios::binary};
    if (!outputFile.is_open())
    {
        return;
    }

    unsigned int amount{ highscores.size() };
    outputFile.write(reinterpret_cast<const char*>(&amount), sizeof(unsigned int));

    for (const HighScoreData& highScore : highscores)
    {
        outputFile.write(reinterpret_cast<const char*>(&highScore), sizeof(HighScoreData));
    }

    outputFile.close();
}
