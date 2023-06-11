#pragma once
#include <string>
#include <vector>

namespace dae
{
	struct HighScoreData
	{
		static const size_t nameSize{4};

		char name[nameSize];
		int level{};
		int score{};

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
		static void SaveHighScores(const std::vector<HighScoreData>& highscores, const std::string& path);

	private:
		HighScoreIO() = default;
	};
}

