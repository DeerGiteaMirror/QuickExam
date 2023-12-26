//
// AnonExam
// Created on 2023/12/18.
//

#pragma once

#include <dto/basic/Content.h>
#include <dto/basic/Enmus.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto::db {

class Answer : public oatpp::DTO {
    DTO_INIT(Answer, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = "Answer id";
    }

    DTO_FIELD(Int32, question_id);
    DTO_FIELD_INFO(question_id) {
        info->description = "Belong to question id";
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
        info->description = "Belong to answer id";
    }
};

}  // namespace AnonExam::dto::db

#include OATPP_CODEGEN_END(DTO)