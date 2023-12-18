//
// AnonExam
// Created on 2023/12/18.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <dtos/basic/Enmus.h>
#include <dtos/basic/Content.h>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace AnonExam::dto::db {

class Answer : public oatpp::DTO {
    DTO_INIT(Answer, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = "Answer id";
    }

    DTO_FIELD(Boolean, is_correct) = false;
    DTO_FIELD_INFO(is_correct) {
        info->description = "Is correct answer";
    }
};

class AnswerContents : public basic::Content {
    DTO_INIT(AnswerContents, Content)

    DTO_FIELD(Int32, answer_id);
    DTO_FIELD_INFO(answer_id) {
        info->description = "Answer id";
    }
};

}  // namespace AnonExam::dto

#include OATPP_CODEGEN_END(DTO)