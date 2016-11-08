#include "Answer.hpp"
namespace hpc {
Answer::Answer()
{
}

Answer::~Answer()
{
}

void Answer::init(const Stage& aStage)
{
}

float calcTheta(Asteroid a, Vector2 v) {
    float dist = a.pos().dist(v);
    float r = a.radius();
    float theta = Math::ACos(Math::Sqrt(dist*dist-r*r)/dist);
    return Math::Abs(theta);
}

Action Answer::getNextAction(const Stage& aStage)
{
    Ship ship = aStage.ship();
    Vector2 shipLocation = ship.pos();
    Vector2 farest = shipLocation;
    Vector2 nearest = Vector2(100000,100000) + shipLocation;
    float epsilon = 0.0001;
    if(ship.canShoot()) {
        // 発射目標にする小惑星を決定します。
        Vector2 targetShootPos;
        float maxlength = 0;
        for(int i = 0; i < aStage.asteroidCount(); i++) {
            Asteroid a1 = aStage.asteroid(i);
            if(!a1.exists())
                continue;
            float theta1 = calcTheta(a1, shipLocation);
            Vector2 a1loc = a1.pos() - shipLocation;
            for(int j = i+1; j < aStage.asteroidCount(); j++) {
                Asteroid a2 = aStage.asteroid(j);
                if(!a2.exists())
                    continue;
                float theta2 = calcTheta(a2, shipLocation);
                Vector2 a2loc = a2.pos() - shipLocation;
                if(a1loc.angle(a2loc) >= theta1 + theta2)
                    continue;
                float rot = theta1-epsilon;
                float angle = a1loc.rotSign(a2loc) > 0 ? rot : -rot;
                float length = Math::Min(a1loc.length(), a2loc.length());
                if(length > maxlength) {
                    targetShootPos = a1loc.getRotatedRad(angle)+shipLocation;
                    maxlength = length;
                }
            }
            if(farest.dist(shipLocation) < a1.pos().dist(shipLocation)) {
                farest = a1.pos();
            }
        }
        if(maxlength == 0)
            return Action::Shoot(farest);
        else
            return Action::Shoot(targetShootPos);
    } else {
        Vector2 targetMovePos;
        for(int i = 0; i < aStage.asteroidCount(); ++i) {
            Asteroid a = aStage.asteroid(i);
            if(a.exists()) {
                if(nearest.dist(shipLocation) > a.pos().dist(shipLocation)) {
                    nearest = a.pos();
                }
            }
        }
        targetMovePos = nearest;
        return Action::Move(targetMovePos);
    }
}

void Answer::finalize(const Stage& aStage)
{
}
} // namespace
