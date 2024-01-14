module ALU_design(A,B ,op_code,alu_out,c_out );
    input  [7:0] A, B;
    input [2:0] op_code;
    output reg [15:0] alu_out;
    output reg c_out;
    
    always@(op_code)
    begin
    case(op_code)
    3'b000:
    begin
        alu_out=A+B;
        c_out=alu_out[8];
        end
    3'b001:
    begin
        alu_out=A-B;
        c_out=alu_out[8];
        end
    3'b010:
        alu_out=A*B;
    3'b011:
    begin
         alu_out= A<<2;
         c_out=1'b0;
         end    
    3'b100:
    begin
            alu_out= A>>2;
            c_out=1'b0;
            end 
    3'b101:
    begin
             alu_out= A&&B; 
             c_out=1'b0;
             end
    3'b110:
    begin
             alu_out= A||B; 
             c_out=1'b0;
             end
    3'b111:
    begin
             alu_out= A^B; 
             c_out=1'b0;
             end
    endcase
    end
    endmodule
