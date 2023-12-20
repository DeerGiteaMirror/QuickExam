//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/Answer.h>
#include <dto/QuestionContent.h>
#include <dto/Tag.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

class Question : public db::Question {
    DTO_INIT(Question, db::Question)

    DTO_FIELD(List<Object<QuestionContent>>,
              question_contents) = List<Object<QuestionContent>>::createShared();
    DTO_FIELD_INFO(question_contents) {
        info->description = "Question contents";
    }

    DTO_FIELD(List<Object<Question>>, sub_questions) = List<Object<Question>>::createShared();
    DTO_FIELD_INFO(sub_questions) {
        info->description = "Sub questions";
    }

    DTO_FIELD(List<Object<Answer>>, answers) = List<Object<Answer>>::createShared();
    DTO_FIELD_INFO(answers) {
        info->description = "Question answers";
    }

    DTO_FIELD(List<Object<Tag>>, tags) = List<Object<Tag>>::createShared();
    DTO_FIELD_INFO(tags) {
        info->description = "Question tags";
    }
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)