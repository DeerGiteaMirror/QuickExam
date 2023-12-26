//
// QuickExam
// Created on 2023/12/25.
//

#pragma once
#include <dto/Tag.h>
#include <dto/basic/Enmus.h>
#include <dto/basic/Response.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)
namespace QuickExam::dto {
class Response : public oatpp::DTO {
    DTO_INIT(Response, DTO)

    DTO_FIELD(Int32, code) = 200;
    DTO_FIELD_INFO(code) {
        info->description = "Response code";
        info->required    = true;
    }

    DTO_FIELD(String, message) = "OK";
    DTO_FIELD_INFO(message) {
        info->description = "Response message";
        info->required    = true;
    }

    DTO_FIELD(String, data) = "";
    DTO_FIELD_INFO(data) {
        info->description = "Response message with detail";
        info->required    = true;
    }
};
}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)