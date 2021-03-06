#ifndef LP_PACKET_HPP_INCLUDED
#define LP_PACKET_HPP_INCLUDED

#include <SFML/Network/Packet.hpp>

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

// Vector2

template<typename T>
sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2<T>& v);
template<typename T>
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2<T>& v);

// Vector3

template<typename T>
sf::Packet& operator <<(sf::Packet& packet, const sf::Vector3<T>& v);
template<typename T>
sf::Packet& operator >>(sf::Packet& packet, sf::Vector3<T>& v);

// Rect

template<typename T>
sf::Packet& operator <<(sf::Packet& packet, const sf::Rect<T>& r);
template<typename T>
sf::Packet& operator >>(sf::Packet& packet, sf::Rect<T>& r);

// Color

sf::Packet& operator <<(sf::Packet& packet, const sf::Color& c);
sf::Packet& operator >>(sf::Packet& packet, sf::Color& c);



//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////


// Vector2

template<typename T>
sf::Packet& operator <<(sf::Packet& packet, const sf::Vector2<T>& v)
{
    return packet << v.x << v.y;
}

template<typename T>
sf::Packet& operator >>(sf::Packet& packet, sf::Vector2<T>& v)
{
    return packet >> v.x >> v.y;
}

// Vector3

template<typename T>
sf::Packet& operator <<(sf::Packet& packet, const sf::Vector3<T>& v)
{
    return packet << v.x << v.y << v.z;
}

template<typename T>
sf::Packet& operator >>(sf::Packet& packet, sf::Vector3<T>& v)
{
    return packet >> v.x >> v.y >> v.z;
}

// Rect

template<typename T>
sf::Packet& operator <<(sf::Packet& packet, const sf::Rect<T>& r)
{
    return packet << r.left << r.top << r.width << r.height;
}

template<typename T>
sf::Packet& operator >>(sf::Packet& packet, sf::Rect<T>& r)
{
    return packet >> r.left >> r.top >> r.width >> r.height;
}


#endif // LP_PACKET_HPP_INCLUDED
