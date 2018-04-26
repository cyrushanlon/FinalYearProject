template<class T>
std::shared_ptr<T> load(std::string uri)
{
    if (this->resources.count(uri) != 1)
    {
        std::shared_ptr<T> rsc = std::shared_ptr<T>(new T);
        rsc.get()->loadFromFile(uri);

        Resource<T>* newResource = new Resource<T>(rsc);

        resources.insert({uri, newResource});
    }

    //resources[uri]->Useage++;
    auto rsc = resources[uri];

    return dynamic_cast<Resource<T>*>(rsc)->resource;
}