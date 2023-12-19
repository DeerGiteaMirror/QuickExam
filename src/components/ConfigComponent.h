//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/Configuration.h>
#include <oatpp/core/base/CommandLineArguments.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>

namespace QuickExam::component {

class ConfigComponent {
private:
    oatpp::base::CommandLineArguments m_cmdArgs;

public:
    explicit ConfigComponent(const oatpp::base::CommandLineArguments &cmdArgs)
        : m_cmdArgs(cmdArgs) {}

public:
    OATPP_CREATE_COMPONENT(oatpp::Object<dto::Configuration>, config)
    ([this] {
        const char *configPath = m_cmdArgs.getNamedArgumentValue("--profile", "./config.json");

        oatpp::String configText = oatpp::String::loadFromFile(configPath);
        if (configText == nullptr) {
            throw std::runtime_error("[AppComponent]: Can't load configuration file");
        }
        auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        auto profile = objectMapper->readFromString<oatpp::Object<dto::Configuration>>(configText);
        return profile;
    }());

    OATPP_CREATE_COMPONENT(oatpp::Object<dto::DataBase>, dbConfig)
    ([this] {
        OATPP_COMPONENT(oatpp::Object<dto::Configuration>, profile);  // 获取配置组件
        return profile->database;
    }());
};

}  // namespace QuickExam::component