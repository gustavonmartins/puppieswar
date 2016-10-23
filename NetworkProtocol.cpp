#include "NetworkProtocol.hpp"

namespace networkprotocol {

int refreshInterval=33;

bool convertPacketToTargetType(sf::Packet& myPacket, GameController& myOutputSet) {

    HeaderType header;

    bool GoBack,GoForward,GoLeft,GoRight,PrepareAction,PrepareAction2,RequestAction,RequestAction2,RequestJump;
    int HorizontalStatus, SelectNext;
    //std::cout<<"Packet Dissassembly started. Packet size is: "<<myPacket.getDataSize()<<std::endl;

    while(!myPacket.endOfPacket()) {
        // std::cout<<"Packet read start"<<std::endl;

        myPacket>>header;

        if (header==static_cast<HeaderType>(FromClient::Controls)) {
            //std::cout<<"Packet type is controls. Unpacking..."<<std::endl;
            myPacket>>GoBack>>GoForward>>GoLeft>>GoRight>>HorizontalStatus>>PrepareAction>>PrepareAction2>>RequestAction>>RequestAction2>>RequestJump>>SelectNext;
            myOutputSet.GoBack=GoBack;
            myOutputSet.GoForward=GoForward;
            myOutputSet.GoLeft=GoLeft;
            myOutputSet.GoRight=GoRight;
            myOutputSet.HorizontalStatus=HorizontalStatus;
            myOutputSet.PrepareAction=PrepareAction;
            myOutputSet.PrepareAction2=PrepareAction2;
            myOutputSet.RequestAction=RequestAction;
            myOutputSet.RequestAction2=RequestAction2;
            myOutputSet.RequestJump=RequestJump;
            myOutputSet.SelectNext=SelectNext;
        } else {
            std::cout<<"Packet not recognized. Stop reading it!"<<std::endl;
            return false;
        }
    }
    myPacket.clear();
}


}
