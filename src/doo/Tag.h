//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <doo/Basic.h>
#include <dto/Tag.h>
#include <dto/db/Tag.h>

#include OATPP_CODEGEN_BEGIN(DbClient)

namespace QuickExam::doo {

class Tag : public Basic {
public:
    explicit Tag(const std::shared_ptr<oatpp::orm::Executor> &executor) : Basic(executor) {}

    QUERY(insertTag,
          "INSERT INTO qe_tag "
          "(id, name, hex_color) "
          "VALUES "
          "(DEFAULT, :t.name, :t.hex_color) "
          "RETURNING id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::Tag>, t))

    QUERY(getTag,
          "SELECT "
          "id, name, hex_color "
          "FROM qe_tag "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(deleteTag,
          "DELETE FROM qe_tag "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(updateTag,
          "UPDATE qe_tag "
          "SET name = :t.name, hex_color = :t.hex_color "
          "WHERE id = :t.id "
          "RETURNING id, name, hex_color",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::Tag>, t))

    QUERY(getAllTagIds,
          "SELECT "
          "id "
          "FROM qe_tag",
          PREPARE(true))

    DEFINE_CONDITION_FUNC(const oatpp::Object<dto::TagCondition> &query) {
        std::string sql = "WHERE 1 = 1 ";
        if (!query->search->empty()) {
            sql += "AND ";
            sql += "id IN (SELECT question_id FROM qe_question_content WHERE content LIKE '%" +
                   query->search + "%') ";
        }
        return sql;
    }

    DEFINE_COUNT_QUERY("qe_tag", dto::TagCondition)

    std::shared_ptr<oatpp::orm::QueryResult>
    getPageByConditions(const oatpp::Object<dto::TagCondition> &query) {
        std::string offset = std::to_string((query->page - 1) * query->page_size);
        std::string limit  = std::to_string(query->page_size);
        std::string sql    = "SELECT ";
        sql += "id, name, hex_color ";
        sql += "FROM qe_tag ";
        sql += conditionSqlString(query);
        sql += "ORDER BY " + query->sort_by + " " + query->sort_order + " ";
        sql += "OFFSET " + offset + " ";
        sql += "LIMIT " + limit + ";";
        LOGD("DEFINE_PAGE_QUERY", "Sql %s", sql.c_str());
        return m_executor->execute(sql, {});
    }
};

}  // namespace QuickExam::doo

#include OATPP_CODEGEN_END(DbClient)