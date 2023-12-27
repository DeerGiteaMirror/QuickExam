//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <components/ErrorHandler.h>
#include <dto/Configuration.h>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/network/tcp/server/ConnectionProvider.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/HttpConnectionHandler.hpp>
#include <oatpp/web/server/HttpRouter.hpp>
#include <oatpp/web/server/interceptor/AllowCorsGlobal.hpp>

namespace QuickExam::component {

class ServiceComponent {
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, m_objectMapper)
    ([] {
        auto mapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
        mapper->getSerializer()->getConfig()->useBeautifier = true;
        mapper->getSerializer()->getConfig()->escapeFlags   = 0;
        return mapper;
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>,
                           serverConnectionProvider)
    ([] {
        OATPP_COMPONENT(oatpp::Object<dto::Configuration>, config);  // Get config component
        return oatpp::network::tcp::server::ConnectionProvider::createShared(
            {config->host, config->port, oatpp::network::Address::IP_4});
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)
    ([] { return oatpp::web::server::HttpRouter::createShared(); }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>,
                           serverConnectionHandler)
    ([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>,
                        router);        // get Router component
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>,
                        objectMapper);  // get ObjectMapper component
        auto connectionHandler = oatpp::web::server::HttpConnectionHandler::createShared(router);
        connectionHandler->setErrorHandler(std::make_shared<ErrorHandler>(objectMapper));

        /* Add CORS request and response interceptors */
        auto allow_cors = std::make_shared<oatpp::web::server::interceptor::AllowCorsGlobal>(
            "*", "GET, POST, OPTIONS, PUT, DELETE, PATCH", "*");
        connectionHandler->addRequestInterceptor(
            std::make_shared<oatpp::web::server::interceptor::AllowOptionsGlobal>());
        connectionHandler->addResponseInterceptor(allow_cors);
        return connectionHandler;
    }());
};
}  // namespace QuickExam::component
