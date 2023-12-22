//
// QuickExam
// Created on 2023/12/21.
//

#pragma once

#include <dto/Tag.h>
#include <dto/basic/Enmus.h>
#include <dto/basic/Response.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {
using namespace oatpp;
class ResponseTag : public basic::Response<Object<dto::Tag>> {
    DTO_INIT(ResponseTag, basic::Response<Object<dto::Tag>>)
};

class ResponseTagPage : public basic::Response<Object<dto::TagPage>> {
    DTO_INIT(ResponseTagPage, basic::Response<Object<dto::TagPage>>)
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)