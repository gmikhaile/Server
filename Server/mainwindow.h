#pragma once

#include <QMainWindow>
#include <QThread>
#include <QTimer>

#include "ui_mainwindow.h"

class ServerThreadPool;
class ClientsListWidget;
class VideoGrabber;
class SliderTabWidget;

enum class CommandType
{
	SEND_IDENT_IMG
};

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
	void init();
	void initVideoGrabberCamera();
	void initVideoGrabberFile();
	void initClientsList();
	void initSetUpBlock();
	void initTabWidget();
	void cropImageAndSend();

private slots:
	void closeConnection();
	void createConnection();
	void closeVideoGrabberCamera();
	void closeVideoGrabberFile();
	void openFileDialog();

	void onDataReady(QByteArray data);
	void receiveFrame(QPixmap frame, QByteArray data);

	void sendDataTCP(QByteArray data, QString client);
	
	void setUpClients();
	void getPhoneAreas();
	void findContours(QPixmap frame);

private:
	Ui::MainWindow m_ui;

	std::unique_ptr<ServerThreadPool> m_server;
	std::unique_ptr<ClientsListWidget> m_clientsListWidget;
	std::unique_ptr<VideoGrabber> m_videoGrabberCameraWorker;
	std::unique_ptr<VideoGrabber> m_videoGrabberFileWorker;
	std::unique_ptr<QThread> m_threadCamera;
	std::unique_ptr<QThread> m_threadFile;
	std::unique_ptr<QTimer> m_timerCamera;
	std::unique_ptr<QTimer> m_timerFile;

	SliderTabWidget* m_colorsAdjusterWidget;

	bool m_isDoneSetup;
	bool m_isShapeDetectorTaskFinished;
	bool m_iscropImageAndSendFinished;
	QMap<QString, QVector<QPoint>> m_shapes;

	QVector<QPair<QPixmap, QString>> m_cropedImages;
	QVector<QPair<QByteArray, QString>> m_cropedData;

	QString m_fileName;

	int m_prevTunedDevice;
};
