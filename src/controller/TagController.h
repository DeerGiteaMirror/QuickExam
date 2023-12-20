//
// QuickExam
// Created on 2023/12/20.
//

#pragma once

#include <dto/Tag.h>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>

#include OATPP_CODEGEN_BEGIN(ApiController)

namespace QuickExam::controller {
using namespace oatpp::web::server::api;
using namespace oatpp::parser::json::mapping;
using namespace oatpp;
class TagController : public ApiController {
public:
    typedef std::shared_ptr<TagController> Ptr;
    explicit TagController(const std::shared_ptr<ObjectMapper> &objectMapper)
        : ApiController(objectMapper, "/api/tag") {
        this->objectMapper = objectMapper;
    }

    static Ptr make(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<TagController>(objectMapper);
    }

private:
    std::shared_ptr<ObjectMapper> objectMapper;

public:
    ENDPOINT("POST", "/create", createTag, BODY_DTO(Object<dto::Tag>, request_body)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(createTag) {
        info->addTag("Tag");
        info->summary     = "Create Tag";
        info->description = "Create a Tag";
        info->addConsumes<Object<dto::Tag>>("application/json");
        info->addResponse(Status::CODE_200, "Success, then re-get tag list");
    }

    ENDPOINT("PUT", "/update", updateTag, BODY_DTO(Object<dto::Tag>, request_body)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(updateTag) {
        info->addTag("Tag");
        info->summary     = "Update Tag";
        info->description = "Update a tag";
        info->addConsumes<Object<dto::Tag>>("application/json");
        info->addResponse(Status::CODE_200, "Success, then re-get tag list");
    }

    ENDPOINT("DELETE", "/delete/{tag_id}", deleteTag, PATH(Int32, tag_id)) {
        return createResponse(Status::CODE_200);
    }
    ENDPOINT_INFO(deleteTag) {
        info->addTag("Tag");
        info->summary     = "Delete Tag";
        info->description = "Delete a tag";
        info->addResponse(Status::CODE_200, "Success, then re-get tag list");
        info->pathParams.add<Int32>("tag_id");
    }
};

}  // namespace QuickExam::controller

#include OATPP_CODEGEN_BEGIN(ApiController)