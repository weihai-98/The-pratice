module mult#(
    parameter filter_demension = 3,
    parameter stride = 1,
    parameter input_demension = 5,
    parameter width = 4,
    parameter m = 0,
    parameter n = 0,
    localparam filter_size=filter_demension*filter_demension,
    localparam input_size=input_demension*input_demension,
    localparam ans_width=width+width
)
(
    input [filter_size*width-1 : 0] filter,
    input [input_size*width-1 : 0] image,
    input clk,
    output [ans_width*filter_size-1 : 0] ans
);
reg signed [width-1:0] filter_a [3-1:0][3-1:0];
reg signed [width-1:0] image_a [3-1:0][3-1:0];
reg signed [ans_width-1:0] result [2:0][2:0];
genvar i,j;
generate
for(i=0;i<3;i=i+1)begin
    for(j=0;j<3;j=j+1)begin
        always@(posedge clk)begin
            image_a[i][j] <= image[(m*5+n+i*5+j+1)*width-1 : (m*5+n+i*5+j)*width];
            filter_a[i][j] <= filter[(3*i+j+1)*width-1 : (3*i+j)*width];
        end
    end
end   
endgenerate
generate
    for(i=0;i<3;i=i+1)begin
        for(j=0;j<3;j=j+1)begin
            mult_gen_0 mult(
                .CLK(clk),  
                .A(image_a[i][j]),      
                .B(filter_a[i][j]),     
                .P(result[i][j])     
            );
        end
    end
endgenerate
generate
    for(i=0;i<3;i=i+1)begin
        for(j=0;j<3;j=j+1)begin
            assign ans[(3*i+j+1)*ans_width-1 : (3*i+j)*ans_width] = result [i][j];
        end
    end
endgenerate
endmodule //mult