#ifndef ITEMCOMPONENT_HPP
#define ITEMCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"
#include "../Game/Item.hpp"

class ItemComponent : public es::Component
{
    public:
        ItemComponent();

        static std::string getId();

        void setItem(Item item);
        Item getItem() const;
        Item moveItem(); // get + remove
        void removeItem();
        bool hasItem() const;

    private:
        Item mItem;
        bool mHasItem;
};

#endif // ITEMCOMPONENT_HPP