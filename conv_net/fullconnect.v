module fullconnect (
    parameter integer bitwidth=8,
    parameter integer previous_layer=25,
    parameter integer next_layer=2
)
(
    input[bitwidth*previous_layer-1:0] data,
    input[bitwidth*previous_layer*next_layer-1:0] weights,
    input[bitwidth*next_layer-1:0] bias,
    output reg [2*bitwidth*next_layer-1:0] result
);
wire signed [2*bitwidth-1:0] inter_result[next_layer-1:0][previous_layer-1:0];//存储计算的中间结果用于累加
wire signed [bitwidth-1:0] bias_array[next_layer-1:0];//将偏置值转换为一维数组存储
genvar i,j,k
    generate//将偏置值转换为一维数组存储
        for(i=0;i<next_layer;i++)begin
            assign bias_array[i]=bias[i*bitwidth+bitwidth-1:i*bitwidth];
        end
    endgenerate

    generate//前向传播的计算
        for(i=0;i<next_layer;i++)begin
            for(j=0;j<previous_layer;j++)begin
                assign inter_result[i][j]=data[j*bitwidth+bitwidth-1:j*bitwidth]*weights[(i*previous_layer+j)*bitwidth+bitwidth-1:(i*previous_layer+j)*bitwidth];
            end
        end
    endgenerate

    integer sum,m,n;
    always@(*)begin//计算输出值
        for(m=0;m<next_layer;m++)begin
            sum=0;
            for(n=0;n<previous_layer;n++)begin
                sum=sum+inter_result[m][n];
            end
            sum=sum+bias_array[m];
            result[m*2*bitwidth+2*bitwidth-1:m*2*bitwidth]=sum;
        end
    end

endmodule //fullconnect