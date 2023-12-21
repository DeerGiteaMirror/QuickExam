//
// QuickExam
// Created on 2023/12/21.
//

#pragma once

#include <dto/basic/Enmus.h>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/codegen.hpp>
#include <oatpp/web/protocol/http/Http.hpp>

#define ASSERT_DB(DB_RES)                                                                          \
    if (!(DB_RES)->isSuccess()) {                                                                  \
        LOGE("Database Error", "%s", (DB_RES)->getErrorMessage()->c_str());                        \
        using namespace oatpp::web::protocol::http;                                                \
        throw oatpp::web::protocol::http::HttpError(Status::CODE_500,                              \
                                                    (DB_RES)->getErrorMessage()->c_str());         \
    }

#define ASSERT_HTTP(COND, MSG)                                                                     \
    if (!(COND)) {                                                                                 \
        LOGE("Http Error", "%s", MSG);                                                             \
        using namespace oatpp::web::protocol::http;                                                \
        throw oatpp::web::protocol::http::HttpError(Status::CODE_500, MSG);                        \
    }

#define ASSERT_EXIST(COND, MSG)                                                                    \
    if (!(COND)) {                                                                                 \
        LOGE("Not Found", "%s", MSG);                                                              \
        using namespace oatpp::web::protocol::http;                                                \
        throw oatpp::web::protocol::http::HttpError(Status::CODE_404, MSG);                        \
    }

#define RETURN_STATUS_SUCCESS(DTO)                                                                 \
    (DTO)->code    = 200;                                                                          \
    (DTO)->message = "success";                                                                    \
    return DTO;

#include OATPP_CODEGEN_BEGIN(DTO)

namespace QuickExam::dto::basic {

template <class T>
class Response : public oatpp::DTO {
    DTO_INIT(Response, DTO)

    DTO_FIELD(Int32, code) = 200;
    DTO_FIELD_INFO(code) {
        info->description = "Response code";
        info->required    = true;
    }

    DTO_FIELD(String, message) = "OK";
    DTO_FIELD_INFO(message) {
        info->description = "Response message";
        info->required    = true;
    }

    DTO_FIELD(T, data);
    DTO_FIELD_INFO(data) {
        info->description = "Response data";
    }
};

}  // namespace QuickExam::dto::basic

#include OATPP_CODEGEN_END(DTO)