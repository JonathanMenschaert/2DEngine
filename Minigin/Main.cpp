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
#include <iostream>
void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Background object
	auto bgObj = std::make_shared<dae::GameObject>();
	auto bgRender = bgObj->AddComponent<dae::RenderComponent>(bgObj);
	bgRender->SetTexture("background.tga");

	auto bgTrans = bgObj->AddComponent<dae::TransformComponent>(bgObj);
	bgTrans->SetLocalPosition(glm::vec3{ 0.f, 0.f, 0.f });	
	scene.Add(bgObj);

	//Logo object
	bgObj = std::make_shared<dae::GameObject>();
	bgRender = bgObj->AddComponent<dae::RenderComponent>(bgObj);
	bgRender->SetTexture("logo.tga");	

	bgTrans = bgObj->AddComponent<dae::TransformComponent>(bgObj);
	bgTrans->SetLocalPosition(glm::vec2{ 216.f, 180.f });
	scene.Add(bgObj);

	//Text Object
	auto textObj = std::make_shared<dae::GameObject>();

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = textObj->AddComponent<dae::TextComponent>(textObj);
	textComponent->SetText("Programming 4 Assignment");
	textComponent->SetFont(font);
	textComponent->SetColor(255, 255, 255, 255);	

	auto textRender = textObj->AddComponent<dae::RenderComponent>(textObj);

	auto textTrans = textObj->AddComponent<dae::TransformComponent>(textObj);
	textTrans->SetLocalPosition(glm::vec2{ 80.f, 20.f});
	scene.Add(textObj);

	//Fps Object
	auto fpsObj = std::make_shared<dae::GameObject>();
	auto fpsTrans = fpsObj->AddComponent<dae::TransformComponent>(fpsObj);
	fpsTrans->SetLocalPosition(glm::vec2{ 10.f, 10.f });	
	
	auto fpsRender = fpsObj->AddComponent<dae::RenderComponent>(fpsObj);

	auto fpsText = fpsObj->AddComponent<dae::TextComponent>(fpsObj);
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 16);
	fpsText->SetFont(font);
	fpsText->SetColor(255, 255, 0, 255);

	auto fpsComponent = fpsObj->AddComponent<dae::FPSComponent>(fpsObj);	
	scene.Add(fpsObj);

	//Transform test
	auto transObj1 = std::make_shared<dae::GameObject>();
	auto trans1 = transObj1->AddComponent<dae::TransformComponent>(transObj1);
	trans1->SetLocalPosition(glm::vec2{ 10.f, 10.f });


	auto transObj2 = std::make_shared<dae::GameObject>();
	auto trans2 = transObj2->AddComponent<dae::TransformComponent>(transObj2);
	trans2->SetLocalPosition(glm::vec2{ 10.f, 10.f });

	auto transObj3 = std::make_shared<dae::GameObject>();
	auto trans3 = transObj3->AddComponent<dae::TransformComponent>(transObj3);
	trans3->SetLocalPosition(glm::vec2{ 30.f, 30.f });

	transObj2->SetParent(transObj1, false);

	glm::vec3 pos = trans2->GetWorldPosition();

	std::cout << "\nWorld Pos X: " << pos.x << " Pos Y: " << pos.y << " Pos Z: " << pos.z << "\n";

	pos = trans2->GetLocalPosition();
	std::cout << "Local Pos X: " << pos.x << " Pos Y: " << pos.y << " Pos Z: " << pos.z << "\n";
	transObj2->SetParent(transObj3, true);
	

	pos = trans2->GetWorldPosition();
	std::cout << "World Pos X: " << pos.x << " Pos Y: " << pos.y << " Pos Z: " << pos.z << "\n";
	pos = trans2->GetLocalPosition();

	std::cout << "Local Pos X: " << pos.x << " Pos Y: " << pos.y << " Pos Z: " << pos.z << "\n";
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}