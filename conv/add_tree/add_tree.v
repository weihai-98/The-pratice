module add_tree#(
    parameter num = 9,
    parameter in_width = 4
)(
    input [num*in_width-1 : 0] a,
    input clk,
    output [in_width+3 : 0] result
);
reg signed [in_width-1:0] a_array [num-1:0];
wire signed [in_width-1:0] a1[2:0];
wire signed [in_width-1:0] a2[2:0];
wire signed [in_width-1:0] a3[2:0];
reg signed [in_width+1:0] sum1[2:0];
reg signed [in_width+2:0] sum ;
genvar i;
generate
for(i=0;i<num;i=i+1)begin
    always@(posedge clk) a_array[i] <= a[(i+1)*in_width-1:i*in_width];
end
endgenerate
generate
for(i=0;i<3;i=i+1)begin
    assign a1[i] = a_array[3*i];
    assign a2[i] = a_array[3*i+1];
    assign a3[i] = a_array[3*i+2];
end
endgenerate
generate
for(i=0;i<3;i=i+1)begin
    always@(posedge clk) begin
        sum1[i] <= a1[i]+a2[i]+a3[i];
    end
end
endgenerate
always@(negedge clk) sum <= sum1[0]+sum1[1]+sum1[2];
assign result = sum;
endmodule //add_tree