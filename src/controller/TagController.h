//
// QuickExam
// Created on 2023/12/20.
//

#pragma once

#include <dto/Tag.h>
#include <dto/response/Tag.h>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>
#include <service/TagService.h>

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
    service::TagService           tag_service;

public:
    ENDPOINT("POST", "/create", createTag, BODY_DTO(Object<dto::Tag>, request_body)) {
        return createDtoResponse(Status::CODE_200, tag_service.createTag(request_body));
    }
    ENDPOINT_INFO(createTag) {
        info->addTag("Tag");
        info->summary     = "Create Tag";
        info->description = "Create a Tag";
        info->addConsumes<Object<dto::Tag>>("application/json");
        info->addResponse<Object<dto::ResponseTag>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("PUT", "/update", updateTag, BODY_DTO(Object<dto::Tag>, request_body)) {
        return createDtoResponse(Status::CODE_200, tag_service.updateTag(request_body));
    }
    ENDPOINT_INFO(updateTag) {
        info->addTag("Tag");
        info->summary     = "Update Tag";
        info->description = "Update a tag";
        info->addConsumes<Object<dto::Tag>>("application/json");
        info->addResponse<Object<dto::ResponseTag>>(Status::CODE_200, "application/json");
    }

    ENDPOINT("DELETE", "/delete/{tag_id}", deleteTag, PATH(Int32, tag_id)) {
        return createDtoResponse(Status::CODE_200, tag_service.deleteTag(tag_id));
    }
    ENDPOINT_INFO(deleteTag) {
        info->addTag("Tag");
        info->summary     = "Delete Tag";
        info->description = "Delete a tag";
        info->pathParams.add<Int32>("tag_id");
        info->addResponse<Object<dto::basic::Response<String>>>(Status::CODE_200,
                                                                "application/json");
    }

    ENDPOINT("POST",
             "/get/list/by/conditions",
             getTagListByConditions,
             BODY_DTO(Object<dto::TagCondition>, request_body)) {
        return createDtoResponse(Status::CODE_200,
                                 tag_service.getTagsByPageConditions(request_body));
    }
    ENDPOINT_INFO(getTagListByConditions) {
        info->addTag("Tag");
        info->summary     = "Get Tag List By Conditions";
        info->description = "Get a list of tags by conditions";
        info->addConsumes<Object<dto::TagCondition>>("application/json");
        info->addResponse<Object<dto::ResponseTagPage>>(Status::CODE_200, "application/json");
    }
};

}  // namespace QuickExam::controller

#include OATPP_CODEGEN_BEGIN(ApiController)