#pragma once

#include "Singleton.h"

#include <memory>
#include <map>
#include <string>

namespace kiko {

	class CreatorBase {

	public:

		virtual ~CreatorBase() = default;

		virtual std::unique_ptr<class Object> Create() = 0;

	};

	template <typename T>
	class Creator : public CreatorBase {

		virtual std::unique_ptr<T> Create() override {

			return std::make_unique<T>();

		}

	};

	class Factory : public Singleton<Factory> {

	public:

		template <typename T>
		void Register(const std::string& key);

		template <typename T>
		std::unique_ptr<T> Create(const std::string& key);

	private:

		std::map<std::string, std::unique_ptr<CreatorBase>> m_registy;

	};

	template<typename T>
	inline void Factory::Register(const std::string& key) {

		m_registy[key] = std::make_unique<Create<T>>();

	}

	template<typename T>
	inline std::unique_ptr<T> Factory::Create(const std::string& key) {


		auto iter = m_registy.find(key);
		if (iter != m_registy.end())
			return std::unique_ptr<T>(iter->second->Create());

		return std::unique_ptr<T>();
	
	}

}