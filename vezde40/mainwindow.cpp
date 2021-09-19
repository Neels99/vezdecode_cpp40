#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QJsonObject>
#include <QMessageBox>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //For test
    //QUrl url("https://httpbin.org/post");
    QUrl url("https://localhost:8000/api");
    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");


    QByteArray params;
    params.append("param1=1&");
    params.append("param2=2");
//    QUrlQuery params(url);
//    params.addQueryItem("param1", "1");
//    params.addQueryItem("param2", "2");

    QObject::connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(replyFinished(QNetworkReply *)));

    manager->post(request, params); //params.toString().toUtf8());
}

void MainWindow::replyFinished(QNetworkReply* reply)
{
    QString str;
    if (reply->isFinished() && !reply->error())
    {
        str = QString(reply->readAll());
    } else
    {
        if (reply->error())
            str = reply->errorString();
    }
    QMessageBox msg_box;
    msg_box.setStandardButtons(0);
    msg_box.setText(str);

    QTimer::singleShot(5000, &msg_box, SLOT(hide()));
    msg_box.exec();
}
