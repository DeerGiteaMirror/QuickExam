//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/AnswerContent.h>
#include <dto/db/Answer.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

class Answer : public db::Answer {
    DTO_INIT(Answer, db::Answer)

    DTO_FIELD(List<Object<AnswerContent>>,
              answer_contents) = List<Object<AnswerContent>>::createShared();
    DTO_FIELD_INFO(answer_contents) {
        info->description = "Answer contents";
    }
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)