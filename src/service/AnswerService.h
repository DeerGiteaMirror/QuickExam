//
// QuickExam
// Created on 2023/12/22.
//

#pragma once

#include <doo/Answer.h>
#include <dto/Answer.h>
#include <service/BasicService.h>

namespace QuickExam::service {
using namespace oatpp;
class AnswerService : public BasicService {
private:
    OATPP_COMPONENT(std::shared_ptr<doo::Answer>, answer_doo);

public:
    AnswerService()  = default;
    ~AnswerService() = default;

public:  // ---> Service methods
    List<Object<dto::AnswerContent>> getAnswerContents(const Int32 &answer_id);

    List<Object<dto::Answer>> getAnswersByQuestionId(const Int32 &question_id);
};

}  // namespace QuickExam::service
