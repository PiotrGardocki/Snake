#include <utility>
#include "Button.hpp"
#include <Other/Utility.hpp>

Button::Button()
	: mNormalTexture(nullptr),
	mSelectTexture(nullptr),
	mActiveTexture(nullptr)
{
	setSelectable(true);
}

void Button::setText(const std::string & text)
{
	mText.setString(text);
	centerOrigin(mText);
}

void Button::setFont(const sf::Font & font)
{
	mText.setFont(font);
	centerOrigin(mText);
}

void Button::setCharacterSize(unsigned int size)
{
	mText.setCharacterSize(size);
	centerOrigin(mText);
}

void Button::setCallback(std::function<void()> callback)
{
	mCallback = std::move(callback);
}

void Button::setNormalTexture(const sf::Texture * texture)
{
	mNormalTexture = texture;
	setTexture(mNormalTexture);
}

void Button::setSelectTexture(const sf::Texture * texture)
{
	mSelectTexture = texture;
}

void Button::setActiveTexture(const sf::Texture * texture)
{
	mActiveTexture = texture;
}

void Button::select()
{
	GUIComponent::select();
	setTexture(mSelectTexture);
}

void Button::deselect()
{
	GUIComponent::deselect();
	setTexture(mNormalTexture);
}

void Button::activate()
{
	GUIComponent::activate();

	if (canBeActive())
		setTexture(mActiveTexture);

	if (mCallback)
		mCallback();

	if (!canBeActive())
		deactivate();
}

void Button::deactivate()
{
	GUIComponent::deactivate();
	if (isSelected())
		setTexture(mSelectTexture);
	else
		setTexture(mNormalTexture);
}

sf::FloatRect Button::getGlobalBounds() const
{
	return getTransform().transformRect(mSprite.getGlobalBounds());
}

sf::Vector2f Button::getSize() const
{
	sf::FloatRect bounds = mSprite.getLocalBounds();
	return sf::Vector2f(bounds.width, bounds.height);
}

bool Button::contains(const sf::Vector2f & vector) const
{
	return getGlobalBounds().contains(vector);
}

void Button::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mSprite, states);
	target.draw(mText, states);
}

void Button::setTexture(const sf::Texture * texture)
{
	if (texture == nullptr)
		return;
	mSprite.setTexture(*texture);
	sf::FloatRect bounds = mSprite.getLocalBounds();
	mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
}
