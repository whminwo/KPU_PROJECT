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

#include "account.h"

Json::Value UserList = load_data();

void showProfile() {
    QMessageBox::information(nullptr, "Profile", "Profile clicked!");
}

void showSettings() {
    QMessageBox::information(nullptr, "Settings", "Settings clicked!");
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

    parent->addWidget(loginWindow);
}

void initRegisterWindow(QStackedWidget *parent) {
    QWidget *registerWindow = new QWidget();
    registerWindow->setFixedSize(500, 400); 
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
        QString usernameText = username->text(); 
        QString emailText = email->text();
        QString idText = id->text();
        QString passwordText = password->text();
        std::string usernameStdString = usernameText.toStdString();
        std::string emailStdString = emailText.toStdString();
        std::string idStdString = idText.toStdString();
        std::string passwordStdString = passwordText.toStdString();

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

    // 메뉴 바에 계정 메뉴 추가
    menuBar->addMenu(accountMenu);

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
    QObject::connect(settingsAction, &QAction::triggered, &showSettings);

    // 로그아웃 액션을 람다 함수로 연결하여 QStackedWidget 인덱스를 변경
    QObject::connect(logoutAction, &QAction::triggered, [parent]() {
    parent->setCurrentIndex(0);
    QMessageBox::information(nullptr, "Logout", "You have been logged out.");
    });
}