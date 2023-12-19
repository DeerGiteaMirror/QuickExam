//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <dto/db/Answer.h>
#include <oatpp-postgresql/orm.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

namespace QuickExam::doo {

class Answer : public oatpp::orm::DbClient {
public:
    explicit Answer(const std::shared_ptr<oatpp::orm::Executor> &executor)
        : oatpp::orm::DbClient(executor) {
        std::string createTableAnswer = "CREATE TABLE IF NOT EXISTS qe_answer ("
                                        "id SERIAL PRIMARY KEY,"
                                        "is_correct BOOLEAN NOT NULL DEFAULT FALSE"
                                        ");";

        std::string createTableAnswerContent =
            "CREATE TABLE IF NOT EXISTS qe_answer_content ("
            "id SERIAL PRIMARY KEY,"
            "content_type INTEGER NOT NULL,"
            "content TEXT NOT NULL,"
            "content_index INTEGER NOT NULL,"
            "answer_id INTEGER NOT NULL,"
            "FOREIGN KEY (answer_id) REFERENCES qe_answer(id) ON DELETE CASCADE"
            ");";

        executor->execute(createTableAnswer, {});
        executor->execute(createTableAnswerContent, {});
    }

    QUERY(insertAnswer,
          "INSERT INTO qe_answer "
          "(id, is_correct) "
          "VALUES "
          "(DEFAULT, :a.is_correct) "
          "RETURNING id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::Answer>, a))

    QUERY(insertAnswerContent,
          "INSERT INTO qe_answer_content "
          "(id, content_type, content, content_index, answer_id) "
          "VALUES "
          "(DEFAULT, :a.content_type, :a.content, :a.content_index, :a.answer_id) "
          "RETURNING id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::AnswerContents>, a))

    QUERY(getAnswer,
          "SELECT "
          "* "
          "FROM qe_answer "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(getAnswerContentsByAnswerId,
          "SELECT "
          "* "
          "FROM qe_answer_content "
          "WHERE answer_id = :answer_id",
          PREPARE(true),
          PARAM(oatpp::Int32, answer_id))

    QUERY(deleteAnswer,
          "DELETE "
          "FROM qe_answer "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(deleteAnswerContent,
          "DELETE "
          "FROM qe_answer_content "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(deleteAnswerContentByAnswerId,
          "DELETE "
          "FROM qe_answer_content "
          "WHERE answer_id = :answer_id",
          PREPARE(true),
          PARAM(oatpp::Int32, answer_id))

    QUERY(updateAnswer,
          "UPDATE qe_answer "
          "SET is_correct = :a.is_correct "
          "WHERE id = :a.id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::Answer>, a))

    QUERY(updateAnswerContent,
          "UPDATE qe_answer_content "
          "SET "
          "content_type = :a.content_type, "
          "content = :a.content, "
          "content_index = :a.content_index "
          "WHERE id = :a.id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::AnswerContents>, a))
};

}  // namespace QuickExam::doo

#include OATPP_CODEGEN_END(DbClient)