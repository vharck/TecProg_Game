#include "Entidade.hpp"

#include "GerenciadorColisoes.hpp"

namespace JOGACO
{
    class Projetil : public Entidade
    {
    protected:
        enum class ProjectileType
        {
            Normal,
            Bouncing,
            Explosive
        };

        ProjectileType type;
        sf::Vector2f direction;
        const float speed;
        const int damage;
        const int lifetime;
        int currentLifetime;

        Gerenciadores::GerenciadorColisoes::Trigger *trigger;

    public:
        Projetil(ProjectileType projectileType, sf::Vector2f position, sf::Vector2f direction, float speed, int damage, int lifetime,
                 sf::Vector2f size = sf::Vector2f(10.f, 10.f),
                 Gerenciadores::GerenciadorColisoes::Collider::ColliderLayer layer = Gerenciadores::GerenciadorColisoes::Collider::ColliderLayer::GenericTrigger);
        ~Projetil();

        void update() override;
        void move();
        void onCollisionEnter(Gerenciadores::GerenciadorColisoes::Collider *other);

        const sf::Vector2f &getDirection() const;
        void setDirection(const sf::Vector2f &newDirection);
    };
}