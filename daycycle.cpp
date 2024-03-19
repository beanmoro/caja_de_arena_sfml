#include "include.h"
#include "game.h"

void Game::dayCycle(){

    // -- Variables Utiles -- //

    int actualTime = gameTime.asMilliseconds();
    int dayTime = (actualTime - ( tpd*days));

    // -- Contar Dias -- //

    if( dayTime >= tpd){days++;}

    // -- Establecer cuando dura cada medida de tiempo segun los ticks del TPD -- //

    hours = dayTime/tph;
    minutes = dayTime/tpm-(hours*60);
    seconds = dayTime/tps-((minutes*60)+(hours*60*60));

    // -- Mitad Dia Mita Noche -- //

    if(  dayTime < tpd/2 ){

        r = (dayTime/rpd);
        g = (dayTime/gpd);
        b = (dayTime/bpd);

    }else if(dayTime > tpd/2){

        r = (tpd-dayTime)/rpd;
        g = (tpd-dayTime)/gpd;
        b = (tpd-dayTime)/bpd;
    }

    // -- Medida de Seguridad Anti Errores -- //

    if(r < 0){ r = 0;}else if(r > rLimit){ r = rLimit;}
    if(g < 0){ g = 0;}else if(g > gLimit){ g = gLimit;}
    if(b < 0){ b = 0;}else if(b > bLimit){ b = bLimit;}

    if(hours > 23){ hours = 0;}
    if(minutes > 59){ minutes = 0;}
    if(seconds > 59){ seconds = 0;}


}
