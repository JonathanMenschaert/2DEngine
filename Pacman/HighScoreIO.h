#pragma once
#include <string>
#include <vector>

namespace dae
{
	struct HighScoreData
	{
		char name[3];
		unsigned int level;
		unsigned int score;
	};

	class HighScoreIO
	{
	public:
		~HighScoreIO() = default;
		HighScoreIO(const HighScoreIO& component) = delete;
		HighScoreIO(HighScoreIO&& component) noexcept = delete;
		HighScoreIO& operator=(const HighScoreIO& component) = delete;
		HighScoreIO& operator=(HighScoreIO&& component) noexcept = delete;

		static std::vector<HighScoreData> LoadHighScoreTable(const std::string& path);
		static void SaveLevelLayout(const std::vector<HighScoreData>& highscores, const std::string& path);

	private:
		HighScoreIO() = default;
	};
}

