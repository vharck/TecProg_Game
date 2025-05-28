// Game Object

#include "Ente.hpp"

using namespace sf;
using namespace std;
namespace JOGACO
{
    Ente::Ente()
    {
        // ler textura do arquivo
    }

    Ente::~Ente()
    {
        if (texture != NULL)
        {
            delete texture;
            texture = NULL;
        }
        gerenciadorGrafico = NULL;
    }

    void Ente::draw()
    {
        // se desenhar na tela
    }
}