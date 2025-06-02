#include "WorldEater.hpp"

#include "GerenciadorColisoes.hpp"
#include "Utilidade.hpp"

namespace JOGACO
{

    WorldEater::WorldEater(sf::Vector2f position, int maxHealth, int threatLevel, float _sineWaveAmplitude, float _sineWaveFrequency, WorldEaterSegment _segment, float _circularMovementRadius, float _movementSpeed, float _slowMovementSpeed, float _skyDiveSpeed)
        : Inimigo(position, maxHealth, threatLevel, 0.f, 0.f, 0, 0, 0, 0.f, 0.f, sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 0.f), Vector2f(0.f, 0.f), CharacterState::Idle),
          currentAction(WorldEaterAction::Enter),
          currentSegment(_segment),
          sineWaveAmplitude(_sineWaveAmplitude),
          sineWaveFrequency(_sineWaveFrequency),
          circularMovementRadius(_circularMovementRadius),
          movementSpeed(_movementSpeed),
          slowMovementSpeed(_slowMovementSpeed),
          skyDiveSpeed(_skyDiveSpeed),
          currentActionFrame(0),
          nextSegment(nullptr)
    {
        if (_segment == WorldEaterSegment::Head)
        {
            nextSegment = new WorldEater(position, maxHealth, threatLevel, _sineWaveAmplitude, _sineWaveFrequency, WorldEaterSegment::Body, _circularMovementRadius, _movementSpeed, _slowMovementSpeed, _skyDiveSpeed);
        }
        else if (_segment == WorldEaterSegment::Body)
        {
            if (threatLevel > 1)
            {
                nextSegment = new WorldEater(position, maxHealth, threatLevel - 1, _sineWaveAmplitude, _sineWaveFrequency, WorldEaterSegment::Body, _circularMovementRadius, _movementSpeed, _slowMovementSpeed, _skyDiveSpeed);
            }
            else
            {
                nextSegment = new WorldEater(position, maxHealth, threatLevel, _sineWaveAmplitude, _sineWaveFrequency, WorldEaterSegment::Tail, _circularMovementRadius, _movementSpeed, _slowMovementSpeed, _skyDiveSpeed);
            }
        }
    }

    WorldEater::~WorldEater()
    {
        if (nextSegment)
        {
            delete nextSegment;
            nextSegment = nullptr;
        }
    }

    void WorldEater::performCircularMovement()
    {
    }

    void WorldEater::performSineWaveMovement()
    {
    }

    void WorldEater::performSlowMovement()
    {
    }

    void WorldEater::performSkyDive()
    {
    }

    void WorldEater::performAction()
    {
        if (currentActionFrame > 0)
            currentActionFrame--;
        else
            currentAction = (WorldEaterAction)Utilidade::random(1, 5);

        switch (currentAction)
        {
        case WorldEaterAction::Enter:
            // TODO implementar a lógica de cada fase do boss, a ideia é que seja tipo o Devourer of Gods do terraria
            break;
        case WorldEaterAction::CircularMovement:
            performCircularMovement();
            break;
        case WorldEaterAction::SineWaveMovement:
            performSineWaveMovement();
            break;
        case WorldEaterAction::SlowMovement:
            performSlowMovement();
            break;
        case WorldEaterAction::SkyDive:
            performSkyDive();
            break;
        }
    }

    void WorldEater::moveNextSegment(Vector2f postion)
    {
    }

    void WorldEater::update()
    {
        if (currentSegment == WorldEaterSegment::Body)
            move();
    }

    void WorldEater::move()
    {
        if (nextSegment)
        {
            nextSegment->moveNextSegment(position);
        }

        if (currentSegment == WorldEaterSegment::Head)
            performAction();
    }

    void WorldEater::attack()
    {
        // TODO implementar o bagui de jogar umas bolas de fogo
    }

    void WorldEater::save()
    {
        // TODO implementar o bagui de salvar o estado do inimigo
    }

    void WorldEater::chase() {}
    void WorldEater::patrol() {}

}
