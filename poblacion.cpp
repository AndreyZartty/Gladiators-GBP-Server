//
// Created by jose on 13/05/19.
//

#include "poblacion.h"


Poblacion::Poblacion(string _nombrePoblacion)
{
    nombrePoblacion = _nombrePoblacion;
    char vocales [] = {"aeiou"};
    char consonantes [] = {"bcdfghjlmnprstv"};
    string nombre;
    setGeneracion(1);
    for (int i=0; i <10; i++){
        nombre = "";
        Gladiador* gladiador = new Gladiador(getGeneracion());
        for (int i = 3; i > 0; i--){
            int r1 = rand() % 14;
            int r2 = rand() % 4;
            char letra1 = consonantes[r1];
            char letra2 = vocales[r2];
            string s1 (1, letra1);
            string s2 (1, letra2);
            nombre = nombre+s1+s2;
        }
        gladiador->setNombre(nombre);
        insertarGladiador(gladiador);
        insertarCopia(gladiador);
        cout<< "Se ha creado el gladiador: "<< gladiador->getNombre() <<" gen: "<<getGeneracion()<<" resistencia: "<<gladiador->getResistencia()<<endl;
    }
    setMejor();
}

int Poblacion::getGeneracion()
{
    return generacion;
}

void Poblacion::setGeneracion(int Generacion)
{
    generacion = Generacion;
}

void Poblacion::insertarGladiador(Gladiador *gladiador)
{
    gladiadores.insertLast(gladiador);
}

void Poblacion::insertarCopia(Gladiador *gladiador)
{
    copia.insertLast(gladiador);
}

List Poblacion::getGladiadores()
{
    return gladiadores;
}

List Poblacion::getPadres(){
    return padres;
}

void Poblacion::setPadres(){
    //padres.getPointerHead()->set_nxtNd(nullptr);
    //padres.setPointerHead(nullptr);
    padres.vaciar();
    gladiadores.bubbleSort();
    for (int i=8;i>0;i--) {
        padres.insertFirst(gladiadores.recorrer(i));
    }
    /*
    List ltemp = gladiadores;
    Gladiador *gtemp;

    for (int i=8;i>0;i--) {
        gtemp=ltemp.recorrer(0);
        int x;
        for (int j=0;j<ltemp.getSize();j++) {
            if(ltemp.recorrer(j)->getResistencia()>gtemp->getResistencia()){
                gtemp=ltemp.recorrer(j);
                x= j;
            }
        }
        //ltemp.sacar(x);
        padres.insertLast(ltemp.sacar(x));
    }
    */
    for (int h=0;h<padres.getSize();h++) {
        cout<<"ltemp "<<padres.recorrer(h)->getNombre()<<endl;
    }

}

string Poblacion::getNombrePoblacion(){
    return nombrePoblacion;
}

void Poblacion::setMejor(){
    Gladiador* temp;
    mejor=gladiadores.recorrer(0);
    for(int i=0;i<gladiadores.getSize();i++){
        temp = gladiadores.recorrer(i);
        if(temp->getResistencia()>mejor->getResistencia()){
            mejor=temp;
        }
    }
}

Gladiador* Poblacion::getMejor(){
    cout<<"El mejor de la poblacion "<< nombrePoblacion <<" es: "<<mejor->getNombre()<<endl;
    gladiadores.bubbleSort();
    return mejor;
}

void Poblacion::nuevageneracion(){
    //cout<<"oooh1"<<endl;
    setGeneracion(generacion+=1);
    //cout<<generacion<<endl;
    setPadres();

    List *generacion = new List();

    Gladiador* temp;
    for (int i=0;i<gladiadores.getSize();i++) {
        if (gladiadores.recorrer(i)->getEdad()>=70 || gladiadores.recorrer(i)->getMuerto()){

        }else {
            temp = gladiadores.recorrer(i);
            temp->setEdad(temp->getEdad()+15);
            temp->setResistencia();
        }
    }

    char vocales [] = {"aeiou"};
    char consonantes [] = {"bcdfghjlmnprstv"};
    string nombre;

    for (int i=0; i <8; i+=2){
        nombre = "";
        Gladiador* gladiador = new Gladiador(getGeneracion(),padres.recorrer(i),padres.recorrer(i+1));
        for (int i = 3; i > 0; i--){
            int r1 = rand() % 14;
            int r2 = rand() % 4;
            char letra1 = consonantes[r1];
            char letra2 = vocales[r2];
            string s1 (1, letra1);
            string s2 (1, letra2);
            nombre = nombre+s1+s2;
        }
        gladiador->setNombre(nombre);
        gladiador->setNombrePadre1(padres.recorrer(i)->getNombre());
        gladiador->setNombrePadre2(padres.recorrer(i+1)->getNombre());
        insertarGladiador(gladiador);
        insertarCopia(gladiador);
        generacion->insertLast(gladiador);
        cout<< "Se ha creado el gladiador: "<< gladiador->getNombre() <<" gen: "<<getGeneracion()<<" resistencia: "<<gladiador->getResistencia()<<endl;
    }

    for (int i=0; i <8; i+=2){
        nombre = "";
        Gladiador* gladiador = new Gladiador(getGeneracion(),padres.recorrer(i+1),padres.recorrer(i));
        for (int i = 3; i > 0; i--){
            int r1 = rand() % 14;
            int r2 = rand() % 4;
            char letra1 = consonantes[r1];
            char letra2 = vocales[r2];
            string s1 (1, letra1);
            string s2 (1, letra2);
            nombre = nombre+s1+s2;
        }
        gladiador->setNombre(nombre);
        gladiador->setNombrePadre1(padres.recorrer(i+1)->getNombre());
        gladiador->setNombrePadre2(padres.recorrer(i)->getNombre());
        insertarGladiador(gladiador);
        insertarCopia(gladiador);
        generacion->insertLast(gladiador);
        cout<< "Se ha creado el gladiador: "<< gladiador->getNombre() <<" gen: "<<getGeneracion()<<" resistencia: "<<gladiador->getResistencia()<<endl;
    }
    generaciones.push_back(generacion);
    gladiadores.bubbleSort();
}

vector <List*> Poblacion::getGeneraciones() {
    return generaciones;
}