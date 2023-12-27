//
// QuickExam
// Created on 2023/12/20.
//

#pragma once

#include <dto/Configuration.h>
#include <oatpp-postgresql/orm.hpp>
#include <utils/Logger.h>

#include OATPP_CODEGEN_BEGIN(DbClient)

namespace QuickExam::doo {

class Migration : public oatpp::orm::DbClient {
public:
    explicit Migration(const std::shared_ptr<oatpp::orm::Executor> &executor)
        : oatpp::orm::DbClient(executor) {
        OATPP_COMPONENT(oatpp::Object<dto::Configuration>, config);
        std::string migration_path = config->resource + "/database-migrations";
        LOGI("Database Migration", "Migration Path=%s", migration_path.c_str());

        oatpp::orm::SchemaMigration migration(executor);

        migration.addFile(1, migration_path + "/001_init.sql");
        // TODO - Add more migrations here.
        migration.migrate();

        auto version = executor->getSchemaVersion();
        LOGI("Database Migration", "Version = %ld", version);
    }
};

}  // namespace QuickExam::doo

#include OATPP_CODEGEN_END(DbClient)