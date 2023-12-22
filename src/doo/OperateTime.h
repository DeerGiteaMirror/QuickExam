//
// QuickExam
// Created on 2023/12/22.
//

#pragma once

#include <doo/Basic.h>
#include <dto/db/Tag.h>

#include OATPP_CODEGEN_BEGIN(DbClient)

namespace QuickExam::doo {

class OperateTime : public Basic {
public:
    explicit OperateTime(const std::shared_ptr<oatpp::orm::Executor> &executor) : Basic(executor) {}

    //    QUERY(insertOperateTime,
    //          "INSERT INTO :table_name "
    //          "(id, belong_id, created_at, updated_at) "
    //          "VALUES "
    //          "(DEFAULT, :belong_id, CURRENT_TIMESTAMP, CURRENT_TIMESTAMP) "
    //          "RETURNING id, belong_id, created_at, updated_at",
    //          PREPARE(true),
    //          PARAM(oatpp::String, table_name),
    //          PARAM(oatpp::Int32, belong_id))

    //    QUERY(updateOperateTime,
    //          "UPDATE :table_name "
    //          "SET "
    //          "update_at = CURRENT_TIMESTAMP "
    //          "WHERE belong_id = :belong_id "
    //          "RETURNING id, belong_id, created_at, updated_at",
    //          PREPARE(true),
    //          PARAM(oatpp::String, table_name),
    //          PARAM(oatpp::Int32, belong_id))
    //
    //    QUERY(getOperateTime,
    //          "SELECT "
    //          "* "
    //          "FROM :table_name "
    //          "WHERE belong_id = :belong_id",
    //          PREPARE(true),
    //          PARAM(oatpp::String, table_name),
    //          PARAM(oatpp::Int32, belong_id))

    std::shared_ptr<oatpp::orm::QueryResult> insertOperateTime(const std::string &table_name,
                                                               int                belong_id) {
        std::string sql = "INSERT INTO " + table_name +
                          " (id, belong_id, created_at, updated_at) "
                          "VALUES "
                          "(DEFAULT, " +
                          std::to_string(belong_id) +
                          ", CURRENT_TIMESTAMP, CURRENT_TIMESTAMP) "
                          "RETURNING id, belong_id, created_at, updated_at";
        return m_executor->execute(sql, {});
    }

    std::shared_ptr<oatpp::orm::QueryResult> updateOperateTime(const std::string &table_name,
                                                               int                belong_id) {
        std::string sql = "UPDATE " + table_name +
                          " SET "
                          "update_at = CURRENT_TIMESTAMP "
                          "WHERE belong_id = " +
                          std::to_string(belong_id) +
                          " RETURNING id, belong_id, created_at, updated_at";
        return m_executor->execute(sql, {});
    }

    std::shared_ptr<oatpp::orm::QueryResult> getOperateTime(const std::string &table_name,
                                                            int                belong_id) {
        std::string sql = "SELECT "
                          "* "
                          "FROM " +
                          table_name + " WHERE belong_id = " + std::to_string(belong_id);
        return m_executor->execute(sql, {});
    }
};

}  // namespace QuickExam::doo

#include OATPP_CODEGEN_END(DbClient)