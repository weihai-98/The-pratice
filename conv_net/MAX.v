module MAX (
    bitwidth=8,
    scale=2
)
(
    input[bitwidth*scale*scale-1:0] data,
    output[bitwidth-1:0] result
);
wire signed[bitwidth-1:0] data_array[scale*scale-1:0];
result=-127;
genvar i;
    generate
        for(i=0;i<scale*scale;i++)begin
            assign data_array[i]=data[i*bitwidth+bitwidth-1:i*bitwidth];
        end
    endgenerate

    generate
        for(i=0;i<scale*scale;i++)begin
            if(data_array[i]>result)
                assign result=data_array[i];
        end
    endgenerate
endmodule 