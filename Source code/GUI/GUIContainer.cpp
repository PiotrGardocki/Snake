#include "GUIContainer.hpp"

GUIContainer::GUIContainer(const sf::RenderWindow & mouseRelativeTo)
	: mSelectedComponent(-1),
	mMouseControlEnable(false),
	mKeyboardControlEnable(true),
	mCurrentControl(none),
	mMouseRelativeTo(mouseRelativeTo)
{
}

void GUIContainer::packComponent(std::shared_ptr<GUIComponent> component)
{
	mComponents.push_back(component);

	if (mCurrentControl == keyboard && !hasSelection())
		selectNext();
}

void GUIContainer::setMouseControl(bool flag)
{
	mMouseControlEnable = flag;
}

void GUIContainer::setKeyboardControl(bool flag)
{
	mKeyboardControlEnable = flag;
}

bool GUIContainer::canBeSelected() const
{
	return false;
}

bool GUIContainer::canBeActive() const
{
	return false;
}

void GUIContainer::handleEvent(const sf::Event & event)
{
	if (hasSelection() && mComponents[mSelectedComponent]->isActive())
	{
		mComponents[mSelectedComponent]->handleEvent(event);
		return;
	}
	
	if (event.type == sf::Event::MouseMoved)
	{
		if (mMouseControlEnable)
		{
			setControl(mouse);
			checkMouseSelect(sf::Vector2i(event.mouseMove.x, event.mouseMove.y));
		}
		return;
	}
	if (event.type == sf::Event::MouseButtonReleased)
	{
		if (mCurrentControl == mouse && hasSelection())
			mComponents[mSelectedComponent]->activate();
		return;
	}
	if (event.type == sf::Event::KeyReleased)
	{
		if (mKeyboardControlEnable)
		{
			setControl(keyboard);
			auto & code = event.key.code;
			if (code == sf::Keyboard::W || code == sf::Keyboard::Up)
			{
				setControl(keyboard);
				selectPrevious();
			}
			else if (code == sf::Keyboard::S || code == sf::Keyboard::Down)
			{
				setControl(keyboard);
				selectNext();
			}
			else if ((code == sf::Keyboard::Enter || code == sf::Keyboard::Space) && hasSelection())
			{
				setControl(keyboard);
				mComponents[mSelectedComponent]->activate();
			}
			return;
		}
	}
}

void GUIContainer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	for (auto & component : mComponents)
		target.draw(*component, states);
}

bool GUIContainer::hasSelection() const
{
	return mSelectedComponent >= 0;
}

void GUIContainer::select(short index)
{
	if (index >= mComponents.size() || !mComponents[index]->canBeSelected())
		return;
	if (hasSelection())
		mComponents[mSelectedComponent]->deselect();
	mSelectedComponent = index;
	mComponents[mSelectedComponent]->select();
}

void GUIContainer::selectNext()
{
	if (hasSelection())
	{
		int index = mSelectedComponent + 1;
		while (index != mSelectedComponent)
		{
			index = index % mComponents.size();
			if (mComponents[index]->canBeSelected())
			{
				select(index);
				break;
			}
			++index;
		}
	}
	else
	{
		for (short index = 0; index < mComponents.size(); ++index)
		{
			if (mComponents[index]->canBeSelected())
			{
				select(index);
				break;
			}
		}
	}
}

void GUIContainer::selectPrevious()
{
	if (hasSelection())
	{
		int index = mSelectedComponent - 1;
		while (index != mSelectedComponent)
		{
			index = (index + mComponents.size()) % mComponents.size();
			if (mComponents[index]->canBeSelected())
			{
				select(index);
				break;
			}
			--index;
		}
	}
	else
	{
		for (short index = 0; index < mComponents.size(); ++index)
		{
			if (mComponents[index]->canBeSelected())
			{
				select(index);
				break;
			}
		}
	}
}

void GUIContainer::checkMouseSelect(const sf::Vector2i & mouse)
{
	sf::Vector2f mousePoss = mMouseRelativeTo.mapPixelToCoords(mouse);
	mousePoss = getInverseTransform().transformPoint(mousePoss);

	for (short index = 0; index < mComponents.size(); ++index)
	{
		if (mComponents[index]->contains(mousePoss) && mComponents[index]->canBeSelected())
		{

			select(index);
			return;
		}
	}

	if (hasSelection())
	{
		mComponents[mSelectedComponent]->deselect();
		mSelectedComponent = -1;
	}
}

void GUIContainer::setControl(CurrentControl control)
{
	switch (control)
	{
	case GUIContainer::mouse:
		if (mMouseControlEnable)
		{
			mCurrentControl = mouse;
		}
		break;

	case GUIContainer::keyboard:
		if (mKeyboardControlEnable)
		{
			mCurrentControl = keyboard;
		}
		break;

	case GUIContainer::none:
		if (hasSelection())
			mComponents[mSelectedComponent]->deselect();
		mSelectedComponent = -1;
		break;
	}
}
