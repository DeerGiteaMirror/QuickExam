//
// AnonExam
// Created on 2023/12/18.
//

#pragma once

#include <dto/basic/Content.h>
#include <dto/basic/Enmus.h>
#include <dto/db/Answer.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto::db {

class Question : public oatpp::DTO {
    DTO_INIT(Question, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = "Question id";
    }

    DTO_FIELD(Boolean, is_sub_question) = false;
    DTO_FIELD_INFO(is_sub_question) {
        info->description = "Is sub question";
    }

    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = "Question title";
    }

    DTO_FIELD(Enum<basic::QuestionType>::AsNumber, type);
    DTO_FIELD_INFO(type) {
        info->description = "Question type";
    }

    DTO_FIELD(Int32, estimated_time_sec);
    DTO_FIELD_INFO(estimated_time_sec) {
        info->description = "Estimated time to answer the question";
    }

    DTO_FIELD(Int32, score);
    DTO_FIELD_INFO(score) {
        info->description = "Preset score";
    }
};

class QuestionContents : public basic::Content {
    DTO_INIT(QuestionContents, Content)

    DTO_FIELD(Int32, question_id);
    DTO_FIELD_INFO(question_id) {
        info->description = "Question id";
    }
};

class QuestionAnswers : public oatpp::DTO {
    DTO_INIT(QuestionAnswers, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = "Map id";
    }

    DTO_FIELD(Int32, question_id);
    DTO_FIELD_INFO(question_id) {
        info->description = "Question id";
    }

    DTO_FIELD(Int32, answer_id);
    DTO_FIELD_INFO(answer_id) {
        info->description = "Answer id";
    }
};

class QuestionSubQuestions : public oatpp::DTO {
    DTO_INIT(QuestionSubQuestions, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = "Map id";
    }

    DTO_FIELD(Int32, question_id);
    DTO_FIELD_INFO(question_id) {
        info->description = "Question id";
    }

    DTO_FIELD(Int32, sub_question_id);
    DTO_FIELD_INFO(sub_question_id) {
        info->description = "Sub question id";
    }
};

class QuestionTag : public oatpp::DTO {
    DTO_INIT(QuestionTag, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = "Map id";
    }

    DTO_FIELD(Int32, question_id);
    DTO_FIELD_INFO(question_id) {
        info->description = "Question id";
    }

    DTO_FIELD(Int32, tag_id);
    DTO_FIELD_INFO(tag_id) {
        info->description = "Tag id";
    }

    DTO_FIELD(Int32, priority);
    DTO_FIELD_INFO(priority) {
        info->description = "Tag priority";
    }
};

}  // namespace AnonExam::dto::db

#include OATPP_CODEGEN_END(DTO)