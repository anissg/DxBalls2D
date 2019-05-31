#include "stdafx.h"
#include "PhysicsSim.h"

bool PhysicsSim::Initialize(HINSTANCE hInstance, wstring title, wstring windowClass, int width, int height)
{
    this->width = width;
    this->height = height;

    Engine::Initialize(hInstance, title, windowClass, width, height);
    gfx.InitializeSpriteBatch();

    HRESULT hr;
    hr = CreateWICTextureFromFile(gfx.GetDevice(), L"ball01.png", res1.GetAddressOf(), tex1.ReleaseAndGetAddressOf());
    if (FAILED(hr))
    {
        Logger::get().Log("Failed to create texture.", ERR);
        return false;
    }
    hr = CreateWICTextureFromFile(gfx.GetDevice(), L"ball02.png", res2.GetAddressOf(), tex2.ReleaseAndGetAddressOf());
    if (FAILED(hr))
    {
        Logger::get().Log("Failed to create texture.", ERR);
        return false;
    }
    hr = CreateWICTextureFromFile(gfx.GetDevice(), L"ball03.png", res3.GetAddressOf(), tex3.ReleaseAndGetAddressOf());
    if (FAILED(hr))
    {
        Logger::get().Log("Failed to create texture.", ERR);
        return false;
    }
    hr = CreateWICTextureFromFile(gfx.GetDevice(), L"ball04.png", res4.GetAddressOf(), tex4.ReleaseAndGetAddressOf());
    if (FAILED(hr))
    {
        Logger::get().Log("Failed to create texture.", ERR);
        return false;
    }
    hr = CreateWICTextureFromFile(gfx.GetDevice(), L"ball05.png", res5.GetAddressOf(), tex5.ReleaseAndGetAddressOf());
    if (FAILED(hr))
    {
        Logger::get().Log("Failed to create texture.", ERR);
        return false;
    }

    spriteBatch = gfx.GetSpriteBatch();

    EmitBalls(XMVectorSet(width / 2, height / 2, 0, 0), 600, 30, 5);

    return true;
}

void PhysicsSim::Update(double elapsedTime)
{
    UpdateCoulisions();

    for (int i = 0; i < balls.size(); i++)
    {
        balls[i].Update(elapsedTime);
    }
}

void PhysicsSim::Render()
{
    gfx.Clear(Colors::WhiteSmoke);

    spriteBatch->Begin(SpriteSortMode_Deferred, gfx.GetStates()->NonPremultiplied());

    for (int i = 0; i < balls.size(); i++)
    {
        balls[i].Render(spriteBatch);
    }

    spriteBatch->End();

    gfx.Present();
}

inline int frnd(int max) { return (rand() % max); }

void PhysicsSim::EmitBalls(XMVECTOR center, float raduis, int count, int color)
{
    Ball* b;
    float r;
    for (int i = 0; i < count; i++)
    {
        XMVECTOR direction = XMVectorSet(cos(i * 6.28 / count), sin(i * 6.28 / count), 0, 0);
        r = frnd(20) + 15;
        AddBall(center + direction * raduis,
            direction * (frnd(100) + 100),
            r * 0.1f,
            r,
            i % 5 + 1);
    }
}

void PhysicsSim::UpdateCoulisions()
{
    XMVECTOR dist, vi, vj, dspeed, alpha;
    float d, mi, mj, dotp;
    for (int i = 0; i < balls.size(); i++)
    {
        for (int j = i + 1; j < balls.size(); j++)
        {
            if (balls[i].ColisionDetection(balls[j]))
            {
                mi = balls[i].GetMass();
                mj = balls[j].GetMass();
                vi = balls[i].GetSpeed();
                vj = balls[j].GetSpeed();

                dspeed = vi - vj;
                dist = balls[i].GetPosition() - balls[j].GetPosition();
                d = XMVectorGetX(XMVector2Length(dist));
                dotp = XMVectorGetX(XMVector2Dot(dspeed, dist));
                balls[i].SetSpeed(vi - ((2 * mj * dotp) / ((mi + mj) * d * d) * dist));

                dspeed = vj - vi;
                dist = balls[j].GetPosition() - balls[i].GetPosition();
                dotp = XMVectorGetX(XMVector2Dot(dspeed, dist));
                balls[j].SetSpeed(vj - ((2 * mi * dotp) / ((mi + mj) * d * d) * dist));

                while (balls[i].ColisionDetection(balls[j]))
                {
                    balls[i].Update(0.01f);
                    balls[j].Update(0.01f);
                }
            }
        }
        if (XMVectorGetX(balls[i].GetPosition()) <= balls[i].GetRadius())
        {
            balls[i].SetSpeed(XMVectorSetX(balls[i].GetSpeed(), -XMVectorGetX(balls[i].GetSpeed())));
            balls[i].SetPosition(XMVectorSetX(balls[i].GetPosition(), balls[i].GetRadius()));
        }
        else
            if (XMVectorGetX(balls[i].GetPosition()) >= width - balls[i].GetRadius())
            {
                balls[i].SetSpeed(XMVectorSetX(balls[i].GetSpeed(), -XMVectorGetX(balls[i].GetSpeed())));
                balls[i].SetPosition(XMVectorSetX(balls[i].GetPosition(), width - balls[i].GetRadius()));
            }
        if ((XMVectorGetY(balls[i].GetPosition()) <= balls[i].GetRadius()))
        {
            balls[i].SetSpeed(XMVectorSetY(balls[i].GetSpeed(), -XMVectorGetY(balls[i].GetSpeed())));
            balls[i].SetPosition(XMVectorSetY(balls[i].GetPosition(), balls[i].GetRadius()));
        }
        else
            if (XMVectorGetY(balls[i].GetPosition()) >= height - balls[i].GetRadius())
            {
                balls[i].SetSpeed(XMVectorSetY(balls[i].GetSpeed(), -XMVectorGetY(balls[i].GetSpeed())));
                balls[i].SetPosition(XMVectorSetY(balls[i].GetPosition(), height - balls[i].GetRadius()));
            }
    }
}

void PhysicsSim::AddBall(XMVECTOR position, XMVECTOR speed, float mass, float raduis, int color)
{
    Ball b(position, speed, mass, raduis, color);
    ComPtr<ID3D11Texture2D> res;
    switch (color)
    {
    case 1:
        res1.As(&res);
        b.SetTexture(tex1.Get(), res.Get());
        break;
    case 2:
        res2.As(&res);
        b.SetTexture(tex2.Get(), res.Get());
        break;
    case 3:
        res3.As(&res);
        b.SetTexture(tex3.Get(), res.Get());
        break;
    case 4:
        res4.As(&res);
        b.SetTexture(tex4.Get(), res.Get());
        break;
    case 5:
        res4.As(&res);
        b.SetTexture(tex5.Get(), res.Get());
        break;
    }
    balls.push_back(b);
}