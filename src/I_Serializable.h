#ifndef I_SERIALIZABLE_H
#define I_SERIALIZABLE_H

#include <SFML/Network.hpp>

class I_Serializable {
public:
    I_Serializable() {};

	~I_Serializable() {};

    typedef sf::Packet DataType;

    virtual DataType* serialize()=0;
    virtual void deserialize(DataType*)=0;



protected:
    DataType UpData;
    DataType DownData;

private:

};

#endif // I_SERIALIZABLE_H
