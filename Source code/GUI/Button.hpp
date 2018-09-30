#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <functional>
#include <string>
#include "GUIComponent.hpp"

class Button : public GUIComponent
{
    public:
        Button();

		void setText(const std::string & text);
		void setFont(const sf::Font & font);
		void setCharacterSize(unsigned int size);
		void setCallback(std::function<void()> callback);

		void setNormalTexture(const sf::Texture * texture);
		void setSelectTexture(const sf::Texture * texture);
		void setActiveTexture(const sf::Texture * texture);

		virtual void select() override;
		virtual void deselect() override;
		virtual void activate() override;
		virtual void deactivate() override;

		sf::FloatRect getGlobalBounds() const;
		sf::Vector2f getSize() const;
		virtual bool contains(const sf::Vector2f & vector) const override;

	private:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
		void setTexture(const sf::Texture * texture);

    private:
		const sf::Texture * mNormalTexture;
		const sf::Texture * mSelectTexture;
		const sf::Texture * mActiveTexture;

		sf::Sprite mSprite;
		sf::Text mText;
		std::function<void()> mCallback;
};

#endif // BUTTON_HPP_