//set simulation time as 1000 ns
`timescale 1ns / 1ps

module traffic_sys_tb();

    // Inputs
    reg clk;
    reg reset;

    // Outputs
    wire [2:0] north_light;
    wire [2:0] west_light;
    wire [2:0] south_light;
    wire [2:0] east_light;

    // Instantiate the module
    Traffic_sys DUT (
        .north_light(north_light),
        .west_light(west_light),
        .south_light(south_light),
        .east_light(east_light),
        .clk(clk),
        .reset(reset)
    );

    // Clock generation
    always begin
        #5 clk = ~clk; // Toggle clock every 5 time units
    end

    // Initial reset
    initial begin
        clk = 0;
        reset = 1;
        #10 reset = 0; // Deassert reset after 10 time units
    end

    // Test scenario
    initial begin
        // Wait for a few clock cycles for initializations
        #20;

        // Test all possible state transitions

        // Case 1: Initial state
        if (north_light === 3'b001 && west_light === 3'b100 && south_light === 3'b100 && east_light === 3'b100)
            $display("Case 1 Passed: Initial state");
        else
            $display("Case 1 Failed: Initial state");

        // Case 2: Transition from north to north_yellow
        #40;
        if (north_light === 3'b010 && west_light === 3'b100 && south_light === 3'b100 && east_light === 3'b100)
            $display("Case 2 Passed: Transition from north to north_yellow");
        else
            $display("Case 2 Failed: Transition from north to north_yellow");

        // Case 3: Transition from north_yellow to west
        #40;
        if (north_light === 3'b100 && west_light === 3'b001 && south_light === 3'b100 && east_light === 3'b100)
            $display("Case 3 Passed: Transition from north_yellow to west");
        else
            $display("Case 3 Failed: Transition from north_yellow to west");

        // Continue adding similar checks for other state transitions

        $finish; // End simulation after all tests are complete
    end

endmodule
