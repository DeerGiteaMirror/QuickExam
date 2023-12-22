//
// QuickExam
// Created on 2023/12/21.
//

#pragma once

#include <doo/Answer.h>
#include <doo/Question.h>
#include <doo/Tag.h>
#include <dto/Question.h>
#include <dto/basic/Enmus.h>
#include <dto/basic/Response.h>
#include <dto/response/Question.h>
#include <service/AnswerService.h>
#include <service/BasicService.h>
#include <service/TagService.h>

namespace QuickExam::service {
using namespace oatpp;
class QuestionService : public BasicService {
private:
    OATPP_COMPONENT(std::shared_ptr<doo::Question>, question_doo);
    OATPP_COMPONENT(std::shared_ptr<doo::Tag>, tag_doo);
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, m_objectMapper);

    std::string operate_time_table_name = "qe_question_operate_time";

    AnswerService m_answer_service;
    TagService    m_tag_service;

public:
    QuestionService()  = default;
    ~QuestionService() = default;

public:  // ---> Controller methods
    Object<dto::ResponseQuestionPage>
    getQuestionsByPageConditions(const Object<dto::QuestionCondition> &page_conditions);

    Object<dto::ResponseQuestion> getQuestionById(const Int32 &id);

    Object<dto::ResponseQuestion> createQuestion(const Object<dto::Question> &question);

    Object<dto::ResponseQuestion> updateQuestion(const Object<dto::Question> &question);

    Object<dto::basic::Response<String>> deleteQuestion(const Int32 &id);

    Object<dto::ResponseQuestionContents>
    addQuestionContent(const Object<dto::QuestionContent> &content);

    Object<dto::ResponseQuestionContents> deleteQuestionContent(const Int32 &id);

    Object<dto::ResponseQuestionContent>
    updateQuestionContent(const Object<dto::QuestionContent> &content);

public:  // ---> Service methods
    /**
     * @brief Get the Question Details object
     * @param question The question object
     * @return Object<dto::Question> The question object
     */
    Object<dto::Question> getQuestionDetails(const Object<dto::Question> &question);

    /**
     * @brief Get the Question Contents object
     * @param question_id The question id
     * @return List<Object<dto::QuestionContent>> The question contents list
     */
    List<Object<dto::QuestionContent>> getQuestionContents(const Int32 &question_id);
    Object<dto::QuestionContent>       getQuestionContent(const Int32 &content_id);

    /**
     * @brief Get the Question Tags object
     * @param question_id The question id
     * @return List<Object<dto::Tag>> The question tags list
     */
    List<Object<dto::Tag>> getQuestionTags(const Int32 &question_id);

    /**
     * @brief Get the Question Answers object (with answer contents)
     * @param question_id The question id
     * @return  List<Object<dto::Answer>> The question answers list
     */
    List<Object<dto::Answer>> getQuestionAnswers(const Int32 &question_id);

    /**
     * @brief Get the Sub Questions object (with details)
     * @param question_id The question id
     * @return List<Object<dto::Question>> The sub questions list
     */
    List<Object<dto::Question>> getSubQuestions(const Int32 &question_id);
};

}  // namespace QuickExam::service
