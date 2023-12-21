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
#include <dto/response/Question.h>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <utils/Logger.h>

namespace QuickExam::service {
using namespace oatpp;
class QuestionService {
private:
    OATPP_COMPONENT(std::shared_ptr<doo::Question>, question_doo);
    OATPP_COMPONENT(std::shared_ptr<doo::Tag>, tag_doo);
    OATPP_COMPONENT(std::shared_ptr<doo::Answer>, answer_doo);
    OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, m_objectMapper);

public:
    QuestionService()  = default;
    ~QuestionService() = default;

    Object<dto::ResponseQuestionPage>
    getQuestionsByPageConditions(const Object<dto::QuestionCondition> &page_conditions);

    Object<dto::ResponseQuestion> getQuestionById(const Int32 &id);

private:
    /**
     * @brief Get the Question Details object
     * @param question The question object
     * @return Object<dto::Question> The question object
     */
    Object<dto::Question> getQuestionDetails(const Object<dto::Question> &question);
};

}  // namespace QuickExam::service
