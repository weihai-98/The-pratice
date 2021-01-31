`timescale 1ns/1ps
module add_tree_tb ();
wire [35:0] a;
reg [35:0] a_;
wire [7:0]result;
reg clk;
initial
begin
    clk=0;
    a_=0;
end
always #10 clk=~clk;
always@(posedge clk) begin
    a_=a_+36'b000100010001000100010001000100010001;
end
assign a=a_;
add_tree add(
.a(a),
.clk(clk),
.result(result)
);
endmodule 