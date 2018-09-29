#include "GUIComponent.hpp"

GUIComponent::GUIComponent()
	: mCanBeSelected(false),
	mCanBeActive(false),
	mIsSelected(false),
	mIsActive(false)
{
}

GUIComponent::~GUIComponent()
{
}

bool GUIComponent::canBeSelected() const
{
	return mCanBeSelected;
}

bool GUIComponent::isSelected() const
{
	return mIsSelected;
}

void GUIComponent::select()
{
	mIsSelected = true;
}

void GUIComponent::deselect()
{
	mIsSelected = false;
}

void GUIComponent::setSelectable(bool canBeSelected)
{
	mCanBeSelected = canBeSelected;
}

bool GUIComponent::canBeActive() const
{
	return mCanBeActive;
}

bool GUIComponent::isActive() const
{
	return mIsActive;
}

void GUIComponent::activate()
{
	mIsActive = true;
}

void GUIComponent::deactivate()
{
	mIsActive = false;
}

void GUIComponent::setActiveMode(bool canBeActive)
{
	mCanBeActive = canBeActive;
}

void GUIComponent::handleEvent(const sf::Event & event)
{
}

bool GUIComponent::contains(const sf::Vector2f & vector) const
{
	return false;
}
