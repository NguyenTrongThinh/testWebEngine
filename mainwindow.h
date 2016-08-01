#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QtWebEngine>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QWebEngineView *view;
    QNetworkAccessManager *m_pNetworkAccessManager;
private:
    void getCoordinates(const QString& address);
    void showCoordinates(double east, double north, bool saveMarker);
    void SetMarker(double east, double north, QString caption);
private slots:
    void replyFinished(QNetworkReply* reply);
    void on_btnHome_clicked();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
