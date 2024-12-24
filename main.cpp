#include <string>
#include <ctime>
#include <Windows.h>

#include "header/play.h"
#include "header/menu.h"

/* ////////////////////////////////////////////////
  Author DIEGO J D ARIAS - diegojdarias@gmail.com.
*////////////////////////////////////////////////


int main() {

    ocultarCursor();
    srand(unsigned int(time(0)));

    bool finalizar{ false };
    int puntajesMaximos[10]{};
    std::string nombresTop[10]{
        " _ _ _      _ _ _      _ _ _ ", " _ _ _      _ _ _      _ _ _ ", " _ _ _      _ _ _      _ _ _ ",
        " _ _ _      _ _ _      _ _ _ ", " _ _ _      _ _ _      _ _ _ ", " _ _ _      _ _ _      _ _ _ ",
        " _ _ _      _ _ _      _ _ _ ", " _ _ _      _ _ _      _ _ _ ", " _ _ _      _ _ _      _ _ _ ",
        " _ _ _      _ _ _      _ _ _ " };

    bienvenido();
    PlaySound(TEXT("Musica/Inicio.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    while (!finalizar)
    {
        menuPrincipal();

        finalizar = elegir(puntajesMaximos, nombresTop);

        colorFondo(BLACK);
    }
    system("cls");

    return EXIT_SUCCESS;
}