#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextObject.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "FPSComponent.h"
#include "TextComponent.h"
#include "RenderComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<dae::GameObject>();
	go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go->SetTexture("logo.tga");
	go->SetPosition(216, 180);
	scene.Add(go);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<dae::TextObject>("Programming 4 Assignment", font);
	to->SetPosition(80, 20);
	scene.Add(to);

	//Fps Object
	auto fpsObj = std::make_shared<dae::GameObject>();
	auto fpsTrans = std::make_shared<dae::TransformComponent>();
	fpsTrans->SetParent(fpsObj);
	fpsTrans->SetTranslation(glm::vec2{ 80.f, 20.f });
	fpsObj->AddComponent(fpsTrans);
	
	auto fpsRender = std::make_shared<dae::RenderComponent>();
	fpsRender->SetParent(fpsObj);
	fpsObj->AddComponent(fpsRender);

	auto fpsText = std::make_shared<dae::TextComponent>();
	fpsText->SetFont(font);
	fpsText->SetColor(255, 255, 255, 255);
	fpsText->SetParent(fpsObj);
	fpsObj->AddComponent(fpsText);

	auto fpsComponent = std::make_shared<dae::FPSComponent>();
	fpsComponent->SetParent(fpsObj);
	fpsObj->AddComponent(fpsComponent);
	scene.Add(fpsObj);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}