//
// AnonExam
// Created on 2023/12/19.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace AnonExam::dto::db {

class Quiz : public oatpp::DTO {};

}  // namespace AnonExam::dto::db

#include OATPP_CODEGEN_END(DTO)