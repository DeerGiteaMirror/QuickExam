//
// QuickExam
// Created on 2023/12/21.
//

#include "QuestionService.h"

namespace QuickExam::service {

Object<dto::ResponseQuestionPage>
QuestionService::getQuestionsByPageConditions(const Object<dto::QuestionCondition> &conditions) {
    auto page_info = dto::QuestionPage::createShared();
    GET_PAGE(question_doo, conditions, page_info, dto::Question);
    auto page_items = List<Object<dto::Question>>::createShared();
    for (auto &question : *page_info->items) {
        page_items->push_back(getQuestionDetails(question));
    }
    page_info->items = page_items;
    auto response    = dto::ResponseQuestionPage::createShared();
    response->data   = page_info;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::Question> QuestionService::getQuestionDetails(const Object<dto::Question> &question) {
#define IF_DB_ERROR                                                                                \
    if (!db_res->isSuccess()) {                                                                    \
        LOGE("getQuestionDetails", "getQuestionContentsByQuestionId failed %s",                    \
             db_res->getErrorMessage()->c_str());                                                  \
        return question;                                                                           \
    }
    // init
    question->sub_questions     = List<Object<dto::Question>>::createShared();
    question->answers           = List<Object<dto::Answer>>::createShared();
    question->tags              = List<Object<dto::Tag>>::createShared();
    question->question_contents = List<Object<dto::QuestionContent>>::createShared();
    // get contents
    auto db_res = question_doo->getQuestionContentsByQuestionId(question->id);
    IF_DB_ERROR;
    question->question_contents = db_res->fetch<List<Object<dto::QuestionContent>>>();
    // get answers
    db_res = answer_doo->getAnswersByQuestionId(question->id);
    IF_DB_ERROR;
    question->answers = db_res->fetch<List<Object<dto::Answer>>>();
    for (auto &answer : *question->answers) {
        db_res = answer_doo->getAnswerContentsByAnswerId(answer->id);
        IF_DB_ERROR;
        answer->answer_contents = db_res->fetch<List<Object<dto::AnswerContent>>>();
    }
    // get tags
    db_res = question_doo->getQuestionTagsIdByQuestionId(question->id);
    IF_DB_ERROR;
    auto tags_id = db_res->fetch<List<Object<dto::db::QuestionTags>>>();
    for (auto &tag_id : *tags_id) {
        db_res = tag_doo->getTag(tag_id->tag_id);
        IF_DB_ERROR;
        auto tags = db_res->fetch<List<Object<dto::Tag>>>();
        if (tags->size() != 1) {
            LOGW("getQuestionDetails", "getTag failed %s", db_res->getErrorMessage()->c_str());
            continue;
        }
        question->tags->push_back(tags->front());
    }
    // get sub questions
    db_res = question_doo->getQuestionSubQuestionsIdByQuestionId(question->id);
    IF_DB_ERROR;
    auto sub_questions_id = db_res->fetch<List<Object<dto::db::QuestionSubQuestions>>>();
    for (auto &sub_question_id : *sub_questions_id) {
        db_res = question_doo->getQuestion(sub_question_id->sub_question_id);
        IF_DB_ERROR;
        auto sub_questions = db_res->fetch<List<Object<dto::Question>>>();
        if (sub_questions->size() != 1) {
            LOGW("getQuestionDetails", "getQuestion failed %s", db_res->getErrorMessage()->c_str());
            continue;
        }
        auto sub_question = getQuestionDetails(sub_questions->front());
        question->sub_questions->push_back(sub_question);
    }
    return question;
#undef IF_DB_ERROR
}

Object<dto::ResponseQuestion> QuestionService::getQuestionById(const Int32 &id) {
    auto db_res = question_doo->getQuestion(id);
    ASSERT_DB(db_res);
    auto        questions = db_res->fetch<List<Object<dto::Question>>>();
    std::string msg       = "Question id: " + std::to_string(id) + " not found";
    ASSERT_EXIST(questions->size() == 1, msg.c_str());
    auto data      = getQuestionDetails(questions->front());
    auto response  = dto::ResponseQuestion::createShared();
    response->data = data;
    RETURN_STATUS_SUCCESS(response);
}

}  // namespace QuickExam::service
