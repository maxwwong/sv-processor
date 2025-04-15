module (
    input logic clk
    input logic writeEnable
    input logic [31:0] writeData
    input logic [4:0] writeAddress
    input logic [4:0] ra1
    input logic [4:0] ra2
    output logic [31:0] rVal1
    output logic [31:0] rVal2
);

    always_ff @( posedge clk ) begin : registerWrite
        if (writeEnable) begin
        end
    end

endmodule