//
// QuickExam
// Created on 2023/12/21.
//

#include "QuestionService.h"

namespace QuickExam::service {

Object<dto::ResponseQuestionPage>
QuestionService::getQuestionsByPageConditions(const Object<dto::QuestionCondition> &conditions) {
    auto page_data = dto::QuestionPage::createShared();
    GET_PAGE(question_doo, conditions, page_data, dto::Question);
    for (auto &question : *page_data->items) {
        question->tags = getQuestionTags(question->id);
    }
    auto response  = dto::ResponseQuestionPage::createShared();
    response->data = page_data;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::Question> QuestionService::getQuestionDetails(const Object<dto::Question> &question) {
    // get contents
    question->question_contents = getQuestionContents(question->id);
    // get answers
    question->answers = getQuestionAnswers(question->id);
    // get tags
    question->tags = getQuestionTags(question->id);
    // get sub questions
    question->sub_questions = getSubQuestions(question->id);
    // get operate time
    question->operate_time = getOperateTime(operate_time_table_name, question->id);
    return question;
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

Object<dto::ResponseQuestion>
QuestionService::createQuestion(const Object<dto::Question> &question) {
    auto db_res = question_doo->insertQuestion(question);
    ASSERT_DB(db_res);
    auto data = dto::Question::createShared();
    FETCH_SINGLE(db_res, dto::Question, data);
    data->operate_time = createOperateTime(operate_time_table_name, data->id);
    auto response      = dto::ResponseQuestion::createShared();
    response->data     = data;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseQuestion>
QuestionService::updateQuestion(const Object<dto::Question> &question) {
    auto db_res = question_doo->updateQuestion(question);
    ASSERT_DB(db_res);
    updateOperateTime(operate_time_table_name, question->id);
    auto response  = dto::ResponseQuestion::createShared();
    response->data = getQuestionDetails(question);
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::basic::Response<String>> QuestionService::deleteQuestion(const Int32 &id) {
    auto db_res = question_doo->deleteQuestion(id);
    ASSERT_DB(db_res);
    auto response  = dto::basic::Response<String>::createShared();
    response->data = "Delete question id: " + std::to_string(id) + " success";
    RETURN_STATUS_SUCCESS(response);
}

List<Object<dto::QuestionContent>> QuestionService::getQuestionContents(const Int32 &question_id) {
    auto return_list = List<Object<dto::QuestionContent>>::createShared();
    auto db_res      = question_doo->getQuestionContentsByQuestionId(question_id);
    IF_DB_ERROR(return_list);
    return_list = db_res->fetch<List<Object<dto::QuestionContent>>>();
    return return_list;
}

List<Object<dto::Tag>> QuestionService::getQuestionTags(const Int32 &question_id) {
    auto return_list = List<Object<dto::Tag>>::createShared();
    auto db_res      = question_doo->getQuestionTagsIdByQuestionId(question_id);
    IF_DB_ERROR(List<Object<dto::Tag>>::createShared());
    auto tags_id = db_res->fetch<List<Object<dto::db::QuestionTags>>>();
    for (auto &tag_id : *tags_id) {
        auto tag = m_tag_service.getTagById(tag_id->tag_id);
        return_list->push_back(tag);
    }
    return return_list;
}

List<Object<dto::Answer>> QuestionService::getQuestionAnswers(const Int32 &question_id) {
    return m_answer_service.getAnswersByQuestionId(question_id);
}

List<Object<dto::Question>> QuestionService::getSubQuestions(const Int32 &question_id) {
    auto return_list = List<Object<dto::Question>>::createShared();
    auto db_res      = question_doo->getQuestionSubQuestionsIdByQuestionId(question_id);
    IF_DB_ERROR(return_list);
    auto sub_questions_id = db_res->fetch<List<Object<dto::db::QuestionSubQuestions>>>();
    if (sub_questions_id->empty())
        return return_list;
    for (auto &sub_question_id : *sub_questions_id) {
        db_res = question_doo->getQuestion(sub_question_id->sub_question_id);
        IF_DB_ERROR(return_list);
        auto sub_questions = dto::Question::createShared();
        FETCH_SINGLE(db_res, dto::Question, sub_questions);
        auto sub_question = getQuestionDetails(sub_questions);
        return_list->push_back(sub_question);
    }
    return return_list;
}

Object<dto::ResponseQuestionContents>
QuestionService::addQuestionContent(const Object<QuestionContent> &content) {
    auto db_res = question_doo->insertQuestionContent(content);
    ASSERT_DB(db_res);
    auto response  = dto::ResponseQuestionContents::createShared();
    response->data = getQuestionContents(content->question_id);
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseQuestionContents> QuestionService::deleteQuestionContent(const Int32 &id) {
    auto db_res = question_doo->deleteQuestionContent(id);
    ASSERT_DB(db_res);
    auto response  = dto::ResponseQuestionContents::createShared();
    response->data = getQuestionContents(id);
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseQuestionContent>
QuestionService::updateQuestionContent(const Object<QuestionContent> &content) {
    auto db_res = question_doo->updateQuestionContent(content);
    ASSERT_DB(db_res);
    auto response  = dto::ResponseQuestionContent::createShared();
    response->data = getQuestionContent(content->id);
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::QuestionContent> QuestionService::getQuestionContent(const Int32 &content_id) {
    auto db_res = question_doo->getQuestionContent(content_id);
    ASSERT_DB(db_res);
    auto return_content = dto::QuestionContent::createShared();
    FETCH_SINGLE(db_res, dto::QuestionContent, return_content);
    return return_content;
}

}  // namespace QuickExam::service