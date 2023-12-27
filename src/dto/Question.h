//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/Answer.h>
#include <dto/QuestionContent.h>
#include <dto/Tag.h>
#include <dto/basic/Page.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

class Question : public db::Question {
    DTO_INIT(Question, db::Question)

    DTO_FIELD(List<Object<QuestionContent>>, question_contents);
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

    DTO_FIELD(List<Object<Tag>>, tags);
    DTO_FIELD_INFO(tags) {
        info->description = "Question tags";
    }
};

class QuestionCondition : public basic::Condition {
    DTO_INIT(QuestionCondition, basic::Condition)

    DTO_FIELD(List<Int32>, tag_ids) = List<Int32>::createShared();
    DTO_FIELD_INFO(tag_ids) {
        info->description = "Question tags (empty means all tags)";
    }

    DTO_FIELD(List<Int32>, types) = List<Int32>::createShared();
    DTO_FIELD_INFO(types) {
        info->description = "Question types (empty means all types)";
    }

    DTO_FIELD(Int32, is_published) = -1;
    DTO_FIELD_INFO(is_published) {
        info->description = "Is published (0: false, 1: true, -1: all)";
    }
};

class QuestionPage : public basic::Page<oatpp::Object<Question>> {
    DTO_INIT(QuestionPage, basic::Page<oatpp::Object<Question>>)
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)