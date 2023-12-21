//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/Configuration.h>
#include <oatpp-swagger/Model.hpp>
#include <oatpp-swagger/Resources.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/core/utils/ConversionUtils.hpp>

namespace QuickExam::component {

class SwaggerComponent {
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)
    ([] {
        OATPP_COMPONENT(oatpp::Object<dto::Configuration>, config);
        oatpp::swagger::DocumentInfo::Builder builder;
        builder.setTitle("QuickExam")
            .setDescription("QuickExam Swagger API Docs")
            .setVersion("1.0")
            .addServer("http://" + config->host + ":" + std::to_string(config->port),
                       "server on web server")
            .addServer(config->swagger_host, "server on localhost");

        return builder.build();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)
    ([] {
        OATPP_COMPONENT(oatpp::Object<dto::Configuration>, config);
        return oatpp::swagger::Resources::loadResources(config->resource + "/swagger-ui");
    }());
};
}  // namespace QuickExam::component