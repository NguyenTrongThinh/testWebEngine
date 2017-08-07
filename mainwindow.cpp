#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QtWebEngine::initialize();
    view = new QWebEngineView(parent);
    view->setUrl(QUrl("qrc:/maps/google_maps.html"));
    ui->verticalLayout->addWidget(view);
    m_pNetworkAccessManager = new QNetworkAccessManager(this);
    connect(m_pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getCoordinates(const QString &address)
{
    QString url = QString("http://maps.google.com/maps/api/geocode/json?address=%1&sensor=false&language=en").arg(address);
    m_pNetworkAccessManager->get(QNetworkRequest(QUrl(url)));
}

void MainWindow::showCoordinates(double east, double north, bool saveMarker)
{
    qDebug() << "Form, showCoordinates" << east << north;

    QString str =
            QString("var newLoc = new google.maps.LatLng(%1, %2); ").arg(north).arg(east) +
            QString("map.setCenter(newLoc);") +
            QString("map.setZoom(%1);").arg(8);

     qDebug() << str;
     view->page()->runJavaScript(str);
     if (saveMarker)
         SetMarker(east, north, "Ho Chi Minh City");
}

void MainWindow::SetMarker(double east, double north, QString caption)
{
    QString str =
            QString("var image = 'qrc:/resource/bluedot.png';") +
            QString("var marker = new google.maps.Marker({") +
            QString("position: new google.maps.LatLng(%1, %2),").arg(north).arg(east) +
            QString("map: map,") +
            QString("title: %1").arg("\""+caption+"\",") +
            QString("icon: image,") +
            QString("});") +
            QString("markers.push(marker);");

    qDebug() << str;
    view->page()->runJavaScript(str);

}

void MainWindow::Route(double oeast, double onorth, double deast, double dnorth, QString trvalMode)
{
//    QString str =
//        QString("map.drawRoute({") +
//        QString("origin: [%1, %2],").arg(oeast).arg(onorth) +
//        QString("destination: [%1, %2],").arg(deast).arg(dnorth) +
//        QString("travelMode: '%1',").arg(trvalMode) +
//        QString("strokeColor: '#131540',") +
//        QString("strokeOpacity: 0.6,") +
//        QString("strokeWeight: 6") +
//        QString("});");
//        qDebug() << str;
    QString str =
               QString("var orig = new google.maps.LatLng(37.388769, -122.158954);") +
               QString("var dest = new google.maps.LatLng(37.391979, -122.167891);") +
               QString("var routeOptions = {") +
                   QString("origin: orig,") +
                   QString("destination: dest,") +
                   QString("travelMode: google.maps.TravelMode.DRIVING") +
               QString("};") +
               QString("service = new google.maps.DirectionsService();") +
               QString("service.route(routeOptions, handleDirections);");
        qDebug() << str;
        view->page()->runJavaScript(str);
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    QByteArray json = reply->readAll();
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    QJsonObject obj = doc.object();

    QJsonValue results = obj.take("results");
    if (results != QJsonValue::Undefined)
    {
        if (results.isArray())
        {
            QJsonArray array = results.toArray();
            QJsonObject formatted_address = array.at(0).toObject();
            QJsonValue geometry = formatted_address.take("geometry");
            if (geometry != QJsonValue::Undefined)
            {
                QJsonValue location = geometry.toObject().take("location");
                if (location != QJsonValue::Undefined)
                {
                    double lat = location.toObject().value("lat").toDouble();
                    double lng = location.toObject().value("lng").toDouble();
                    qDebug() << "lat: " << location.toObject().value("lat").toDouble();
                    qDebug() << "lng: " << location.toObject().value("lng").toDouble();
                    //Set Cordinate
                    showCoordinates(lng, lat, true);
                }
            }

            qDebug() << "Address: " << formatted_address.value("formatted_address").toString();

        }
    }
}

void MainWindow::on_btnHome_clicked()
{
    getCoordinates("Ho Chi Minh City, Viet Nam");
    //Route(-12.044012922866312, -77.02470665341184, -12.090814532191756, -77.02271108990476, "driving");
}
