//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/QuestionContent.h>
#include <dto/response/QuestionContent.h>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>
#include <service/QuestionService.h>

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace QuickExam::controller {
using namespace oatpp::web::server::api;
using namespace oatpp::parser::json::mapping;
using namespace oatpp;
class QuestionContentController : public ApiController {
public:
    typedef std::shared_ptr<QuestionContentController> Ptr;
    explicit QuestionContentController(const std::shared_ptr<ObjectMapper> &objectMapper)
        : ApiController(objectMapper, "/api/question/content") {
        this->objectMapper = objectMapper;
    }

    static Ptr make(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<QuestionContentController>(objectMapper);
    }

private:
    std::shared_ptr<ObjectMapper> objectMapper;
    service::QuestionService      question_service;

public:
    ENDPOINT("POST",
             "/create",
             createQuestionContent,
             BODY_DTO(Object<dto::QuestionContent>, req_body)) {
        return createDtoResponse(Status::CODE_200, question_service.addQuestionContent(req_body));
    }
    ENDPOINT_INFO(createQuestionContent) {
        info->addTag("Question Content");
        info->summary     = "Add Content";
        info->description = "Create a content for a question";
        info->addConsumes<Object<dto::QuestionContent>>("application/json");
        info->addResponse<Object<dto::ResponseQuestionContent>>(Status::CODE_200,
                                                                "application/json");
    }

    ENDPOINT("PUT",
             "/update",
             updateQuestionContent,
             BODY_DTO(Object<dto::QuestionContent>, req_body)) {
        return createDtoResponse(Status::CODE_200,
                                 question_service.updateQuestionContent(req_body));
    }
    ENDPOINT_INFO(updateQuestionContent) {
        info->addTag("Question Content");
        info->summary     = "Update Content";
        info->description = "Update a content";
        info->addConsumes<Object<dto::QuestionContent>>("application/json");
        info->addResponse<Object<dto::ResponseQuestionContent>>(Status::CODE_200,
                                                                "application/json");
    }

    ENDPOINT("DELETE", "/delete", deleteQuesionContent, QUERY(Int32, content_id)) {
        return createDtoResponse(Status::CODE_200,
                                 question_service.deleteQuestionContent(content_id));
    }
    ENDPOINT_INFO(deleteQuesionContent) {
        info->addTag("Question Content");
        info->summary                                          = "Delete Content";
        info->description                                      = "Delete a content";
        info->queryParams.add<Int32>("content_id").name        = "content_id";
        info->queryParams.add<Int32>("content_id").description = "Content id";
        info->queryParams.add<Int32>("content_id").required    = true;
        info->addResponse<Object<dto::Response>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("GET", "/get/list/by/question", getQuestionContents, QUERY(Int32, question_id)) {
        return createDtoResponse(Status::CODE_200,
                                 question_service.getQuestionContentsByQuestionId(question_id));
    }
    ENDPOINT_INFO(getQuestionContents) {
        info->addTag("Question Content");
        info->summary                                           = "Get Contents";
        info->description                                       = "Get all contents of a question";
        info->queryParams.add<Int32>("question_id").name        = "question_id";
        info->queryParams.add<Int32>("question_id").description = "Question id";
        info->queryParams.add<Int32>("question_id").required    = true;
        info->addResponse<Object<dto::ResponseQuestionContents>>(Status::CODE_200,
                                                                 "application/json");
    }
};

}  // namespace QuickExam::controller

#include OATPP_CODEGEN_BEGIN(ApiController)