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
static inline FactoryRegister factoryRegister;              \


#define IMPLEMENT_FACTORY_REGISTER(Type) Type::FactoryRegister::FactoryRegister()


template<typename T>
class Factorable {

protected:
    class FactorableTypeInfo {
    public:
        using FactoryArgType = std::vector<std::string>;
        using FactoryRType = std::shared_ptr<T>;
        using FactoryType = std::function<FactoryRType(FactoryArgType)>;

        FactorableTypeInfo() = default;

        FactorableTypeInfo(const FactoryType &factory) : factory(factory) {};

        FactoryType factory;
    };

private:
    static inline std::map<std::string, FactorableTypeInfo> factories;

protected:
    static void registerFactory(const std::string &, const FactorableTypeInfo &);

public:

    class TypeFactoryDoesNotExistException : public std::exception {

    public:
        TypeFactoryDoesNotExistException() : std::exception("type info does not exist") {}
    };

    static typename FactorableTypeInfo::FactoryRType
    createType(const std::string &key, const typename FactorableTypeInfo::FactoryArgType &arguments);

};

template<typename T>
typename Factorable<T>::FactorableTypeInfo::FactoryRType
Factorable<T>::createType(const std::string &key,
                          const typename Factorable::FactorableTypeInfo::FactoryArgType &arguments) {
    if (!factories.count(key)) throw TypeFactoryDoesNotExistException();
    return factories[key].factory(arguments);
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


//Event::EventTypeInfo::FactoryRType
//Event::createEvent(const string &key, const Event::EventTypeInfo::FactoryArgType &arguments) {
//    if (!events.count(key)) throw EventDoesNotExistException();
//    return events[key].factory(arguments);
//}



#endif //TECHNION_234124_FACTORY_H
