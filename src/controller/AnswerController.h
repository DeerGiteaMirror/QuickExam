//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/Answer.h>
#include <dto/response/Answer.h>
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
    service::AnswerService        answer_service;

public:
    ENDPOINT("POST", "/create", createAnswer, BODY_DTO(Object<dto::Answer>, request)) {
        return createDtoResponse(Status::CODE_200, answer_service.createAnswer(request));
    }
    ENDPOINT_INFO(createAnswer) {
        info->addTag("Answer");
        info->summary     = "Create Answer";
        info->description = "Create an answer";
        info->addConsumes<Object<dto::Answer>>("application/json");
        info->addResponse<Object<dto::ResponseAnswer>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("PUT", "/update", updateAnswer, BODY_DTO(Object<dto::Answer>, req_body)) {
        return createDtoResponse(Status::CODE_200, answer_service.updateAnswer(req_body));
    }
    ENDPOINT_INFO(updateAnswer) {
        info->addTag("Answer");
        info->summary     = "Update Answer";
        info->description = "Update an answer";
        info->addConsumes<Object<dto::Answer>>("application/json");
        info->addResponse<Object<dto::ResponseAnswer>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("DELETE", "/delete", deleteAnswer, QUERY(Int32, answer_id)) {
        return createDtoResponse(Status::CODE_200, answer_service.deleteAnswer(answer_id));
    }
    ENDPOINT_INFO(deleteAnswer) {
        info->addTag("Answer");
        info->summary                                         = "Delete Answer";
        info->description                                     = "Delete an answer";
        info->queryParams.add<Int32>("answer_id").name        = "answer_id";
        info->queryParams.add<Int32>("answer_id").description = "Answer Id";
        info->queryParams.add<Int32>("answer_id").required    = true;
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("GET", "/get/list/by/question", getAnswerListByQuestion, QUERY(Int32, question_id)) {
        return createDtoResponse(Status::CODE_200,
                                 answer_service.getAnswersByQuestionId(question_id));
    }
    ENDPOINT_INFO(getAnswerListByQuestion) {
        info->addTag("Answer");
        info->summary                                           = "Get Answer List By Question";
        info->description                                       = "Get answer list by question id";
        info->queryParams.add<Int32>("question_id").name        = "question_id";
        info->queryParams.add<Int32>("question_id").description = "Question Id";
        info->queryParams.add<Int32>("question_id").required    = true;
        info->addResponse<Object<dto::ResponseAnswers>>(Status::CODE_200, "application/json");
    }
};

}  // namespace QuickExam::controller

#include OATPP_CODEGEN_BEGIN(ApiController)