#include <QApplication>
#include <QStackedWidget>
#include <ui.h>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QStackedWidget mainWidget;

    initLoginWindow(&mainWidget);
    initRegisterWindow(&mainWidget);
    initFirstPageWindow(&mainWidget);
    
    mainWidget.show();
    return app.exec();
}