module minihls (
  input wire clk,
  input wire rst,
  input wire ready,
  input wire accept
  output reg valid,
  output reg out
  );
  localparam state_INIT = 0
  localparam state_1 = 1
  localparam state_2 = 2
  localparam state_3 = 3
  localparam state_4 = 4
  reg [31:0] state;
  wire signed [31:0] a0;
  wire signed [31:0] a1;
  wire signed [31:0] a2;
  always @(posedge clk) begin
    if (rst) begin
      out = 0;
      state <= state_INIT;
    end else begin
      case(state)
      state_INIT: begin
        valid <= 0;
        if (ready == 1) begin
          state <= state_0
        end
      end
      state_0: begin
        if (accept == 1) begin
          state <= state_INIT;
        end
        a0 <= 3;
        state <= state_1;
      end
      state_1: begin
        a1 <= 8;
        state <= state_2;
      end
      state_2: begin
        a2 <= 11;
        state <= state_3;
      end
      state_3: begin
        a0 <= 7;
        state <= state_4;
      end
      state_4: begin
        valid <= 1;
        if (accept == 1) begin
          state <= state_INIT;
        end
        out <= a0;
      end
      endcase
    end
  end
endmodule