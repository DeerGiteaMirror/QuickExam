//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

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
        : ApiController(objectMapper) {
        this->objectMapper = objectMapper;
    }

    static Ptr make(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) {
        return std::make_shared<QuestionController>(objectMapper);
    }

private:
    std::shared_ptr<ObjectMapper> objectMapper;

public:
};

}  // namespace QuickExam::controller

#include OATPP_CODEGEN_BEGIN(ApiController)