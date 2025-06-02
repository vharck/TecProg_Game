#pragma once
#include "Inimigo.hpp"

#include "GerenciadorColisoes.hpp"

#include <SFML/Graphics.hpp>

namespace JOGACO
{
    class WorldEater : public Inimigo
    {
    public:
        enum class WorldEaterAction
        {
            Enter,
            CircularMovement,
            SineWaveMovement,
            SlowMovement,
            SkyDive
        };

        enum class WorldEaterSegment
        {
            Head,
            Body,
            Tail
        };

    private:
        WorldEaterAction currentAction;
        WorldEaterSegment currentSegment;

        float sineWaveAmplitude;
        float sineWaveFrequency;
        float circularMovementRadius;
        float movementSpeed;
        float slowMovementSpeed;
        float skyDiveSpeed;

        int currentActionFrame;

        WorldEater *nextSegment;

        void performCircularMovement();
        void performSineWaveMovement();
        void performSlowMovement();
        void performSkyDive();
        void performAction();

    protected:
        void move() override;
        void chase() override;
        void patrol() override;
        void attack() override;
        void save() override;
        void update() override;

    public:
        WorldEater(sf::Vector2f position, int maxHealth, int threatLevel,
                   float sineWaveAmplitude, float sineWaveFrequency,
                   WorldEaterSegment segment,
                   float circularMovementRadius, float movementSpeed, float slowMovementSpeed, float skyDiveSpeed);

        ~WorldEater() override;

        void moveNextSegment(Vector2f postion);
    };
}