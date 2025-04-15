`include "alu_types.svh"

module alu (
    input logic [31:0] a,
    input logic [31:0] b,
    input alu_ops op,
    output logic [31:0] out
);

    always_comb begin : alu_logic
        case (op)
            Add: out = a + b;
            Sub: out = a - b;
            And: out = a & b;
            Or: out = a | b;
            Xor: out = a ^ b;
            Sll: out = a << b[4:0];
            Srl: out = a >> b[4:0];
            Sra: out = $signed(a) >>> b[4:0];
            Eq: out = (a == b) ? 32'b1: 32'b0;
            Neq: out = (a != b) ? 32'b1: 32'b0;
            Slt: out = ($signed(a) < $signed(b)) ? 32'b1: 32'b0;
            Sltu: out = (a < b) ? 32'b1: 32'b0;
        endcase
    end

endmodule
