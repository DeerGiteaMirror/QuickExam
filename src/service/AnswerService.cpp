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

List<Object<dto::Answer>> AnswerService::getAnswersByQuestionId(const Int32 &question_id) {
    auto return_list = List<Object<dto::Answer>>::createShared();
    auto db_res      = answer_doo->getAnswersByQuestionId(question_id);
    IF_DB_ERROR(return_list)
    return_list = db_res->fetch<List<Object<dto::Answer>>>();
    for (auto &answer : *return_list) {
        answer->answer_contents = getAnswerContents(answer->id);
    }
    return return_list;
}

}  // namespace QuickExam::service
