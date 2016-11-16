#ifndef I_EXTRACTABLEGRAPHICS_H
#define I_EXTRACTABLEGRAPHICS_H

#include <SFML/Graphics.hpp>
#include <list>

class I_ExtractableGraphics {
private:

public:
    I_ExtractableGraphics() {}

    ~I_ExtractableGraphics() {}

    typedef sf::Drawable* PartialOutput;
    typedef std::list<PartialOutput> Output;
    virtual Output extractGraphics() = 0 ;

protected:


};


#endif // I_EXTRACTABLEGRAPHICS_H
