#include <iostream>
#include <cmath>
#include "Framefactory.h"
#include "sprite.h"
#include "gamedata.h"


const Vector2f WALL_LEFT = Vector2f(-1, 0);
const Vector2f WALL_RIGHT = Vector2f(1, 0);
const Vector2f WALL_TOP = Vector2f(0, 1);
const Vector2f WALL_BOTTOM = Vector2f(0, -1);

Sprite::Sprite(const Vector2f& pos, const Vector2f& vel, 
               const string& n, const Frame* f) :
  Drawable(pos, vel, 
           Vector2f(Gamedata::getInstance()->getXmlInt(n+"MaxXspeed"),
                    Gamedata::getInstance()->getXmlInt(n+"MaxYspeed"))), 
  name(n),
  frame(f)
{ }

Sprite::Sprite(const Vector2f& pos, const Vector2f& vel, 
               const string& n) :
  Drawable(pos, vel, 
           Vector2f(Gamedata::getInstance()->getXmlInt(n+"MaxXspeed"),
                    Gamedata::getInstance()->getXmlInt(n+"MaxYspeed"))), 
  name(n),
  frame(const_cast<Frame*> (FrameFactory::getInstance()->getFrame(name,"sprite")[0]))
{ }
Sprite::Sprite(const string& n, const string& type, float xPos, float yPos) :
Drawable(Vector2f(xPos,yPos),  
                Vector2f(Gamedata::getInstance()->getXmlInt(n+"Xspeed"),
                 Gamedata::getInstance()->getXmlInt(n+"Yspeed")),Vector2f(Gamedata::getInstance()->getXmlInt(n+"Xspeed"),
                 Gamedata::getInstance()->getXmlInt(n+"Yspeed"))), 
  name(n),
  frame(const_cast<Frame*> (FrameFactory::getInstance()->getFrame(name,"sprite")[0])) { }

Sprite::Sprite(const Sprite& s) :
  Drawable(s.getPosition(), s.getVelocity(), s.getMaxVelocity()), 
  name( s.getName() ),
  frame(s.frame)
  { }

Sprite& Sprite::operator=(const Sprite& rhs) {
  setName( rhs.getName() );
  setPosition(rhs.getPosition());
  setVelocity(rhs.getVelocity());
  setMaxVelocity(rhs.getMaxVelocity());
  frame = rhs.frame;
  return *this;
}

void Sprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

unsigned Sprite::getPixel(Uint32 i, Uint32 j) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  x = i - x;
  y = j - y;
  Uint32 *pixels = static_cast<Uint32 *>(frame->getSurface()->pixels);
  return pixels[ ( y * frame->getWidth() ) + x ];
}


int Sprite::getDistance(const Sprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void Sprite::update(Uint32 ticks) { 
  float incr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()+incr );
  float height = static_cast<float>(frame->getHeight());
  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if  (Y() > Gamedata::getInstance()->getXmlInt("worldHeight")-height)  {
    velocityY( -abs( velocityY() ) );
  }

  incr = velocityX() * static_cast<float>(ticks) * 0.001;
  if (name == "aibullet") {
    X( X()+incr );}
  else X( X()+incr );
  float width = static_cast<float>(frame->getWidth());
  if (name == "aibullet"){
    velocityX( -abs( velocityX() ) );
  }
  else {

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if (( X() > Gamedata::getInstance()->getXmlInt("worldWidth")-width) && name != "bullet") {
    velocityX( -abs( velocityX() ) );
  }  
}
}
