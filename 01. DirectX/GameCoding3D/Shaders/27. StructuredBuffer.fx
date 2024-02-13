
// 어떤 데이터를 넣어줄지 struct
struct InputDesc
{
    matrix input;
};

struct OutputDesc
{
    matrix result;
};

StructuredBuffer<InputDesc> Input;
RWStructuredBuffer<OutputDesc> Output; //Read Write
                                                          
[numthreads(500, 1, 1)]
void CS(uint id : SV_GroupIndex)
{
    matrix result = Input[id].input * 2;
    
    Output[id].result = result;
}

technique11 T0
{
    pass P0 
    {
        SetVertexShader(NULL);
        SetPixelShader(NULL);
        SetComputeShader(CompileShader(cs_5_0, CS()));
    }
};
