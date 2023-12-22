//
// QuickExam
// Created on 2023/12/22.
//

#pragma once

#include <dto/Configuration.h>
#include <oatpp-postgresql/orm.hpp>
#include <utils/Logger.h>

#include OATPP_CODEGEN_BEGIN(DbClient)

namespace QuickExam::doo {

class Basic : public oatpp::orm::DbClient {
protected:
    std::shared_ptr<oatpp::orm::Executor> m_executor;

public:
    explicit Basic(const std::shared_ptr<oatpp::orm::Executor> &executor)
        : oatpp::orm::DbClient(executor) {
        m_executor = executor;
    }
};

}  // namespace QuickExam::doo

#include OATPP_CODEGEN_END(DbClient)