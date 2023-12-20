//
// QuickExam
// Created on 2023/12/20.
//

#pragma once

#include <dto/db/Tag.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

class Tag : public db::Tag {
    DTO_INIT(Tag, db::Tag)
};

}  // namespace QuickExam::dto

#include OATPP_CODEGEN_END(DTO)