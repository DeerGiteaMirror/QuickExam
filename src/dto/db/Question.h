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

    DTO_FIELD(Int32, parent) = -1;
    DTO_FIELD_INFO(parent) {
        info->description = "Parent question id (-1 if not a sub question)";
    }

    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = "Question title";
    }

    DTO_FIELD(Enum<basic::QuestionType>::AsNumber, type);
    DTO_FIELD_INFO(type) {
        info->description = "Question type";
    }

    DTO_FIELD(Int32, estimated_time_sec) = 0;
    DTO_FIELD_INFO(estimated_time_sec) {
        info->description = "Estimated time to answer the question";
    }

    DTO_FIELD(Int32, score) = 0;
    DTO_FIELD_INFO(score) {
        info->description = "Preset score";
    }

    DTO_FIELD(Boolean, is_published) = false;
    DTO_FIELD_INFO(is_published) {
        info->description = "Is published (only published questions will be referenced in exams)";
    }

    DTO_FIELD(Int32, reference_count) = 0;
    DTO_FIELD_INFO(reference_count) {
        info->description = "Reference count";
    }

    DTO_FIELD(Int32, correct_count) = 0;
    DTO_FIELD_INFO(correct_count) {
        info->description = "Correct count";
    }

    DTO_FIELD(String, created_at);
    DTO_FIELD_INFO(created_at) {
        info->description = "Content type";
    }

    DTO_FIELD(String, updated_at);
    DTO_FIELD_INFO(updated_at) {
        info->description = "Content type";
    }
};

class QuestionContents : public basic::Content {
    DTO_INIT(QuestionContents, Content)

    DTO_FIELD(Int32, question_id);
    DTO_FIELD_INFO(question_id) {
        info->description = "Question id";
    }
};

class QuestionSubQuestion : public oatpp::DTO {
    DTO_INIT(QuestionSubQuestion, DTO)

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

    DTO_FIELD(Int32, sub_question_index);
    DTO_FIELD_INFO(sub_question_index) {
        info->description = "Sub question index";
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

}  // namespace QuickExam::dto::db

#include OATPP_CODEGEN_END(DTO)