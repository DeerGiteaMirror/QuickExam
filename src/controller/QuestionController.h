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
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(createQuestion) {
        info->addTag("Question");
        info->summary     = "Create Question";
        info->description = "Create a question";
        info->addConsumes<Object<dto::Question>>("application/json");
        info->addResponse<Object<dto::Question>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("POST",
             "/create/content",
             addQuestionContent,
             BODY_DTO(Object<dto::QuestionContent>, req_body)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(addQuestionContent) {
        info->addTag("Question");
        info->summary     = "Add Content";
        info->description = "Create a content for a question";
        info->addConsumes<Object<dto::QuestionContent>>("application/json");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("POST",
             "/create/{question_id}/sub_question",
             addSubQuestion,
             PATH(Int32, question_id),
             BODY_DTO(Object<dto::Question>, req_body)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(addSubQuestion) {
        info->addTag("Question");
        info->summary     = "Add Sub Question";
        info->description = "Create a sub question for a question";
        info->pathParams.add<Int32>("question_id");
        info->addConsumes<Object<dto::Question>>("application/json");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("POST",
             "/add/{question_id}/tag/{tag_id}",
             addQuestionTag,
             PATH(Int32, question_id),
             PATH(Int32, tag_id)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(addQuestionTag) {
        info->addTag("Question");
        info->summary     = "Add Tag";
        info->description = "Bind tag id to question id";
        info->pathParams.add<Int32>("question_id");
        info->pathParams.add<Int32>("tag_id");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("PUT", "/update", updateQuestion, BODY_DTO(Object<dto::Question>, req_body)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(updateQuestion) {
        info->addTag("Question");
        info->summary     = "Update Question";
        info->description = "Update a question";
        info->addConsumes<Object<dto::Question>>("application/json");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("PUT",
             "/update/content",
             updateQuestionContent,
             BODY_DTO(Object<dto::QuestionContent>, req_body)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(updateQuestionContent) {
        info->addTag("Question");
        info->summary     = "Update Content";
        info->description = "Update a content";
        info->addConsumes<Object<dto::QuestionContent>>("application/json");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("DELETE",
             "/delete/{question_id}/tag/{tag_id}",
             deleteQuestionTag,
             PATH(Int32, question_id),
             PATH(Int32, tag_id)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(deleteQuestionTag) {
        info->addTag("Question");
        info->summary     = "Delete Question Tag";
        info->description = "Delete a tag from a question";
        info->pathParams.add<Int32>("question_id");
        info->pathParams.add<Int32>("tag_id");
        info->addResponse<Object<dto::Question>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("DELETE", "/delete/{question_id}", deleteQuestion, PATH(Int32, question_id)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(deleteQuestion) {
        info->addTag("Question");
        info->summary     = "Delete Question";
        info->description = "Delete a question";
        info->pathParams.add<Int32>("question_id");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("DELETE",
             "/delete/content/{content_id}",
             deleteQuesionContent,
             PATH(Int32, content_id)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(deleteQuesionContent) {
        info->addTag("Question");
        info->summary                                         = "Delete Content";
        info->description                                     = "Delete a content";
        info->pathParams.add<Int32>("content_id").description = "Content id";
        info->pathParams.add<Int32>("content_id").required    = true;
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("GET", "/get/{question_id}", getQuestionById, PATH(Int32, question_id)) {
        return createDtoResponse(Status::CODE_200, question_service.getQuestionById(question_id));
    }
    ENDPOINT_INFO(getQuestionById) {
        info->addTag("Question");
        info->summary                                          = "Get Question By Id";
        info->description                                      = "Get a question by id";
        info->pathParams.add<Int32>("question_id").description = "Question id";
        info->pathParams.add<Int32>("question_id").required    = true;
        info->addResponse<Object<dto::ResponseQuestion>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("POST",
             "/get/list/by/conditions",
             getQuestions,
             BODY_DTO(Object<dto::QuestionCondition>, req_body)) {
        return createDtoResponse(Status::CODE_200,
                                 question_service.getQuestionsByPageConditions(req_body));
    }
    ENDPOINT_INFO(getQuestions) {
        info->addTag("Question");
        info->summary     = "Get Questions";
        info->description = "Get questions by page and size";
        info->addConsumes<Object<dto::QuestionCondition>>("application/json");
        info->addResponse<Object<dto::ResponseQuestionPage>>(Status::CODE_200, "application/json");
    }
};

}  // namespace QuickExam::controller

#include OATPP_CODEGEN_BEGIN(ApiController)