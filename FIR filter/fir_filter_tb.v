`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 14.01.2024 13:47:27
// Design Name: 
// Module Name: fir_tb
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


module fir_tb();

  // Parameters
  parameter N = 16;

  // Signals
  reg clk = 0;
  reg reset = 0;
  reg [N-1:0] data_in;
  wire [N-1:0] data_out;

  // Instantiate the FIR_Filter module
  FIR_Filter uut (clk,reset,data_in,data_out);

  // Clock generation
  always begin
    #5 clk = ~clk;
  end

  // Test stimulus
  initial begin
    // Initialize inputs
    reset = 1;
    data_in = 0;

    // Apply reset
    #10 reset = 0;

    // Test scenario
    // You can modify this part based on your specific requirements
    // Here, we are applying a simple impulse response with a single non-zero input at the beginning
    #10 data_in = 8'b0000000000000001; // Apply an impulse response

    // Monitor and display results
    $monitor("Time=%0t, Input=%b, Output=%b", $time, data_in, data_out);

    // Run simulation
    #100 $finish;
  end

endmodule
