//
// QuickExam
// Created on 2023/12/20.
//

#pragma once

#include <dto/db/Question.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

class QuestionContent : public db::QuestionContents {
    DTO_INIT(QuestionContent, db::QuestionContents)
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)