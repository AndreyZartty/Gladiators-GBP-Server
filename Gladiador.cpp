
#include "Gladiador.h"

#include <math.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <cstdlib>
#include <strings.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <json-c/json.h>
#include <json-c/debug.h>
#include <json-c/json_object.h>
#include "list.h"

#define PORT 3550
#define MAXDATASIZE 1000

using namespace std;

string decToBinary(int n)
{
    // Size of an integer is assumed to be 32 bits
    string res;
    for (int i = 3; i >= 0; i--) {
        int k = n >> i;
        if (k & 1)
            res+="1";
        else
            res+= "0";
    }
    return res;
}

int binToDec(int binario)
{
    int exp,digito;
    int decimal;
    //cout << "Binario: "<< binario<<endl;

    exp=0;
    decimal=0;
    while(((int)(binario/10))!=0)
    {

        digito = (int)binario % 10;
        decimal = decimal + digito * pow(2,exp);
        exp++;
        binario=(int)(binario/10);
    }
    decimal=decimal + binario * pow(2,exp);
    //cout << endl << "Decimal: " << decimal << endl;
    return decimal;
}

/**
 * Representa un Gladiador
 *
 * @since 30/04/19
 */


Gladiador::Gladiador() {
    current = new Vector2(0, 0);
    target = new Vector2(9,9);
}

Gladiador::Gladiador(int generacion)
{
    if (generacion == 1){
        //srand (time(NULL));
        int random = 15 + rand() % (61 - 15);
        setEdad(random);
        random = 1 + rand() % (5 - 1);

        setInteligencia(random);
        random = 1 + rand() % (5 - 1);

        setCondicionFisica(random);
        random = 1 + rand() % (5 - 1);

        setFuerzaSuperior(random);
        random = 1 + rand() % (5 - 1);

        setFuerzaInferior(random);
        setResistencia();
        setExpectativaVida(getResistencia()/10);
        setProbabilidadSupervivencia(getResistencia()-4);
        SendJson();
    }
    else {
        cout << "Introduzca los padres si no es la primera generacion" << endl;
    }
}

void Gladiador::mutacion(string *gen){
    cout<<"mutacion de gen: "<<*gen;
    int random = rand() % 2;
    if (random==1){
        if(gen->substr(0,1)=="1"){
            *gen="0"+gen->substr(1,2);
        }else {
            *gen="1"+gen->substr(1,2);
        }
    }else {
        if(gen->substr(1,2)=="1"){
            *gen=gen->substr(0,1)+"0";
        }else {
            *gen=gen->substr(0,1)+"1";
        }
    }
    cout<<" a: "<<*gen<<endl;
}

Gladiador::Gladiador(int generacion, Gladiador *padre1, Gladiador *padre2)
{
    int random1 = 1 + rand() % (100-1);
    if (generacion == 1){
        cout << "No introduzca padres, ya que no es de la primera generacion" << endl;
    }
    else {
        string cromosomaInte1 = decToBinary(padre1->getInteligencia()).substr(0,2);
        string cromosomaInte2 = decToBinary(padre2->getInteligencia()).substr(2,4);
        string cromosomaCond1 = decToBinary(padre1->getCondicionFisica()).substr(0,2);
        string cromosomaCond2 = decToBinary(padre2->getCondicionFisica()).substr(2,4);
        string cromosomaFuerzaSup1 = decToBinary(padre1->getFuerzaSuperior()).substr(0,2);
        string cromosomaFuerzaSup2 = decToBinary(padre2->getFuerzaSuperior()).substr(2,4);
        string cromosomaFuerzaInf1 = decToBinary(padre1->getFuerzaInferior()).substr(0,2);
        string cromosomaFuerzaInf2 = decToBinary(padre2->getFuerzaInferior()).substr(2,4);
        string *arr[]={&cromosomaInte1,&cromosomaInte2,&cromosomaCond1,&cromosomaCond2,&cromosomaFuerzaSup1,&cromosomaFuerzaSup2,&cromosomaFuerzaInf1,&cromosomaFuerzaInf2};
        //cout<<padre1->getInteligencia()<<endl;
        //cout<<cromosomaInte1<<endl;
        if (random1<=5){
            int random2 = 0 + rand() % (7-0);
            mutacion(arr[random2]);
        }
        setInteligencia(binToDec(atoi((cromosomaInte1+cromosomaInte2).c_str())));
        setCondicionFisica(binToDec(atoi((cromosomaCond1+cromosomaCond2).c_str())));
        setFuerzaSuperior(binToDec(atoi((cromosomaFuerzaSup1+cromosomaFuerzaSup2).c_str())));
        setFuerzaInferior(binToDec(atoi((cromosomaFuerzaInf1+cromosomaFuerzaInf2).c_str())));
        setEdad(20);
        setResistencia();
        setExpectativaVida(getResistencia()/10);
        setProbabilidadSupervivencia(getResistencia()-4);
        SendJson();
    }
}

void Gladiador::setNombre(string Nombre)
{
    nombre = Nombre;
}

void Gladiador::setEdad(int Edad)
{
    edad = Edad;
}

void Gladiador::setProbabilidadSupervivencia(int PS)
{
    probabilidadSupervivencia = PS;
}

void Gladiador::setExpectativaVida(int EV)
{
    expectativaVida = EV;
}

void Gladiador::setInteligencia(int Inteligencia)
{
    inteligencia = Inteligencia;
}

void Gladiador::setCondicionFisica(int CF)
{
    condicionFisica = CF;
}

void Gladiador::setFuerzaSuperior(int FS)
{
    fuerzaSuperior = FS;
}

void Gladiador::setFuerzaInferior(int FI)
{
    fuerzaInferior = FI;
}

void Gladiador::setResistencia()
{
    int resist=0;
    if(70<=edad){
        muerto=true;
    }

    else {
        if(25 <= edad && edad <= 45){
            resist += 20;
        }
        else if (25 > edad){
            resist += 15;
        }
        else if (45 < edad){
            resist += 10;
        }
        resist += 2*inteligencia;
        resist += 2*condicionFisica;
        resist += 2*fuerzaInferior;
        resist += 2*fuerzaSuperior;
    }

    resistencia = resist;
    //cout <<"resistencia de " << nombre << ": " <<resistencia << endl;
    //cout <<"edad: "<< edad << endl;
}

void Gladiador::morir(){
    muerto=true;
}

bool Gladiador::getMuerto(){
    return muerto;
}

string Gladiador::getNombre()
{
    return nombre;
}

int Gladiador::getEdad()
{
    return edad;
}

int Gladiador::getProbabilidadSupervivencia()
{
    return probabilidadSupervivencia;
}

int Gladiador::getExpectativaVida()
{
    return expectativaVida;
}

int Gladiador::getInteligencia()
{
    return inteligencia;
}

int Gladiador::getCondicionFisica()
{
    return condicionFisica;
}

int Gladiador::getFuerzaSuperior()
{
    return fuerzaSuperior;
}

int Gladiador::getFuerzaInferior()
{
    return fuerzaInferior;
}

int Gladiador::getResistencia()
{
    return resistencia;
}
int Gladiador::SendJson()
{
    /*char* str;
    int fd, numbytes;
    struct sockaddr_in client;

    fd = socket(AF_INET, SOCK_STREAM, 0);

    char buf[MAXDATASIZE];

    struct hostent *he;

    if (fd < 0)
    {
        printf("Error : Could not create socket\n");
        return 1;
    }
    else
    {
        client.sin_family = AF_INET;
        client.sin_port = htons(PORT);
        client.sin_addr.s_addr = inet_addr("192.168.100.28");
        memset(client.sin_zero, '\0', sizeof(client.sin_zero));
    }

    if (::connect(fd, (const struct sockaddr *)&client, sizeof(client)) < 0)
    {
        printf("ERROR connecting to server\n");
        return 1;
    }

    json_object *jobj = json_object_new_object();

    string auxNombre = nombre;
    int n = auxNombre.length();
    char nombreJson[n + 1];
    strcpy(nombreJson, auxNombre.c_str());

    string auxEdad= to_string(edad);
    n = auxEdad.length();
    char edadJson[n + 1];
    strcpy(edadJson, auxEdad.c_str());

    string auxPS = to_string(probabilidadSupervivencia);
    n = auxPS.length();
    char PSJson[n + 1];
    strcpy(PSJson, auxPS.c_str());

    string auxEV = to_string(expectativaVida);
    n = auxEV.length();
    char EVJson[n + 1];
    strcpy(EVJson, auxEV.c_str());

    string auxIntelig = to_string(inteligencia);
    n = auxIntelig.length();
    char inteligJson[n + 1];
    strcpy(inteligJson, auxIntelig.c_str());

    string auxCF = to_string(condicionFisica);
    n = auxCF.length();
    char CFJson[n + 1];
    strcpy(CFJson, auxCF.c_str());

    string auxFS = to_string(fuerzaSuperior);
    n = auxFS.length();
    char FSJson[n + 1];
    strcpy(FSJson, auxFS.c_str());

    string auxFI = to_string(fuerzaInferior);
    n = auxFI.length();
    char FIJson[n + 1];
    strcpy(FIJson, auxFI.c_str());

    string auxResist = to_string(resistencia);
    n = auxResist.length();
    char resistJson[n + 1];
    strcpy(resistJson, auxResist.c_str());
    for (int i = 0; i < n; i++)
        cout << nombreJson[i];

    json_object *jstring = json_object_new_string(nombreJson);
    json_object *jstring2 = json_object_new_string(edadJson);
    json_object *jstring3 = json_object_new_string(PSJson);
    json_object *jstring4 = json_object_new_string(EVJson);
    json_object *jstring5 = json_object_new_string(inteligJson);
    json_object *jstring6 = json_object_new_string(CFJson);
    json_object *jstring7 = json_object_new_string(FSJson);
    json_object *jstring8 = json_object_new_string(FIJson);
    json_object *jstring9 = json_object_new_string(resistJson);

    json_object_object_add(jobj,"Nombre", jstring);
    json_object_object_add(jobj,"Edad", jstring2);
    json_object_object_add(jobj,"ProbabilidadSupervivencia", jstring3);
    json_object_object_add(jobj,"ExpectativaVida", jstring4);
    json_object_object_add(jobj,"Inteligencia", jstring5);
    json_object_object_add(jobj,"CondicionFisica", jstring6);
    json_object_object_add(jobj,"FuerzaSuperior", jstring7);
    json_object_object_add(jobj,"FuerzaInferior", jstring8);
    json_object_object_add(jobj,"Resistencia", jstring9);



    if (strcpy(buf, json_object_to_json_string(jobj)) == NULL) {
        printf("ERROR strcpy()");
        exit(-1);
    }

    if (write(fd, buf, strlen(buf)) == -1)
    {
        printf("ERROR write()");
        exit(-1);
    }

    printf("Written data\n");

    memset(buf, 0, MAXDATASIZE);

    ::close(fd);*/
}