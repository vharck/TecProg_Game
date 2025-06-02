// Game Object
#pragma once
#include "GerenciadorGrafico.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>

namespace JOGACO
{

    class Ente
    {
    protected:
        int id;
        GerenciadorGrafico *gerenciadorGrafico;
        Texture *texture;

    public:
        Ente();
        virtual ~Ente();
        virtual void update() = 0;
        void draw();
    };
}