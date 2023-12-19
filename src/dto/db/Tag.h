//
// AnonExam
// Created on 2023/12/19.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto::db {

class Tag : public oatpp::DTO {
    DTO_INIT(Tag, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = "Tag id";
    }

    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = "Tag name";
    }

    DTO_FIELD(Int32, hex_color);
    DTO_FIELD_INFO(hex_color) {
        info->description = "Tag color in hex";
    }
};

}  // namespace AnonExam::dto::db

#include OATPP_CODEGEN_END(DTO)