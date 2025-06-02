#pragma once

#include <SFML/Graphics.hpp>
#include "Entidade.hpp"

#include <Vector>
#include <functional>

using namespace sf;
using namespace std;
using std::vector;

namespace JOGACO
{
    class Jogador;
    class Inimigo;

    namespace Gerenciadores
    {
        class GerenciadorColisoes
        {
        public:
            class Collider : public sf::RectangleShape
            {
                // REQ classe aninhada
            public:
                enum class ColliderLayer
                {
                    Ground,
                    Player,
                    Enemy,
                    GenericTrigger // triggers for players and enemies
                };

            protected:
                Vector2f position;
                Vector2f size;
                bool isActive = true;
                ColliderLayer layer;

                Entidade *parrentEntity = nullptr;

                vector<Collider *> collidingEntities;
                function<void(Collider *Other)> collisionEnterCallbacks;
                function<void(Collider *Other)> collisionStayCallbacks;
                function<void(Collider *Other)> collisionExitCallbacks;

            public:
                Collider(Entidade *parrent, Vector2f position, Vector2f size, ColliderLayer layer, bool isActive = true);
                virtual ~Collider() = default;

                const Vector2f getPosition() const;
                const Vector2f getSize() const;
                const ColliderLayer getLayer() const;
                const bool isActive() const;
                Entidade *getParrentEntity() const;
                void setPosition(const Vector2f &newPosition);
                void setSize(const Vector2f &newSize);

                template <typename T>
                void subscribeToCollisionEnter(T *obj, void (T::*callback)(Collider *other));

                template <typename T>
                void unsubscribeFromCollisionEnter(T *obj, void (T::*callback)(Collider *other));
            };

            class Physic : public Collider
            {
            public:
                Physic(Entidade *parrent, Vector2f position, Vector2f size, ColliderLayer layer = ColliderLayer::Ground, bool isActive = true);

                void callCollisionEnter();
            };

            class Trigger : public Collider
            {
            public:
                Trigger(Entidade *parrent, Vector2f position, Vector2f size, ColliderLayer layer = ColliderLayer::GenericTrigger, bool isActive = true);

                void callCollisionEnter();
                void callCollisionExit();
                void callCollisionStay();

                template <typename T>
                void subscribeToCollisionExit(T *obj, void (T::*callback)(Collider *other));
                template <typename T>
                void subscribeToCollisionStay(T *obj, void (T::*callback)(Collider *other));

                template <typename T>
                void unsubscribeFromCollisionExit(T *obj, void (T::*callback)(Collider *other));
                template <typename T>
                void unsubscribeFromCollisionStay(T *obj, void (T::*callback)(Collider *other));
            };
        };
    };

};