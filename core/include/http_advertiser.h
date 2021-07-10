//////////////////////////////////////////////////////////////////////////////////////
//    akashi - a server for Attorney Online 2                                       //
//    Copyright (C) 2020  scatterflower                                             //
//                                                                                  //
//    This program is free software: you can redistribute it and/or modify          //
//    it under the terms of the GNU Affero General Public License as                //
//    published by the Free Software Foundation, either version 3 of the            //
//    License, or (at your option) any later version.                               //
//                                                                                  //
//    This program is distributed in the hope that it will be useful,               //
//    but WITHOUT ANY WARRANTY; without even the implied warranty of                //
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                 //
//    GNU Affero General Public License for more details.                           //
//                                                                                  //
//    You should have received a copy of the GNU Affero General Public License      //
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.        //
//////////////////////////////////////////////////////////////////////////////////////
#ifndef HTTP_ADVERTISER_H
#define HTTP_ADVERTISER_H

#include <QtNetwork>
#include <QObject>


/**
 * @brief Represents the advertiser of the server. Sends current server information to masterserver.
 */
class HTTPAdvertiser : public QObject
{
    Q_OBJECT
public:
    /**
     * @brief Constructor for the HTTP_Advertiser class.
     */
    explicit HTTPAdvertiser();


    /**
     *  @brief Deconstructor for the HTTP_Advertiser class. Yes, that's it. Can't say more about it.
     */
    ~HTTPAdvertiser();

public slots:

    /**
     * @brief Establishes a connection with masterserver to register or update the listing on the masterserver.
     */
    void msAdvertiseServer();

    /**
     * @brief Reads the information send as a reply for further error handling.
     * @param reply Response data from the masterserver. Information contained is send to the console if debug is enabled.
     */
    void msRequestFinished(QNetworkReply *reply);

    /**
     * @brief setAdvertiserSettings Configures the values being advertised to masterserver.
     * @param f_name Servername.
     * @param f_description Serverdescription.
     * @param f_port Client port.
     * @param f_ws_port Optional Websocket proxy port.
     * @param f_players Maximum amount of clients.
     * @param f_master_url URL of the advertisement target.
     */
    void setAdvertiserSettings(QString f_name, QString f_description, int f_port, int f_ws_port, int f_players, QUrl f_master_url, bool f_debug);

private:

    /**
     * @brief Pointer to the network manager, necessary to execute POST requests to the masterserver.
     */
    QNetworkAccessManager* m_manager;

    /**
     * @brief Name of the server send to the masterserver. Changing this will change the display name in the serverlist
     */
    QString m_name;

    /**
     * @brief Description of the server that is displayed in the client when the server is selected.
     */
    QString m_description;

    /**
     * @brief Client port for the AO2-Client.
     */
    int m_port;

    /**
     * @brief Websocket proxy port for WebAO users.
     */
    int m_ws_port;

    /**
     * @brief Maximum amount of clients that can be connected to the server.
     */
    int m_players;

    /**
     * @brief URL of the masterserver that m_manager posts to. This is almost never changed.
     */
    QUrl m_masterserver;

    /**
     * @brief Controls if network replies are printed to console. Should only be true if issues communicating with masterserver appear.
     */
    bool m_debug;
};

#endif // HTTP_ADVERTISER_H
