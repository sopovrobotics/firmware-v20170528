#include "controlserver.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>
#include <QHostAddress>
#include "cmd_handlers/create_cmd_handlers.h"
#include <QProcess>
#include <QFile>
// QT_USE_NAMESPACE

// ---------------------------------------------------------------------

ControlServer::ControlServer(ISettings *pSett, QObject *parent) : QObject(parent) {
	m_pSettings = pSett;
	m_pWebSocketServer = new QWebSocketServer(QStringLiteral("SopovRobotics"), QWebSocketServer::NonSecureMode, this);

    if (m_pWebSocketServer->listen(QHostAddress::Any, pSett->get_port())) {
        qDebug() << "SopovRobotics listening on port" << pSett->get_port();
        connect(m_pWebSocketServer, &QWebSocketServer::newConnection, this, &ControlServer::onNewConnection);
        connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &ControlServer::closed);
        create_cmd_handlers(m_mapCmdHandlers);
        m_bHasError = false;
    }else{
		qDebug() << "[ERROR] SopovRobotics could not listening on port" << pSett->get_port();
		m_bHasError = true;
	}

	unexportPin(m_pSettings->get_drivers_pin_A1());
	unexportPin(m_pSettings->get_drivers_pin_A2());
	unexportPin(m_pSettings->get_drivers_pin_B1());
	unexportPin(m_pSettings->get_drivers_pin_B2());

	exportPin(m_pSettings->get_drivers_pin_A1());
	exportPin(m_pSettings->get_drivers_pin_A2());
	exportPin(m_pSettings->get_drivers_pin_B1());
	exportPin(m_pSettings->get_drivers_pin_B2());

	directionOutPin(m_pSettings->get_drivers_pin_A1());
	directionOutPin(m_pSettings->get_drivers_pin_A2());
	directionOutPin(m_pSettings->get_drivers_pin_B1());
	directionOutPin(m_pSettings->get_drivers_pin_B2());
	
	// comb
	unexportPin(m_pSettings->get_servo_pin_comb());
	exportPin(m_pSettings->get_servo_pin_comb());
	directionOutPin(m_pSettings->get_servo_pin_comb());
	
	connect(this, &ControlServer::_sendAutoStoppedSignal, this, &ControlServer::_sendAutoStopped);
}

// ---------------------------------------------------------------------

ControlServer::~ControlServer() {
    m_pWebSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

// ---------------------------------------------------------------------

bool ControlServer::hasError(){
	return m_bHasError;
}

// ---------------------------------------------------------------------

void ControlServer::onNewConnection()
{
    QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

    
	qDebug() << "NewConnection " << pSocket->peerAddress().toString() << " " << pSocket->peerPort();

    connect(pSocket, &QWebSocket::textMessageReceived, this, &ControlServer::processTextMessage);
    connect(pSocket, &QWebSocket::binaryMessageReceived, this, &ControlServer::processBinaryMessage);
    connect(pSocket, &QWebSocket::disconnected, this, &ControlServer::socketDisconnected);

    m_clients << pSocket;
    
    QJsonObject obj;
    obj["msg"] = "info";
	obj["version"] = "v20170528";
	obj["firmware"] = 1;
	obj["name"] = "ForKeva";
	// TODO 

	QJsonObject capabilities;
	capabilities["turnleft"] = true;
	capabilities["turnright"] = true;
	capabilities["forward"] = true;
	capabilities["backward"] = true;
	capabilities["autocontrol"] = false;
	capabilities["light"] = false;
	obj["capabilities"] = capabilities;
	this->sendMessage(pSocket, obj);
}

// ---------------------------------------------------------------------

void ControlServer::processTextMessage(QString message) {
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
	QJsonObject jsonData = doc.object();
	QString cmd = "";
	if(jsonData.contains("cmd")){
		cmd = jsonData["cmd"].toString();
	}else{
		QJsonObject obj;
		obj["error"] = "Invalid command format";
		this->sendMessage(pClient, obj);
		return;
	}
	
	QString secret = "";
	if(jsonData.contains("secret")){
		secret = jsonData["secret"].toString();
	}else{
		QJsonObject obj;
		obj["error"] = "Not found field with secret";
		this->sendMessage(pClient, obj);
		return;
	}
	
	if(secret != m_pSettings->get_secret()){
		QJsonObject obj;
		obj["error"] = "Wrong secret";
		this->sendMessage(pClient, obj);
		return;
	}


	if(m_mapCmdHandlers.contains(cmd)){
		qDebug() << cmd;
		m_mapCmdHandlers[cmd]->handle(pClient, this, jsonData);
	}else{
		qDebug() << "Unknown command: " << cmd;
		QJsonObject obj;
		obj["error"] = "Unknown command";
		this->sendMessage(pClient, obj);
		return;
	}
}

// ---------------------------------------------------------------------

void ControlServer::processBinaryMessage(QByteArray message) {
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "Binary Message received:" << message;
    if (pClient) {
        pClient->sendBinaryMessage(message);
    }
}

// ---------------------------------------------------------------------

void ControlServer::socketDisconnected() {
    QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
    qDebug() << "socketDisconnected:" << pClient;
    if (pClient) {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}

// ---------------------------------------------------------------------

void ControlServer::sendMessage(QWebSocket *pClient, QJsonObject obj){
	 if (pClient) {
		QJsonDocument doc(obj);
		QString message = doc.toJson(QJsonDocument::Compact);
		qDebug() << QDateTime::currentDateTimeUtc().toString() << " [WS] >>> " << message;
        pClient->sendTextMessage(message);
    }
}

// ---------------------------------------------------------------------

void ControlServer::sendMessage(QWebSocket *pClient, const QByteArray &data){
	 if (pClient) {
		// qDebug() << QDateTime::currentDateTimeUtc().toString() << " [WS] >>> send binary data " << data.size();
        pClient->sendBinaryMessage(data);
    }
}

// ---------------------------------------------------------------------

ISettings * ControlServer::settings(){
	return m_pSettings;
}

// ---------------------------------------------------------------------

void ControlServer::turnleft(){

	setPinValue(
		m_pSettings->get_drivers_pin_A1(),
		m_pSettings->get_drivers_turnleft_A1()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_A2(),
		m_pSettings->get_drivers_turnleft_A2()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_B1(),
		m_pSettings->get_drivers_turnleft_B1()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_B2(),
		m_pSettings->get_drivers_turnleft_B2()
	);
}

// ---------------------------------------------------------------------

void ControlServer::turnright(){
	setPinValue(
		m_pSettings->get_drivers_pin_A1(),
		m_pSettings->get_drivers_turnright_A1()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_A2(),
		m_pSettings->get_drivers_turnright_A2()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_B1(),
		m_pSettings->get_drivers_turnright_B1()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_B2(),
		m_pSettings->get_drivers_turnright_B2()
	);
}

// ---------------------------------------------------------------------

void ControlServer::forward(){
	setPinValue(
		m_pSettings->get_drivers_pin_A1(),
		m_pSettings->get_drivers_forward_A1()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_A2(),
		m_pSettings->get_drivers_forward_A2()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_B1(),
		m_pSettings->get_drivers_forward_B1()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_B2(),
		m_pSettings->get_drivers_forward_B2()
	);
}

// ---------------------------------------------------------------------

void ControlServer::backward(){
	setPinValue(
		m_pSettings->get_drivers_pin_A1(),
		m_pSettings->get_drivers_backward_A1()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_A2(),
		m_pSettings->get_drivers_backward_A2()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_B1(),
		m_pSettings->get_drivers_backward_B1()
	);
	setPinValue(
		m_pSettings->get_drivers_pin_B2(),
		m_pSettings->get_drivers_backward_B2()
	);
}

// ---------------------------------------------------------------------

void ControlServer::stop(){
	setPinValue(
		m_pSettings->get_drivers_pin_A1(),
		0
	);
	setPinValue(
		m_pSettings->get_drivers_pin_A2(),
		0
	);
	setPinValue(
		m_pSettings->get_drivers_pin_B1(),
		0
	);
	setPinValue(
		m_pSettings->get_drivers_pin_B2(),
		0
	);
}

// ---------------------------------------------------------------------

void ControlServer::comb_up(){
	this->pwmPin(
		m_pSettings->get_servo_pin_comb(),
		m_pSettings->get_servo_pin_comb_value_up()
	);
}

// ---------------------------------------------------------------------

void ControlServer::comb_down(){
	this->pwmPin(
		m_pSettings->get_servo_pin_comb(),
		m_pSettings->get_servo_pin_comb_value_down()
	);
}

// ---------------------------------------------------------------------

void ControlServer::start_auto(QString script){
	stop_auto();
	m_pThreadAuto = new ThreadAuto(this, script);
	m_pThreadAuto->start();
}

// ---------------------------------------------------------------------

void ControlServer::stop_auto(){
	if(m_pThreadAuto != NULL){
		m_pThreadAuto->terminate();
		m_pThreadAuto = NULL;
	}
	stop();
}

// ---------------------------------------------------------------------

void ControlServer::_sendAutoStopped(){
	QJsonObject obj;
	obj["cmd"] = "auto_stopped";
	for(int i = 0; i < m_clients.size(); i++){
		sendMessage(m_clients[i], obj);
	}
}

// ---------------------------------------------------------------------

void ControlServer::send_auto_stopped(){
	emit _sendAutoStoppedSignal();
}

// ---------------------------------------------------------------------

void ControlServer::unexportPin(int pin){
	QFile file("/sys/class/gpio/unexport");
	if (file.open(QIODevice::WriteOnly)){
		QTextStream stream( &file );
		stream << QString::number(pin) << endl;
	}else{
		qDebug() << "Could not open gpio" + QString::number(pin) + "/unexport";
	}
}

// ---------------------------------------------------------------------

void ControlServer::exportPin(int pin){
	QFile file("/sys/class/gpio/export");
	if (file.open(QIODevice::WriteOnly)){
		QTextStream stream( &file );
		stream << QString::number(pin) << endl;
	}else{
		qDebug() << "Could not open gpio" + QString::number(pin) + "/export";
	}
}

// ---------------------------------------------------------------------

void ControlServer::setPinValue(int pin, int value){
	QFile file("/sys/class/gpio/gpio" + QString::number(pin) + "/value");
	if (file.open(QIODevice::WriteOnly)){
		qDebug() << "Set value " << value << " to " << pin;
		QTextStream stream( &file );
		stream << QString::number(value) << endl;
	} else {
		qDebug() << "Could not open gpio" + QString::number(pin) + "/value";
	}
}

// ---------------------------------------------------------------------


void ControlServer::directionOutPin(int pin){
	QFile file("/sys/class/gpio/gpio" + QString::number(pin) + "/direction");
	if (file.open(QIODevice::WriteOnly)){
		QTextStream stream( &file );
		stream  << "out" << endl;
	}else{
		qDebug() << "Could not open gpio" + QString::number(pin) + "/direction";
	}
}

// ---------------------------------------------------------------------

void ControlServer::pwmPin(int pin, int width_signal_usec){
	QString gpio_path = "/sys/class/gpio/gpio" + QString::number(pin) + "/value";
	QFile file(gpio_path);
	if (file.open(QIODevice::WriteOnly)){
		qDebug() << "PWM on pin " << pin << " started for " << width_signal_usec;
		QTextStream stream( &file );
		int counter = 0;
		QString one = QString::number(1);
		QString zero = QString::number(0);
		QElapsedTimer timer;
		qint64 elapsed;
		while(true){
			qDebug() << "1";
			timer.restart();
			stream << one << endl;
			elapsed = timer.nsecsElapsed()/1000;
			QThread::usleep(width_signal_usec);
			stream << zero << endl;
			elapsed = timer.nsecsElapsed()/1000;
			QThread::usleep(20000 - elapsed);
			counter++;
			if(counter > 21){
				break;
				return;
			}
		}
		qDebug() << "PWM on pin " << pin << " finished";
	}else{
		qDebug() << "Could not open " << gpio_path << " for pwm";
	}
}

// ---------------------------------------------------------------------
