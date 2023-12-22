//
// QuickExam
// Created on 2023/12/21.
//

#pragma once

#include <dto/Question.h>
#include <dto/basic/Enmus.h>
#include <dto/basic/Response.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {
using namespace oatpp;
class ResponseQuestion : public basic::Response<Object<dto::Question>> {
    DTO_INIT(ResponseQuestion, basic::Response<Object<dto::Question>>)
};

class ResponseQuestionPage : public basic::Response<Object<dto::QuestionPage>> {
    DTO_INIT(ResponseQuestionPage, basic::Response<Object<dto::QuestionPage>>)
};

class ResponseQuestionContents : public basic::Response<List<Object<dto::QuestionContent>>> {
    DTO_INIT(ResponseQuestionContents, basic::Response<List<Object<dto::QuestionContent>>>)
};

class ResponseQuestionContent : public basic::Response<Object<dto::QuestionContent>> {
    DTO_INIT(ResponseQuestionContent, basic::Response<Object<dto::QuestionContent>>)
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)