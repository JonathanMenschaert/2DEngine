#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "Scenes.h"

void load()
{
	dae::SceneManager::GetInstance().AddScene("LevelTester", dae::LevelTester::LoadScene, true);

	dae::SceneManager::GetInstance().AddScene("SingleLevel0", dae::SingleOne::LoadScene);
	dae::SceneManager::GetInstance().AddScene("SingleLevel1", dae::SingleTwo::LoadScene);

	dae::SceneManager::GetInstance().AddScene("CoopLevel0", dae::CoopOne::LoadScene);
	dae::SceneManager::GetInstance().AddScene("CoopLevel1", dae::CoopTwo::LoadScene);

	dae::SceneManager::GetInstance().AddScene("VersusLevel0", dae::VersusOne::LoadScene);
	dae::SceneManager::GetInstance().AddScene("VersusLevel1", dae::VersusTwo::LoadScene);

	dae::SceneManager::GetInstance().AddScene("Main Menu", dae::MainMenu::LoadScene);
	dae::SceneManager::GetInstance().AddScene("HighScoreSave", dae::HighScoreSave::LoadScene);
	dae::SceneManager::GetInstance().AddScene("HighScoreList", dae::HighScoreList::LoadScene);
}


int main(int, char* []) {
	dae::Minigin engine{ "Data/" };
	std::srand(static_cast<int>(std::time(nullptr)));
	engine.Run(load);
	return 0;
}
