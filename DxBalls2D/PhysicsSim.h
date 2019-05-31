#pragma once
#include "stdafx.h"

using namespace DirectX;

class PhysicsSim : public Engine
{
    int width;
    int height;
    ComPtr<ID3D11ShaderResourceView> tex1;
    ComPtr<ID3D11ShaderResourceView> tex2;
    ComPtr<ID3D11ShaderResourceView> tex3;
    ComPtr<ID3D11ShaderResourceView> tex4;
    ComPtr<ID3D11ShaderResourceView> tex5;
    ComPtr<ID3D11Resource> res1;
    ComPtr<ID3D11Resource> res2;
    ComPtr<ID3D11Resource> res3;
    ComPtr<ID3D11Resource> res4;
    ComPtr<ID3D11Resource> res5;
    shared_ptr<SpriteBatch> spriteBatch;
    vector<Ball> balls;
    void UpdateCoulisions();
public:
    bool Initialize(HINSTANCE hInstance, wstring title, wstring windowClass, int width, int height) override;
    void Update(double elapsedTime) override;
    void Render() override;
    void AddBall(XMVECTOR position, XMVECTOR speed, float mass, float raduis, int color);
    void EmitBalls(XMVECTOR center, float raduis, int count, int color);
};

