//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

class Log : public oatpp::DTO {
    DTO_INIT(Log, DTO)

    DTO_FIELD(String, save_path) = "./logs";
    DTO_FIELD_INFO(save_path) {
        info->description = "Log save path";
        info->required    = true;
    }

    DTO_FIELD(UInt32, max_size_mb) = 2;
    DTO_FIELD_INFO(max_size_mb) {
        info->description = "Log file max size(MB)";
        info->required    = true;
    }

    DTO_FIELD(UInt32, preserve_days) = 7;
    DTO_FIELD_INFO(preserve_days) {
        info->description = "Log file preserve days";
        info->required    = true;
    }

    DTO_FIELD(Boolean, debug) = false;
    DTO_FIELD_INFO(debug) {
        info->description = "Is debug mode";
        info->required    = true;
    }
};

class DataBase : public oatpp::DTO {
    DTO_INIT(DataBase, DTO)

    DTO_FIELD(String, host);
    DTO_FIELD_INFO(host) {
        info->description = "Host";
    }

    DTO_FIELD(Int32, port);
    DTO_FIELD_INFO(port) {
        info->description = "Port";
    }

    DTO_FIELD(String, database);
    DTO_FIELD_INFO(database) {
        info->description = "Database";
    }

    DTO_FIELD(String, username);
    DTO_FIELD_INFO(username) {
        info->description = "Username";
    }

    DTO_FIELD(String, password);
    DTO_FIELD_INFO(password) {
        info->description = "Password";
    }
};

class Configuration : public oatpp::DTO {
    DTO_INIT(Configuration, DTO)

    DTO_FIELD(String, host);
    DTO_FIELD_INFO(host) {
        info->description = "Host";
    }

    DTO_FIELD(UInt16, port);
    DTO_FIELD_INFO(port) {
        info->description = "Port";
    }

    DTO_FIELD(Object<DataBase>, database);
    DTO_FIELD_INFO(database) {
        info->description = "Database configuration";
    }

    DTO_FIELD(String, resource);
    DTO_FIELD_INFO(resource) {
        info->description = "Resource path";
    }

    DTO_FIELD(Object<Log>, log) = Log::createShared();
    DTO_FIELD_INFO(log) {
        info->description = "Log configuration";
    }
};

}  // namespace QuickExam::dto
