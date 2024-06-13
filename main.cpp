#include <QApplication>
#include <QStackedWidget>
#include <ui.h>
#include <json/json.h> 

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QStackedWidget mainWidget;

    initWindow(&mainWidget);
    mainWidget.show();
    
    return app.exec();
}

