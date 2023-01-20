#ifndef _PARTICULAS_H_
#define _PARTICULAS_H_

#include <Gosu/Gosu.hpp>

#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include "animation.h"
#include "log.h"

#include <ctime>
#include <vector>

#define lim 0.70

struct Particula{

    float angulo;

    float distancia;

    float tamanyo;

    int duracion;
    
    boost::shared_ptr<Gosu::Image> imagen;

    Gosu::Color color;

    int pasoActual;

    float posX;

    float posY;

    float posTemp;

    float coefTam;

    Particula(float angulo,
              float distancia,
              float tamanyo,
              int duracion,
              boost::shared_ptr<Gosu::Image> img,
              Gosu::Color color) :
        angulo(angulo),
        distancia(distancia),
        tamanyo(tamanyo),
        duracion(duracion),
        imagen(img),
        color(color),
        pasoActual(0),
        posX(0),
        posY(0){
	
    }
    void update(){
        if(pasoActual != duracion){
            pasoActual ++;
        }

        posTemp = Animacion::easeOutQuart(pasoActual, 0, 1, duracion); 

        if(posTemp >= lim){
            color.setAlpha ( 255 * (1 - (posTemp - lim) / (1 - lim)));
        }else{
            color.setAlpha(255);
        }

        coefTam = tamanyo * (1 - posTemp);
	
        posX = Gosu::offsetX(angulo, posTemp * distancia) 
            - imagen -> width() * coefTam / 2;
        posY = Gosu::offsetY(angulo, posTemp * distancia) 
            - imagen -> height() * coefTam / 2;

        
    }

    void draw(int oX, int oY){
        imagen -> draw(oX + posX, oY + posY, 7, coefTam, coefTam, color, Gosu::amAdditive);
    }

    float estado(){
        return (float)pasoActual / (float)duracion;
    }
};


class SistemaParticulas{
    /// Destino gráfico donde dibujar las partículas
    Gosu::Graphics * g;

    /// Cantidad de partículas a mostrar
    unsigned cantidadParticulas;

    /// Duración del efecto
    float duracion;

    /// Posición de la animación
    float pasoActual;

    /// Distancia del efecto
    float distancia;

    /// Escala de la explosión
    float escala;

    /// Color de las partículas
    Gosu::Color color;

    /// Imágenes de las partículas
    boost::shared_ptr<Gosu::Image> partc1, partc2;

    /// Contenedor para las partículas
    vector<boost::shared_ptr<Particula> > vectorParticulas;

    /// Flag que indica si el sistema de partícula está activo
    bool activo;

    /// Posición donde se debe pintar
    int x, y;
public:
    SistemaParticulas(Gosu::Graphics * g, 
                      unsigned cantidadParticulas, 
                      unsigned duracion, 
                      int x,
                      int y,
                      unsigned distancia=200, 
                      float escala=1, 
                      Gosu::Color color = Gosu::Color::WHITE) : 
        g(g), 
        cantidadParticulas(cantidadParticulas), 
        duracion(duracion), 
        distancia(distancia), 
        escala(escala), 
        color(color),
        x(x), y(y){

        activo = true;


	
        partc1 . reset(new Gosu::Image(*g, L"media/partc1.png"));
        partc2 . reset(new Gosu::Image(*g, L"media/partc2.png"));

        pasoActual = 0;

        vectorParticulas.reserve(cantidadParticulas);

        for (size_t i = 0; i < cantidadParticulas; ++i)
        {
            vectorParticulas.push_back(boost::shared_ptr<Particula>(nuevaPartc()));
        }

    }

    Particula * nuevaPartc(){
        return new Particula(Gosu::random(0,360),
                             Gosu::random(0, 1) * distancia,
                             Gosu::random(0, escala),
                             Gosu::random(0.1, 1) * duracion,
                             (Gosu::random(0,1)? partc1 : partc2),
                             color);
    }

    bool ended(){
        return !activo;
    }

    void draw(){

        if(++pasoActual < duracion){
            for (unsigned i = 0; i < cantidadParticulas; ++i){
                vectorParticulas[i] -> update();
                vectorParticulas[i] -> draw(x,y);
            }            
        }else{
            activo = false;
        }
    }
};

#endif /* _PARTICULAS_H_ */
