#ifndef NETWORKPROTOCOL_HPP_INCLUDED
#define NETWORKPROTOCOL_HPP_INCLUDED

#include <iostream>

#include <SFML/Network.hpp>

#include "controls/GameController.hpp"



namespace networkprotocol {
typedef sf::Packet PacketType;
typedef sf::Uint16 HeaderType;
enum class FromServer : HeaderType {Blank, KillClient, ServerMessage};
enum class FromClient : HeaderType {Blank, Disconnect,KillServer, ClientMessage, Position,Controls};

extern int refreshInterval;

bool convertPacketToTargetType(sf::Packet&, GameController&);
}




#endif // NETWORKPROTOCOL_HPP_INCLUDED
