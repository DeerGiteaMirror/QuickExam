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

ENUM(CandidateStatus,
     v_int32,
     VALUE(notified, 0, "notified"),
     VALUE(attending, 1, "attending"),
     VALUE(absent, 2, "absent"),
     VALUE(finished, 3, "finished"))

}  // namespace QuickExam::dto::basic

#include OATPP_CODEGEN_END(DTO)
