//
// QuickExam
// Created on 2023/12/21.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#define DEFINE_CONDITION_FUNC static std::string conditionSqlString

#define DEFINE_COUNT_QUERY(TABLE_NAME, CONDITION_DTO)                                              \
    std::shared_ptr<oatpp::orm::QueryResult> getPageCountByConditions(                             \
        const oatpp::Object<CONDITION_DTO> &query) {                                               \
        std::string sql = "SELECT ";                                                               \
        sql += "COUNT(*) AS total_count ";                                                         \
        sql += "FROM " TABLE_NAME " ";                                                             \
        sql += conditionSqlString(query) + ";";                                                    \
        LOGD("DEFINE_COUNT_QUERY", "Sql %s", sql.c_str());                                         \
        return m_executor->execute(sql, {});                                                       \
    }

#define DEFINE_PAGE_QUERY(TABLE_NAME, CONDITION_DTO)                                               \
    std::shared_ptr<oatpp::orm::QueryResult> getPageByConditions(                                  \
        const oatpp::Object<CONDITION_DTO> &query) {                                               \
        std::string offset = std::to_string((query->page - 1) * query->page_size);                 \
        std::string limit  = std::to_string(query->page_size);                                     \
        std::string sql    = "SELECT ";                                                            \
        sql += "* ";                                                                               \
        sql += "FROM " TABLE_NAME " ";                                                             \
        sql += conditionSqlString(query);                                                          \
        sql += "ORDER BY " + query->sort_by + " " + query->sort_order + " ";                       \
        sql += "OFFSET " + offset + " ";                                                           \
        sql += "LIMIT " + limit + ";";                                                             \
        LOGD("DEFINE_PAGE_QUERY", "Sql %s", sql.c_str());                                          \
        return m_executor->execute(sql, {});                                                       \
    }

#define GET_PAGE(DOO, CONDITION_DATA, PAGE_DATA, ITEM_DTO)                                         \
    {                                                                                              \
        auto DB_RES = (DOO)->getPageCountByConditions(CONDITION_DATA);                             \
        ASSERT_DB(DB_RES);                                                                         \
        auto totals =                                                                              \
            DB_RES->fetch<oatpp::List<oatpp::Object<dto::basic::Page<Void>>>>()->front();          \
        (PAGE_DATA)->total_count = totals->total_count;                                            \
        (PAGE_DATA)->total_page  = totals->total_count % (CONDITION_DATA)->page_size == 0 ?        \
                                       totals->total_count / (CONDITION_DATA)->page_size :         \
                                       totals->total_count / (CONDITION_DATA)->page_size + 1;      \
        if ((CONDITION_DATA)->page > (PAGE_DATA)->total_page) {                                    \
            (CONDITION_DATA)->page = (PAGE_DATA)->total_page;                                      \
        }                                                                                          \
        if ((CONDITION_DATA)->page <= 0) {                                                         \
            (CONDITION_DATA)->page = 1;                                                            \
        }                                                                                          \
        DB_RES = (DOO)->getPageByConditions(CONDITION_DATA);                                       \
        ASSERT_DB(DB_RES);                                                                         \
        (PAGE_DATA)->items = DB_RES->fetch<oatpp::List<oatpp::Object<ITEM_DTO>>>();                \
    }

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto::basic {
template <class L>
class Page : public oatpp::DTO {
    DTO_INIT(Page, DTO)

    DTO_FIELD(Int32, page) = 1;
    DTO_FIELD_INFO(page) {
        info->description = "Page number";
        info->required    = true;
    }

    DTO_FIELD(Int32, page_size) = 10;
    DTO_FIELD_INFO(page_size) {
        info->description = "Page size";
        info->required    = true;
    }

    DTO_FIELD(Int32, total_count) = 0;
    DTO_FIELD_INFO(total_count) {
        info->description = "Total number of records";
        info->required    = true;
    }

    DTO_FIELD(Int32, total_page) = 0;
    DTO_FIELD_INFO(total_page) {
        info->description = "Total number of pages";
        info->required    = true;
    }

    DTO_FIELD(List<L>, items) = List<L>::createShared();
    DTO_FIELD_INFO(items) {
        info->description = "Data list";
        info->required    = true;
    }
};

class Condition : public oatpp::DTO {
    DTO_INIT(Condition, DTO)

    DTO_FIELD(Int32, page) = 1;
    DTO_FIELD_INFO(page) {
        info->description = "Page number";
        info->required    = true;
    }

    DTO_FIELD(Int32, page_size) = 10;
    DTO_FIELD_INFO(page_size) {
        info->description = "Page size";
        info->required    = true;
    }

    DTO_FIELD(String, sort_by) = "id";
    DTO_FIELD_INFO(sort_by) {
        info->description = "Sort by";
    }

    DTO_FIELD(String, sort_order) = "ASC";
    DTO_FIELD_INFO(sort_order) {
        info->description = "Sort order (ASC or DESC)";
    }

    DTO_FIELD(String, search) = "";
    DTO_FIELD_INFO(search) {
        info->description = "Search keyword";
    }
};

}  // namespace QuickExam::dto::basic

#include OATPP_CODEGEN_END(DTO)