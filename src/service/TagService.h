//
// QuickExam
// Created on 2023/12/22.
//

#pragma once

#include <doo/Tag.h>
#include <dto/Tag.h>
#include <dto/response/Tag.h>
#include <service/BasicService.h>

namespace QuickExam::service {
using namespace dto;
class TagService : public BasicService {
private:
    OATPP_COMPONENT(std::shared_ptr<doo::Tag>, tag_doo);

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
    Object<dto::Tag> getTagById(const Int32 &tag_id);
};

}  // namespace QuickExam::service
