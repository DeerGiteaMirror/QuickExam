//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/Answer.h>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace QuickExam::controller {
using namespace oatpp::web::server::api;
using namespace oatpp::parser::json::mapping;
using namespace oatpp;
class AnswerController : public ApiController {
public:
    typedef std::shared_ptr<AnswerController> Ptr;
    explicit AnswerController(const std::shared_ptr<ObjectMapper> &objectMapper)
        : ApiController(objectMapper, "/api/answer") {
        this->objectMapper = objectMapper;
    }

    static Ptr make(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<AnswerController>(objectMapper);
    }

private:
    std::shared_ptr<ObjectMapper> objectMapper;

public:
    ENDPOINT("POST", "/create", createAnswer, BODY_DTO(Object<dto::Answer>, request)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(createAnswer) {
        info->summary = "Create Answer";
        info->addConsumes<Object<dto::Answer>>("application/json");
        info->addResponse(Status::CODE_200);
    }
};

}  // namespace QuickExam::controller

#include OATPP_CODEGEN_BEGIN(ApiController)