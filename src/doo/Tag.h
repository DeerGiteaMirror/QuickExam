//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/db/Tag.h>
#include <oatpp-postgresql/orm.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

namespace QuickExam::doo {

class Tag : public oatpp::orm::DbClient {
public:
    explicit Tag(const std::shared_ptr<oatpp::orm::Executor> &executor)
        : oatpp::orm::DbClient(executor) {}

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
          "* "
          "FROM qe_tag "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(getAllTags,
          "SELECT "
          "* "
          "FROM qe_tag",
          PREPARE(true))

    QUERY(getTagByName,
          "SELECT "
          "* "
          "FROM qe_tag "
          "WHERE name = :name",
          PREPARE(true),
          PARAM(oatpp::String, name))

    QUERY(deleteTag,
          "DELETE FROM qe_tag "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(updateTag,
          "UPDATE qe_tag "
          "SET name = :t.name, hex_color = :t.hex_color "
          "WHERE id = :t.id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::Tag>, t))
};

}  // namespace QuickExam::doo

#include OATPP_CODEGEN_END(DbClient)