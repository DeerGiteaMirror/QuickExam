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
    // get tags for extra
    for (auto &question : *page_data->items) {
        question->tags = m_tag_service.getTagsByQuestion(question->id);
    }
    auto response  = dto::ResponseQuestionPage::createShared();
    response->data = page_data;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::Question> QuestionService::getQuestionDetails(const Object<dto::Question> &question) {
    // get contents
    question->question_contents = getQuestionContents(question->id);
    // get answers
    question->answers = m_answer_service.getAnswerListByQuestionId(question->id);
    // get tags
    question->tags = m_tag_service.getTagsByQuestion(question->id);
    // get sub questions
    question->sub_questions = getSubQuestions(question->id);
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
    auto response  = dto::ResponseQuestion::createShared();
    response->data = data;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseQuestion>
QuestionService::updateQuestion(const Object<dto::Question> &question) {
    auto db_res = question_doo->updateQuestion(question);
    ASSERT_DB(db_res);
    auto response  = dto::ResponseQuestion::createShared();
    response->data = getQuestionDetails(question);
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::Response> QuestionService::deleteQuestion(const Int32 &id) {
    auto db_res = question_doo->deleteQuestion(id);
    ASSERT_DB(db_res);
    auto response  = dto::Response::createShared();
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

List<Object<dto::Question>> QuestionService::getSubQuestions(const Int32 &question_id) {
    auto return_list = List<Object<dto::Question>>::createShared();
    auto db_res      = question_doo->getQuestionSubQuestionsIdByQuestionId(question_id);
    IF_DB_ERROR(return_list);
    auto sub_questions_id = db_res->fetch<List<Object<dto::db::QuestionSubQuestion>>>();
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

Object<dto::ResponseQuestionContent>
QuestionService::addQuestionContent(const Object<QuestionContent> &content) {
    auto db_res = question_doo->insertQuestionContent(content);
    ASSERT_DB(db_res);
    auto data = dto::QuestionContent::createShared();
    FETCH_SINGLE(db_res, dto::QuestionContent, data);
    auto response  = dto::ResponseQuestionContent::createShared();
    response->data = data;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::Response> QuestionService::deleteQuestionContent(const Int32 &id) {
    auto db_res = question_doo->deleteQuestionContent(id);
    ASSERT_DB(db_res);
    auto response = dto::Response::createShared();
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

Object<dto::ResponseQuestionContents>
QuestionService::getQuestionContentsByQuestionId(const Int32 &question_id) {
    auto db_res = question_doo->getQuestionContentsByQuestionId(question_id);
    ASSERT_DB(db_res);
    auto return_list = db_res->fetch<List<Object<dto::QuestionContent>>>();
    auto response    = dto::ResponseQuestionContents::createShared();
    response->data   = return_list;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::Response> QuestionService::questionAddTag(const Int32 &question_id,
                                                      const Int32 &tag_id,
                                                      const Int32 &priority) {
    auto question_tag         = dto::db::QuestionTag::createShared();
    question_tag->question_id = question_id;
    question_tag->tag_id      = tag_id;
    question_tag->priority    = priority;
    auto db_res               = question_doo->insertQuestionTag(question_tag);
    ASSERT_DB(db_res);
    FETCH_SINGLE(db_res, dto::db::QuestionTag, question_tag);
    auto response = dto::Response::createShared();
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::Response> QuestionService::questionDeleteTag(const Int32 &id) {
    auto db_res = question_doo->deleteQuestionTag(id);
    ASSERT_DB(db_res);
    auto response = dto::Response::createShared();
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseQuestion>
QuestionService::questionAddSubQuestion(const Int32                 &parent_id,
                                        const Object<dto::Question> &question) {
    auto db_res = question_doo->insertQuestion(question);
    ASSERT_DB(db_res);
    auto sub_question = dto::Question::createShared();
    FETCH_SINGLE(db_res, dto::Question, sub_question);
    auto question_sub_question             = dto::db::QuestionSubQuestion::createShared();
    question_sub_question->question_id     = parent_id;
    question_sub_question->sub_question_id = sub_question->id;
    db_res = question_doo->insertQuestionSubQuestion(question_sub_question);
    ASSERT_DB(db_res);
    auto response  = dto::ResponseQuestion::createShared();
    response->data = sub_question;
    RETURN_STATUS_SUCCESS(response);
}

}  // namespace QuickExam::service