#include "whiteboard.h"
#include <QWebSocket>
#include <QDebug>

Whiteboard::Whiteboard(QWidget *parent) : QWidget(parent), pixmap(400, 300), webSocket() {
    pixmap.fill(Qt::white);
    connectWebSocket();
}

void Whiteboard::connectWebSocket() {
    qDebug() << "Attempting to connect to WebSocket...";

    // Ensure webSocket is initialized and properly connected
    connect(&webSocket, &QWebSocket::connected, this, &Whiteboard::onWebSocketConnected);
    connect(&webSocket, &QWebSocket::disconnected, this, &Whiteboard::onWebSocketDisconnected);
    connect(&webSocket, &QWebSocket::textMessageReceived, this, &Whiteboard::onTextMessageReceived);

    connect(&webSocket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
            this, &Whiteboard::onWebSocketError);

    webSocket.open(QUrl(QStringLiteral("ws://127.0.0.1:8080")));
}

void Whiteboard::onWebSocketConnected() {
    qDebug() << "WebSocket connected!";
    webSocket.sendTextMessage("Test message from Qt client");
}

void Whiteboard::onWebSocketDisconnected() {
    qDebug() << "WebSocket disconnected!";
}

void Whiteboard::onWebSocketError(QAbstractSocket::SocketError error) {
    qDebug() << "WebSocket error:" << error << webSocket.errorString();
}

void Whiteboard::onTextMessageReceived(const QString &message) {
    qDebug() << "Message received in onTextMessageReceived:" << message;
    processMessage(message);
}

void Whiteboard::sendDrawingData(const QPoint &start, const QPoint &end) {
    QString message = QString("DRAW %1,%2,%3,%4")
    .arg(start.x()).arg(start.y()).arg(end.x()).arg(end.y());

    webSocket.sendTextMessage(message);
}

void Whiteboard::mousePressEvent(QMouseEvent *event) {
    lastPoint = event->pos();
}

void Whiteboard::mouseMoveEvent(QMouseEvent *event) {
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(lastPoint, event->pos());

    sendDrawingData(lastPoint, event->pos());

    lastPoint = event->pos();
    update();
}

void Whiteboard::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}

void Whiteboard::processMessage(const QString &message) {
    qDebug() << "Message received in processMessage: " << message;
    QStringList parts = message.split(" ");
    if (parts[0] == "DRAW") {
        QStringList points = parts[1].split(",");
        if (points.size() == 4) {
            QPoint start(points[0].toInt(), points[1].toInt());
            QPoint end(points[2].toInt(), points[3].toInt());

            QPainter painter(&pixmap);
            painter.setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
            painter.drawLine(start, end);
            update();
        }
    }
}
