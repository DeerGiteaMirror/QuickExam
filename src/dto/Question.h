//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/Answer.h>
#include <dto/db/Question.h>
#include <dto/db/Tag.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

class Question : public db::Question {
    DTO_INIT(Question, db::Question)

    DTO_FIELD(List<Object<db::QuestionContents>>, question_contents);
    DTO_FIELD_INFO(question_contents) {
        info->description = "Question contents";
    }

    DTO_FIELD(List<Object<Question>>, sub_questions);
    DTO_FIELD_INFO(sub_questions) {
        info->description = "Sub questions";
    }

    DTO_FIELD(List<Object<Answer>>, answers);
    DTO_FIELD_INFO(answers) {
        info->description = "Question answers";
    }

    DTO_FIELD(List<Object<db::Tag>>, tags);
    DTO_FIELD_INFO(tags) {
        info->description = "Question tags";
    }
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)