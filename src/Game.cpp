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
                if (is3dMode) {

                    graphicsSystem.getUserInput();

                } else {
                    toDelete_HumanView.getUserInput();
                }
                //

                if ( clientPlaysOnline ) {
                    
                    if (is3dMode){toDelete_HumanView.uploadPacketToAllConnected( graphicsSystem.getController().serialize() );}
                    else {
                    
                        toDelete_HumanView.uploadPacketToAllConnected( toDelete_HumanView.getController().serialize() );
                    
                    }
                }
            }
        }

        if ( isServer ) {
            if ( ClientList.size() > 0 ) {

                updateGame( dt_sec, AvtsCollection, ClientList.rbegin()->second.Controls );
            }
        } else {
            if (is3dMode) {
                updateGame( dt_sec, AvtsCollection, graphicsSystem.getController() );
            } else {
                updateGame( dt_sec, AvtsCollection, toDelete_HumanView.getController() );
            }


        }

        if (is3dMode) {
            graphicsSystem.update();
        } else {
            toDelete_HumanView.generateGraphics( AvtsCollection);
        }
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
    }
}

void Game::updateGame( const double& dt_sec, AvatarsCollection& _AvtCollection, GameController& _gameController ) {
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

    std::cout << "Graphics at 2d or 3d? (2d/3d): " << std::endl;
    std::cin >> answerGraphics;

    if ( answerGraphics == "2d" ) {
        is3dMode = false;
        std::cout << "Being 2d " << std::endl;
        toDelete_HumanView.init();
    } else if ( answerGraphics == "3d" ) {
        is3dMode = true;
        std::cout << "Being 3d" << std::endl;
        graphicsSystem.setSoul( Veejay::SoulType::OpenGL );
        graphicsSystem.initSoul();
        graphicsSystem.inviteGuest( &AvtsCollection );
    }







}

void Game::stop() {
    graphicsSystem.shutdown();
}
