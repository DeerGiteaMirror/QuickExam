//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <doo/Answer.h>
#include <doo/Migration.h>
#include <doo/OperateTime.h>
#include <doo/Question.h>
#include <doo/Tag.h>
#include <dto/Configuration.h>
#include <oatpp/core/macro/component.hpp>

#define CREATE_EXECUTOR                                                                            \
    OATPP_COMPONENT(oatpp::Object<dto::DataBase>, config);                                         \
    std::string connect_str = "postgresql://";                                                     \
    connect_str += config->username;                                                               \
    connect_str += ":";                                                                            \
    connect_str += config->password;                                                               \
    connect_str += "@";                                                                            \
    connect_str += config->host;                                                                   \
    connect_str += ":";                                                                            \
    connect_str += std::to_string(config->port);                                                   \
    connect_str += "/";                                                                            \
    connect_str += config->database;                                                               \
    auto connectionProvider =                                                                      \
        std::make_shared<oatpp::postgresql::ConnectionProvider>(connect_str);                      \
    auto connectionPool = oatpp::postgresql::ConnectionPool::createShared(                         \
        connectionProvider, 40 /* 最大连接数 */, std::chrono::seconds(5) /* connection TTL */);    \
    auto executor = std::make_shared<oatpp::postgresql::Executor>(connectionPool);

namespace QuickExam::component {

class DataBaseComponent {
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<doo::Migration>, migration)
    ([] {
        CREATE_EXECUTOR
        return std::make_shared<doo::Migration>(executor);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<doo::OperateTime>, operate_time_doo)
    ([] {
        CREATE_EXECUTOR
        return std::make_shared<doo::OperateTime>(executor);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<doo::Tag>, tag_doo)
    ([] {
        CREATE_EXECUTOR
        return std::make_shared<doo::Tag>(executor);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<doo::Question>, question_doo)
    ([] {
        CREATE_EXECUTOR
        return std::make_shared<doo::Question>(executor);
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<doo::Answer>, answer_doo)
    ([] {
        CREATE_EXECUTOR
        return std::make_shared<doo::Answer>(executor);
    }());
};

}  // namespace QuickExam::component