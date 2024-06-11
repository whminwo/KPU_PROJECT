cmake_minimum_required(VERSION 3.10)

project(KPU_PROJECT VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Qt5와 jsoncpp 패키지 찾기
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(jsoncpp REQUIRED)

# 소스 파일 설정
set(SOURCES main.cpp)

set(ACCOUNT_SOURCES src/account/account.cpp)
set(ACCOUNT_HEADERS src/account/account.h)

set(UI_SOURCES src/ui.cpp)
set(UI_HEADERS src/ui.h)

set(MANAGER_SOURCES src/file_sys/file_manage.cpp)
set(MANAGER_HEADERS src/file_sys/file_manage.h)

set(TARGET automa_project_operater)
set(ACCOUNT_LIB account)
set(MANAGER_LIB manger)
set(UI_LIB ui)

# include 디렉토리 추가
include_directories(src/account)
include_directories(src/file_sys)
include_directories(src)

# account 라이브러리 생성
add_library(${ACCOUNT_LIB} ${ACCOUNT_SOURCES} ${ACCOUNT_HEADERS})
target_link_libraries(${ACCOUNT_LIB} jsoncpp_lib)

# manger
add_library(${MANAGER_LIB} ${MANAGER_SOURCES} ${MANAGER_HEADERS})
target_link_libraries(${MANAGER_LIB} jsoncpp_lib)

# ui 라이브러리 생성
add_library(${UI_LIB} ${UI_SOURCES} ${UI_HEADERS})
target_link_libraries(${UI_LIB} ${ACCOUNT_LIB} Qt5::Widgets)

# main 실행 파일 생성 및 링크
add_executable(${TARGET} ${SOURCES})
target_link_libraries(${TARGET} Qt5::Widgets ${UI_LIB} ${MANAGER_LIB})

