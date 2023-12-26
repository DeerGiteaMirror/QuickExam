//
// QuickExam
// Created on 2023/12/22.
//

#include "AnswerService.h"

namespace QuickExam::service {
List<Object<dto::AnswerContent>> AnswerService::getAnswerContents(const Int32 &answer_id) {
    auto return_list = List<Object<dto::AnswerContent>>::createShared();
    auto db_res      = answer_doo->getAnswerContentsByAnswerId(answer_id);
    IF_DB_ERROR(return_list)
    return_list = db_res->fetch<List<Object<dto::AnswerContent>>>();
    return return_list;
}

List<Object<dto::Answer>> AnswerService::getAnswerListByQuestionId(const Int32 &question_id) {
    auto return_list = List<Object<dto::Answer>>::createShared();
    auto db_res      = answer_doo->getAnswersByQuestionId(question_id);
    IF_DB_ERROR(return_list)
    return_list = db_res->fetch<List<Object<dto::Answer>>>();
    for (auto &answer : *return_list) {
        answer->answer_contents = getAnswerContents(answer->id);
    }
    return return_list;
}

Object<dto::ResponseAnswers> AnswerService::getAnswersByQuestionId(const Int32 &id) {
    auto data      = getAnswerListByQuestionId(id);
    auto response  = dto::ResponseAnswers::createShared();
    response->data = data;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseAnswer> AnswerService::createAnswer(const Object<dto::Answer> &answer) {
    auto db_res = answer_doo->insertAnswer(answer);
    ASSERT_DB(db_res);
    auto data = dto::Answer::createShared();
    FETCH_SINGLE(db_res, dto::Answer, data);
    auto response  = dto::ResponseAnswer::createShared();
    response->data = data;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseAnswer> AnswerService::updateAnswer(const Object<dto::Answer> &answer) {
    auto db_res = answer_doo->updateAnswer(answer);
    ASSERT_DB(db_res);
    auto data = dto::Answer::createShared();
    FETCH_SINGLE(db_res, dto::Answer, data);
    auto response  = dto::ResponseAnswer::createShared();
    response->data = data;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::Response> AnswerService::deleteAnswer(const Int32 &id) {
    auto db_res = answer_doo->deleteAnswer(id);
    ASSERT_DB(db_res);
    auto response = dto::Response::createShared();
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseAnswerContent>
AnswerService::addAnswerContent(const Object<dto::AnswerContent> &content) {
    auto db_res = answer_doo->insertAnswerContent(content);
    ASSERT_DB(db_res);
    auto data = dto::AnswerContent::createShared();
    FETCH_SINGLE(db_res, dto::AnswerContent, data);
    auto response  = dto::ResponseAnswerContent::createShared();
    response->data = data;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseAnswerContents>
AnswerService::getAnswerContentsByAnswerId(const Int32 &answer_id) {
    auto data      = getAnswerContents(answer_id);
    auto response  = dto::ResponseAnswerContents::createShared();
    response->data = data;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::Response> AnswerService::deleteAnswerContent(const Int32 &id) {
    auto db_res = answer_doo->deleteAnswerContent(id);
    ASSERT_DB(db_res);
    auto response = dto::Response::createShared();
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseAnswerContent>
AnswerService::updateAnswerContent(const Object<dto::AnswerContent> &content) {
    auto db_res = answer_doo->updateAnswerContent(content);
    ASSERT_DB(db_res);
    auto data = dto::AnswerContent::createShared();
    FETCH_SINGLE(db_res, dto::AnswerContent, data);
    auto response  = dto::ResponseAnswerContent::createShared();
    response->data = data;
    RETURN_STATUS_SUCCESS(response);
}

}  // namespace QuickExam::service
