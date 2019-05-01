//
// Created by jose on 30/04/19.
//

#ifndef GLADIATORS_GBP_SERVER_GLADIADOR_H
#define GLADIATORS_GBP_SERVER_GLADIADOR_H

#include <string>
using namespace std;

class Gladiador {

private:
    string id_unico;
    int edad;
    int proba_sup_nextgen;
    int gen_esperadas_sup;
    string inteligencia_em;
    string condicion_fis;
    int fuerza_tronco_sup;
    int fuerza_tronco_inf;
    int resistencia;
public:
    Gladiador();

    const string &getId_unico() const;

    void setId_unico(const string &id_unico);

    int getEdad() const;

    void setEdad(int edad);

    int getProba_sup_nextgen() const;

    void setProba_sup_nextgen(int proba_sup_nextgen);

    int getGen_esperadas_sup() const;

    void setGen_esperadas_sup(int gen_esperadas_sup);

    const string &getInteligencia_em() const;

    void setInteligencia_em(const string &inteligencia_em);

    const string &getCondicion_fis() const;

    void setCondicion_fis(const string &condicion_fis);

    int getFuerza_tronco_sup() const;

    void setFuerza_tronco_sup(int fuerza_tronco_sup);

    int getFuerza_tronco_inf() const;

    void setFuerza_tronco_inf(int fuerza_tronco_inf);

    int getResistencia() const;

    void setResistencia(int resistencia);

};


#endif //GLADIATORS_GBP_SERVER_GLADIADOR_H
