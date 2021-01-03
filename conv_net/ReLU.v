module ReLU(
    parameter integer bitwidth=8
)
(
    input signed [bitwidth-1:0] data,
    output signed [bitwidth-1:0] result
);
assign result=data>0?data:0;
endmodule //ReLU