#ifndef GUICOMPONENT_HPP_
#define GUICOMPONENT_HPP_

#include <SFML/Graphics.hpp>

class GUIComponent : public sf::Drawable, public sf::Transformable
{
    public:
        GUIComponent();
        virtual ~GUIComponent() = 0;

		virtual bool canBeSelected() const;
		bool isSelected() const;
		virtual void select();
		virtual void deselect();
		void setSelectable(bool canBeSelected);

		virtual bool canBeActive() const;
		bool isActive() const;
		virtual void activate();
		virtual void deactivate();
		void setActiveMode(bool canBeActive);

		virtual void handleEvent(const sf::Event & event);
		virtual bool contains(const sf::Vector2f & vector) const;

    private:
		bool mCanBeSelected;
		bool mCanBeActive;

		bool mIsSelected;
		bool mIsActive;
};

#endif // GUICOMPONENT_HPP_
