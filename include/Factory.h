//
// Created by jamal on 07/08/2024.
//

#ifndef TECHNION_234124_FACTORY_H
#define TECHNION_234124_FACTORY_H

#include <map>
#include <vector>
#include <string>
#include <functional>


#define CREATE_FACTORY_REGISTER()     class FactoryRegister { \
public:\
FactoryRegister();\
};\
\
static inline FactoryRegister factoryRegister{};              \


#define IMPLEMENT_FACTORY_REGISTER(Type)  \
Type::FactoryRegister::FactoryRegister()

class TypeFactoryDoesNotExistException : public std::exception {

public:
    TypeFactoryDoesNotExistException() : std::exception("type info does not exist") {}
};

template<typename T>
class Factorable {

protected:
    class FactorableTypeInfo {
    public:
        using FactoryArgType = std::vector<std::string>;
        using FactoryRType = std::shared_ptr<T>;
        using FactoryType = std::function<FactoryRType(FactoryArgType)>;

    private:
        FactoryType factory;
    public:

        FactorableTypeInfo() = default;

        FactorableTypeInfo(const FactoryType &factory) : factory(factory) {};

        FactoryRType operator()(const FactoryArgType &);

        FactoryRType operator()();

    };

private:
    static inline std::map<std::string, FactorableTypeInfo> factories{};

protected:
    static void registerFactory(const std::string &, const FactorableTypeInfo &);

    static void registerFactory(const std::string &, const typename FactorableTypeInfo::FactoryType &);

    static void
    registerFactory(const std::string &, const std::function<typename FactorableTypeInfo::FactoryRType()> &);


public:


    static typename FactorableTypeInfo::FactoryRType
    createType(const std::string &key, const typename FactorableTypeInfo::FactoryArgType &arguments);

    static std::map<std::string, FactorableTypeInfo> getFactories();

    static std::vector<std::string> getFactoryKeys();
};

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
//    return this->operator()(arguments);
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
std::map<std::string, typename Factorable<T>::FactorableTypeInfo> Factorable<T>::getFactories() {
    return factories;
}

template<typename T>
std::vector<std::string> Factorable<T>::getFactoryKeys() {
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
    if (!factories.count(key)) throw TypeFactoryDoesNotExistException();
    return factories[key](arguments);
}


template<typename T>
void Factorable<T>::registerFactory(const std::string &key, const Factorable::FactorableTypeInfo &info) {
    factories.insert(
            std::pair(
                    key,
                    info
            )
    );
}


#endif //TECHNION_234124_FACTORY_H
