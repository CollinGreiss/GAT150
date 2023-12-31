#pragma once
#include <list>
#include "Actor.h"

namespace kiko {

	class Renderer;

	class Scene {

	public:

		Scene() = default;

		bool Initialize();
		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll(bool force = false);

		bool Load(const std::string& filename);
		void Read(const json_t& value);

		bool LoadLevel() { return Load(m_level); }
		void SetLevel(const std::string& level, bool load = true) { m_level = level; if (load) LoadLevel(); }
		const std::string& GetLevel() { return m_level; }

		template<typename T = Actor>
		void SetDisabledAll(bool disabled);

		template<typename T>
		T* GetActor();

		template<typename T = Actor>
		T* GetActor(const std::string& name);

		template<typename T = Actor>
		T* GetTile(const vec2 position);



	private:

		std::string m_level;
		std::list< std::unique_ptr<Actor> > m_actors;

	};

	template<typename T>
	inline void Scene::SetDisabledAll(bool disabled) {

		for (auto& actor : m_actors) {

			T* result = dynamic_cast<T*> (actor.get());
			if (result) result->disabled = disabled;

		}

	}

	template<typename T>
	inline T* Scene::GetActor() {

		for (auto& actor : m_actors) {

			T* result = dynamic_cast<T*> (actor.get());
			if (result) return result;

		}

		return nullptr;

	}

	template<typename T>
	inline T* Scene::GetActor(const std::string& name)
	{

		for (auto& actor : m_actors) {

			if (actor->name == name) {

				T* result = dynamic_cast<T*> (actor.get());
				if (result) return result;

			}

		}

		return nullptr;

	}

	template<typename T>
	inline T* Scene::GetTile(const vec2 position) {

		for (auto& actor : m_actors) {

			if (actor->GetTransform().position == position && actor->name != "Select") {

				T* result = dynamic_cast<T*> (actor.get());
				if (result) return result;

			}

		}

		return nullptr;

	}

}