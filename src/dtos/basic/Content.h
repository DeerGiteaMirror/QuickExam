//
// AnonExam
// Created on 2023/12/18.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <dtos/basic/Enmus.h>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace AnonExam::dto::basic {

class Content : public oatpp::DTO {
    DTO_INIT(Content, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = "Content id";
    }

    DTO_FIELD(Enum<ContentTypes>::AsNumber, content_type);
    DTO_FIELD_INFO(content_type) {
        info->description = "Content type";
    }

    DTO_FIELD(String, content);
    DTO_FIELD_INFO(content) {
        info->description = "Content";
    }

    DTO_FIELD(Int32, content_index);
    DTO_FIELD_INFO(content_index) {
        info->description = "Content index";
    }
};

}

#include OATPP_CODEGEN_END(DTO)