#include <iostream>
#include <fstream>
#include <json/json.h> 

/**
 * @brief Function to get the current device date.
 *
 * @return return current device date.
 * 
 */ 
std::string now_local_date();

/**
 * @brief Function to read Project data from a JSON file.
 * 
 * @return Return Project data in "data/project_data.json" as json value.
 */
Json::Value load_project_data();

/**
 * @brief Function to save Project data in a JSON file.
 * 
 * This function uses the global variable ProjectInfo.
 */
int save_project_data(const Json::Value& ProjectInfo);

/**
 * @brief Find duplicate Project Title Name in ProjectInfo data.
 * 
 * This function returns True False by comparing whether the {Project Title Name} matches the information entered in the ProjectInfo.
 * This function uses the global variable ProjectInfo.
 * 
 * @param project_name Project Title Name
 * 
 * @return Whether {Project Title Name} duplicates were found in ProjectInfo.
 */ 
bool is_duplicate2(const Json::Value& ProjectInfo, const std::string& project_name);

/**
 * @brief Function to create a project.
 * 
 * This function uses the global variable ProjectInfo.
 * 
 * @param project_name      Project Title Name
 * @param dead_line         Project Dead Line
 * @param op_id             Project Operater ID
 * @param member            Project Using Users
 * 
 * @return Returns 1 if the Project is successfully created. Returns 0 if the same {Project Title Name} exists.
 * 
 */
int createProject(Json::Value& ProjectInfo, const std::string& project_name, const std::string& dead_line, const std::string& op_id, const std::string& member);

/**
 * @brief Function to delete a project.
 * 
 * This function uses the global variable ProjectInfo.
 * 
 * @param project_name      Project Title Name
 * @param op_id             Project Operater ID
 * 
 * @return Returns 1 if the Project is successfully delete.
 * 
 */
int deleteProject(Json::Value& ProjectInfo, const std::string& project_name, const std::string& op_id);

/**
 * @brief projects managed by the operator as Json Value
 * 
 * This function uses the global variable ProjectInfo.
 * 
 * @param project_name      Project Title Name
 * @param Operater          Project Operater ID
 * 
 * @return Returns all projects managed by the operator as Json Value
 * 
 */
Json::Value findProjectArray(const Json::Value& ProjectInfo, const std::string& Operater);