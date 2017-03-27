/*	
	4-bit unsigned Multiplier adder circuit on DE10-LITE
	8 Switches used to enter 2 4-bit numbers
	Segments HEX2 and HEX0 display 4-bit numbers
	Segements HEX5 and HEX4 display product in HEX
*/

module Chp3_Multiplier_top (Switches, SEG5, SEG4, SEG2, SEG0);

input [7:0] Switches;
output [6:0] SEG5, SEG4, SEG2, SEG0;
wire [7:0] Product;

Multipliern U0 (Switches, Product);
defparam U0.n = 4;

Single_Segment U1 (
	.Case(Switches[7:4]),
	.Out(SEG2)
	);
Single_Segment U2 (
	.Case(Switches[3:0]),
	.Out(SEG0)
	);
	
Single_Segment U3 (
	.Case(Product[3:0]),
	.Out(SEG4)
	);

Single_Segment U4 (
	.Case(Product[7:4]),
	.Out(SEG5)
	);

endmodule

module Multipliern(M, Q, P);

parameter n = 4;
input [n-1:0] M, Q;
output reg [2*n-1:0] P;
wire [4*n-1:4] W;
wire [4*n-1:0] WFA;
wire [4*n-1:4] C;


/* Perform first two Ands*/
	and(WFA[0], M[0], Q[0]),
		(WFA[1], M[1], Q[0]),
		(WFA[2], M[2], Q[0]),
		(WFA[3], M[3], Q[0]);
	and(W[4], M[0], Q[1]),
		(W[5], M[1], Q[1]),
		(W[6], M[2], Q[1]),
		(W[7], M[3], Q[1]);
		
/* Sum the two Ands */
		fulladder FA0 (1'b0, W[4], WFA[1], WFA[4], C[4]); // Cin, X, Y, S, Cout
		fulladder FA1 (C[4], W[5], WFA[2], WFA[5], C[5]);
		fulladder FA2 (C[5], W[6], WFA[3], WFA[6], C[6]);
		fulladder FA3 (C[6], W[7], 1'b0,   WFA[7], C[7]);

genvar i;

generate
		for(i = 2; i < n; i=i+1)
		begin: i_loop
			/* Perform Reoccuring And*/
			and(W[4*i+0], M[0], Q[i]),
				(W[4*i+1], M[1], Q[i]),
				(W[4*i+2], M[2], Q[i]),
				(W[4*i+3], M[3], Q[i]);
			
			fulladder stage0 (1'b0,     W[4*i+0], WFA[4*(i-1)+1], WFA[4*i+0], C[4*i+0]);
			fulladder stage1 (C[4*i+0], W[4*i+1], WFA[4*(i-1)+2], WFA[4*i+1], C[4*i+1]);
			fulladder stage2 (C[4*i+1], W[4*i+2], WFA[4*(i-1)+3], WFA[4*i+2], C[4*i+2]);
			fulladder stage3 (C[4*i+2], W[4*i+3], C[4*i-1],       WFA[4*i+3], C[4*i+3]);
		end
endgenerate

	integer k;
	always @ (WFA)
	begin
		for(k = 0; k < n; k=k+1)
			begin: k_loop
				P[k] = WFA[4*k];
			end
			P[2*n-2: n] = WFA[4*n-1:4*n-3];  // WFA15-13
			P[2*n-1] = C[4*n-1];					// set final carry bit
	end
endmodule 


module fulladder (input Cin, input X, input Y, output S, output Cout);
	assign Cout = (X&Y)|(Cin&X)|(Y&Cin);
	assign S = X ^ Y ^ Cin;
endmodule 