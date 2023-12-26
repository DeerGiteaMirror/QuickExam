//
// QuickExam
// Created on 2023/12/22.
//

#pragma once

#include <doo/Answer.h>
#include <dto/Answer.h>
#include <dto/response/Answer.h>
#include <dto/response/AnswerContent.h>
#include <service/BasicService.h>

namespace QuickExam::service {
using namespace oatpp;
class AnswerService : public BasicService {
private:
    OATPP_COMPONENT(std::shared_ptr<doo::Answer>, answer_doo);

public:
    AnswerService()  = default;
    ~AnswerService() = default;

public:  // ---> Controller methods (Answer)
    Object<dto::ResponseAnswers> getAnswersByQuestionId(const Int32 &question_id);

    Object<dto::ResponseAnswer> createAnswer(const Object<dto::Answer> &answer);

    Object<dto::ResponseAnswer> updateAnswer(const Object<dto::Answer> &answer);

    Object<dto::Response> deleteAnswer(const Int32 &id);

public:  // ---> Controller methods (Content)
    Object<dto::ResponseAnswerContent> addAnswerContent(const Object<dto::AnswerContent> &content);

    Object<dto::ResponseAnswerContents> getAnswerContentsByAnswerId(const Int32 &answer_id);

    Object<dto::Response> deleteAnswerContent(const Int32 &id);

    Object<dto::ResponseAnswerContent>
    updateAnswerContent(const Object<dto::AnswerContent> &content);

public:  // ---> Service methods
    /**
     * @brief Get the answer content list by answer id
     * @param answer_id The answer id
     * @return List<Object<dto::AnswerContent>> The answer content list
     */
    List<Object<dto::AnswerContent>> getAnswerContents(const Int32 &answer_id);

    /**
     * @brief Get the answer list by question id
     * @param question_id The question id
     * @return List<Object<dto::Answer>> The answer list
     */
    List<Object<dto::Answer>> getAnswerListByQuestionId(const Int32 &question_id);
};

}  // namespace QuickExam::service
