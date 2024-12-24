#pragma once
#pragma execution_character_set("utf-8")

/* ////////////////////////////////////////////////
  Author DIEGO J D ARIAS - diegojdarias@gmail.com.
*////////////////////////////////////////////////


void    menuPrincipal();
void    dibujarMarco(int posx, int posy, bool blocked);
void    ingreseNombre(std::string& nombre, int numero);
void    cuadroMayor();
void    cuadroMenor();
void    cuadroMenuCentro();
void    blockers();
void    scoredCard(int turno = 0);
void    dibujarCuadrados(int posx, int posy, bool blocked);
void    dibujarDados(int numero, int posx, int posy, bool blocked = false);
void    cuadroMenu();
void    principalGame();
char    continuamos(int puntos, bool bonus);
void    menuScore(const std::string& nombre, int puntosTotales, int round[], int turno, int i);
void    roundPerdida();
void    estadisticas(int puntaje[], std::string nombres[]);
void    creditos();
void    bienvenido();
int     ingreseOpcion();
void    opcionIncorrecta();
bool    salir();
void    generarBlocker(int i, const std::string& nombre);
void    nombreScored(const std::string& nombre, int turno);
void    mostrarPuntosRonda(int puntos, bool bonus);
void    mostrarJugador(const std::string& nombre);
void    tirarDados();
void    resumen(
	    const std::string& nombre, 
	    int puntosTotales, 
	    int round[], 
	    int cBonus[], 
	    int turno, 
	    int mejorTiro[], 
	    int puntosPerdido[], 
	    int puntosDobles[]
);
void    cuadroResumen(int turno);
void    ganador(const std::string& nombre);