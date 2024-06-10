#include <json/json.h> 

Json::Value load_data();
void save_data(const Json::Value& UserList);
bool is_duplicate(const Json::Value& UserList, const std::string& email, const std::string& id);
int create_account(Json::Value& UserList, const std::string& name, const std::string& email, const std::string& id, const std::string& pw, bool is_organizations = false);
int login(const Json::Value& UserList, const std::string& id, const std::string& pw);