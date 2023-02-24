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

	//Background object
	auto bgObj = std::make_shared<dae::GameObject>();
	auto bgRender = std::make_shared<dae::RenderComponent>();
	bgRender->SetTexture("background.tga");
	bgRender->SetParent(bgObj);
	bgObj->AddComponent(bgRender);

	auto bgTrans = std::make_shared<dae::TransformComponent>();
	bgTrans->SetParent(bgObj);
	bgTrans->SetTranslation(glm::vec2{ 0.f, 0.f });
	bgObj->AddComponent(bgTrans);
	scene.Add(bgObj);

	//Logo object
	bgObj = std::make_shared<dae::GameObject>();
	bgRender = std::make_shared<dae::RenderComponent>();
	bgRender->SetTexture("logo.tga");
	bgRender->SetParent(bgObj);
	bgObj->AddComponent(bgRender);

	bgTrans = std::make_shared<dae::TransformComponent>();
	bgTrans->SetTranslation(glm::vec2{ 216, 180 });
	bgTrans->SetParent(bgObj);
	bgObj->AddComponent(bgTrans);
	scene.Add(bgObj);

	//Text Object
	auto textObj = std::make_shared<dae::GameObject>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_shared<dae::TextComponent>();
	textComponent->SetText("Programming 4 Assignment");
	textComponent->SetFont(font);
	textComponent->SetColor(255, 255, 255, 255);
	textComponent->SetParent(textObj);
	textObj->AddComponent(textComponent);

	auto textRender = std::make_shared<dae::RenderComponent>();
	textRender->SetParent(textObj);
	textObj->AddComponent(textRender);

	auto textTrans = std::make_shared<dae::TransformComponent>();
	textTrans->SetTranslation(glm::vec2{ 80, 20 });
	textTrans->SetParent(textObj);
	textObj->AddComponent(textTrans);
	scene.Add(textObj);

	//Fps Object
	auto fpsObj = std::make_shared<dae::GameObject>();
	auto fpsTrans = std::make_shared<dae::TransformComponent>();
	fpsTrans->SetParent(fpsObj);
	fpsTrans->SetTranslation(glm::vec2{ 10.f, 10.f });
	fpsObj->AddComponent(fpsTrans);
	
	auto fpsRender = std::make_shared<dae::RenderComponent>();
	fpsRender->SetParent(fpsObj);
	fpsObj->AddComponent(fpsRender);

	auto fpsText = std::make_shared<dae::TextComponent>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	fpsText->SetFont(font);
	fpsText->SetColor(255, 255, 0, 255);
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