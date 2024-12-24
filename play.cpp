#include <Windows.h>
#include <iostream>

#include "header/play.h"
#include "header/menu.h"

/* ////////////////////////////////////////////////
  Author DIEGO J D ARIAS - diegojdarias@gmail.com.
*////////////////////////////////////////////////


inline void colorFondo(unsigned short colores) {
    HANDLE hConsola{ GetStdHandle(STD_OUTPUT_HANDLE) };
    CONSOLE_SCREEN_BUFFER_INFO color;

    GetConsoleScreenBufferInfo(hConsola, &color);
    SetConsoleTextAttribute(hConsola, (color.wAttributes & 0xFF0F) | (colores << 4));
}

inline void colorTexto(unsigned short colores) {
    HANDLE color{ GetStdHandle(STD_OUTPUT_HANDLE) };

    SetConsoleTextAttribute(color, colores);
}

inline void posicion(short x, short y) noexcept {

    HANDLE hConsola{ GetStdHandle(STD_OUTPUT_HANDLE) };
    COORD posicionXY{ x, y };

    SetConsoleCursorPosition(hConsola, posicionXY);
}

void ocultarCursor() {
    HANDLE hConsola{ GetStdHandle(STD_OUTPUT_HANDLE) };
    
    CONSOLE_CURSOR_INFO cursor{};
    cursor.dwSize = 50;
    cursor.bVisible = FALSE;

    SetConsoleCursorInfo(hConsola, &cursor);
}

bool elegir(int puntaje[], std::string nombres[]) {

    int opcion{ ingreseOpcion() };

    switch (opcion)
    {
    case 1:
        play(puntaje, nombres, 1);
        break;
    case 2:
        play(puntaje, nombres, 2);
        break;
    case 3:
        estadisticas(puntaje, nombres);
        break;
    case 4:
        creditos();
        break;
    case 0:
        return salir();
    default:
        opcionIncorrecta();
        break;
    }

    return false;
}

int bloqueadores() {

    int aleatorio{ generarRandom() };

    return aleatorio;
}

int generarRandom() {

    int aleatorio{ rand() % 6  + 1 };

    return aleatorio;
}

int tirar(int& x, int bloquer1, int bloquer2, int& e) {

    int aleatorio{ generarRandom() }, b1{ bloquer1 }, b2{ bloquer2 };

    puntaje(aleatorio, x, b1, b2, e);

    return aleatorio;
}

void puntaje(int aleatorio, int& x, int bloquer1, int bloquer2, int& e) {
    
    if ((aleatorio != bloquer1) && (aleatorio != bloquer2))
    {
        x += aleatorio;
    }
    else
    {
        e--;
    }
}

void ordenarPuntaje(int puntaje[], int n, std::string nombres[]) {

    for (int i = 0; i < n - 1; ++i) 
    {
        for (int j = i + 1; j < n; ++j) 
        {
            if (puntaje[i] < puntaje[j]) 
            {
                int temp = puntaje[i];
                std::string temN = nombres[i]; 
                puntaje[i] = puntaje[j];
                nombres[i] = nombres[j];
                puntaje[j] = temp;
                nombres[j] = temN;
            }
        }
    }
}

void play(int puntaje[], std::string nombres[], int n) {

    std::string nombre1, nombre2, jugadores[2]{};
    int blocker[2]{}, puntos[2]{}, puntoTotales[2]{}, dados[5]{}, rondajugador1[5]{}, rondajugador2[5]{};
    int cantidadJugadores{ n }, cBonus[2]{}, mejorTiro[2]{}, puntosPerdidos[2]{}, puntosDobles[2]{};
    char datos;

    cuadroMayor();  // PARA REFRESCAR EL INGRESO.

    if (cantidadJugadores == 1) // SEGUN LA ELECCION SE DEFINE UNO O DOS JUGADORES.
    {
        ingreseNombre(nombre1, 1);
        jugadores[0] = nombre1;
    }
    else
    {
        ingreseNombre(nombre1, 1);
        ingreseNombre(nombre2, 2);
  
        jugadores[0] = nombre1;
        jugadores[1] = nombre2;
    }
    
    PlaySound(TEXT("Musica/Loop.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    for (int i{ 1 }; i < 6; ++i)
    {
        if (i == 1)   // SI ES LA PRIMERA VEZ QUE SE ENTRA, GENERA LA PANTALLA PRINCIPAL DEL JUEGO.
        {
            principalGame();
        }
        else
        {
            blockers();
            cuadroMenor();
        }

        for (int turno{}; turno < cantidadJugadores; ++turno) // SE ASIGNA LOS TURNOS PARA LOS JUGADORES.
        { 
            bool continuar{ true }, blockerGenerados{ false };
            int dadosActivos{ 5 }, eliminado{ 5 };

            if (turno == 0) 
            {
                cuadroMenor();
                blockers();
                scoredCard(turno);
                menuScore(jugadores[turno], puntoTotales[turno], rondajugador1, turno, i);
            } 
            else 
            {
                cuadroMenor();
                blockers();
                scoredCard(turno);
                menuScore(jugadores[turno], puntoTotales[turno], rondajugador2, turno, i); 
            }

            while (continuar)
            {
                bool bonus{ false };
                int cBlocker{};

                if (!blockerGenerados)  // SE CREA LOS BLOCKERS POR PRIMERA VEZ EN CADA RONDA.
                {
                    constexpr int y{ 5 };
                    int x{ 9 };
                    
                    generarBlocker(i, jugadores[turno]);  // MENSAJE DE GENERAR BLOCKERS.
                    cuadroMenor();
                    
                    for (int j{}; j < 2; ++j) // SE CREAN LOS BLOCKERS
                    {
                        for (int k{}; k < 1; ++k)
                        {
                            blocker[j] = bloqueadores();
                            movimientoDados(x, y); 
                            dibujarDados(blocker[j], x, y);
                        }
                        x += 13;
                    }  
                    blockerGenerados = !blockerGenerados;
                }

                cuadroMenor();
                tirarDados();

                if (dadosActivos != 0) // SI HAY DADOS ACTIVOS, SE PROCEDE A JUGAR!.
                {
                    constexpr int y{ 23 };
                    int x{ 41 };

                    for (int j{}; j < dadosActivos; ++j)
                    {
                        for (int k{}; k < 1; ++k) 
                        {
                            dados[j] = tirar(puntos[turno], blocker[0], blocker[1], eliminado);  // SE TIRAN LOS DADOS.
                            movimientoDados(x, y);

                            if (dados[j] == blocker[0] || dados[j] == blocker[1])  // SE COMPRUEBA SI ESTAN BLOQUEADOS.
                            {
                                dibujarDados(dados[j], x, y, true);
                                posicion(x + 1, y - 2); colorFondo(BG_RED); std::cout << "BLOCKED";
                                cBlocker++;
                            } 
                            else 
                            {
                                dibujarDados(dados[j], x, y);
                            }
                            colorTexto(WHITE); colorFondo(BG_PURPLE);
                        }
                        x += 9;
                    } 
                }

                if (turno == 0)  // SE SUMAN LOS PUNTOS SEGUN JUGADOR.
                {
                    if (cBlocker == 0)
                    {
                        if (dadosActivos != 1)
                        {
                            if (sonIguales(dados, (dadosActivos))) // AQUI HACEMOS LA COMPROBACIONES, Y EL BONUS MOSTRAMOS.
                            {
                                constexpr int y{ 21 };
                                int x{ 41 };

                                puntos[turno] = (puntos[turno] * 2);
                                rondajugador1[i - 1] += puntos[turno];
                                puntosDobles[turno] += puntos[turno];
                                bonus = !bonus;

                                for (int j{}; j < (dadosActivos); ++j)
                                {
                                    posicion(x, y); colorFondo(BG_GREEN); std::cout << "BONUS-X2";                                                  
                                    x += 9;
                                }
                                cBonus[turno]++; // CONTAMOS LOS BONUS GANADOS, CANTIDAD DE BONUS. 
                            }
                            else
                                rondajugador1[i - 1] += puntos[turno];
                        }
                        else
                            rondajugador1[i - 1] += puntos[turno];
                    }
                    else
                        rondajugador1[i - 1] += puntos[turno];
                }
                else
                {
                    if (cBlocker == 0)
                    {
                        if (dadosActivos != 1)
                        {
                            if (sonIguales(dados, (dadosActivos))) // AQUI HACEMOS LA COMPROBACIONES, Y EL BONUS MOSTRAMOS.
                            {
                                constexpr int y{21};
                                int x{ 41 };

                                puntos[turno] = (puntos[turno] * 2);
                                rondajugador2[i - 1] += puntos[turno];
                                puntosDobles[turno] += puntos[turno];
                                bonus = !bonus;

                                for (int j{}; j < (dadosActivos); ++j)
                                {
                                    posicion(x, y); colorFondo(BG_GREEN); std::cout << "BONUS-X2";
                                    x += 9;
                                }
                                cBonus[turno]++; // CONTAMOS LOS BONUS GANADOS, CANTIDAD DE BONUS. 
                            }
                            else
                                rondajugador2[i - 1] += puntos[turno];
                        }
                        else
                            rondajugador2[i - 1] += puntos[turno];
                    }
                    else
                        rondajugador2[i - 1] += puntos[turno];
                }
                
                dadosActivos = eliminado;

                if (dadosActivos == 0)  // SI SE ELIMINA EL ULTIMO DADO DE LA RONDA, SE RESETEA EL PUNTAJE A CERO DE LA RONDA ACTUAL.
                {
                    if (turno == 0) 
                    {
                        puntosPerdidos[turno] += rondajugador1[i - 1]; // TODO: ESTAMOS REALIZANDO ESTO
                        puntoTotales[turno] -= rondajugador1[i - 1]; 
                        rondajugador1[i - 1] = 0;
                        puntos[turno] = 0;

                        scoredCard(turno); 
                        menuScore(jugadores[turno], puntoTotales[turno], rondajugador1, turno, i);
                        roundPerdida();
                    } 
                    else 
                    {
                        puntosPerdidos[turno] += rondajugador2[i - 1]; // TODO: ESTAMOS REALIZANDO ESTO
                        puntoTotales[turno] -= rondajugador2[i - 1];
                        rondajugador2[i - 1] = 0; 
                        puntos[turno] = 0;

                        scoredCard(turno);
                        menuScore(jugadores[turno], puntoTotales[turno], rondajugador2, turno, i);
                        roundPerdida();
                    }
                    break;
                }
                
                puntoTotales[turno] += puntos[turno]; // AQUI //////////////////////////////////

                if (turno == 0)  // SE ACTUALIZA LOS PUNTOS.
                {
                    menuScore(jugadores[turno], puntoTotales[turno], rondajugador1, turno, i);
                } 
                else 
                {
                    menuScore(jugadores[turno], puntoTotales[turno], rondajugador2, turno, i);
                }
                
                datos = continuamos(puntos[turno], bonus); // AQUI //////////////////////////////////

                if ((datos != 's') && (datos != 'S'))  // SE CONSULTA SI CONTINUA LA PARTIDA.
                {
                    continuar = !continuar;

                    blockers();
                    cuadroMenor();
                } 
                cuadroMenor();

                if (puntos[turno] > mejorTiro[turno])
                    mejorTiro[turno] = puntos[turno];

                puntos[turno] = 0;
            }
        }
    }

    for (int indice{}; indice < cantidadJugadores; ++indice) // SE ACOMODAN LOS PUNTAJES PARA ESTADISTICA
    { 
        if (cantidadJugadores == 1) 
        {
            puntaje[9] = puntoTotales[indice];
            nombres[9] = jugadores[indice];
        } 
        else 
        {
            puntaje[8 + indice] = puntoTotales[indice];
            nombres[8 + indice] = jugadores[indice];
        }
    }

    if (cantidadJugadores == 1)
    {
        resumen(jugadores[0], puntoTotales[0], rondajugador1, cBonus, 0, mejorTiro, puntosPerdidos, puntosDobles);
    }
    else
    {
        resumen(jugadores[0], puntoTotales[0], rondajugador1, cBonus, 0, mejorTiro, puntosPerdidos, puntosDobles);
        resumen(jugadores[1], puntoTotales[1], rondajugador2, cBonus, 1, mejorTiro, puntosPerdidos, puntosDobles);

        if (puntoTotales[0] > puntoTotales[1])  // QUIEN ES EL GANADOR
            ganador(jugadores[0]);
        else
            ganador(jugadores[1]);
    }
    
    ordenarPuntaje(puntaje, 10, nombres);
    estadisticas(puntaje, nombres);
    cuadroMayor();
    PlaySound(TEXT("Musica/Inicio.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
}

void movimientoDados(int x, int y) {

    for (int j{}; j < 100; ++j) {
        dibujarDados(6, x, y);
        dibujarDados(5, x, y);
        dibujarDados(4, x, y);
        dibujarDados(3, x, y);
        dibujarDados(2, x, y);
        dibujarDados(1, x, y);
    }
}

bool sonIguales(int arr[], int n) {
    for (int i{ 1 }; i < n; ++i) {
        if (arr[i] != arr[0]) {
            return false; 
        }
    }
    return true;
}

short centrar(const std::string& nombre, short y) {

    std::size_t largo{ nombre.length() };
    short x{ (y - static_cast<short>(largo)) / 2 };

    return x;
}