//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/Question.h>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace QuickExam::controller {
using namespace oatpp::web::server::api;
using namespace oatpp::parser::json::mapping;
using namespace oatpp;
class QuestionController : public ApiController {
public:
    typedef std::shared_ptr<QuestionController> Ptr;
    explicit QuestionController(const std::shared_ptr<ObjectMapper> &objectMapper)
        : ApiController(objectMapper, "/api/queation") {
        this->objectMapper = objectMapper;
    }

    static Ptr make(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<QuestionController>(objectMapper);
    }

private:
    std::shared_ptr<ObjectMapper> objectMapper;

public:
    ENDPOINT("POST", "/create", createQuestion, BODY_DTO(Object<dto::Question>, request)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(createQuestion) {
        info->summary = "Create Question";
        info->addConsumes<Object<dto::Question>>("application/json");
        info->addResponse(Status::CODE_200);
    }
};

}  // namespace QuickExam::controller

#include OATPP_CODEGEN_BEGIN(ApiController)