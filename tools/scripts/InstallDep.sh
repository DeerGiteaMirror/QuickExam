#!/bin/bash

# prepare

ROOT_PATH=$(pwd)/../..
INSTALL_PATH="$ROOT_PATH/third_party"
CACHE_PATH="$INSTALL_PATH/.cache"
LOG_FILE="$CACHE_PATH/build.log"
rm -rf "$CACHE_PATH"
mkdir -p "$CACHE_PATH"

CURRENT_STEP=1
TOTAL_STEPS=19

execute() {
    local info_msg="$1"
    local error_msg="$2"
    shift 2

    if [ ! "$error_msg" ]; then
        error_msg="error"
    fi

    if [ "$info_msg" ]; then
        printf "(%d/%d): %s\n" "$CURRENT_STEP" "$TOTAL_STEPS" "$info_msg"
        CURRENT_STEP=$((CURRENT_STEP + 1))
    fi
    "$@" >>"$LOG_FILE" 2>&1 || error_exit "$error_msg, check $LOG_FILE for details"
}


# install oatpp
cd "$CACHE_PATH" || exit 1
execute "cloning oatpp" "failed to install oatpp" \
    git clone https://ssl.lunadeer.cn:14446/mirror/oatpp.git && \
    cd oatpp
execute "checkout oatpp 1.3.0" "failed to checkout oatpp 1.3.0" \
    git checkout 1.3.0 && \
    mkdir build && \
    cd build
execute "cmake oatpp" "failed to cmake oatpp" \
    cmake -DCMAKE_INSTALL_PREFIX="$INSTALL_PATH" ..
execute "compiling oatpp" "failed to make oatpp" \
    make -j$(nproc)
execute "installing oatpp" "failed to make install oatpp" \
    make install

# install oatpp-swagger
cd "$CACHE_PATH" || exit 1
execute "cloning oatpp-swagger" "failed to install oatpp-swagger" \
    git clone https://ssl.lunadeer.cn:14446/mirror/oatpp-swagger.git && \
    cd oatpp-swagger
execute "checkout oatpp-swagger 1.3.0" "failed to checkout oatpp-swagger 1.3.0" \
    git checkout 1.3.0 && \
    mkdir build && \
    cd build
execute "cmake oatpp-swagger" "failed to cmake oatpp-swagger" \
    cmake -DCMAKE_INSTALL_PREFIX="$INSTALL_PATH"  ..
execute "compiling oatpp-swagger" "failed to make oatpp-swagger" \
    make -j$(nproc)
execute "installing oatpp-swagger" "failed to make install oatpp-swagger" \
    make install

#  install PostgreSQL dev
cd "$CACHE_PATH" || exit 1
execute "cloning PostgreSQL dev" "failed to install PostgreSQL dev" \
    git clone https://ssl.lunadeer.cn:14446/mirror/postgresql.git && \
    cd postgresql
execute "checkout PostgreSQL REL_15_3" "failed to checkout PostgreSQL REL_15_3" \
    git checkout REL_15_3
execute "configure PostgreSQL" "failed to configure PostgreSQL" \
    ./configure --prefix="$INSTALL_PATH" --without-readline
execute "compiling PostgreSQL" "failed to make PostgreSQL" \
    make -j$(nproc)
execute "installing PostgreSQL" "failed to make install PostgreSQL" \
    make install

# install oatpp-postgresql
cd "$CACHE_PATH" || exit 1
execute "cloning oatpp-postgresql" "failed to install oatpp-postgresql" \
    git clone https://ssl.lunadeer.cn:14446/mirror/oatpp-postgresql.git && \
    cd oatpp-postgresql && \
    mkdir build && \
    cd build
execute "cmake oatpp-postgresql" "failed to cmake oatpp-postgresql" \
    cmake -DCMAKE_INSTALL_PREFIX="$INSTALL_PATH" ..
execute "compiling oatpp-postgresql" "failed to make oatpp-postgresql" \
    make -j$(nproc)
execute "installing oatpp-postgresql" "failed to make install oatpp-postgresql" \
    make install
