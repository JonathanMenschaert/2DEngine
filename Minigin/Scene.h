#pragma once
//#include "SceneManager.h"
#include <memory>
#include <string>
#include <vector>

namespace dae
{
	class GameObject;
	class Scene final
	{
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		void SetObjectPersistent(std::shared_ptr<GameObject> persistentObject);

		void SetPersistentObjects(std::vector<std::shared_ptr<GameObject>> persistentObject);
		std::vector<std::shared_ptr<GameObject>> GetPersistentObjects(bool emptyPersistentVector = true);

		void Init();
		void Update();
		void LateUpdate();
		void Render() const;
		void OnGui();

		explicit Scene(const std::string& name);
		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 

		std::string m_name;
		std::vector <std::shared_ptr<GameObject>> m_Objects{};
		std::vector <std::shared_ptr<GameObject>> m_PersistentObjects{};

		static unsigned int m_idCounter; 
	};

}
