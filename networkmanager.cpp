/*
 *   This file is part of QRail.
 *
 *   QRail is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   QRail is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with QRail.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "networkmanager.h"
Network::Manager *Network::Manager::m_instance = nullptr;

/**
 * @file networkmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief QRail::Network::Manager facade constructor
 * @package Network
 * @private
 * Constructs a QRail::Network::Manager facade to access the network using the HTTP protocol.
 * The QRail::Network::Manager facade makes network access in Qt abstract from the underlying library (QNetworkAccessManager, libCurl, ...).
 */
Network::Manager::Manager(QObject *parent): QObject(parent)
{
    // Initiate a new QNetworkAccessManager
    this->setQNAM(new QNetworkAccessManager(this));
    QNetworkConfigurationManager QNAMConfig;
    this->QNAM()->setConfiguration(QNAMConfig.defaultConfiguration());

    // Connect QNetworkAccessManager signals
    connect(this->QNAM(),
            SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)),
            this,
            SIGNAL(networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility)));
    connect(this->QNAM(),
            SIGNAL(sslErrors(QNetworkReply *, QList<QSslError>)),
            this,
            SIGNAL(sslErrorsReceived(QNetworkReply *, QList<QSslError>)));
    connect(this->QNAM(),
            SIGNAL(finished(QNetworkReply *)),
            this,
            SLOT(streamFinished(QNetworkReply *)));
}

/**
 * @file networkmanager.cpp
 * @author Dylan Van Assche
 * @date 9 Aug 2018
 * @brief Get a QRail::Network::Manager instance
 * @param QObject *parent = nullptr
 * @return QRail::Network::Manager *manager
 * @package Network
 * @public
 * Constructs a QRail::Network::Manager if none exists and returns the instance.
 */
Network::Manager *Network::Manager::getInstance()
{
    if (m_instance == nullptr) {
        qDebug() << "Creating new QRail::Network::Manager";
        m_instance = new Manager();
    }
    return m_instance;
}

// Invokers
/**
 * @file networkmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Get a resource
 * @param const QUrl &url
 * @param QObject *caller
 * @package Network
 * @public
 * Retrieves a certain resource from the given QUrl &url using a GET request.
 * The result as a QNetworkReply *reply will be available through the Qt event system.
 * Implement the customEvent() method in your QObject to receive the data.
 */
void Network::Manager::getResource(const QUrl &url)
{
    qDebug() << "GET resource:" << url;
    QNetworkRequest request = this->prepareRequest(url);
    m_reply = this->QNAM()->get(request);
    connect(m_reply, SIGNAL(readyRead()), this, SLOT(streamReceived()));
}

void Network::Manager::streamFinished(QNetworkReply *reply)
{
    qDebug() << "Stream finished:" << reply->url();
}

void Network::Manager::streamReceived()
{
    qDebug() << "Received event from stream";
    qDebug() << QString(m_reply->readAll()).simplified().replace("data: ", "");
    qDebug() << "-----------------------------------------------------";
}

// Helpers
/**
 * @file networkmanager.cpp
 * @author Dylan Van Assche
 * @date 17 Jul 2018
 * @brief Prepare the HTTP request
 * @param const QUrl &url
 * @return QNetworkRequest request
 * @package Network
 * @public
 * Everytime a HTTP request has been made by the user it needs several default headers to complete it's mission.
 * The prepareRequest method just does that, it adds the Accept, User-Agent header to the request and allows redirects.
 */
QNetworkRequest Network::Manager::prepareRequest(const QUrl &url)
{
    QNetworkRequest request(url);
    request.setRawHeader(QByteArray("Accept"), QByteArray(ACCEPT_HEADER));
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);
    request.setHeader(QNetworkRequest::ContentTypeHeader, CONTENT_TYPE);
    request.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork); // Events shouldn't be cached
    return request;
}

// Getter & Setters
/**
 * @file networkmanager.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Gets the QNAM instance
 * @return QNetworkAccessManager *QNAM
 * @package Network
 * @public
 * Gets the QNetworkAccessManager instance.
 */
QNetworkAccessManager *Network::Manager::QNAM() const
{
    return m_QNAM;
}

/**
 * @file networkmanager.cpp
 * @author Dylan Van Assche
 * @date 21 Jul 2018
 * @brief Sets the QNAM instance
 * @param QNetworkAccessManager *value
 * @package Network
 * @public
 * Sets the QNetworkAccessManager instance.
 */
void Network::Manager::setQNAM(QNetworkAccessManager *value)
{
    m_QNAM = value;
}
