//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <doo/Basic.h>
#include <dto/Question.h>
#include <dto/db/Question.h>
#include <utils/Logger.h>

#include OATPP_CODEGEN_BEGIN(DbClient)

namespace QuickExam::doo {

class Question : public Basic {
public:
    explicit Question(const std::shared_ptr<oatpp::orm::Executor> &executor) : Basic(executor) {}

    QUERY(insertQuestion,
          "INSERT INTO qe_question "
          "(id, parent, title, type, estimated_time_sec, score, "
          "is_published, reference_count, correct_count) "
          "VALUES "
          "(DEFAULT, :q.parent, :q.title, :q.type, :q.estimated_time_sec, :q.score, "
          "DEFAULT, DEFAULT, DEFAULT) "
          "RETURNING id, parent, title, type, estimated_time_sec, score, "
          "is_published, reference_count, correct_count",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::Question>, q))

    QUERY(insertQuestionContent,
          "INSERT INTO qe_question_content "
          "(id, content_type, content, content_index, question_id) "
          "VALUES "
          "(DEFAULT, :q.content_type, :q.content, :q.content_index, :q.question_id) "
          "RETURNING id, content_type, content, content_index, question_id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::QuestionContents>, q))

    QUERY(insertQuestionSubQuestion,
          "INSERT INTO qe_question_sub_questions "
          "(id, sub_question_id, question_id) "
          "VALUES "
          "(DEFAULT, :q.sub_question_id, :q.question_id) "
          "RETURNING id, sub_question_id, question_id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::QuestionSubQuestion>, q))

    QUERY(insertQuestionTag,
          "INSERT INTO qe_question_tag "
          "(id, tag_id, question_id, priority) "
          "VALUES "
          "(DEFAULT, :q.tag_id, :q.question_id, :q.priority) "
          "RETURNING id, tag_id, question_id, priority",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::QuestionTag>, q))

    QUERY(getQuestion,
          "SELECT "
          "id, parent, title, type, estimated_time_sec, score, "
          "is_published, reference_count, correct_count, "
          "to_char(created_at, 'YYYY-MM-DD HH24:MI:SS') as created_at, "
          "to_char(updated_at, 'YYYY-MM-DD HH24:MI:SS') as updated_at "
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
          "id, tag_id, question_id, priority "
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

    QUERY(deleteQuestionTag,
          "DELETE "
          "FROM qe_question_tag "
          "WHERE id = :id",
          PREPARE(true),
          PARAM(oatpp::Int32, id))

    QUERY(updateQuestion,
          "UPDATE qe_question "
          "SET parent = :q.parent, "
          "title = :q.title, "
          "type = :q.type, "
          "estimated_time_sec = :q.estimated_time_sec, "
          "score = :q.score "
          "is_published = :q.is_published, "
          "reference_count = :q.reference_count, "
          "correct_count = :q.correct_count, "
          "updated_at = CURRENT_TIMESTAMP "
          "WHERE id = :q.id "
          "RETURNING id, parent, title, type, estimated_time_sec, score, "
          "is_published, reference_count, correct_count, "
          "to_char(created_at, 'YYYY-MM-DD HH24:MI:SS') as created_at, "
          "to_char(updated_at, 'YYYY-MM-DD HH24:MI:SS') as updated_at",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::Question>, q))

    QUERY(updateQuestionContent,
          "UPDATE qe_question_content "
          "SET "
          "content_type = :q.content_type, "
          "content = :q.content, "
          "content_index = :q.content_index "
          "WHERE id = :q.id "
          "RETURNING id, content_type, content, content_index, question_id",
          PREPARE(true),
          PARAM(oatpp::Object<dto::db::QuestionContents>, q))

    QUERY(getQuestionsByTagId,
          "SELECT "
          "* "
          "FROM qe_question "
          "WHERE id IN (SELECT question_id FROM qe_question_tag WHERE tag_id = :tag_id)",
          PREPARE(true),
          PARAM(oatpp::Int32, tag_id))

    DEFINE_CONDITION_FUNC(const oatpp::Object<dto::QuestionCondition> &query) {
        std::string sql = "WHERE 1 = 1 ";
        if (!query->search->empty()) {
            sql += "AND (";
            sql += "id IN (SELECT question_id FROM qe_question_content WHERE content LIKE '%" +
                   query->search + "%') ";
            sql += "OR ";
            sql += "title LIKE '%" + query->search + "%' ";
            sql += ") ";
        }
        if (!query->types->empty()) {
            sql += "AND ";
            sql += "type IN (";
            for (auto &type : *query->types) {
                sql += std::to_string(type) + ", ";
            }
            sql.pop_back();
            sql.pop_back();
            sql += ") ";
        }
        if (!query->tag_ids->empty()) {
            sql += "AND ";
            sql += "id IN (SELECT question_id FROM qe_question_tag WHERE tag_id IN (";
            for (auto &tag_id : *query->tag_ids) {
                sql += std::to_string(tag_id) + ", ";
            }
            sql.pop_back();
            sql.pop_back();
            sql += ")) ";
        }
        if (query->is_published == 0 || query->is_published == 1) {
            std::string bool_str = query->is_published == 0 ? "false" : "true";
            sql += "AND ";
            sql += "is_published = " + bool_str + " ";
        }
        if (query->after_create_time != 0) {
            sql += "AND ";
            sql += "created_at > to_timestamp(" + std::to_string(query->after_create_time) + ") ";
        }
        if (query->before_create_time != 0) {
            sql += "AND ";
            sql += "created_at < to_timestamp(" + std::to_string(query->before_create_time) + ") ";
        }
        if (query->after_update_time != 0) {
            sql += "AND ";
            sql += "updated_at > to_timestamp(" + std::to_string(query->after_update_time) + ") ";
        }
        if (query->before_update_time != 0) {
            sql += "AND ";
            sql += "updated_at < to_timestamp(" + std::to_string(query->before_update_time) + ") ";
        }
        return sql;
    }

    DEFINE_COUNT_QUERY("qe_question", dto::QuestionCondition)

    std::shared_ptr<oatpp::orm::QueryResult>
    getPageByConditions(const oatpp::Object<dto::QuestionCondition> &query) {
        std::string offset = std::to_string((query->page - 1) * query->page_size);
        std::string limit  = std::to_string(query->page_size);
        std::string sql    = "SELECT ";
        sql += "id, parent, title, type, estimated_time_sec, score, ";
        sql += "is_published, reference_count, correct_count, ";
        sql += "to_char(created_at, 'YYYY-MM-DD HH24:MI:SS') as created_at, ";
        sql += "to_char(updated_at, 'YYYY-MM-DD HH24:MI:SS') as updated_at ";
        sql += "FROM qe_question ";
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