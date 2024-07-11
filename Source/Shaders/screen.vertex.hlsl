struct VertexPosColor
{
    float3 Position : POSITION;
    float2 TexCoord : TEXCOORD;
};

struct VertexOutput
{
    float2 TexCoord : TexCoord;
    float4 Position : SV_POSITION;
};

struct TransformData
{
    matrix MVP;
};
ConstantBuffer<TransformData> Transform : register(b0);

VertexOutput main(VertexPosColor IN)
{
    VertexOutput OUT;
    OUT.Position = mul(Transform.MVP, float4(IN.Position, 1.0f));
    OUT.TexCoord = IN.TexCoord;
    
    return OUT;
}