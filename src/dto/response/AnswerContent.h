//
// QuickExam
// Created on 2023/12/25.
//

#pragma once

#include <dto/Answer.h>
#include <dto/basic/Enmus.h>
#include <dto/basic/Response.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

using namespace oatpp;
class ResponseAnswerContent : public basic::Response<Object<dto::AnswerContent>> {
    DTO_INIT(ResponseAnswerContent, basic::Response<Object<dto::AnswerContent>>)
};

class ResponseAnswerContents : public basic::Response<List<Object<dto::AnswerContent>>> {
    DTO_INIT(ResponseAnswerContents, basic::Response<List<Object<dto::AnswerContent>>>)
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)