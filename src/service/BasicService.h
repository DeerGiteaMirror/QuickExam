//
// QuickExam
// Created on 2023/12/22.
//

#pragma once

#include <doo/OperateTime.h>
#include <dto/basic/OperateTime.h>
#include <dto/basic/Response.h>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <utils/Database.h>
#include <utils/Logger.h>

namespace QuickExam::service {
using namespace oatpp;
class BasicService {
private:
    OATPP_COMPONENT(std::shared_ptr<doo::OperateTime>, operate_time_doo);

protected:  // ---> Service methods
    /**
     * @brief Update the question operate time
     * @param belong_id The question id
     * @return Object<dto::QuestionOperateTime> The question newest operate time object
     */
    Object<dto::basic::OperateTime> updateOperateTime(const String &table_name,
                                                      const Int32  &belong_id);

    /**
     * @brief Create the question operate time
     * @param belong_id The question id
     * @return Object<dto::QuestionOperateTime> The question newest operate time object
     */
    Object<dto::basic::OperateTime> createOperateTime(const String &table_name,
                                                      const Int32  &belong_id);

    /**
     * @brief Get the question operate time
     * @param belong_id The question id
     * @return Object<dto::QuestionOperateTime> The question newest operate time object
     */
    Object<dto::basic::OperateTime> getOperateTime(const String &table_name,
                                                   const Int32  &belong_id);
};

}  // namespace QuickExam::service
