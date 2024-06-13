#include <iostream>
#include <fstream>
#include <json/json.h> 

Json::Value load_project_data();
int save_project_data(const Json::Value& ProjectInfo);
bool is_duplicate2(const Json::Value& ProjectInfo, const std::string& project_name);
int createProject(Json::Value& ProjectInfo, const std::string& project_name, const std::string& dead_line, const std::string& op_id, const std::string& member);
int deleteProject(Json::Value& ProjectInfo, const std::string& project_name, const std::string& op_id);