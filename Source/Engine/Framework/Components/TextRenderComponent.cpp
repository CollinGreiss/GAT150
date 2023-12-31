#include "TextRenderComponent.h"

#include "Framework/Resource/ResourceManager.h"
#include "Framework/Actor.h"

namespace kiko {

	CLASS_DEFINITION(TextRenderComponent);
	
	TextRenderComponent::TextRenderComponent(const TextRenderComponent& other) {

		text = other.text;
		fontName = other.fontName;
		fontSize = other.fontSize;

		m_changed = true;
		m_text = std::make_unique<Text>(*other.m_text.get());

	}

	bool TextRenderComponent::Initialize() {

		if (!fontName.empty()) // <GET_RESOURCE with font type, font name and fontsize>
			m_text = std::make_unique<kiko::Text>(GET_RESOURCE(Font, fontName, fontSize));
		
		return true;

	}

	void TextRenderComponent::Update(float dt) {}
	
	void TextRenderComponent::Draw(Renderer& renderer) {

		if (m_changed) {
			m_changed = false;
			m_text->Create(renderer, text, color);
		}

		m_text->Draw(renderer, m_owner->GetTransform());

	}

	void TextRenderComponent::SetText(const std::string& string) {
		
		if (string != text) {
			text = string;
			m_changed = true;
		}

	}

	void TextRenderComponent::Read(const json_t& value) {

		READ_DATA(value, text);
		READ_DATA(value, fontName);
		READ_DATA(value, fontSize);
		READ_DATA(value, color);

	}

}