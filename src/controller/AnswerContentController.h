//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/Answer.h>
#include <dto/response/AnswerContent.h>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>
#include <service/AnswerService.h>

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace QuickExam::controller {
using namespace oatpp::web::server::api;
using namespace oatpp::parser::json::mapping;
using namespace oatpp;
class AnswerContentController : public ApiController {
public:
    typedef std::shared_ptr<AnswerContentController> Ptr;
    explicit AnswerContentController(const std::shared_ptr<ObjectMapper> &objectMapper)
        : ApiController(objectMapper, "/api/answer/content") {
        this->objectMapper = objectMapper;
    }

    static Ptr make(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<AnswerContentController>(objectMapper);
    }

private:
    std::shared_ptr<ObjectMapper> objectMapper;
    service::AnswerService        answer_service;

public:
    ENDPOINT("POST", "/create", addAnswerContent, BODY_DTO(Object<dto::AnswerContent>, req_body)) {
        return createDtoResponse(Status::CODE_200, answer_service.addAnswerContent(req_body));
    }
    ENDPOINT_INFO(addAnswerContent) {
        info->addTag("Answer Content");
        info->summary     = "Add Answer Content";
        info->description = "Create content for an answer";
        info->addConsumes<Object<dto::AnswerContent>>("application/json");
        info->addResponse<Object<dto::ResponseAnswerContent>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("PUT",
             "/update",
             updateAnswerContent,
             BODY_DTO(Object<dto::AnswerContent>, req_body)) {
        return createDtoResponse(Status::CODE_200, answer_service.updateAnswerContent(req_body));
    }
    ENDPOINT_INFO(updateAnswerContent) {
        info->addTag("Answer Content");
        info->summary     = "Update Answer Content";
        info->description = "Update an answer content";
        info->addConsumes<Object<dto::AnswerContent>>("application/json");
        info->addResponse<Object<dto::ResponseAnswerContent>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("DELETE", "/delete", deleteAnswerContent, QUERY(Int32, content_id)) {
        return createDtoResponse(Status::CODE_200, answer_service.deleteAnswerContent(content_id));
    }
    ENDPOINT_INFO(deleteAnswerContent) {
        info->addTag("Answer Content");
        info->summary                                          = "Delete Answer Content";
        info->description                                      = "Delete an answer content";
        info->queryParams.add<Int32>("content_id").name        = "content_id";
        info->queryParams.add<Int32>("content_id").description = "Content Id";
        info->queryParams.add<Int32>("content_id").required    = true;
        info->addResponse<Object<dto::Response>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("GET", "/get/list/by/answer", getAnswerContentsByAnswerId, QUERY(Int32, answer_id)) {
        return createDtoResponse(Status::CODE_200,
                                 answer_service.getAnswerContentsByAnswerId(answer_id));
    }
    ENDPOINT_INFO(getAnswerContentsByAnswerId) {
        info->addTag("Answer Content");
        info->summary                                         = "Get Answer Contents By Answer Id";
        info->description                                     = "Get answer contents by answer id";
        info->queryParams.add<Int32>("answer_id").name        = "answer_id";
        info->queryParams.add<Int32>("answer_id").description = "Answer Id";
        info->queryParams.add<Int32>("answer_id").required    = true;
        info->addResponse<Object<dto::ResponseAnswerContents>>(Status::CODE_200,
                                                               "application/json");
    }
};

}  // namespace QuickExam::controller

#include OATPP_CODEGEN_BEGIN(ApiController)