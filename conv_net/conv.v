module conv(
    parameter integer bitwidth=8,
    parameter integer filterwidth=3,
    parameter integer filterheight=3,
    parameter integer stride=1,
    parameter integer channel=3,
    parameter integer datawidth=28,
    parameter integer dataheight=28,
    parameter integer batch=2
)
(
    input[bitwidth*channel*datawidth*dataheight-1:0] data,
    input[bitwidth*batch*channel*filterwidth*filterheight-1:0] filterweight,
    output reg signed [(2*bitwidth)*batch*((dataheight-filterheight+1)/stride)*((datawidth-filterwidth+1)/stride)-1:0] result
);
wire[bitwidth-1:0] data_array[channel-1:0][dataheight-1:0][datawidth-1:0];//存储转换为三维后的输入数据值
wire[bitwidth-1:0] filter_array[batch-1:0][channel-1:0][filterheight-1:0][filterheight-1:0]; //存储转换为四维后的滤波器权重值
wire[bitwidth-1:0] out[batch-1:0][(dataheight-filterheight+1)/stride-1:0][(datawidth-filterwidth+1)/stride-1:0];
genvar i,j,k,m,n,row,col;
    generate       //将一维输入数据转换为三维存储
        for(i=0;i<channel;i++) begin
            for(j=0;j<dataheight;j++) begin
                for(k=0;k<datawidth;k++) begin
                    assign data_array[i][j][k]=data[(i*datawidth*dataheight+j*datawidth+k)*bitwidth+bitwidth-1:(i*datawidth*dataheight+j*datawidth+k)*bitwidth];
                end
            end
        end      
    endgenerate

    generate //将一维输入的滤波器权重转换为四维存储
        for(i=0;i<batch;i++)begin
            for(j=0;j<channel;j++) begin
                for(k=0;k<filterheight;k++) begin
                    for(m=0;m<filterwidth;m++) begin
                        assign filter_array[i][j][k][m]=filterweight[(i*channel*datawidth*dataheight+j*datawidth*dataheight+k*filterwidth+m)*bitwidth+bitwidth-1:(i*channel*datawidth*dataheight+j*datawidth*dataheight+k*filterwidth+m)*bitwidth];
                    end
                end
            end
        end      
    endgenerate

    generate //进行卷积计算
        for(row=0;row<(dataheight-filterheight+1)/stride;row++) begin
            for(col=0;col<(datawidth-filterwidth+1)/stride;col++) begin
                for(i=0;i<batch;i++) begin
                    for(j=0;j<channel;j++) begin
                        for(m=0;m<filterheight;m++) begin
                            for(n=0;n<filterwidth;n++) begin
                                assign out[i][row][col]+=filter_array[i][j][m][n]*data_array[j][m+row*stride][n+col*stride];
                            end
                        end
                    end
                end
            end
        end
    endgenerate

integer i_,row_,col_;
always@(*)begin //将卷积计算结果输出
    for(i_=0;i_<batch;i_++) begin
        for(row_=0;row_<(dataheight-filterheight+1)/stride;row_++) begin
            for(col_=0;col_<(datawidth-filterwidth+1)/stride;col_++) begin
                result[(i_*((dataheight-filterheight+1)/stride)*(datawidth-filterwidth+1)/stride)+row_*((dataheight-filterheight+1)/stride;row++))+col_)*bitwidth+bitwidth-1
                :(i_*((dataheight-filterheight+1)/stride)*(datawidth-filterwidth+1)/stride)+row_*((dataheight-filterheight+1)/stride;row++))+col_)*bitwidth]=out[i][row][col];
            end
        end
    end
end
endmodule