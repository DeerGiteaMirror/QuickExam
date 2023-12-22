//
// QuickExam
// Created on 2023/12/22.
//

#pragma once

#define IF_DB_ERROR(RETURN)                                                                        \
    if (!db_res->isSuccess()) {                                                                    \
        LOGE("Database", "failed %s", db_res->getErrorMessage()->c_str());                         \
        return RETURN;                                                                             \
    }

#define FETCH_SINGLE(DB_RES, DTO_TYPE, RETURN)                                                     \
    {                                                                                              \
        using namespace oatpp;                                                                     \
        auto __ITEMS__ = (DB_RES)->fetch<List<Object<DTO_TYPE>>>();                                \
        if (__ITEMS__->size() == 1) {                                                              \
            (RETURN) = __ITEMS__->front();                                                         \
        } else {                                                                                   \
            (RETURN) = DTO_TYPE::createShared();                                                   \
        }                                                                                          \
    }
