module max_pool (
    parameter integer bitwidth=8,
    parameter integer datawidth=24,
    parameter integer dataheight=24,
    parameter integer datachannel=2,
    parameter integer scale=2
)
(
    input[bitwidth*datawidth*dataheight-1:0] data,
    output[bitwidth*datawidth/scale*dataheight/scale-1:0] result
);
wire[bitwidth-1:0] data_array[channel-1:0][dataheight-1:0][datawidth-1:0];
wire[bitwidth*scale*scale-1:0] data_group[channel-1:0][dataheight/scale-1:0][datawidth/scale-1:0];
genvar i,j,k,m,n;
    generate//将一维数据转换为三维存储
        for(i=0;i<channel;i++) begin
            for(m=0;m<dataheight;m++) begin
                for(n=0;n<datawidth;n++) begin
                    assign data_array[i][m][n]=data[(i*dataheight*datawidth+m*datawidth+n)*bitwidth+bitwidth-1
                    :(i*dataheight*datawidth+m*datawidth+n)*bitwidth];
                end
            end
        end
    endgenerate

    generate//选取将要进行最大值池化的数据
        for(i=0;i<channel;i++)begin
            for(j=0;j<dataheight/scale;j++)begin
                for(k=0;k<datawidth/scale;k++)begin
                    for(m=0;m<dataheight;m++)begin
                        for(n=0;n<datawidth;n++)begin
                           assign data_group[i][j][k][(m*datawidth+n)*bitwidth+bitwidth-1:(m*datawidth+n)*bitwidth]=data_array[i][m][n]; 
                        end
                    end
                end
            end
        end
    endgenerate

    generate//进行最大值池化并输出
       for(i=0;i<channel;i++)begin
            for(j=0;j<dataheight/scale;j++)begin
                for(k=0;k<datawidth/scale;k++)begin
                    MAX(bitwith,scale) max(data_group[i][j][k],result[(i*dataheight/scale*datawidth/scale+j*datawidth/scale+k)*bitwidth+bitwidth-1
                    :(i*dataheight/scale*datawidth/scale+j*datawidth/scale+k)*bitwidth])
                end
            end
        end
    endgenerate 
endmodule 