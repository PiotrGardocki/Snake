#ifndef GUICONTAINER_HPP_
#define GUICONTAINER_HPP_

#include <vector>
#include <memory>
#include "GUIComponent.hpp"

class GUIContainer : public GUIComponent
{
    public:
        GUIContainer(const sf::RenderWindow & mouseRelativeTo);

		void packComponent(std::shared_ptr<GUIComponent> component);

		void setMouseControl(bool flag);
		void setKeyboardControl(bool flag);

		virtual bool canBeSelected() const override;
		virtual bool canBeActive() const override;
		virtual void handleEvent(const sf::Event & event) override;

	private:
		virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

		bool hasSelection() const;
		void select(short index);
		void selectNext();
		void selectPrevious();

		void checkMouseSelect(const sf::Vector2i & mouse);

		enum CurrentControl
		{
			mouse,
			keyboard,
			none
		};
		
		void setControl(CurrentControl control);

    private:
		std::vector<std::shared_ptr<GUIComponent>> mComponents;
		short mSelectedComponent;
		
		bool mMouseControlEnable;
		bool mKeyboardControlEnable;

		CurrentControl mCurrentControl;
		const sf::RenderWindow & mMouseRelativeTo;
};

#endif // GUICONTAINER_HPP_
