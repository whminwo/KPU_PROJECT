#include <iostream>
#include <fstream>
#include <json/json.h> // jsoncpp 라이브러리

#include "account.h"

Json::Value load_data() {
    Json::Value UserList;
    std::ifstream file("data/user_data.json", std::ifstream::binary);
    if (file.is_open()) {
        file >> UserList;
        file.close();
    } else {
        UserList = Json::arrayValue;
    }
    return UserList;
}

void save_data(const Json::Value& UserList) {
    std::ofstream file("data/user_data.json", std::ofstream::binary);
    if (file.is_open()) {
        Json::StyledWriter writer;
        file << writer.write(UserList);
        file.close();

    } else {
        std::cerr << "Cannot open file for writing" << std::endl;
    }
}


bool is_duplicate(const Json::Value& UserList, const std::string& email, const std::string& id) {
    for (const auto& user : UserList) {
        if (user["Email"].asString() == email || user["ID"].asString() == id) {
            return true;
        }
    }
    return false;
}


int create_account(Json::Value& UserList, const std::string& name, const std::string& email, const std::string& id, const std::string& pw, bool is_organizations) {
    if (is_duplicate(UserList, email, id)) {
        std::cerr << "Email or ID already exists. Cannot create account." << std::endl;
        return 0; //동일한 이름의 ID나 이메일이 있음
    }

    if(name == "" | email == "" | id == "" | pw == ""){
        std::cerr << "Email or ID already exists. Cannot create account." << std::endl;
        return -1; // 입력이 이상함
    }

    Json::Value user_data;
    user_data["Name"] = name;
    user_data["Email"] = email;
    user_data["ID"] = id;
    user_data["PW"] = pw;
    user_data["IsOrganizations"] = is_organizations;

    UserList.append(user_data);
    save_data(UserList);
    return 1; // 생성 완료
}

int login(const Json::Value& UserList, const std::string& id, const std::string& pw) {
    for (const auto& user : UserList) {
        if (user["ID"].asString() == id && user["PW"].asString() == pw) {
            return 1; // 계정 일치
        }
    }
    return 0; // 계정 불일치
}