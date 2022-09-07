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

cbuffer NoiseData : register(b3)
{
    float Time;
    float Dummy0;
    float Dummy1;
    float Dummy2;
};

// �׷���ī�忡�� �̷����°�.
Output Blur_VS(Input _Input)
{
    Output NewOutPut = (Output) 0;
    NewOutPut.Pos = _Input.Pos;
    NewOutPut.Tex = _Input.Tex;
    return NewOutPut;
}

float WhiteNoise(float2 coord)
{
    return frac(sin(dot(coord, float2(8.7819, 3.255))) * 437.645);
}
float grain(float2 st)
{
    return frac(sin(dot(st.xy, float2(17.0, 180.))) * 2500.);
}

Texture2D Tex : register(t0);
SamplerState Smp : register(s0);
float4 Blur_PS(Output _Input) : SV_Target0
{
    // �Ķ���
    
    //float2 PixelUVSize = float2(1.0f / 1920.0f, 1.0f / 1080.0f);
    //float2 PixelUVCenter = _Input.Tex.xy;
    //float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    //float2 CurUV = StartUV;
    //
    //float4 Result = (float4) 0.0f;
    // 
    //float2 samplePoint = CurUV;
    //float4 Texture = Tex.Sample(Smp, samplePoint);
    //float noise = WhiteNoise(CurUV * Time) - 0.5;
    //Texture.rgb += float3(noise, noise, noise);
    //return Texture;
    //
    float2 PixelUVSize = float2(1.0f / 1920.0f, 1.0f / 1080.0f);
    float2 PixelUVCenter = _Input.Tex.xy;
    float2 StartUV = PixelUVCenter + (-PixelUVSize * 1.5);
    float2 CurUV = StartUV;


    float4 Texture = Tex.Sample(Smp, CurUV);

    float3 grainPlate = float(grain(CurUV + Time)) - 0.005;
    grainPlate /= 2;
    //Get the webcam
   
        
    //Mix the two signals together
    float3 mixer = lerp(Texture.rgb, grainPlate, .1);
	
    
    Texture = float4(mixer, 1.0);
    return Texture;

}
