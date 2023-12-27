//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/Question.h>
#include <dto/QuestionContent.h>
#include <dto/Tag.h>
#include <dto/response/Question.h>
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
class QuestionController : public ApiController {
public:
    typedef std::shared_ptr<QuestionController> Ptr;
    explicit QuestionController(const std::shared_ptr<ObjectMapper> &objectMapper)
        : ApiController(objectMapper, "/api/question") {
        this->objectMapper = objectMapper;
    }

    static Ptr make(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<QuestionController>(objectMapper);
    }

private:
    std::shared_ptr<ObjectMapper> objectMapper;
    service::QuestionService      question_service;

public:
    ENDPOINT("POST", "/create", createQuestion, BODY_DTO(Object<dto::Question>, req_body)) {
        return createDtoResponse(Status::CODE_200, question_service.createQuestion(req_body));
    }
    ENDPOINT_INFO(createQuestion) {
        info->addTag("Question");
        info->summary     = "Create Question";
        info->description = "Create a question";
        info->addConsumes<Object<dto::Question>>("application/json");
        info->addResponse<Object<dto::ResponseQuestion>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("POST", "/add/tag", addQuestionTag, QUERY(Int32, question_id), QUERY(Int32, tag_id)) {
        // todo: add tag
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(addQuestionTag) {
        info->addTag("Question");
        info->summary                                           = "Add Tag";
        info->description                                       = "Bind tag id to question id";
        info->queryParams.add<Int32>("question_id").name        = "question_id";
        info->queryParams.add<Int32>("question_id").description = "Question id";
        info->queryParams.add<Int32>("question_id").required    = true;
        info->queryParams.add<Int32>("tag_id").name             = "tag_id";
        info->queryParams.add<Int32>("tag_id").description      = "Tag id";
        info->queryParams.add<Int32>("tag_id").required         = true;
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("PUT", "/update", updateQuestion, BODY_DTO(Object<dto::Question>, req_body)) {
        return createDtoResponse(Status::CODE_200, question_service.updateQuestion(req_body));
    }
    ENDPOINT_INFO(updateQuestion) {
        info->addTag("Question");
        info->summary     = "Update Question";
        info->description = "Update a question";
        info->addConsumes<Object<dto::Question>>("application/json");
        info->addResponse<Object<dto::ResponseQuestion>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("DELETE",
             "/delete/tag",
             deleteQuestionTag,
             QUERY(Int32, question_id),
             QUERY(Int32, tag_id)) {
        // todo: delete tag
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(deleteQuestionTag) {
        info->addTag("Question");
        info->summary                                           = "Delete Question Tag";
        info->description                                       = "Delete a tag from a question";
        info->queryParams.add<Int32>("question_id").name        = "question_id";
        info->queryParams.add<Int32>("question_id").description = "Question id";
        info->queryParams.add<Int32>("question_id").required    = true;
        info->queryParams.add<Int32>("tag_id").name             = "tag_id";
        info->queryParams.add<Int32>("tag_id").description      = "Tag id";
        info->queryParams.add<Int32>("tag_id").required         = true;
        info->addResponse<Object<dto::Response>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("DELETE", "/delete", deleteQuestion, QUERY(Int32, question_id)) {
        return createDtoResponse(Status::CODE_200, question_service.deleteQuestion(question_id));
    }
    ENDPOINT_INFO(deleteQuestion) {
        info->addTag("Question");
        info->summary                                           = "Delete Question";
        info->description                                       = "Delete a question";
        info->queryParams.add<Int32>("question_id").name        = "question_id";
        info->queryParams.add<Int32>("question_id").description = "Question id";
        info->queryParams.add<Int32>("question_id").required    = true;
        info->addResponse<Object<dto::Response>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("GET", "/get", getQuestionById, QUERY(Int32, question_id)) {
        return createDtoResponse(Status::CODE_200, question_service.getQuestionById(question_id));
    }
    ENDPOINT_INFO(getQuestionById) {
        info->addTag("Question");
        info->summary                                           = "Get Question By Id";
        info->description                                       = "Get a question by id";
        info->queryParams.add<Int32>("question_id").name        = "question_id";
        info->queryParams.add<Int32>("question_id").description = "Question id";
        info->queryParams.add<Int32>("question_id").required    = true;
        info->addResponse<Object<dto::ResponseQuestion>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("POST",
             "/get/by/conditions",
             getQuestions,
             BODY_DTO(Object<dto::QuestionCondition>, req_body)) {
        return createDtoResponse(Status::CODE_200,
                                 question_service.getQuestionsByPageConditions(req_body));
    }
    ENDPOINT_INFO(getQuestions) {
        info->addTag("Question");
        info->summary     = "Get Questions";
        info->description = "Get questions basic info (but have tags) by conditions. "
                            "This will not return append info like contents, answers, etc.";
        info->addConsumes<Object<dto::QuestionCondition>>("application/json");
        info->addResponse<Object<dto::ResponseQuestionPage>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("POST",
             "/create/sub_question",
             addSubQuestion,
             QUERY(Int32, parent_question_id),
             BODY_DTO(Object<dto::Question>, req_body)) {
        // todo: add sub question
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(addSubQuestion) {
        info->addTag("Question");
        info->summary     = "Add Sub Question";
        info->description = "Create a sub question for a question";
        info->queryParams.add<Int32>("parent_question_id").name        = "parent_question_id";
        info->queryParams.add<Int32>("parent_question_id").description = "Parent qÏuestion id";
        info->queryParams.add<Int32>("parent_question_id").required    = true;
        info->addConsumes<Object<dto::Question>>("application/json");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }
};

}  // namespace QuickExam::controller

#include OATPP_CODEGEN_BEGIN(ApiController)