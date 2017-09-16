#ifndef MANA_HPP
#define MANA_HPP


///Clase que define y hace render al mana que esta en la pantalla.
///Ver abajo.


class Mana
{
    public:
        Mana();
        ~Mana();
    protected:
    private:

    ///static Agnar& or Dione& Player;
    ///Todo el mana usa la misma referencia al player para calcular cuando es absorbido.
    ///Debe de haber manejo de lifetime.
    ///El mana vive hasta que es absorbido, despues la memoria es liberada.
    ///Los enemigos y el jugador tienen una referencia a un Collectibles Generator.
    ///El CollectiblesGenerator crea Mana y se encarga de controlar su tiempo de vida.
    ///Un funcionamiento muy similar a un sistema de particulas.
    ///Se puede adaptar el codigo de los thor::Particle Systems.

    ///El Collectibles Generator genera un ManaGenerator y un CurrencyGenerator.
    ///Estos a su vez hacen ejercen sus responsabilidades basados en los enemigos y el jugador.
    ///El CollectiblesGenerator tiene una referencia a todos los enemigos existentes y el jugador.
    ///Cuando el jugador o un enemigo muere estos se encargan de generar mana y/o currency en el area cercana.
    ///El CollectiblesGenerator usa la posicion del jugador y deteccion simple de colisiones.
    ///Para que el jugador "absorba" el mana y el currency respectivamente.
    ///El mana se ve atraido hacia el jugador si esta un poco cerca, el currency no.
    ///Cuando un enemigo muere, se deja intacta la referencia, ya que algunos enemigos son reutilizables.
    ///La referencia se ignora cuando el enemigo esta muerto, si es vuelto a la vida entonces vuelve a tener validez.
    ///El jugador tiene metodos para aumentar la cantidad de mana y currency.
    ///Estos metodos son invocados por los generators en cuestion cuando algun collectible es absorbido.
    ///Si la vida del mana (o currency) se termina antes de ser absorbida esta no aumenta las cantidades respectivas.




};

#endif // MANA_HPP
