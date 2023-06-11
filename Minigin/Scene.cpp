#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void dae::Scene::SetObjectPersistent(std::shared_ptr<GameObject> persistentObject)
{
	m_PersistentObjects.emplace_back(persistentObject);
}

void dae::Scene::SetPersistentObjects(std::vector<std::shared_ptr<GameObject>> persistentObjects)
{
	m_PersistentObjects = persistentObjects;
}

std::vector<std::shared_ptr<GameObject>> dae::Scene::GetPersistentObjects(bool emptyPersistentVector)
{
	std::vector<std::shared_ptr<GameObject>> persistentObjects {m_PersistentObjects};
	if (emptyPersistentVector)
	{
		m_PersistentObjects.clear();
	}
	return persistentObjects ;
}

void dae::Scene::Init()
{
	for (auto& object : m_Objects)
	{
		object->Init();
	}
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void dae::Scene::LateUpdate()
{
	for (auto& object : m_Objects)
	{
		object->LateUpdate();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void dae::Scene::OnGui()
{
	for (auto& object : m_Objects)
	{
		object->OnGui();
	}
}

