//
// QuickExam
// Created on 2023/12/22.
//

#include "TagService.h"

namespace QuickExam::service {
Object<dto::Tag> TagService::getTagById(const Int32 &tag_id) {
    auto return_tag = Object<dto::Tag>::createShared();
    auto db_res     = tag_doo->getTag(tag_id);
    IF_DB_ERROR(return_tag)
    FETCH_SINGLE(db_res, dto::Tag, return_tag);
    return return_tag;
}

Object<dto::ResponseTagPage>
TagService::getTagsByPageConditions(const Object<TagCondition> &page_conditions) {
    auto page_data = dto::TagPage::createShared();
    GET_PAGE(tag_doo, page_conditions, page_data, dto::Tag);
    auto response  = dto::ResponseTagPage::createShared();
    response->data = page_data;
    RETURN_STATUS_SUCCESS(response);
}

Object<basic::Response<String>> TagService::deleteTag(const Int32 &tag_id) {
    auto db_res = tag_doo->deleteTag(tag_id);
    ASSERT_DB(db_res);
    auto response  = basic::Response<String>::createShared();
    response->data = "Delete tag success";
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseTag> TagService::updateTag(const Object<Tag> &tag) {
    auto db_res = tag_doo->updateTag(tag);
    ASSERT_DB(db_res);
    auto data = dto::Tag::createShared();
    FETCH_SINGLE(db_res, dto::Tag, data);
    auto response  = dto::ResponseTag::createShared();
    response->data = data;
    RETURN_STATUS_SUCCESS(response);
}

Object<dto::ResponseTag> TagService::createTag(const Object<Tag> &tag) {
    auto db_res = tag_doo->insertTag(tag);
    ASSERT_DB(db_res);
    auto data = dto::Tag::createShared();
    FETCH_SINGLE(db_res, dto::Tag, data);
    auto response  = dto::ResponseTag::createShared();
    response->data = data;
    RETURN_STATUS_SUCCESS(response);
}

List<Object<Tag>> TagService::getTagsByQuestion(const Int32 &question_id) {
    auto return_list = List<Object<dto::Tag>>::createShared();
    auto db_res      = question_doo->getQuestionTagsIdByQuestionId(question_id);
    IF_DB_ERROR(List<Object<dto::Tag>>::createShared());
    auto tags_id = db_res->fetch<List<Object<dto::db::QuestionTag>>>();
    for (auto &tag_id : *tags_id) {
        auto tag = getTagById(tag_id->tag_id);
        return_list->push_back(tag);
    }
    return return_list;
}
}  // namespace QuickExam::service
