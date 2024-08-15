//
// Created by jamal on 15/08/2024.
//
#include "Factory.h"


template<typename T>
typename Factorable<T>::FactoriesType &Factorable<T>::getFactory() {
    static auto *factories = new FactoriesType();

    return *factories;
}

template<typename T>
typename Factorable<T>::FactorableTypeInfo::FactoryRType
Factorable<T>::FactorableTypeInfo::operator()(const Factorable::FactorableTypeInfo::FactoryArgType &arguments) {
    return factory(arguments);
}


template<typename T>
typename Factorable<T>::FactorableTypeInfo::FactoryRType
Factorable<T>::FactorableTypeInfo::operator()() {
    Factorable::FactorableTypeInfo::FactoryArgType arguments;
    return factory(arguments);
}

template<typename T>
void Factorable<T>::registerFactory(const std::string &key,
                                    const std::function<typename FactorableTypeInfo::FactoryRType()> &factory) {
    registerFactory(key, FactorableTypeInfo([factory](const typename FactorableTypeInfo::FactoryArgType &) {
        return factory();
    }));
}

template<typename T>
void Factorable<T>::registerFactory(const std::string &key,
                                    const typename Factorable::FactorableTypeInfo::FactoryType &factory) {
    registerFactory(key, FactorableTypeInfo(factory));
}


template<typename T>
std::vector<std::string> Factorable<T>::getFactoryKeys() {
    auto factories = getFactory();
    std::vector<std::string> keys;
    keys.reserve(factories.size());
    for (const auto &[key, _]: factories) {
        keys.push_back(key);
    }
    return keys;
}

template<typename T>
typename Factorable<T>::FactorableTypeInfo::FactoryRType
Factorable<T>::createType(const std::string &key,
                          const typename Factorable::FactorableTypeInfo::FactoryArgType &arguments) {
    auto factories = getFactory();
    if (!factories.count(key)) throw TypeFactoryDoesNotExistException();
    return factories[key](arguments);
}


template<typename T>
void Factorable<T>::registerFactory(const std::string &key, const Factorable::FactorableTypeInfo &info) {
    FactoriesType &factory = getFactory();

    factory.insert(
            std::pair(
                    key,
                    std::move(info)
            )
    );
}

class Player;

template
class Factorable<Player>;


class Strategy;

template
class Factorable<Strategy>;


class Event;

template
class Factorable<Event>;


class Monster;

template
class Factorable<Monster>;
