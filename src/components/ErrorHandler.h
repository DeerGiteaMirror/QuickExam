
#pragma once

#include <dto/response/Response.h>
#include <oatpp/web/protocol/http/outgoing/ResponseFactory.hpp>
#include <oatpp/web/server/handler/ErrorHandler.hpp>
#include <utils/Logger.h>

namespace QuickExam {
class ErrorHandler : public oatpp::web::server::handler::ErrorHandler {
private:
    typedef oatpp::web::protocol::http::outgoing::Response        OutgoingResponse;
    typedef oatpp::web::protocol::http::Status                    Status;
    typedef oatpp::web::protocol::http::outgoing::ResponseFactory ResponseFactory;

private:
    std::shared_ptr<oatpp::data::mapping::ObjectMapper> m_objectMapper;

public:
    explicit ErrorHandler(const std::shared_ptr<oatpp::data::mapping::ObjectMapper> &objectMapper)
        : m_objectMapper(objectMapper) {
        LOGD("ErrorHandler", "ErrorHandler created");
    }

    std::shared_ptr<OutgoingResponse> handleError(const Status        &status,
                                                  const oatpp::String &message,
                                                  const Headers       &headers) override {
        auto error     = dto::Response::createShared();
        error->code    = status.code;
        error->message = message;
        error->data    = message;
        auto response  = ResponseFactory::createResponse(Status::CODE_200, error, m_objectMapper);
        for (const auto &pair : headers.getAll()) {
            response->putHeader(pair.first.toString(), pair.second.toString());
        }
        return response;
    }
};
}  // namespace QuickExam