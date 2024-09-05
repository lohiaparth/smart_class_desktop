#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QWebSocket>

class Whiteboard : public QWidget {
    Q_OBJECT

public:
    explicit Whiteboard(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap pixmap;
    QPoint lastPoint;
    QWebSocket webSocket;  // WebSocket member
    void connectWebSocket();  // Method to connect the WebSocket
    void sendDrawingData(const QPoint &start, const QPoint &end);
    void processMessage(const QString &message);
    void onTextMessageReceived(const QString &message);
    void onWebSocketConnected();
    void onWebSocketDisconnected();
    void onWebSocketError(QAbstractSocket::SocketError error);
};

#endif // WHITEBOARD_H
