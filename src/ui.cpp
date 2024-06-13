#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QStackedWidget>
#include <QLabel>
#include <QCheckBox>
#include <QFrame>
#include <QMessageBox>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QStackedWidget>

#include <iostream>
#include <fstream>
#include <string.h>

#include "file_manage.h"
#include "account.h"


Json::Value UserList = load_data();
Json::Value ProjectInfo = load_project_data();
std::string LoginID = "";

std::string getTextBoxToStirng(QLineEdit *textBox){
    QString textBoxText = textBox->text();
    std::string textBoxStdString = textBoxText.toStdString();
    return textBoxStdString;
}

void showProfile() {
    QMessageBox::information(nullptr, "Profile", "Profile clicked!");
}

void initLoginWindow(QStackedWidget *parent) {
    QWidget *loginWindow = new QWidget();
    loginWindow->setFixedSize(500, 400); 
    QVBoxLayout *layout = new QVBoxLayout(loginWindow);
    layout->setAlignment(Qt::AlignCenter);

    QLabel *title = new QLabel("로그인", loginWindow);
    layout->addWidget(title);

    QLineEdit *id = new QLineEdit(loginWindow);
    id->setPlaceholderText("아이디");
    layout->addWidget(id);

    QLineEdit *password = new QLineEdit(loginWindow);
    password->setPlaceholderText("비밀번호");
    password->setEchoMode(QLineEdit::Password);
    layout->addWidget(password);

    QCheckBox *showPasswordCheckbox = new QCheckBox("비밀번호 보이기", loginWindow);
    QObject::connect(showPasswordCheckbox, &QCheckBox::stateChanged, [=](){
        if (showPasswordCheckbox -> isChecked()){
            password->setEchoMode(QLineEdit::Normal);
        }else{
            password->setEchoMode(QLineEdit::Password);
        }
    });
    layout->addWidget(showPasswordCheckbox);

    QPushButton *loginButton = new QPushButton("로그인", loginWindow);
    layout->addWidget(loginButton);

    QObject::connect(loginButton, &QPushButton::clicked, [=]() {
        QString idText = id->text();
        QString passwordText = password->text();
        std::string idStdString = idText.toStdString();
        std::string passwordStdString = passwordText.toStdString();
        qDebug() << "ID:" << idText << "Password:" << passwordText;

        if (login(UserList, idStdString, passwordStdString) == 1) {
            QMessageBox::information(nullptr, "Login!", "Login successful!");
            LoginID = idStdString;
            parent->setFixedSize(1200, 700);
            parent->setCurrentIndex(2);

        }else{
            QMessageBox::warning(nullptr, "Login failed", "Login failed. Invalid ID or password");
        }
        
    });

    QPushButton *toRegisterButton = new QPushButton("회원가입하기", loginWindow);
    layout->addWidget(toRegisterButton);
    QObject::connect(toRegisterButton, &QPushButton::clicked, [=]() {
        parent->setCurrentIndex(1); // 회원가입 창으로 전환
    });
    parent->setStyleSheet(R"(
        QLineEdit {
            border: 1px solid gray;
            border-radius: 10px;
            padding: 5px;
            margin-bottom: 5px;
        }
        QPushButton {
            border: 1px solid #8f8f91;
            border-radius: 6px;
            background-color: #f3f3f3;
            min-width: 80px;
            margin-top: 5px;
        }
        QPushButton:pressed {
            background-color: #a3a3a3;
        }
        QLabel {
            qproperty-alignment: 'AlignCenter';
        }
    )");;

    parent->addWidget(loginWindow);
}

void initRegisterWindow(QStackedWidget *parent) {
    QWidget *registerWindow = new QWidget(); 
    QVBoxLayout *layout = new QVBoxLayout(registerWindow);
    layout->setAlignment(Qt::AlignCenter);

    QLabel *title = new QLabel("회원가입", registerWindow);
    layout->addWidget(title);

    QLineEdit *username = new QLineEdit(registerWindow);
    username->setPlaceholderText("사용자 이름");
    layout->addWidget(username);

    QLineEdit *email = new QLineEdit(registerWindow);
    email->setPlaceholderText("이메일");
    layout->addWidget(email);

    QLineEdit *id = new QLineEdit(registerWindow);
    id->setPlaceholderText("아이디");
    layout->addWidget(id);

    QLineEdit *password = new QLineEdit(registerWindow);
    password->setPlaceholderText("비밀번호");
    password->setEchoMode(QLineEdit::Password);
    layout->addWidget(password);

    QLineEdit *confirmPassword = new QLineEdit(registerWindow);
    confirmPassword->setPlaceholderText("비밀번호 확인");
    confirmPassword->setEchoMode(QLineEdit::Password);
    layout->addWidget(confirmPassword);

    QPushButton *registerButton = new QPushButton("회원가입", registerWindow);
    layout->addWidget(registerButton);
    QObject::connect(registerButton, &QPushButton::clicked, [=]() {
        std::string usernameStdString = getTextBoxToStirng(username);
        std::string emailStdString = getTextBoxToStirng(email);
        std::string idStdString = getTextBoxToStirng(id);
        std::string passwordStdString = getTextBoxToStirng(password);

        if(create_account(UserList, usernameStdString, emailStdString, idStdString, passwordStdString)){
            parent->setCurrentIndex(0);
        }
        
    });

    QPushButton *toLoginButton = new QPushButton("로그인 화면으로", registerWindow);
    layout->addWidget(toLoginButton);
    QObject::connect(toLoginButton, &QPushButton::clicked, [=]() {
        parent->setCurrentIndex(0); // 로그인 창으로 전환
    });

    parent->addWidget(registerWindow);
}

void initFirstPageWindow(QStackedWidget *parent) {
    QWidget *firstPageWindow = new QWidget();

    QFrame* mainFrame = new QFrame(firstPageWindow);
    mainFrame->setFrameShape(QFrame::Box);
    mainFrame->setFrameShadow(QFrame::Raised);

    QVBoxLayout* frameLayout = new QVBoxLayout(mainFrame);

    // 메뉴 바 생성
    QMenuBar* menuBar = new QMenuBar(mainFrame);

    // 계정 메뉴 생성
    QMenu* accountMenu = new QMenu("Account");
    
    // 계정 메뉴에 항목 추가
    QAction* profileAction = new QAction("Profile");
    QAction* settingsAction = new QAction("Settings");
    QAction* logoutAction = new QAction("Logout");

    accountMenu->addAction(profileAction);
    accountMenu->addAction(settingsAction);
    accountMenu->addAction(logoutAction);
    
    QMenu* FileMenu = new QMenu("File");

    QAction* newFileAction = new QAction("New File");
    QAction* newFolderAction = new QAction("New Folder");
    QAction* openFileAction = new QAction("Open File");
    QAction* openFolderAction = new QAction("Open Folder");
    QAction* openRecentAction = new QAction("Open Recent");
    QAction* saveAction = new QAction("Save");

    FileMenu->addAction(newFileAction);
    FileMenu->addAction(newFolderAction);
    FileMenu->addAction(openFileAction);
    FileMenu->addAction(openFolderAction);
    FileMenu->addAction(openRecentAction);
    FileMenu->addAction(saveAction);

    QMenu* ProjectMenu = new QMenu("Project");

    QAction* createProjectAction = new QAction("Create Project");
    QAction* openProjectAction = new QAction("Open Project");

    ProjectMenu->addAction(createProjectAction);
    ProjectMenu->addAction(openProjectAction);

    // 메뉴 바에 계정 메뉴 추가
    menuBar->addMenu(accountMenu);
    menuBar->addMenu(FileMenu);
    menuBar->addMenu(ProjectMenu);
    
    // 메뉴 바의 계정 메뉴를 오른쪽으로 정렬
    QWidget* rightSpacer = new QWidget();
    rightSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    menuBar->setCornerWidget(rightSpacer, Qt::TopRightCorner);
    menuBar->addAction(accountMenu->menuAction());

    frameLayout->setMenuBar(menuBar);

    // 프레임 내부의 다른 콘텐츠 (예: 라벨)
    QLabel* label = new QLabel("This is inside a frame", mainFrame);
    frameLayout->addWidget(label);

    // 메인 레이아웃 설정
    QVBoxLayout* mainLayout = new QVBoxLayout(firstPageWindow);
    mainLayout->addWidget(mainFrame);


    parent->addWidget(firstPageWindow);

    // QAction 시그널을 슬롯에 연결
    QObject::connect(profileAction, &QAction::triggered, &showProfile);
    QObject::connect(settingsAction, &QAction::triggered, [parent]() {
        parent->setCurrentIndex(3);
    });

    // 로그아웃 액션을 람다 함수로 연결하여 QStackedWidget 인덱스를 변경
    QObject::connect(logoutAction, &QAction::triggered, [parent]() {
        LoginID = "";
        parent->setFixedSize(500, 400); 
        parent->setCurrentIndex(0);
        QMessageBox::information(nullptr, "Logout", "You have been logged out.");
    });

    QObject::connect(createProjectAction, &QAction::triggered, [parent]() {
        parent->setFixedSize(500, 400); 
        parent->setCurrentIndex(4);
    });
}

void initSettingWindow(QStackedWidget *parent) {
    QWidget *settingWindow = new QWidget();
    parent->addWidget(settingWindow);
}

void initcreateProjectwindow(QStackedWidget *parent){
    QWidget *createProjectwindow = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(createProjectwindow);
    layout->setAlignment(Qt::AlignCenter);

    QLabel *create_project = new QLabel("프로젝트 생성", createProjectwindow);
    layout->addWidget(create_project);

    QLineEdit *project_name = new QLineEdit(createProjectwindow);
    project_name->setPlaceholderText("프로젝트 이름");
    layout->addWidget(project_name);

    QLineEdit *daed_line = new QLineEdit(createProjectwindow);
    daed_line->setPlaceholderText("기한 ex)yyyy-mm-dd");
    layout->addWidget(daed_line);

    QLineEdit *member_id = new QLineEdit(createProjectwindow);
    member_id->setPlaceholderText("멤버 아이디");
    layout->addWidget(member_id);

    QPushButton *createButton = new QPushButton("프로젝트 생성", createProjectwindow);
    layout->addWidget(createButton);

    QObject::connect(createButton, &QPushButton::clicked, [=]() {
        std::string projectnameStdString = getTextBoxToStirng(project_name);
        std::string daedLineStdString = getTextBoxToStirng(daed_line);
        std::string memberIdStdString = getTextBoxToStirng(member_id);
 
        if (createProject(ProjectInfo, projectnameStdString, daedLineStdString, LoginID, memberIdStdString)){
            parent->setFixedSize(1200, 700);
            parent->setCurrentIndex(2);
        }
    });

    parent->addWidget(createProjectwindow);
}

void initWindow(QStackedWidget *parent){
    initLoginWindow(parent);
    initRegisterWindow(parent);
    initFirstPageWindow(parent);
    initSettingWindow(parent);
    initcreateProjectwindow(parent);
}