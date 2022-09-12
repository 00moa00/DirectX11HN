// #include "myshader.hlsli"

// SV_POSITION �ø�ƽ
// �׷���ī�忡�� �̳༮�� �̷� �η��ϱ� �ϰ� �ڵ����� ó���ϴ� �༮�� ������ �ϰ�.

#include "TransformHeader.fx"
#include "RenderOption.fx"

// 0                                                                                                1 
// 0�������������������������������������������������������������������������������������������������1

struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};

struct Output
{
    float4 Pos : SV_POSITION;
    float4 PosLocal : POSITION;
    float4 Tex0 : TEXCOORD0;
    float4 Tex1 : TEXCOORD1; //����ũ ������ �� �ؽ�ó
};

// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001

cbuffer AtlasData : register(b1)
{
    float2 TextureFramePos;
    float2 TextureFrameSize;
    float4 PivotPos;
};

cbuffer UVData : register(b2)
{
    float OffsetX;
    float OffsetY;
    float Dummy0;
    float Dummy1;
};



Output TextureAtlas_VS(Input _Input)
{
    Output NewOutPut = (Output)0;
    _Input.Pos += PivotPos;
    NewOutPut.Pos = mul(_Input.Pos, WorldViewProjection);
    NewOutPut.PosLocal = _Input.Pos;
    
    // ���ؽ��� ���° ���ؽ� ���� �˼��� ����.
    // NewOutPut.Tex
    // 00    10
    
    // 10    11
    
    NewOutPut.Tex0.x = (_Input.Tex.x  * TextureFrameSize.x) + (TextureFramePos.x);
    NewOutPut.Tex0.y = (_Input.Tex.y * TextureFrameSize.y) + (TextureFramePos.y + OffsetY);

    NewOutPut.Tex1 = _Input.Tex; // uv���� �״�� �־���.
    
    return NewOutPut;
}

cbuffer PixelData : register(b0)
{
    float4 MulColor;
    float4 PlusColor;
    float4 Slice;
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
Texture2D Test : register(t1);

float4 TextureAtlas_PS(Output _Input) : SV_Target0
{
    if (_Input.Tex0.x < Slice.x)
    {
        clip(-1);
    }
    
    float4 MaskColor = Test.Sample(Smp, _Input.Tex1.xy); //������ �� ������ ���� ������ ������
    
    if (MaskColor.a == 0.f) //�������� ���� �κ��� �׷����� �����ž�
    {
        discard;
    }
    
    
    return (Tex.Sample(Smp, _Input.Tex0.xy) * MulColor) + PlusColor;
}
    
    
    
