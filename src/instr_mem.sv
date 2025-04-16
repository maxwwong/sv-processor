module instr_mem (
    input  logic [31:0] pc,
    output logic [31:0] instruction
);

    logic [31:0] memory [0:255];

    assign instruction = memory[pc[9:2]];

    initial begin
        $readmemh("../testing_data/sum_one_to_ten.mem", memory);
    end

endmodule