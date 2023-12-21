//
// AnonExam
// Created on 2023/12/18.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto::basic {

ENUM(ContentTypes,
     v_int32,
     VALUE(text, 0, "text"),
     VALUE(image, 1, "image-base64"),
     VALUE(audio, 2, "audio-url"),
     VALUE(video, 3, "video-url"))

ENUM(QuestionType,
     v_int32,
     VALUE(none, -1, "none"),
     VALUE(single_choice, 0, "single-choice"),
     VALUE(multiple_choice, 1, "multiple-choice"),
     VALUE(judgement, 2, "judgement"),
     VALUE(short_answer, 3, "short-answer"),
     VALUE(long_answer, 4, "long-answer"),
     VALUE(file_upload, 5, "file-upload"))

static oatpp::List<oatpp::Int32> allQuestionTypes() {
    auto list = oatpp::List<oatpp::Int32>::createShared();
    list->push_back(0);
    list->push_back(1);
    list->push_back(2);
    list->push_back(3);
    list->push_back(4);
    list->push_back(5);
    return list;
}

ENUM(CandidateStatus,
     v_int32,
     VALUE(notified, 0, "notified"),
     VALUE(attending, 1, "attending"),
     VALUE(absent, 2, "absent"),
     VALUE(finished, 3, "finished"))

}  // namespace QuickExam::dto::basic

#include OATPP_CODEGEN_END(DTO)
