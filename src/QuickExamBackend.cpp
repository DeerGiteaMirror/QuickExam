//
// AnonExam
// Created on 2023/12/18.
//

#include <components/ConfigComponent.h>
#include <components/DatabaseComponent.h>
#include <components/ServiceComponent.h>
#include <components/SwaggerComponent.h>
#include <controller/AnswerController.h>
#include <controller/QuestionController.h>
#include <iostream>
#include <oatpp-swagger/Controller.hpp>
#include <oatpp/core/base/CommandLineArguments.hpp>
#include <oatpp/network/Server.hpp>

void run(const oatpp::base::CommandLineArguments &args) {
    using namespace QuickExam::component;
    ConfigComponent   configComponent(args);
    ServiceComponent  serviceComponent;
    DataBaseComponent databaseComponent;
    SwaggerComponent  swaggerComponent;

    auto router = serviceComponent.httpRouter.getObject();
    using namespace QuickExam::controller;
    auto answerController   = router->addController(AnswerController::make());
    auto questionController = router->addController(QuestionController::make());

#ifndef NDEBUG
    // 把路由添加到 Swagger
    oatpp::web::server::api::Endpoints swaggerDocEndpoints;
    swaggerDocEndpoints.append(answerController->getEndpoints());
    swaggerDocEndpoints.append(questionController->getEndpoints());

    router->addController(oatpp::swagger::Controller::createShared(swaggerDocEndpoints));
#endif

    oatpp::network::Server server(serviceComponent.serverConnectionProvider.getObject(),
                                  serviceComponent.serverConnectionHandler.getObject());

    auto        connProv = serviceComponent.serverConnectionProvider.getObject();
    std::string port     = connProv->getProperty("port").toString()->c_str();
    std::string host     = connProv->getProperty("host").toString()->c_str();

    server.run();
}

int main(int argc, const char *argv[]) {
    oatpp::base::Environment::init();
    run(oatpp::base::CommandLineArguments(argc, argv));
    oatpp::base::Environment::destroy();
    return 0;
}