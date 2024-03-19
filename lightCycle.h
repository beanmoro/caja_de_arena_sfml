#ifndef LIGHTCYCLE_H_INCLUDED
#define LIGHTCYCLE_H_INCLUDED

class lightCycle{


public:

    lightCycle( int _rl, int _gl, int _bl, int _tpd);
    void lc_Step();
    int lc_getColors(int col);


};

#endif // LIGHTCYCLE_H_INCLUDED
