// #include "myshader.hlsli"

// SV_POSITION �ø�ƽ
// �׷���ī�忡�� �̳༮�� �̷� �η��ϱ� �ϰ� �ڵ����� ó���ϴ� �༮�� ������ �ϰ�.



struct Input
{
    float4 Pos : POSITION;
    float4 Tex : TEXCOORD;
};


struct Output
{
    float4 Pos : SV_POSITION;
    float4 Tex : TEXCOORD;
};


// �׷���ī�忡�� �̷����°�.
Output Vignette_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

// 1000
// 0100
// 2010
// 0301

// 1020
// 0103
// 0010
// 0001

//static float Gau[5][5] =
//{
//    {  }
//};

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 Vignette_PS(Output _Input) : SV_Target0
{
    // �Ķ���
    float2 PixelUVSize = float2(1.0f / 1920.0f, 1.0f / 1080.0f);
    float2 PixelUVCenter = _Input.Tex.xy;
    float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    float2 CurUV = StartUV;
    
    float2 samplePoint = CurUV;
    float4 Texture = Tex.Sample(Smp, samplePoint);
    float vignette = length(float2(0.5, 0.5) - CurUV);
    vignette = clamp(vignette - 0.2, 0, 1);
    Texture.rgb -= vignette;
    return Texture;
   
}
