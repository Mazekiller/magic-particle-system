#pragma once

#include <vector>
#include <map>
#include <memory>
#include <utility>

#include <SFML/System/NonCopyable.hpp>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "Emitter.hpp"
#include "Affector.hpp"
#include "MathConstants.hpp"
#include "Bullet.hpp"

///An abstract class for all generators of bullets, lasers and the sort.
/**A generator is a unique kind of Particle System, just that it will be capable of generating
   more than just quads depending on the implementation.
  *It has a set of functions that will be implemented based on needs, but it will cover rendering, affectors, emitters and updating.
  *Uses a large VertexArray to render anything that is renderable depending on the type of generator.
**/

///Note of 20/04/2015, for now I will postpone the project of making it base class for many things and I will program it to work with bullets only.

///Note of 05/05/2015, the class will be non-copyable to ensure that it is used in a high performance matter to avoid unnecessary copies, therefore it will be a moveable only class.

class Generator : public sf::Drawable, private sf::NonCopyable
{
        friend class Emitter;
        friend class Affector;

    public:

        Generator();                                            ///As non-copyable it needs a move constructor defined.
        Generator(Generator&& G);                               ///As non-copyable it needs a move constructor defined.

        void AddEmitter(Emitter &EMT);
        void AddEmitter(Emitter &EMT, sf::Time EMT_Lifespan);

        void AddAffector(Affector &AFT);
        void AddAffector(Emitter &EMT, sf::Time AFT_Lifespan);

        void ClearAffectors();
        void ClearEmitters();
        void ClearRenderObjects();

        void Update();

        void computeBullets();                                  ///<Computes the quads of the bullets based on the sprite sheet held in TextureHolder.

    private:

        void setBulletTypeTextureRects();                                        ///<Starts the BulletType texture map with the values necessary.

    private:

        std::map<Bullet::BulletType,sf::IntRect> BTextRect_Map;                  ///<Contains the texture rects that are accessed using BulletTypes.

        std::vector<Bullet> Bullet_Vec;

        std::vector<std::pair<std::shared_ptr<Emitter>, sf::Time>> EMT_Vec;      ///<Contains a std::pair with a shared pointer to the emitter in question and the time it will remain alive.
        std::vector<std::pair<std::shared_ptr<Affector>, sf::Time>> AFT_Vec;     ///<Contains a std::pair with a shared pointer to the affector in question and the time it will remain alive.

        mutable sf::VertexArray Vertexes_Vec;                                    ///<The VertexArray that will be used to draw all the bullets.
};
