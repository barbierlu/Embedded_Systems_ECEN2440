module Project_2_top (button, Clk, led, seg_sec, seg_tsec, seg_hsec);
	input [1:0] button;
	input Clk;
	output reg led;
	output [7:0] seg_sec;
	output [6:0] seg_tsec, seg_hsec;
	
	parameter A = 0;
	parameter B = 1;
	parameter C = 2;
	parameter D = 3;
	
	reg en_bcd, en_upcount, reset_n;
	
	reg [1:0] state;
	
	always @(posedge Clk, posedge button)
	begin
		if (button[0] == 1) // possible debug issue with posedge
			state <= 0;
		else
			case (state)
				0:
					begin
						en_bcd <= 0;
						en_upcount <= 0;
						led <= 0;
						reset_n <= 1;
						
					end
				1: ;	// up_counter will change this state
				2: ;
				3: ;
				default: ; // change back to 0
			
	
	
	end
		case (state)

endmodule 
