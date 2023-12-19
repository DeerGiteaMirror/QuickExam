//
// QuickExam
// Created on 2023/12/19.
//

#pragma once

#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto {

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

    DTO_FIELD(String, swagger_ui);
    DTO_FIELD_INFO(swagger_ui) {
        info->description = "Swagger UI resources path";
    }
};

}  // namespace QuickExam::dto
