// This is a FAKE PLL! You should be using the PLL IP available from your FPGA vendor

timeunit 1ps;
timeprecision 1ps;

module pll(
	output logic c0 = 0,
	output logic c1 = 0
);
always
begin
	#1347ps c0 = 1;
	#1347ps c0 = 0;
end

always
begin
	#13470ps c1 = 1;
	#13470ps c1 = 0;
end

endmodule
