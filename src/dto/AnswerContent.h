//
// QuickExam
// Created on 2023/12/20.
//

#pragma once

#include <dto/db/Answer.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

class AnswerContent : public db::AnswerContents {
    DTO_INIT(AnswerContent, db::AnswerContents)
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)