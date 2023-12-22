//
// QuickExam
// Created on 2023/12/22.
//

#include "BasicService.h"

namespace QuickExam::service {
Object<dto::basic::OperateTime> BasicService::updateOperateTime(const String &table_name,
                                                                const Int32  &question_id) {
    auto db_res = operate_time_doo->updateOperateTime(table_name, question_id);
    ASSERT_DB(db_res);
    auto operate_time = db_res->fetch<List<Object<dto::basic::OperateTime>>>();
    ASSERT_EXIST(operate_time->size() == 1, "Update operate time failed");
    return operate_time->front();
}

Object<dto::basic::OperateTime> BasicService::createOperateTime(const String &table_name,
                                                                const Int32  &question_id) {
    auto db_res = operate_time_doo->insertOperateTime(table_name, question_id);
    ASSERT_DB(db_res);
    auto data = dto::basic::OperateTime::createShared();
    FETCH_SINGLE(db_res, dto::basic::OperateTime, data);
    return data;
}

Object<dto::basic::OperateTime> BasicService::getOperateTime(const String &table_name,
                                                             const Int32  &question_id) {
    auto db_res = operate_time_doo->getOperateTime(table_name, question_id);
    ASSERT_DB(db_res);
    auto data = dto::basic::OperateTime::createShared();
    FETCH_SINGLE(db_res, dto::basic::OperateTime, data);
    return data;
}
}  // namespace QuickExam::service
