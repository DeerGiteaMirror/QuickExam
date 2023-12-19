//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/db/Answer.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

class Answer : public db::Answer {
    DTO_INIT(Answer, db::Answer)

    DTO_FIELD(List<Object<db::AnswerContents>>, answer_contents);
    DTO_FIELD_INFO(answer_contents) {
        info->description = "Answer contents";
    }
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)