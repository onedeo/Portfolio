
RWByteAddressBuffer Output; // UAV

struct ComputeInput
{
    uint3 groupID : SV_GroupID;
    uint3 groupeThreadID : SV_GroupThreadID;
    uint3 dispatchThreadID : SV_DispatchThreadID;
    uint groupIndex : SV_GroupIndex;
};
                                                          
[numthreads(10, 8, 3)] //threads 개수 10*8*3
void CS(ComputeInput input)
{
    uint index = input.groupIndex;
    uint outAddress = index * 10 * 4; //ComputeInput의 크기 : 10
    
    Output.Store3(outAddress + 0, input.groupID);
    Output.Store3(outAddress + 12, input.groupeThreadID);
    Output.Store3(outAddress + 24, input.dispatchThreadID);
    Output.Store(outAddress + 36, input.groupIndex);  
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
