//
// Created by jamal on 07/08/2024.
//

#ifndef TECHNION_234124_FACTORY_H
#define TECHNION_234124_FACTORY_H

#include <map>
#include <vector>
#include <string>
#include <functional>
#include <stdexcept>


#define CREATE_FACTORY_REGISTER()     class FactoryRegister { \
public:\
FactoryRegister();\
};\
\
static inline FactoryRegister factoryRegister{};              \


#define IMPLEMENT_FACTORY_REGISTER(Type)  \
Type::FactoryRegister::FactoryRegister()

class TypeFactoryDoesNotExistException : public std::runtime_error {

public:
    TypeFactoryDoesNotExistException() : std::runtime_error("type info does not exist") {}
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

public:
    using FactoriesType = std::map<std::string, FactorableTypeInfo>;

    static inline FactoriesType m_factories;

protected:
    static void registerFactory(const std::string &, const FactorableTypeInfo &);

    static void registerFactory(const std::string &, const typename FactorableTypeInfo::FactoryType &);

    static void
    registerFactory(const std::string &, const std::function<typename FactorableTypeInfo::FactoryRType()> &);

    static FactoriesType& getFactory();


public:


    static typename FactorableTypeInfo::FactoryRType
    createType(const std::string &key, const typename FactorableTypeInfo::FactoryArgType &arguments);

//    static std::map<std::string, FactorableTypeInfo> getFactories();

    static std::vector<std::string> getFactoryKeys();
};


#endif //TECHNION_234124_FACTORY_H
