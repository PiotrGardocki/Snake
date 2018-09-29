template <typename Resource>
void centerOrigin(Resource & resource)
{
	sf::FloatRect bounds = resource.getLocalBounds();
	resource.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}