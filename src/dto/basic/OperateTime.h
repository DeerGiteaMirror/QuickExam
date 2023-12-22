//
// QuickExam
// Created on 2023/12/22.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto::basic {

class OperateTime : public oatpp::DTO {
    DTO_INIT(OperateTime, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = "Content id";
    }

    DTO_FIELD(Int32, belong_id);
    DTO_FIELD_INFO(belong_id) {
        info->description = "Content belong id";
    }

    DTO_FIELD(String, created_at);
    DTO_FIELD_INFO(created_at) {
        info->description = "Content type";
    }

    DTO_FIELD(String, updated_at);
    DTO_FIELD_INFO(updated_at) {
        info->description = "Content type";
    }
};

}  // namespace QuickExam::dto::basic

#include OATPP_CODEGEN_END(DTO)