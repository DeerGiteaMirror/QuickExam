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
        // todo: create answer
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(createAnswer) {
        info->addTag("Answer");
        info->summary     = "Create Answer";
        info->description = "Create an answer";
        info->addConsumes<Object<dto::Answer>>("application/json");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("POST",
             "/create/content",
             addAnswerContent,
             PATH(Int32, question_id),
             BODY_DTO(Object<dto::AnswerContent>, req_body)) {
        // todo: create answer content
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(addAnswerContent) {
        info->addTag("Answer");
        info->summary     = "Add Answer Content";
        info->description = "Create content for an answer";
        info->addConsumes<Object<dto::AnswerContent>>("application/json");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("PUT", "/update", updateAnswer, BODY_DTO(Object<dto::Answer>, req_body)) {
        // todo: update answer
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(updateAnswer) {
        info->addTag("Answer");
        info->summary     = "Update Answer";
        info->description = "Update an answer";
        info->addConsumes<Object<dto::Answer>>("application/json");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("PUT",
             "/update/content",
             updateAnswerContent,
             BODY_DTO(Object<dto::AnswerContent>, req_body)) {
        // todo: update answer content
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(updateAnswerContent) {
        info->addTag("Answer");
        info->summary     = "Update Answer Content";
        info->description = "Update an answer content";
        info->addConsumes<Object<dto::AnswerContent>>("application/json");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("DELETE", "/delete/{answer_id}", deleteAnswer, PATH(Int32, answer_id)) {
        // todo: delete answer
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(deleteAnswer) {
        info->addTag("Answer");
        info->summary     = "Delete Answer";
        info->description = "Delete an answer";
        info->pathParams.add<Int32>("answer_id");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }

    ENDPOINT("DELETE",
             "/delete/content/{content_id}",
             deleteAnswerContent,
             PATH(Int32, content_id)) {
        // todo: delete answer content
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(deleteAnswerContent) {
        info->addTag("Answer");
        info->summary     = "Delete Answer Content";
        info->description = "Delete an answer content";
        info->pathParams.add<Int32>("content_id");
        info->addResponse(Status::CODE_200, "Success, then re-get the question");
    }
};

}  // namespace QuickExam::controller

#include OATPP_CODEGEN_BEGIN(ApiController)