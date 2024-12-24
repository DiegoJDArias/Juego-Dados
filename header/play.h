#pragma once

/* ////////////////////////////////////////////////
  Author DIEGO J D ARIAS - diegojdarias@gmail.com.
*////////////////////////////////////////////////


inline void    colorFondo(unsigned short colores); 
inline void    colorTexto(unsigned short colores);
inline void    posicion(short x, short y) noexcept;
void           ocultarCursor();
bool           elegir(int puntaje[], std::string nombres[]);
int            bloqueadores();
int            generarRandom();
int            tirar(int& x, int bloquer1, int bloquer2, int& e);
void           puntaje(int aleatorio, int& x, int bloquer1, int bloquer2, int& e);
void           ordenarPuntaje(int puntaje[], int n, std::string nombres[]);
void           play(int puntaje[], std::string nombres[], int n);
void           movimientoDados(int x, int y);
bool           sonIguales(int arr[], int n);
short          centrar(const std::string& nombre, short y = 29);

enum Color : unsigned short {
    BLACK             = 0x0000,/*Used*/
    RED               = 0x0004,/*Used*/
    YELLOW            = 0x0006,/*Used*/
    WHITE             = 0x0007,/*Used*/
    LIGTH_PURPLE      = 0x000D,/*Used*/
    WHITE_BRG         = 0x000F,/*Used*/
    BG_BLACK          = 0x0010,/*Used*/
    BG_BLUE           = 0x0011,/*Used*/
    BG_GREEN          = 0x0012,/*Used*/
    BG_RED            = 0x0014,/*Used*/
    BG_PURPLE         = 0x0015,/*Used*/
    BG_GREY           = 0x0018,/*Used*/
    BG_LIGHT_BLUE     = 0x0019,/*Used*/
    BG_WHITE_BRG      = 0x001F /*Used*/
};