//
// AnonExam
// Created on 2023/12/19.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto::db {

class Quiz : public oatpp::DTO {
    DTO_INIT(Quiz, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = "Quiz id";
    }

    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = "Quiz title";
    }

    DTO_FIELD(String, description);
    DTO_FIELD_INFO(description) {
        info->description = "Quiz description";
    }

    DTO_FIELD(Int32, time_limit);
    DTO_FIELD_INFO(time_limit) {
        info->description = "Quiz time limit";
    }

    DTO_FIELD(Int64, create_time);
    DTO_FIELD_INFO(create_time) {
        info->description = "Quiz create time";
    }

    DTO_FIELD(Int64, start_time);
    DTO_FIELD_INFO(start_time) {
        info->description = "Quiz start time";
    }

    DTO_FIELD(Int64, close_time);
    DTO_FIELD_INFO(close_time) {
        info->description = "Quiz close time";
    }

    DTO_FIELD(String, questions_json);
    DTO_FIELD_INFO(questions_json) {
        info->description = "Quiz questions snapshot (json string)"
                            "oatpp::List<oatpp::Object<dto::Question>>";
    }

    DTO_FIELD(Int32, total_score);
    DTO_FIELD_INFO(total_score) {
        info->description = "Quiz total score";
    }

    DTO_FIELD(Boolean, can_see_result);
    DTO_FIELD_INFO(can_see_result) {
        info->description = "After quiz, can see result";
    }
};

}  // namespace QuickExam::dto::db

#include OATPP_CODEGEN_END(DTO)