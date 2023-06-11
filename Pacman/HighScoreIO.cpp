#include "HighScoreIO.h"
#include <fstream>

std::vector<dae::HighScoreData> dae::HighScoreIO::LoadHighScoreTable(const std::string& path)
{
    std::ifstream inputFile{path, std::ios::binary};
    if (!inputFile.is_open())
    {
        return std::vector<HighScoreData>{};
    }
    int amount{};
    inputFile.read(reinterpret_cast<char*>(&amount), sizeof(int));
    
    std::vector<HighScoreData> highScores{static_cast<size_t>(amount)};
    inputFile.read(reinterpret_cast<char*>(highScores.data()), sizeof(HighScoreData) * amount);

    return highScores;
}

void dae::HighScoreIO::SaveHighScores(const std::vector<HighScoreData>& highscores, const std::string& path)
{
    std::ofstream outputFile{path, std::ios::binary};
    if (!outputFile.is_open())
    {
        return;
    }

    int amount{ static_cast<int>(highscores.size() )};
    outputFile.write(reinterpret_cast<const char*>(&amount), sizeof(int));

    for (const HighScoreData& highScore : highscores)
    {
        outputFile.write(reinterpret_cast<const char*>(&highScore), sizeof(HighScoreData));
    }

    outputFile.close();
}
