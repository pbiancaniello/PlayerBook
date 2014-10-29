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
    qmlRegisterType<Choice>("Custom", 1, 0, "Choice");
    qmlRegisterType<Monster>("Custom", 1, 0, "Monster");
    qmlRegisterType<Spell>("Custom", 1, 0, "Spell");
    qmlRegisterType<ContentList>("Custom", 1, 0, "ContentList");

    Database database;
    Character character;
    database.buildDatabase();
    character.setDatabase(&database);
    Feature* feature = new Feature();
    feature->setName("I am a Test Feature");
    feature->addToDesc("This is a test feature");
    feature->addToDesc("<b>Because</b> I like to <i>test things</i>.");
    Choice choice1;
    choice1.setDesc("You may select one cantrip from the wizard spell list");
    choice1.add("Mage Hand","addspell|mage hand");
    choice1.add("Prestidigitation","addspell|prestidigitation");
    feature->addToChoices(&choice1);
    character.addFeature(feature);

    QApplication app(argc, argv);
    //QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("database", &database);
    engine.rootContext()->setContextProperty("character", &character);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
