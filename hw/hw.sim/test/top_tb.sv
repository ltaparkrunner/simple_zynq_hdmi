module top_tb();

timeunit 1ns;
timeprecision 1ns;

initial begin
  #40ms $finish;
end

top top ();

logic [9:0] cx = 800 - 4;
logic [9:0] cy = 525 - 1;

logic [9:0] tmds_values [2:0] = '{10'dx, 10'dx, 10'dx};

always @(posedge top.clk_pixel)
begin
  tmds_values[0] <= top.HDMI_wrapp.hdmi_inst.tmds[0];
  tmds_values[1] <= top.HDMI_wrapp.hdmi_inst.tmds[1];
  tmds_values[2] <= top.HDMI_wrapp.hdmi_inst.tmds[2];
end

always @(posedge top.clk_pixel)
begin
  cx <= cx == top.HDMI_wrapp.frame_width - 1 ? 0 : cx + 1;
  cy <= cx == top.HDMI_wrapp.frame_width-1'b1 ? cy == top.HDMI_wrapp.frame_height-1'b1 ? 0 : cy + 1'b1 : cy;
  if (cx >= 8 && cx < 10)
  begin
    assert(tmds_values[2] == 10'b0100110011) else $fatal("Channel 2 DI GB incorrect: %b", tmds_values[2]);
    assert(tmds_values[1] == 10'b0100110011) else $fatal("Channel 1 DI GB incorrect");
    assert(tmds_values[0] == 10'b1010001110 || tmds_values[0] == 10'b1001110001 || tmds_values[0] == 10'b0101100011 || tmds_values[0] == 10'b1011000011) else $fatal("Channel 0 DI GB incorrect");
  end
end

endmodule
