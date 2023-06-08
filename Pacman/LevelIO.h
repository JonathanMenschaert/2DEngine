#pragma once
#include <vector>
#include <string>
namespace dae
{
	struct LevelLayout final
	{
		int columns;
		int rows;
		std::vector<unsigned char> levelData{};
	};

	class LevelIO final
	{
	public:
		~LevelIO() = default;
		LevelIO(const LevelIO& component) = delete;
		LevelIO(LevelIO&& component) noexcept = delete;
		LevelIO& operator=(const LevelIO& component) = delete;
		LevelIO& operator=(LevelIO&& component) noexcept = delete;

		static LevelLayout LoadLevelLayout(const std::string& path);
		static void SaveLevelLayout(const LevelLayout& levelLayout, const std::string& path);

	private:
		LevelIO() = default;
	};
}

