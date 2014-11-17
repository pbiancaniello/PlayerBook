#include "character.h"
#include "database.h"
#include "contentlist.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QUrl>
#include <QQmlContext>
#include <QQuickView>
#include <QDebug>
#include <QTQml>

//#include <QGuiApplication>

int main(int argc, char *argv[])
{
    qmlRegisterType<Character>("Custom", 1, 0, "Character");
    qmlRegisterType<Database>("Custom", 1, 0, "Database");
    qmlRegisterType<Feature>("Custom", 1, 0, "Feature");
    qmlRegisterType<Choice>("Custom", 1, 0, "Choice");
    qmlRegisterType<Monster>("Custom", 1, 0, "Monster");
    qmlRegisterType<Race>("Custom", 1, 0, "Race");
    qmlRegisterType<Spell>("Custom", 1, 0, "Spell");
    qmlRegisterType<ContentList>("Custom", 1, 0, "ContentList");

    Database database;
    Character base;
    database.buildDatabase();
    base.setDatabase(&database);

    QApplication app(argc, argv);
    //QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("database", &database);
    engine.rootContext()->setContextProperty("base", &base);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
