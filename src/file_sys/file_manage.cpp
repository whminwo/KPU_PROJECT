#include <iostream>
#include <fstream>
#include <sstream>
#include <json/json.h> // jsoncpp 라이브러리
#include <string.h>
#include <time.h>
#include <ctime>

#include "file_manage.h"

std::string now_local_date(){
    char formatted_time[100];

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(formatted_time, "%d-%d-%d", 
            tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);

    std::string date_string(formatted_time);

    return date_string;
}

Json::Value load_project_data() {
    Json::Value ProjectInfo;
    std::ifstream file("data/project_data.json", std::ifstream::binary);
    if (file.is_open()) {
        file >> ProjectInfo;
        file.close();

    } else {
        ProjectInfo = Json::arrayValue;
    }
    return ProjectInfo;
}

int save_project_data(const Json::Value& ProjectInfo) {
    std::ofstream file("data/project_data.json", std::ofstream::binary);
    if (file.is_open()) {
        Json::StyledWriter writer;
        file << writer.write(ProjectInfo);
        file.close();
        return 1;

    } else {
        return -1;
    }
}

bool is_duplicate2(const Json::Value& ProjectInfo, const std::string& project_name) {
    for (const auto& user : ProjectInfo) {
        if (user["ProjectName"].asString() == project_name) {
            return true;
        }
    }
    return false;
}
/*
return 1 : 생성 완료
return 0 : projectName이 겹침
return -2 : 프로젝트 이름이 없음
return -3 : Operater가 없음
*/
int createProject(Json::Value& ProjectInfo, const std::string& project_name, const std::string& dead_line, const std::string& op_id, const std::string& member){
    if (is_duplicate2(ProjectInfo, project_name)) {
        return 0;
    }
    
    if(op_id == ""){
        return -2;
    }
    
    if(project_name == ""){
        return -3;
    }

    
    Json::Value project_data;
    project_data["ProjectName"] = project_name;
    project_data["DeadLine"] = dead_line;
    project_data["Operater"] = op_id;
    project_data["Member"] = member;
    project_data["RecentEditDate"] = now_local_date();

    ProjectInfo.append(project_data);
    save_project_data(ProjectInfo);
    return 1;
}

/*
return 1 : 성공적으로 삭제됨
return 0 : 권한이 없음
return -1 : 프로젝트를 찾지 못함
*/
int deleteProject(Json::Value& ProjectInfo, const std::string& project_name, const std::string& op_id) {
    for (Json::Value::ArrayIndex i = 0; i < ProjectInfo.size(); ++i) {
        if (ProjectInfo[i]["ProjectName"].asString() == project_name) {
            if (ProjectInfo[i]["Operater"].asString() == op_id) {
                Json::Value temp;
                ProjectInfo.removeIndex(i, &temp);
                
                save_project_data(ProjectInfo);
                return 1; 
            } else {   
                return 0;
            }
        }
    }
    return -1;
}

// //사용 에제
// Json::Value ProjectInfo = load_project_data();

// int main(int argc, char *argv[]) {
//     if (createProject(ProjectInfo, "test", "240613", "root", "root", "240610"));
//     else printf("프로젝트 이름이 겹침");
//     int res = deleteProject(ProjectInfo, "test", "root");

//     if (res == 1){
//         std::cerr << "complete" << std::endl;
//     }else if (res == 0){
//         std::cerr << "권한이 없습니다." << std::endl;
//     }else{
//         std::cerr << "프로젝트블 불러 올수 없습니다." << std::endl;
//     }

//     return 0;
// }