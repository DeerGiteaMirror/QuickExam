//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <doo/Basic.h>
#include <dto/db/Answer.h>

#include OATPP_CODEGEN_BEGIN(DbClient)

namespace QuickExam::doo {

class Answer : public Basic {
public:
    explicit Answer(const std::shared_ptr<oatpp::orm::Executor> &executor) : Basic(executor) {}

    QUERY(insertAnswer,
          "INSERT INTO qe_answer "
          "(id, is_correct, question_id) "
          "VALUES "
          "(DEFAULT, :a.is_correct , :a.question_id) "
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

    QUERY(getAnswersByQuestionId,
          "SELECT "
          "* "
          "FROM qe_answer "
          "WHERE question_id = :question_id",
          PREPARE(true),
          PARAM(oatpp::Int32, question_id))

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