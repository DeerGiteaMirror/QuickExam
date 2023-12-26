//
// AnonExam
// Created on 2023/12/18.
//

#include <components/ConfigComponent.h>
#include <components/DatabaseComponent.h>
#include <components/ServiceComponent.h>
#include <components/SwaggerComponent.h>
#include <controller/AnswerContentController.h>
#include <controller/AnswerController.h>
#include <controller/QuestionContentController.h>
#include <controller/QuestionController.h>
#include <controller/TagController.h>
#include <iostream>
#include <oatpp-swagger/Controller.hpp>
#include <oatpp/core/base/CommandLineArguments.hpp>
#include <oatpp/network/Server.hpp>
#include <utils/Logger.h>

void run(const oatpp::base::CommandLineArguments &args) {
    using namespace QuickExam::component;
    ConfigComponent   configComponent(args);
    ServiceComponent  serviceComponent;
    DataBaseComponent databaseComponent;
    SwaggerComponent  swaggerComponent;

    auto router = serviceComponent.httpRouter.getObject();
    using namespace QuickExam::controller;
    auto questionController        = router->addController(QuestionController::make());
    auto questionContentController = router->addController(QuestionContentController::make());
    auto answerController          = router->addController(AnswerController::make());
    auto answerContentController   = router->addController(AnswerContentController::make());
    auto tagController             = router->addController(TagController::make());

#ifndef NDEBUG
    // 把路由添加到 Swagger
    oatpp::web::server::api::Endpoints swaggerDocEndpoints;
    swaggerDocEndpoints.append(questionController->getEndpoints());
    swaggerDocEndpoints.append(questionContentController->getEndpoints());
    swaggerDocEndpoints.append(answerController->getEndpoints());
    swaggerDocEndpoints.append(answerContentController->getEndpoints());
    swaggerDocEndpoints.append(tagController->getEndpoints());

    router->addController(oatpp::swagger::Controller::createShared(swaggerDocEndpoints));
#endif

    oatpp::network::Server server(serviceComponent.serverConnectionProvider.getObject(),
                                  serviceComponent.serverConnectionHandler.getObject());

    auto        connProv = serviceComponent.serverConnectionProvider.getObject();
    std::string port     = connProv->getProperty("port").toString()->c_str();
    std::string host     = connProv->getProperty("host").toString()->c_str();

    LOGI("Server", "Listing on %s ...", (host + ":" + port).c_str());

    server.run();
}

int main(int argc, const char *argv[]) {
    oatpp::base::Environment::init();
    run(oatpp::base::CommandLineArguments(argc, argv));
    oatpp::base::Environment::destroy();
    return 0;
}