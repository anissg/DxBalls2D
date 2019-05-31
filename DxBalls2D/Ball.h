#pragma once
#include "stdafx.h"

class Ball
{
    Sprite sprite;
    XMVECTOR speed;
    float mass;
    float radius;
    int color;
public:
    Ball(XMVECTOR position, XMVECTOR speed, float mass, float radius, int color);
    XMVECTOR GetPosition();
    void SetPosition(XMVECTOR position);
    XMVECTOR GetSpeed();
    void SetSpeed(XMVECTOR speed);
    float GetMass();
    float GetRadius();
    int GetColor();
    void SetTexture(ID3D11ShaderResourceView* texture, ID3D11Texture2D* resource);
    bool ColisionDetection(Ball ball);
    void Update(float time);
    void Render(shared_ptr<SpriteBatch> spriteBatch);
};

