#include <json/json.h> 

/**
 * @brief Function to read User data from a JSON file.
 * 
 * @return Return User data in "data/user_data.json" as json value.
 */
Json::Value load_data();

/**
 * @brief Function to save User data in a JSON file.
 * 
 * This function uses the global variable UserList.
 */
void save_data(const Json::Value& UserList);

/**
 * @brief Find duplicate email or ID in User Info data.
 * 
 * This function returns True False by comparing whether the email or id matches the information entered in the UserList.
 * This function uses the global variable UserList.
 * 
 * @param email    User email
 * @param id       User ID
 * @return Whether email or ID duplicates were found in UserList.
 * 
 */ 
bool is_duplicate(const Json::Value& UserList, const std::string& email, const std::string& id);

/**
 * @brief Function to create a user account.
 * 
 * This function uses the global variable UserList.
 * 
 * @param name      User name
 * @param email     User email
 * @param id        User ID
 * @param pw        User Password
 * @param is_organizations Whether or not the organization is.
 * 
 * @return Returns 1 if the user account is successfully created. Returns 0 if the same email or ID exists.
 */
int create_account(Json::Value& UserList, const std::string& name, const std::string& email, const std::string& id, const std::string& pw, bool is_organizations = false);

/**
 * @brief Check if the ID and password entered in UserList match.
 * 
 * This function compares whether the ID and password match the information entered in the UserList and returns 1 and 0.
 * This function uses the global variable UserList.
 * 
 * @param id        User ID
 * @param pw        User Password
 * @return If the password matches the ID matched in the UserList, 1 is returned. Otherwise, 0 is returned.
 */ 
int login(const Json::Value& UserList, const std::string& id, const std::string& pw);