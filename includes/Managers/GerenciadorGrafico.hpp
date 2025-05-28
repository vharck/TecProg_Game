// Graphic Manager

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class Ente;
class GerenciadorGrafico
{

public:
    GerenciadorGrafico();
    virtual ~GerenciadorGrafico();

    void drawEnte(Ente *ente);
};