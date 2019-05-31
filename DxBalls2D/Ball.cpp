#include "stdafx.h"
#include "Ball.h"

Ball::Ball(XMVECTOR position, XMVECTOR speed, float mass, float radius, int color)
{
    this->sprite.SetPosition(position);
    this->speed = speed;
    this->mass = mass;
    this->radius = radius;
    this->color = color;
}

XMVECTOR Ball::GetPosition()
{
    return sprite.GetPosition();
}

void Ball::SetPosition(XMVECTOR position)
{
    sprite.SetPosition(position);
}

XMVECTOR Ball::GetSpeed()
{
    return speed;
}

void Ball::SetSpeed(XMVECTOR speed)
{
    this->speed = speed;
}

float Ball::GetMass()
{
    return mass;
}

float Ball::GetRadius()
{
    return radius;
}

int Ball::GetColor()
{
    return color;
}

void Ball::SetTexture(ID3D11ShaderResourceView* texture, ID3D11Texture2D* resource)
{
    this->sprite.SetTexture(texture, resource);
    this->sprite.SetScale(2 * this->radius / this->sprite.GetSize().x);
}

bool Ball::ColisionDetection(Ball ball)
{
    return XMVectorGetX(XMVector2Length(this->GetPosition() - ball.GetPosition())) <= (this->radius + ball.GetRadius());
}

void Ball::Update(float time)
{
    XMVECTOR a, dv, dr;
    //F = A * M
    //a=force/mass;
    //dv/dt = a  ==> dv = a*dt;
    //dv=a*(float)dt;
    // mise à jour de la vitesse (on obtient la vitesse au temps t+dt)
    //speed+=dv;
    // dr/dt = v  ==> dr = v*dt;
    dr = speed * time;
    // mise à jour de la position
    sprite.SetPosition(sprite.GetPosition() + dr);
}

void Ball::Render(shared_ptr<SpriteBatch> spriteBatch)
{
    this->sprite.Render(spriteBatch);
}
