//
// Created by jose on 30/04/19.
//

#include "Gladiador.h"

const string &Gladiador::getId_unico() const {
    return id_unico;
}

void Gladiador::setId_unico(const string &id_unico) {
    Gladiador::id_unico = id_unico;
}

int Gladiador::getEdad() const {
    return edad;
}

void Gladiador::setEdad(int edad) {
    Gladiador::edad = edad;
}

int Gladiador::getProba_sup_nextgen() const {
    return proba_sup_nextgen;
}

void Gladiador::setProba_sup_nextgen(int proba_sup_nextgen) {
    Gladiador::proba_sup_nextgen = proba_sup_nextgen;
}

int Gladiador::getGen_esperadas_sup() const {
    return gen_esperadas_sup;
}

void Gladiador::setGen_esperadas_sup(int gen_esperadas_sup) {
    Gladiador::gen_esperadas_sup = gen_esperadas_sup;
}

const string &Gladiador::getInteligencia_em() const {
    return inteligencia_em;
}

void Gladiador::setInteligencia_em(const string &inteligencia_em) {
    Gladiador::inteligencia_em = inteligencia_em;
}

const string &Gladiador::getCondicion_fis() const {
    return condicion_fis;
}

void Gladiador::setCondicion_fis(const string &condicion_fis) {
    Gladiador::condicion_fis = condicion_fis;
}

int Gladiador::getFuerza_tronco_sup() const {
    return fuerza_tronco_sup;
}

void Gladiador::setFuerza_tronco_sup(int fuerza_tronco_sup) {
    Gladiador::fuerza_tronco_sup = fuerza_tronco_sup;
}

int Gladiador::getFuerza_tronco_inf() const {
    return fuerza_tronco_inf;
}

void Gladiador::setFuerza_tronco_inf(int fuerza_tronco_inf) {
    Gladiador::fuerza_tronco_inf = fuerza_tronco_inf;
}

int Gladiador::getResistencia() const {
    return resistencia;
}

void Gladiador::setResistencia(int resistencia) {
    Gladiador::resistencia = resistencia;
}

Gladiador::Gladiador() {}
