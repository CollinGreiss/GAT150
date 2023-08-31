#include "Scene.h"

#include "Components/CollisionComponent.h"

namespace kiko {

	bool Scene::Initialize() {

		for (auto& actor : m_actors)
			actor->Initialize();

		return true;

	}

	void Scene::Update(float dt) {

		auto iter = m_actors.begin();
		while (iter != m_actors.end()) {

			if (!(*iter)->disabled) (*iter)->Update(dt);
			((*iter)->m_destroyed) ? iter = m_actors.erase(iter) : iter++;

		}

	}

	void Scene::Draw(Renderer& renderer) {

		for (auto& actor : m_actors)
			if (!actor->disabled) actor->Draw(renderer);

	}

	void Scene::Add(std::unique_ptr<Actor> actor) {

		actor->m_scene = this;
		m_actors.push_back(std::move(actor));

	}

	void Scene::RemoveAll(bool force) {

		auto iter = m_actors.begin();
		while (iter != m_actors.end()) {

			if (!(*iter)->isPersistent() || force) {
				
				(*iter)->Remove();
				iter = m_actors.erase(iter);
				
			} else
				iter++;

		}


	}

	bool Scene::Load(const std::string& filename) {

		rapidjson::Document document;
		if (!Json::Load(filename, document)) {

			ERROR_LOG("Could not load scene file! " << filename);
			return false;

		}

		Read(document);

		return false;

	}

	void Scene::Read(const json_t& value) {

		if (HAS_DATA(value, actors) && GET_DATA(value, actors).IsArray()) {

			for (auto& actorValue : GET_DATA(value, actors).GetArray()) {

				std::string type;
				READ_DATA(actorValue, type);

				auto actor = CREATE_CLASS_BASE(Actor, type);

				if (!actor) return;

				actor->Read(actorValue);

				if (actor->prototype) {

					std::string name = actor->name;
					//if (!ACTOR_REGISTERED(name))
						Factory::Instance().RegisterPrototype(name, std::move(actor));

				} else {

					Add(std::move(actor));

				}

			}

		}

	}

}