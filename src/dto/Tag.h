//
// QuickExam
// Created on 2023/12/20.
//

#pragma once

#include <dto/basic/Page.h>
#include <dto/db/Tag.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

class Tag : public db::Tag {
    DTO_INIT(Tag, db::Tag)
};

class TagCondition : public basic::Condition {
    DTO_INIT(TagCondition, basic::Condition)
};

class TagPage : public basic::Page<oatpp::Object<Tag>> {
    DTO_INIT(TagPage, basic::Page<oatpp::Object<Tag>>)
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)