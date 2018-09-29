template<typename Identifier, typename Resource>
void ResourceStorage<Identifier, Resource>::load(Identifier id, const std::string & filename)
{
	std::unique_ptr<Resource> resource(new Resource());
	resource->loadFromFile(filename);
	mResources.insert(std::make_pair(id, std::move(resource)));
}

template<typename Identifier, typename Resource>
Resource & ResourceStorage<Identifier, Resource>::get(Identifier id)
{
	auto found = mResources.find(id);
	return *found->second;
}

template<typename Identifier, typename Resource>
const Resource & ResourceStorage<Identifier, Resource>::get(Identifier id) const
{
	auto found = mResources.find(id);
	return *found->second;
}
