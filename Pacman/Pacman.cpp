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
	dae::SceneManager::GetInstance().AddScene("Single1", dae::SingleOne::LoadScene, true);
	dae::SceneManager::GetInstance().AddScene("Main Menu", dae::MainMenu::LoadScene);
}


int main(int, char* []) {
	dae::Minigin engine{ "../Data/" };
	std::srand(static_cast<int>(std::time(nullptr)));
	engine.Run(load);
	return 0;
}
