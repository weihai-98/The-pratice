//进行非线性函数的计算
module activation (
    parameter integer bitwidth=8,
    parameter integer datachannel=3,
    parameter integer dataheight=28,
    parameter integer datawidth=28
)
(
    input[bitwidth*datachannel*dataheight*datawidth-1:0] data,
    output reg [bitwidth*datachannel*dataheight*datawidth-1:0] result
);
genvar i,j,k;
    generate
        for(i=0;i<datachannel;i++)begin
            for(j=0;j<dataheight;j++)begin
                for(k=0;k<datawidth;k++)begin
                    ReLU(bitwidth) relu(data[(i*dataheight*datawidth+j*datawidth+k)*bitwidth+bitwidth-1
                    :i*dataheight*datawidth+j*datawidth+k)*bitwidth],result[(i*dataheight*datawidth+j*datawidth+k)*bitwidth+bitwidth-1
                    :i*dataheight*datawidth+j*datawidth+k)*bitwidth]);
                end
            end
        end
    endgenerate
    
endmodule