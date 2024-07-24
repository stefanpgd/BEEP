struct PixelIN
{
    float2 TexCoord : TexCoord;
    float3 Normal : Normal;
};

Texture2D screenTexture : register(t0);
SamplerState LinearSampler : register(s0);

float4 main(PixelIN IN) : SV_TARGET
{
    float3 lightDir = normalize(float3(0.6, 1.0f, 0.0f));
    
    float diff = saturate(dot(IN.Normal, lightDir));
    float3 objectColor = float3(0.8f, 0.8f, 0.8f);
    
    float3 diffuse = objectColor * diff;
    float3 ambient = objectColor * 0.12;
    
    float3 outputColor = diffuse + ambient;
    outputColor = clamp(outputColor, float3(0.0, 0.0, 0.0), float3(1.0, 1.0, 1.0));
    
    float3 normColor = (IN.Normal * 0.5) + 0.5;
    
    return float4(outputColor, 1.0f);
}