#pragma once

#include <vector>
#include <array>
#include <map>
#include <memory>
#include <utility>

#include <SFML/System/NonCopyable.hpp>

#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/VertexArray.hpp>

#include "Emitter.hpp"
#include "AffectorDefinitions.hpp"
#include "MathConstants.hpp"
#include "Bullet.hpp"
#include "TextureHolder.hpp"

///An abstract class for all generators of bullets, lasers and the sort.
/**A generator is a unique kind of Particle System, just that it will be capable of generating
   more than just quads depending on the implementation.
  *It has a set of functions that will be implemented based on needs, but it will cover rendering, affectors, emitters and updating.
  *Uses a large VertexArray to render anything that is renderable depending on the type of generator.
**/

///Note of 20/04/2015, for now I will postpone the project of making it base class for many things and I will program it to work with bullets only.

///Note of 05/05/2015, the class will be non-copyable to ensure that it is used in a high performance matter to avoid unnecessary copies, therefore it will be a moveable only class.
///Note of 07/05/2015 The class will not use shared pointers, since the ownership of the resources will be held by another class. Instead it will use normal pointers to refer to the emitters and affectors.

///Note of 26/05/2015, finished the texture rect setter method, must work on the update function, the quad computation, transformations and rendering.

///Note of 01/07/2015, the architecture of the fully functional system will be to have all the emission related algorithms in the emit function.
///For testing purposes before the full implementation of emitter functionality, the inner workings of the emit function (no longer virtual by the end of testing) will remain in the update function.
///The emit function will stop being a call to create a bullet, instead it will become a control system with an emission cue and emission control chronometer.

class Generator : public sf::Drawable, private sf::NonCopyable
{
        //friend class Emitter;
        friend class Affector;

    public:

        Generator();                                            ///As non-copyable it needs a default constructor defined.
        Generator(const sf::Texture& T);                        ///Receives a reference to the TextureHolder to allocate textures automatically.
        Generator(Generator&& G);                               ///As non-copyable it needs a move constructor defined.

        Generator& operator=(Generator&& G);

        void AddEmitter(const Emitter &EMT);

        void AddAffector(const Affector &AFT);

        void LinkToTexture(const sf::Texture& T);      ///Temporary method until architecture is better set. (Use connector class or a reference to a Resource manager)

        void ClearAffectors();
        void ClearEmitters();
        void ClearVertexArray();

        void Update() const;

        void setBulletTypeTextureRects();

        void debug() const;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    private:

        void computeBullets() const;
        void computeBullet(const unsigned b) const;                                   ///<Computes the quad of a bullets based on the sprite sheet held in TextureHolder.
        void updateBullet(const unsigned b, sf::Time dt) const;                                    ///Updates time passed and other bullet properties.

    private:

        struct BulletTextureIndex                                                ///A Struct that contains publicly accessible Bullet Types and Colors to use as a key for the texture rect map.
        { ///Cannot be used in a std::map unless it has operators to define order.
            public:
            BulletTextureIndex(Bullet::BulletType T, Bullet::BulletColor C) :Type(T), Color(C) {}

            Bullet::BulletType    Type;
            Bullet::BulletColor   Color;

            ///Used to order the std::map
            bool operator<(const BulletTextureIndex& B) const
            {
                if( static_cast<unsigned>(Type) == static_cast<unsigned>(B.Type) )
                { return static_cast<unsigned>(Color) < static_cast<unsigned>(B.Color); }
                else
                { return static_cast<unsigned>(Type) < static_cast<unsigned>(B.Type); }
            }

            bool operator>(const BulletTextureIndex& B) const
            {
                if( static_cast<unsigned>(Type) == static_cast<unsigned>(B.Type) )
                { return static_cast<unsigned>(Color) > static_cast<unsigned>(B.Color); }
                else
                { return static_cast<unsigned>(Type) > static_cast<unsigned>(B.Type); }
            }
        };

        static unsigned BulletCalculatedMax;
        static std::array<unsigned, 8> ValidColors;

        mutable std::map<BulletTextureIndex,sf::IntRect> BTextRect_Map;                  ///<Contains the texture rects that are accessed using BulletTypes.
        mutable std::vector<Bullet> Bullet_Vec;
        mutable bool mNeedsVertexUpdate;
        mutable sf::VertexArray Vertexes_Vec;                                    ///<The VertexArray that will be used to draw all the bullets.
        mutable sf::Clock BulletClock;

        std::vector<const Emitter*> EMT_Vec;                     ///<Contains a std::pair with a pointer (no ownership) to the emitter in question and the time it will remain alive.
        std::vector<const Affector*> AFT_Vec;                    ///<Contains a std::pair with a pointer (no ownership) to the affector in question and the time it will remain alive.

        const sf::Texture* TexturePtr;





        friend void CreateBullet(const Generator& g, const sf::Time& life,Bullet::BulletType T, Bullet::BulletColor C, const sf::Vector2f& ori, const sf::Vector2f& pos, const sf::Vector2f& vel, const float LinVel,const sf::Vector2f& scale, const float rot, const float rotSp, const float rotSelf, const float rotSelfSp);

};
