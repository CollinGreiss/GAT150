#include "Json.h"

#include "FileIO.h"
#include "Logger.h"
#include <sstream>

#include "rapidjson/include/istreamwrapper.h"
#include <rapidjson/include/writer.h>
#include <rapidjson/include/stringbuffer.h>

namespace kiko {

	bool Json::Load(const std::string& filename, rapidjson::Document& document) {

		std::string buffer;

		if (!kiko::readFile(filename, buffer)) {

			WARNING_LOG("Cannot open file: " << filename);
			return false;

		}

		std::stringstream stream(buffer);
		rapidjson::IStreamWrapper istream(stream);
		
		document.ParseStream(istream);
		
		if (!document.IsObject()) {
			WARNING_LOG("Json file cannot be parsed: " << filename);
			return false;
		}
	
		return true;
	
	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, int& data, bool required) {

		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsInt()) {

			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;

		}

		data = value[name.c_str()].GetInt();
		return true;

	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, float& data, bool required) {

		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsNumber()) {

			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;

		}

		data = value[name.c_str()].GetFloat();
		return true;

	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required) {

		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsBool()) {

			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;

		}

		data = value[name.c_str()].GetBool();
		return true;

	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required) {

		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsString()) {

			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;

		}

		data = value[name.c_str()].GetString();
		return true;

	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, vec2& data, bool required) {

		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 2) {

			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;
		
		}
		
		auto& array = value[name.c_str()];
		
		for (rapidjson::SizeType i = 0; i < array.Size(); i++) {

			if (!array[i].IsNumber()) {

				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;
			
			}
			
			data[i] = array[i].GetFloat();
		
		}
		
		return true;

	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, Color& data, bool required) {

		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4) {

			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;

		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++) {

			if (!array[i].IsNumber()) {

				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;

			}

			data[i] = array[i].GetFloat();

		}

		return true;

	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool required) {

		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray() || value[name.c_str()].Size() != 4) {

			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;

		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++) {

			if (!array[i].IsNumber()) {

				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;

			}

			data[i] = array[i].GetInt();

		}

		return true;

	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data, bool required) {

		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray()) {

			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;

		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++) {

			if (!array[i].IsString()) {

				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;

			}

			data.push_back(array[i].GetString());

		}

		return true;

	}

	bool Json::Read(const rapidjson::Value& value, const std::string& name, std::vector<int>& data, bool required) {

		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray()) {

			if (required) ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;

		}

		auto& array = value[name.c_str()];

		for (rapidjson::SizeType i = 0; i < array.Size(); i++) {

			if (!array[i].IsNumber()) {

				ERROR_LOG("Invalid json data type: " << name.c_str());
				return false;

			}

			data.push_back(array[i].GetInt());

		}

		return true;

	}



	bool Json::Write(rapidjson::Value& document, rapidjson::Value& value, const std::string& name, std::vector<int>& data, const std::string& filename) {


		if (!value.HasMember(name.c_str()) || !value[name.c_str()].IsArray()) {

			ERROR_LOG("Cannot read required json data: " << name.c_str());
			return false;

		}

		auto& array = value[name.c_str()];
		
		for (rapidjson::SizeType i = 0; i < array.Size() - 1; i++) {

			if (array[i].IsInt()) {

				array[i].SetInt( data[i] );

			}

		}

		rapidjson::StringBuffer buffer;
		rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
		document.Accept(writer);

		std::ofstream outFile(filename);

		if (!outFile.is_open()) {

			ERROR_LOG("Failed to open file for writing: " << filename);
			return false;

		}

		outFile << buffer.GetString();
		outFile.close();


	}
	
}