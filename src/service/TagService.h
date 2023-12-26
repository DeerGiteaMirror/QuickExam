//
// QuickExam
// Created on 2023/12/22.
//

#pragma once

#include <doo/Question.h>
#include <doo/Tag.h>
#include <dto/Tag.h>
#include <dto/response/Tag.h>
#include <service/BasicService.h>
#include <service/TagService.h>

namespace QuickExam::service {
using namespace dto;
class TagService : public BasicService {
private:
    OATPP_COMPONENT(std::shared_ptr<doo::Tag>, tag_doo);
    OATPP_COMPONENT(std::shared_ptr<doo::Question>, question_doo);

public:
    TagService()  = default;
    ~TagService() = default;

public:
    Object<dto::ResponseTag> createTag(const Object<dto::Tag> &tag);

    Object<dto::ResponseTag> updateTag(const Object<dto::Tag> &tag);

    Object<dto::basic::Response<String>> deleteTag(const Int32 &tag_id);

    Object<dto::ResponseTagPage>
    getTagsByPageConditions(const Object<dto::TagCondition> &page_conditions);

public:  // ---> Service methods
    /**
     * @brief Get the tag by id
     * @param tag_id The tag id
     * @return Object<dto::Tag> The tag object
     */
    Object<dto::Tag> getTagById(const Int32 &tag_id);

    /**
     * @brief Get the Question Tags object
     * @param question_id The question id
     * @return List<Object<dto::Tag>> The question tags list
     */
    List<Object<dto::Tag>> getTagsByQuestion(const Int32 &question_id);
};

}  // namespace QuickExam::service
