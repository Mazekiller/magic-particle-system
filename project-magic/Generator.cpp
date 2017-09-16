#include "Generator.hpp"
#include "PolarVector.hpp"

#include <iostream>
#include <algorithm>

unsigned Generator::BulletCalculatedMax = 10000;
std::array<unsigned, 8> Generator::ValidColors = {0, 2, 4, 6, 8, 10, 13, 15};

Generator::Generator()
:Bullet_Vec()
,EMT_Vec()
,AFT_Vec()
,Vertexes_Vec(sf::Quads, BulletCalculatedMax * 4)
,BTextRect_Map()
,BulletClock()
,TexturePtr(nullptr)
,mNeedsVertexUpdate(true)
{ Bullet_Vec.reserve(BulletCalculatedMax); }

Generator::Generator(const sf::Texture& T)
:Bullet_Vec()
,EMT_Vec()
,AFT_Vec()
,Vertexes_Vec(sf::Quads, BulletCalculatedMax * 4)
,BTextRect_Map()
,BulletClock()
,TexturePtr(nullptr)
,mNeedsVertexUpdate(true)
{
    Bullet_Vec.reserve(BulletCalculatedMax);
    LinkToTexture(T);
}

Generator::Generator(Generator&& G)
:Bullet_Vec(std::move(G.Bullet_Vec))
,EMT_Vec(std::move(G.EMT_Vec))
,AFT_Vec(std::move(G.AFT_Vec))
,Vertexes_Vec(std::move(G.Vertexes_Vec))
,BTextRect_Map(std::move(G.BTextRect_Map))
,BulletClock(std::move(G.BulletClock))
,mNeedsVertexUpdate(std::move(G.mNeedsVertexUpdate))
,TexturePtr(std::move(G.TexturePtr))
{}

Generator& Generator::operator=(Generator&& G)
{
    Bullet_Vec = std::move(G.Bullet_Vec);
    EMT_Vec = std::move(G.EMT_Vec);
    AFT_Vec = std::move(G.AFT_Vec);
    Vertexes_Vec = std::move(G.Vertexes_Vec);
    BTextRect_Map = std::move(G.BTextRect_Map);
    BulletClock = std::move(G.BulletClock);
    TexturePtr = std::move(G.TexturePtr);
    mNeedsVertexUpdate = std::move(G.mNeedsVertexUpdate);
}

void Generator::LinkToTexture(const sf::Texture& T)
{ TexturePtr = &T; }

void Generator::AddEmitter(const Emitter &EMT)
{
    const Emitter* t = &EMT;
    EMT_Vec.push_back(t);
}

void Generator::AddAffector(const Affector &AFT)
{
    const Affector* t = &AFT;
    AFT_Vec.push_back(t);
}

void Generator::ClearEmitters()
{ EMT_Vec.clear(); }

void Generator::ClearAffectors()
{ AFT_Vec.clear(); }

void Generator::ClearVertexArray()
{ Vertexes_Vec.clear(); }

void Generator::setBulletTypeTextureRects()
{ ///<Case implemented only, use only with current texture structure.
    ///<Sets the texture rect values for the bullets.
    const unsigned Colors_Amount = 16;

    ///<Loop for minimum sized bullets.
    const unsigned Min_Amount = 3;
    const unsigned Min_TextureDisplace = 192;
    const unsigned Min_Size = static_cast<unsigned>(Bullet::BulletSize::Minimum);

    unsigned Min_I_Start = 0; ///Index to the inner working of the enum, minimum bullets use the representative number 0 as a start number. Used for consistency.
    for(unsigned i = 0; i < Min_Amount; ++i)
    {
        for(unsigned c = 0; c < Colors_Amount; ++c)
        {
            BTextRect_Map.insert
            (
             std::make_pair( BulletTextureIndex(static_cast<Bullet::BulletType> (Min_I_Start), static_cast<Bullet::BulletColor> (c) ),
             sf::IntRect(c * Min_Size, (i * Min_Size) + Min_TextureDisplace, Min_Size, Min_Size)  )
            );
        }
        ++Min_I_Start;
    }

    ///<Loop for small sized bullets.
    const unsigned S_Amount = 12;    ///Amount of small bullets in texture, if texture changes or more small bullets are added then this must change.
    const unsigned S_Size = static_cast<unsigned>(Bullet::BulletSize::Small);

    unsigned S_I_Start = 3;          ///Index to the inner working of the enum, small bullets use the representative number 3 as a start number.
    for(unsigned i = 0; i < S_Amount; ++i)
    {
        for(unsigned c = 0; c < Colors_Amount; c++)
        {
            BTextRect_Map.insert
            (
             std::make_pair( BulletTextureIndex( static_cast<Bullet::BulletType> (S_I_Start), static_cast<Bullet::BulletColor> (c) ),
             sf::IntRect(c * S_Size, i * S_Size, S_Size, S_Size) )  /**Rect order is Left, Top, Width, Height**/
            );
        }
        ++S_I_Start;
    }

    ///Array with list of accepted color values (enum) for medium and large bullets.
    const unsigned color_limit = 8;

    const unsigned M_Amount = 7;
    const unsigned M_TextureDisplace = 256; ///Displace to the right.
    const unsigned M_Size = static_cast<unsigned>(Bullet::BulletSize::Medium);

    unsigned M_I_Start = 15; ///Index to the inner working of the enum, medium bullets use the representative number 15 as a start number.
    for(unsigned i = 0; i < M_Amount; ++i)
    {
        for(unsigned c = 0; c < color_limit; ++c)
        {
            BTextRect_Map.insert
            (
             std::make_pair( BulletTextureIndex(static_cast<Bullet::BulletType>(M_I_Start), static_cast<Bullet::BulletColor>(ValidColors[c]) ),
             sf::IntRect( (c * M_Size) + M_TextureDisplace, i * M_Size, M_Size, M_Size ) )
            );
        }
        M_I_Start++;
    }

    ///Loop for large sized bullets. Colors are set, so uses only one loop.
    const unsigned L_Amount = 2;
    const unsigned L_TextureDisplace = 256; ///Displace to the bottom.
    const unsigned L_Size = static_cast<unsigned>(Bullet::BulletSize::Large);

    unsigned L_I_Start = 22; ///Index to the inner working of the enum, medium bullets use the representative number 22 as a start number.
    for(unsigned i = 0; i < L_Amount; ++i)
    {
        for(unsigned c = 0; c < color_limit; ++c)
        {
            BTextRect_Map.insert
            (
             std::make_pair(BulletTextureIndex(static_cast<Bullet::BulletType>(L_I_Start), static_cast<Bullet::BulletColor>(ValidColors[c])),
             sf::IntRect(c * L_Size, L_TextureDisplace * (i + 1), L_Size, L_Size) )  /**Rect order is Left, Top, Width, Height**/
            );
        }
        L_I_Start++;
    }
}

void Generator::Update() const ///Add functionality to give bullet animation when creating and finishing once first tests work.
{
    ///Invalidate vertexes
    mNeedsVertexUpdate = true;

    ///Calls emitters and erases the dead emitters. Emits new bullets
    auto iter = EMT_Vec.begin();
    for(unsigned e = 0; e < EMT_Vec.size(); e++, ++iter)
    {
        if(!EMT_Vec[e]->isDead())
        { EMT_Vec[e]->emit(*this, BulletClock.getElapsedTime()); }
        else
        { delete *(iter); }
    }

    ///Updates bullet properties and calls the affectors on the bullets.
    for(unsigned i = 0; i < Bullet_Vec.size(); ++i)
    {
        updateBullet(i, BulletClock.getElapsedTime());

        if(Bullet_Vec[i].isAlive())
        {
            ///Calls affectors.
            for(unsigned a = 0; a < AFT_Vec.size(); ++a)
            {
                if(!AFT_Vec[a]->isDead())
                { AFT_Vec[a]->affect(Bullet_Vec[i], BulletClock.getElapsedTime()); }
            }
        }
    }

    ///Eliminates particles/bullets whose lifetime has expired.
    //Sorts array in descending lifetime order.
    if(!Bullet_Vec.empty())
    {
        std::sort(Bullet_Vec.begin(), Bullet_Vec.end(), std::greater<Bullet>());

        unsigned x;
        for(x = 0; x < Bullet_Vec.size(); ++x)
        {
            if(!Bullet_Vec[x].isAlive())
            { break; }
        }

        if(x != Bullet_Vec.size())
        { Bullet_Vec.erase(std::next(Bullet_Vec.begin(), x), Bullet_Vec.end()); }
    }

    ///Removes dead affectors, adds to the lifetime of all living affectors.
    auto iter2 = AFT_Vec.begin();
    for(unsigned a = 0; a < AFT_Vec.size(); ++a, ++iter2)
    {
        if(AFT_Vec[a]->isDead())
        { delete *(iter2); }
    }

    BulletClock.restart(); ///Restart the clock each frame.

}

void Generator::updateBullet(const unsigned b, sf::Time dt) const
{
    Bullet_Vec[b].TimePassed += dt;

    PolarVector PV(Bullet_Vec[b].LinearVelocity, getConvertedAngle(Bullet_Vec[b].Position) );

    ///Speed per time control, not per frame.
    Bullet_Vec[b].RotationAngle += dt.asSeconds() * Bullet_Vec[b].RotationSpeed;                    //Rotation Speed.
    Bullet_Vec[b].RotationToSelfAngle += dt.asSeconds() * Bullet_Vec[b].RotationToSelfSpeed;           //Rotation to self Speed.
    Bullet_Vec[b].Position += dt.asSeconds() * Bullet_Vec[b].Velocity; //Velocity.
    Bullet_Vec[b].Position += dt.asSeconds() * PV.TurnToRectangular(); //Linear Velocity.

    //Rotate the position after the translations and assign to the new position.
    Bullet_Vec[b].Position.x = Bullet_Vec[b].Position.x * Math<float>::cos(Bullet_Vec[b].RotationAngle) - Bullet_Vec[b].Position.y * Math<float>::sin(Bullet_Vec[b].RotationAngle);
    Bullet_Vec[b].Position.y = Bullet_Vec[b].Position.x * Math<float>::sin(Bullet_Vec[b].RotationAngle) + Bullet_Vec[b].Position.y * Math<float>::cos(Bullet_Vec[b].RotationAngle);
}

void Generator::computeBullets() const
{
    Vertexes_Vec.clear();

    for(unsigned b = 0; b < Bullet_Vec.size(); ++b)
    {
        unsigned x = b * 4;
        unsigned BulletSize = static_cast<float>( Bullet_Vec[b].getSize() );

        if(!(Bullet_Vec[b].getRotationToSelf() - 0.f <= EPSILON)) ///Sets the self-rotation accordingly.
        {
            //sf::Vector2f Offset(-((BulletSize * Bullet_Vec[b].getScale().x)/2.f), -((BulletSize * Bullet_Vec[b].getScale().y)/2.f));

            std::array<sf::Vector2f, 4> QuadPositions =
            {
                sf::Vector2f( -( (BulletSize * Bullet_Vec[b].Scale.x ) / 2.f), -( (BulletSize * Bullet_Vec[b].Scale.y ) / 2.f )),
                sf::Vector2f( ( (BulletSize * Bullet_Vec[b].Scale.x ) / 2.f), -( (BulletSize * Bullet_Vec[b].Scale.y ) / 2.f ) ),
                sf::Vector2f( ( (BulletSize * Bullet_Vec[b].Scale.x ) / 2.f), (BulletSize * Bullet_Vec[b].Scale.y ) / 2.f ),
                sf::Vector2f( -( (BulletSize * Bullet_Vec[b].Scale.x ) / 2.f) , ( (BulletSize * Bullet_Vec[b].Scale.y ) / 2.f) )
            };

            sf::Transform selfRotate;
            selfRotate.rotate(Bullet_Vec[b].RotationToSelfAngle);

            for(unsigned q = 0; q < 4; ++q) ///Try out transform function.
            {
                Vertexes_Vec.append(sf::Vertex(QuadPositions[q]));
                Vertexes_Vec[x + q].position = selfRotate.transformPoint(Vertexes_Vec[x + q].position);
                Vertexes_Vec[x + q].position += Bullet_Vec[b].Origin + Bullet_Vec[b].Position;
            }
        }
        else
        {
            std::array<sf::Vector2f, 4> QuadPositions =
            {
                sf::Vector2f(0, 0) + Bullet_Vec[b].Origin + Bullet_Vec[b].Position,
                sf::Vector2f(BulletSize * Bullet_Vec[b].getScale().x, 0) + Bullet_Vec[b].Origin + Bullet_Vec[b].Position,
                sf::Vector2f(BulletSize * Bullet_Vec[b].getScale().x, BulletSize * Bullet_Vec[b].getScale().y) + Bullet_Vec[b].Origin + Bullet_Vec[b].Position,
                sf::Vector2f(0, BulletSize * Bullet_Vec[b].getScale().y) + Bullet_Vec[b].Origin + Bullet_Vec[b].Position
            };

            for(unsigned q = 0; q < 4; ++q)
            { Vertexes_Vec.append(sf::Vertex(QuadPositions[q])); }

        }

        ///Sets the texture-rect of the bullet according to how it's set.
        BulletTextureIndex BTI( Bullet_Vec[b].getType(), Bullet_Vec[b].getColor() ); ///During emission there is a cross check to avoid access to non existing textures.

        float left = BTextRect_Map.find(BTI)->second.left;
        float right = left + BTextRect_Map.find(BTI)->second.width;
        float top = BTextRect_Map.find(BTI)->second.top;
        float bottom = top + BTextRect_Map.find(BTI)->second.height;

        Vertexes_Vec[x].texCoords = sf::Vector2f(left, top);
        Vertexes_Vec[x + 1].texCoords = sf::Vector2f(right, top);
        Vertexes_Vec[x + 2].texCoords = sf::Vector2f(right, bottom);
        Vertexes_Vec[x + 3].texCoords = sf::Vector2f(left, bottom);
    }
}

void Generator::debug() const
{
    std::cout << "Total Amount of Bullets: " << Bullet_Vec.size() << std::endl;
}

void Generator::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(mNeedsVertexUpdate)
    {
        computeBullets();
        mNeedsVertexUpdate = false;
    }

    states.texture = TexturePtr;
    target.draw(Vertexes_Vec, states);
}

void CreateBullet(const Generator& g, const sf::Time& life,Bullet::BulletType T, Bullet::BulletColor C, const sf::Vector2f& ori, const sf::Vector2f& pos, const sf::Vector2f& vel, const float LinVel,const sf::Vector2f& scale, const float rot, const float rotSp, const float rotSelf, const float rotSelfSp)
{
    ///Program a control to not accept bullet color values that do not exist for some types.
    //Accesible colors are: Gray = 0, Red = 2, Purple = 4, Blue = 6, Cyan = 8, Green = 10, Yellow = 13 and Silver = 15.
    Bullet b(life);
    b.setType(T);

    if(b.getSize() == Bullet::BulletSize::Medium || b.getSize() == Bullet::BulletSize::Large)
    {
        auto it = std::find(Generator::ValidColors.begin(), Generator::ValidColors.end(), static_cast<unsigned>(C));
        if(it != Generator::ValidColors.end())
        { b.setColor(C); }
        else
        {
            unsigned color = static_cast<unsigned>(C);
            if(color < 10)
            {
                color += 1; //The closest match is always one up in this case.
                b.setColor(static_cast<Bullet::BulletColor>(color));
            }
            else
            {
                if(color == 11)
                {
                    color = 10;
                    b.setColor(static_cast<Bullet::BulletColor>(color));
                }
                else
                {
                    color = 13; //Assumes yellow, since it's the closest match.
                    b.setColor(static_cast<Bullet::BulletColor>(color));
                }
            }
        }
    }
    else
    { b.setColor(C); }

    b.setPosition(pos);
    b.setVelocity(vel);
    b.setOrigin(ori);
    b.setLinearVelocity(LinVel);
    b.setScale(scale);
    b.setRotation(rot);
    b.setRotationSpeed(rotSp);
    b.setRotationToSelf(rotSelf);
    b.setRotationToSelfSpeed(rotSelfSp);
    b.restartClock();

    g.Bullet_Vec.push_back(std::move(b)); //Make it faster.
}
