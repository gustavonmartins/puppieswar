#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/System.hpp>

#include "src/controls/GameController.hpp"
#include "AvatarsCollection.hpp"
#include "HumanView.hpp"

#include "PostMan.hpp"
#include "Generic.hpp"


struct I_GameClientOrServer {
    virtual void handleIncomingNetwork() = 0;
    virtual void getUserInput() = 0;
    virtual void broadcastUserInput() = 0;
    virtual void broadcastStatus() = 0;
    virtual void init()=0;
    virtual void shutdown()=0;
    virtual void updateGame();
    virtual ~I_GameClientOrServer();
};

struct GameServer: public I_GameClientOrServer {
    void handleIncomingNetwork() override;
    void getUserInput() override;
    void broadcastUserInput() override;
    void broadcastStatus() override;
    void init() override;
    void shutdown() override;

/*
    void listenToNewConnection();
    void downloadAllClientContents();
    void updateGame();
    */
    virtual ~GameServer();
};

struct GameClient:public I_GameClientOrServer {
    void handleIncomingNetwork() override;
    void getUserInput() override;
    void broadcastUserInput() override;
    void broadcastStatus() override;
    void init() override;
    void shutdown() override;

    /*
    void tryConnecting();
    void getUserInput();
    void uploadData();
    void updateGame();
    ,
    */
    virtual ~GameClient();
};

struct Game {

    std::string answer;
    bool isServer;
    bool clientPlaysOnline;

    PostMan ServerPostMan;
    int ServerPort;

    struct ClientProperties {
        int ID;
        std::string Name;
        sf::Packet DownPacket;
        sf::Packet UpPacket;
        GameController Controls;
    };

    typedef std::map<int, ClientProperties> ClientListType;
    ClientListType ClientList;
    std::map<int, sf::Packet*> LinkToDownPackages;
    std::vector<int> ConnectedPlayers;

    AvatarsCollection AvtsCollection;

    HumanView toDelete_HumanView;

    void run();
    void updateGame(const double&, AvatarsCollection&, const GameController&);
    void init();
    void stop();

    void downloadAllClientContents(ClientListType&, std::map<int, sf::Packet*>&, PostMan&) ;
    virtual ~Game();
    Game();

private:
    std::unique_ptr<I_GameClientOrServer> ClientOrServer;

};


#endif // GAME_HPP_INCLUDED
