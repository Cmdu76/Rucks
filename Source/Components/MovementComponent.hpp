#ifndef MOVEMENTCOMPONENT_HPP
#define MOVEMENTCOMPONENT_HPP

#include "../../Lib/EntitySystem/Component.hpp"

class MovementComponent : public es::Component
{
    public:
        MovementComponent();

        static std::string getId();

        void setSpeed(float speed);
        float getSpeed() const;

    private:
        float mSpeed;
};

#endif // MOVEMENTCOMPONENT_HPP