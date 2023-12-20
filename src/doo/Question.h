//
// QuickExam
// Created on 2023/12/19.
//

#pragma once
#include <dto/db/Question.h>
#include <oatpp-postgresql/orm.hpp>

#include OATPP_CODEGEN_BEGIN(DbClient)

namespace QuickExam::doo {

class Question : public oatpp::orm::DbClient {
public:
    explicit Question(const std::shared_ptr<oatpp::orm::Executor> &executor)
        : oatpp::orm::DbClient(executor) {}

    QUERY(insertQuestion,
          "INSERT INTO qe_question "
          "(id, is_sub_question, title, type, estimated_time_sec, score, "
          "is_published, reference_count, correct_count) "
          "VALUES "
          "(DEFAULT, :q.is_sub_question, :q.title, :q.type, :q.estimated_time_sec, :q.score, "
          ":q.is_published, :q.reference_count, :q.correct_count) "
          "RETURNING id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::Question>, q))

    QUERY(insertQuestionContent,
          "INSERT INTO qe_question_content "
          "(id, content_type, content, content_index, question_id) "
          "VALUES "
          "(DEFAULT, :q.content_type, :q.content, :q.content_index, :q.question_id) "
          "RETURNING id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::QuestionContents>, q))

    QUERY(insertQuestionSubQuestion,
          "INSERT INTO qe_question_sub_questions "
          "(id, sub_question_id, question_id) "
          "VALUES "
          "(DEFAULT, :q.sub_question_id, :q.question_id) "
          "RETURNING id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::QuestionSubQuestions>, q))

    QUERY(insertQuestionTag,
          "INSERT INTO qe_question_tag "
          "(id, tag_id, question_id, priority) "
          "VALUES "
          "(DEFAULT, :q.tag_id, :q.question_id, :q.priority) "
          "RETURNING id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::QuestionTag>, q))

    QUERY(getQuestion,
          "SELECT "
          "* "
          "FROM qe_question "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(getQuestionContent,
          "SELECT "
          "* "
          "FROM qe_question_content "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(getQuestionContentsByQuestionId,
          "SELECT "
          "* "
          "FROM qe_question_content "
          "WHERE question_id = :question_id",
          PREPARE(true),
          PARAM(oatpp::Int32, question_id))

    QUERY(getQuestionSubQuestionsIdByQuestionId,
          "SELECT "
          "* "
          "FROM qe_question_sub_questions "
          "WHERE question_id = :question_id",
          PREPARE(true),
          PARAM(oatpp::Int32, question_id))

    QUERY(getQuestionTagsIdByQuestionId,
          "SELECT "
          "* "
          "FROM qe_question_tag "
          "WHERE question_id = :question_id",
          PREPARE(true),
          PARAM(oatpp::Int32, question_id))

    QUERY(deleteQuestion,
          "DELETE "
          "FROM qe_question "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(deleteQuestionContent,
          "DELETE "
          "FROM qe_question_content "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(deleteQuestionContentByQuestionId,
          "DELETE "
          "FROM qe_question_content "
          "WHERE question_id = :question_id",
          PREPARE(true),
          PARAM(oatpp::Int32, question_id))

    QUERY(deleteQuestionSubQuestionByQuestionId,
          "DELETE "
          "FROM qe_question_sub_questions "
          "WHERE question_id = :question_id",
          PREPARE(true),
          PARAM(oatpp::Int32, question_id))

    QUERY(deleteQuestionTagByQuestionId,
          "DELETE "
          "FROM qe_question_tag "
          "WHERE question_id = :question_id",
          PREPARE(true),
          PARAM(oatpp::Int32, question_id))

    QUERY(updateQuestion,
          "UPDATE qe_question "
          "SET is_sub_question = :q.is_sub_question, "
          "title = :q.title, "
          "type = :q.type, "
          "estimated_time_sec = :q.estimated_time_sec, "
          "score = :q.score "
          "is_published = :q.is_published, "
          "reference_count = :q.reference_count, "
          "correct_count = :q.correct_count "
          "WHERE id = :q.id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::Question>, q))

    QUERY(updateQuestionContent,
          "UPDATE qe_question_content "
          "SET "
          "content_type = :q.content_type, "
          "content = :q.content, "
          "content_index = :q.content_index "
          "WHERE id = :q.id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::QuestionContents>, q))
};

}  // namespace QuickExam::doo

#include OATPP_CODEGEN_END(DbClient)