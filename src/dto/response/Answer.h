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
class ResponseAnswer : public basic::Response<Object<dto::Answer>> {
    DTO_INIT(ResponseAnswer, basic::Response<Object<dto::Answer>>)
};

class ResponseAnswers : public basic::Response<List<Object<dto::Answer>>> {
    DTO_INIT(ResponseAnswers, basic::Response<List<Object<dto::Answer>>>)
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)