//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/basic/Content.h>
#include <dto/basic/Enmus.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto::db {

class Candidate : public oatpp::DTO {
    DTO_INIT(Candidate, DTO)

    DTO_FIELD(Int32, id);
    DTO_FIELD_INFO(id) {
        info->description = "Candidate id";
    }

    DTO_FIELD(String, email);
    DTO_FIELD_INFO(email) {
        info->description = "Candidate email";
    }

    DTO_FIELD(String, number);
    DTO_FIELD_INFO(number) {
        info->description = "Candidate number (uuid)";
    }

    DTO_FIELD(Int32, quiz_id);
    DTO_FIELD_INFO(quiz_id) {
        info->description = "Associated quiz id";
    }

    DTO_FIELD(Enum<basic::CandidateStatus>::AsNumber, status);
    DTO_FIELD_INFO(status) {
        info->description = "Candidate status";
    }

    DTO_FIELD(Int32, score);
    DTO_FIELD_INFO(score) {
        info->description = "Candidate score";
    }

    DTO_FIELD(Int64, time_started);
    DTO_FIELD_INFO(time_started) {
        info->description = "Time when the candidate started the quiz";
    }

    DTO_FIELD(Int64, time_ended);
    DTO_FIELD_INFO(time_ended) {
        info->description = "Time when the candidate ended the quiz";
    }

    DTO_FIELD(Int64, time_spent);
    DTO_FIELD_INFO(time_spent) {
        info->description = "Time spent on the quiz";
    }

    DTO_FIELD(String, answers_json);
    DTO_FIELD_INFO(answers_json) {
        info->description = "Candidate answers snapshot (json string)"
                            "oatpp::List<oatpp::Object<dto::CandidateQuestionAnswer>>";
    }
};

}  // namespace QuickExam::dto::db

#include OATPP_CODEGEN_END(DTO)