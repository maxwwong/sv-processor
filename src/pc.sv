module pc (
    input logic clk,
    input logic pcWriteEnable,
    input logic reset,
    input logic [31:0] pcIn,
    output logic [31:0] pcOut
);
    logic [31:0] pcReg;

    always_ff @( posedge clk ) begin : updatePc
        if (reset) begin
            pcReg <= 0;
        end else if (pcWriteEnable) begin
            pcReg <= pcIn;
        end
    end

endmodule
