`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 13.04.2023 06:43:54
// Design Name: 
// Module Name: Alu_tb
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module Alu_tb();
reg [7:0] A,B;
reg[2:0] op_code;
wire [15:0] alu_out;
wire c_out;
ALU_design DUT(A,B ,op_code,alu_out,c_out);
initial 
begin
A=8'b11111111;B=8'b01010101;op_code=3'b000;
#10 op_code=3'b001;
#10 op_code=3'b010;
#10 op_code=3'b011;
#10 op_code=3'b100;
#10 op_code=3'b101;
#10 op_code=3'b110;
#10 op_code=3'b111;
#10 $finish;
end
endmodule

