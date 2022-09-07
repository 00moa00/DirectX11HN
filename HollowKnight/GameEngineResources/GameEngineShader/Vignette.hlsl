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

float Vignette(float2 uv, float size)
{
    float d = length((uv - 0.5f) * 2.0f) / length(float2(1.0, 0));
    
    d /= size;
    
    float s = d * d * (3.0f - 2.0f * d);
    
    float v = lerp(d, s, 0.6f);
    float re = max(0.0, 1.0f - v);
    return re;
}
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
    
    float fShade = Vignette(CurUV, 5);
    
    float4 src = Texture *= fShade;
    float4 Re = float4(src.rgb, 1.0);
    return Re;
    
    //float vignette = length(float2(0.5, 0.5) - CurUV);
    //vignette = clamp(vignette - 0.2, 0, 1);
    //Texture.rgb -= vignette;
    //return Texture;
    

        
    //float2 PixelUVSize = float2(1.0f / 1920.0f, 1.0f / 1080.0f);
    //float2 PixelUVCenter = _Input.Tex.xy;
    //float2 StartUV = PixelUVCenter + (-PixelUVSize * 2);
    //float2 CurUV = StartUV;
    
    //float2 samplePoint = CurUV;
    //float4 Texture = Tex.Sample(Smp, samplePoint);
    //float2 coord = (samplePoint - 0.5) * (_Input.Tex.x / _Input.Tex.y) * 2.0;
    
    
    //float rf = sqrt(dot(coord, coord)) * 0.25f;
    //float rf2_1 = rf * rf + 1.0;
    //float e = 1.0 / (rf2_1 * rf2_1);
    
    //float4 src = float4(1.0, 1.0, 1.0, 0.4);
    //float4 Result = float4(src.rgb * e, 1.0);
    
    //return Re;
   
}
