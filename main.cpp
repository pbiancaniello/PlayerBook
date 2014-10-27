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
    qmlRegisterType<Database>("Custom", 1, 0, "Database");
    qmlRegisterType<Feature>("Custom", 1, 0, "Feature");
    qmlRegisterType<Monster>("Custom", 1, 0, "Monster");
    qmlRegisterType<Spell>("Custom", 1, 0, "Spell");
    qmlRegisterType<ContentList>("Custom", 1, 0, "ContentList");

    Database database;
    Character character;
    database.buildDatabase();
    character.setDatabase(&database);
    //Feature* feature; //= new Feature();
    //character.addFeature(feature);
    //feature->addToChoiceMap("test","testeffect");
    //feature->addToChoiceMap("another choice","testeffect2");

    QApplication app(argc, argv);
    //QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("database", &database);
    engine.rootContext()->setContextProperty("character", &character);
    //engine.rootContext()->setContextProperty("feature", &feature);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
