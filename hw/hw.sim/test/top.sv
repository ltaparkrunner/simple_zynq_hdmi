module top ();
logic [2:0] tmds_p;
logic tmds_clock_p;
logic [2:0] tmds_n;
logic tmds_clock_n;

logic clk_pixel;
logic clk_pixel_x10;

pll pll(.c0(clk_pixel_x10), .c1(clk_pixel));

logic ready;
logic rstn;
initial begin
  rstn = 0;
  #20 rstn = 1;
end

logic [23:0] rgb; // = 24'd0;
assign rgb = !ready ? 24'h000 : 24'h111;
// 640x480 @ 59.94Hz
HDMI_wrapp HDMI_wrapp(
  .i_clk_pixel_x5(clk_pixel_x10),
  .i_clk_pixel(clk_pixel),
  .tmds_p(tmds_p),
  .tmds_clock_p(tmds_clock_p),
  .tmds_n(tmds_n),
  .tmds_clock_n(tmds_clock_n),
  .i_data(rgb),
  .i_valid(),
  .o_ready(ready),
  .i_sof(),
  .i_eol(),
  .i_rstn(rstn)
);

endmodule
