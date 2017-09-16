#include "Player.hpp"

#include <string>
#include <vector>

#pragma once

#ifndef EPSILON
#define EPSILON 0.0001
#endif

///Respecto a la dificultad:

/*Funcion global para todas las cosas que lo necesiten.
 *La dificultad se define en uno de los play states.
 *Es un campo accessible a casi todo el mundo.
 *Variable estatica de la mayoria de las clases que la ocupan (Una referencia no tiene sentido).
 *Podria ser heredada de una mini-clase base que solo tiene esas funciones, no necesita polimorfismo.
 */


class Enemy : public Characters
{
  public:

    Enemy(const float hitPoints = 0.0, const float sp = 0.0);

    virtual ~Enemy();

    //Player* Main; ///Para verificar lo que hace el jugador y responder a sus acciones directamente.

    float getHitPoints() const;

    //static Difficulty getCurrentDifficulty(); ///Modifica la variable estatica para trabajo que requiera de dificultad.
    //static Difficulty D; ///No tiene uso aun.

    void selfDamage(); ///Funcion que se encarga de hacer dano a la entidad si esta esta siendo atacada.

    bool isBeingAttacked(); ///Verifica si esta siendo atacado y setea la booleana segun corresponde.
    ///El efecto visual de cuando esta siendo atacado es dado por los disparos del jugador.

    virtual bool isDead();

    virtual void Die() = 0;

  protected:
    float HitPoints;     ///Vida
    bool BeingAttacked;

};

class CommonEnemy : public Enemy, public sf::Drawable
{
    public:
        CommonEnemy();
        ~CommonEnemy();

};












