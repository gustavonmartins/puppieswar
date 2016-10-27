#include <SFML/System.hpp>
#include <iostream>
#include <memory>
#include "Game.hpp"


void GameServer::handleIncomingNetwork() {}
void GameServer::getUserInput() {}
void GameServer::broadcastUserInput() {}
void GameServer::broadcastStatus() {}
void GameServer::init() {}
void GameServer::shutdown() {}
GameServer::~GameServer() {}

void GameClient::handleIncomingNetwork() {}
void GameClient::getUserInput() {}
void GameClient::broadcastUserInput() {}
void GameClient::broadcastStatus() {}
void GameClient::init() {}
void GameClient::shutdown() {}
GameClient::~GameClient() {}

void I_GameClientOrServer::updateGame() {}
I_GameClientOrServer::~I_GameClientOrServer() {}

Game::Game(): ClientOrServer( nullptr ) {

}
Game::~Game() {}

void Game::run() {

    while ( true/*window.isOpen()*/ ) {

        double dt_sec;
        sf::Time dt;
        static const sf::Clock gameClock;
        static sf::Time previousTime = gameClock.getElapsedTime();
        dt = gameClock.getElapsedTime() - previousTime;
        previousTime = gameClock.getElapsedTime();
        dt_sec = dt.asSeconds();

        static Timer timerForNewClients;
        static Timer timerForDownload;
        static Timer timerForUpLoad;
        if ( timerForNewClients.getTimerApproval( 2000, false ) ) {

            if ( isServer ) {
                ServerPostMan.listenToNewConnection( ServerPort );
            } else if ( clientPlaysOnline ) {
                if ( toDelete_HumanView.tryConnecting ) {
                    int connected;
                    connected = toDelete_HumanView.tryToConnect();
                    if ( connected >= 1 ) {
                        toDelete_HumanView.tryConnecting = false;
                    }
                }
            }
        }

        if ( timerForDownload.getTimerApproval( 0, false ) ) {
            if ( isServer ) {
                downloadAllClientContents( ClientList, LinkToDownPackages, ServerPostMan );
            }
        }

        if ( timerForUpLoad.getTimerApproval( 1.2 * networkprotocol::refreshInterval, false ) ) {
            if ( !isServer ) {
                toDelete_HumanView.getUserInput( toDelete_HumanView.m_RenderWindow, toDelete_HumanView.m_Event, toDelete_HumanView.m_Controller );
                if ( clientPlaysOnline ) {
                    toDelete_HumanView.uploadData( toDelete_HumanView.m_Controller.serialize() );
                }
            }
        }

        if ( isServer ) {
            if ( ClientList.size() > 0 ) {

                updateGame( dt_sec, AvtsCollection, ClientList.rbegin()->second.Controls );
            }
        } else {
            updateGame( dt_sec, AvtsCollection, toDelete_HumanView.m_Controller );
        }
        toDelete_HumanView.generateGraphics( toDelete_HumanView.m_RenderWindow, AvtsCollection );
        graphicsSystem.update();
    }
}

void Game::downloadAllClientContents( ClientListType& ClientList, std::map<int, sf::Packet*>& LinkToDownPackages, PostMan& ServerPostMan ) {
    ServerPostMan.downloadPackages();
    ServerPostMan.debug_checkDownSizes();

    ServerPostMan.resizeMapByActiveConnection( ClientList, false );
    ServerPostMan.resizeMapByActiveConnection2( LinkToDownPackages, false );


    for ( auto& currentClient : ClientList ) {
        auto prepareThisLink = LinkToDownPackages.find( currentClient.first );
        if ( prepareThisLink == LinkToDownPackages.end() ) {
            std::cout << "Hologram assembly failed on client " << currentClient.first;
        } else {
            prepareThisLink->second = &( currentClient.second.DownPacket );
        }
    }
    ServerPostMan.transferDownloadedPackages( LinkToDownPackages );
    //std::cout<<"Size of package: "<<sizeof(*(HologramOfDownPackages.rbegin()->second))<<std::endl;

    for ( auto& currentClient : ClientList ) {
        networkprotocol::convertPacketToTargetType( currentClient.second.DownPacket, currentClient.second.Controls );
        //copiedControl=currentClient.second.Controls;
    }
}

void Game::updateGame( const double& dt_sec, AvatarsCollection& _AvtCollection, const GameController& _gameController ) {
    _AvtCollection.interpretControls( _gameController );
    _AvtCollection.updateOnMainTick( dt_sec );
}

void Game::init() {
    std::cout << "Do you want to be a server? (y/n): " << std::endl;
    std::cin >> answer;

    if ( answer == "y" ) {
        isServer = true;
        std::cout << "Being a server! " << std::endl;
        ClientOrServer = std::make_unique<GameServer>();
    } else if ( answer == "n" ) {
        isServer = false;
        std::cout << "Being a client! " << std::endl;
        ClientOrServer = std::make_unique<GameClient>();
    }

    if ( isServer ) {
        std::cout << "In which port should this server operate: " << std::endl;
        std::cin >> ServerPort;
    } else {
        std::cout << "Do you want to play online? (y/n): " << std::endl;
        std::cin >> answer;
        if ( answer == "y" ) {
            clientPlaysOnline = true;
            std::cout << "Playing online as a client! " << std::endl;
            toDelete_HumanView.askWhereToConnect();
        } else if ( answer == "n" ) {
            clientPlaysOnline = false;
            std::cout << "Client not playing online! " << std::endl;
        }
    }

    graphicsSystem.setSoul( Veejay::SoulType::OpenGL );
    graphicsSystem.init();
    graphicsSystem.inviteGuest( &AvtsCollection );
    AvtsCollection.joinParty();


    toDelete_HumanView.createWindow( 700, 500 );

}

void Game::stop() {
    graphicsSystem.shutdown();
}
