
/* 
	Compares 2 Four-bit Numbers by using subtraction
	Three outputs: 
		Z = 1 if numbers are equal
		N = 1 if result is negative
		V = 1 if arithmetic overflow occurs
		(Z, N, V are 0 otherwise)
						
	Swithches (SW7-0) on DE10-Lite are used to enter numbers
	LEDR2-0 indicate V, N, and Z
	
*/

module Chp3_top (Switch, V, N, Z);


input [7:0] Switch;
output V, N, Z; // link these to the LEDs
wire [4:0] w;

addern U1 (
	.Cin(1'b1),					// subtraction
	.Num1(Switch[7:4]),
	.Num2(Switch[3:0]),
	.S(w[3:0]),
	.overflow(w[4])
	);
defparam U1.n = 4;

get_V U2 (w[4:3], V);
get_N U3 (w[3], N);
get_Z U4 (w[3:0], Z);


endmodule


module addern (Cin, Num1, Num2, S, overflow);
parameter n = 4;

input Cin;
input [n-1:0] Num1, Num2;
output [n-1:0] S;
output overflow;
wire [n-1:0] w1;
wire [n:0] w2;

xor(w1[3], Cin, Num2[3]),
	(w1[2], Cin, Num2[2]),
	(w1[1], Cin, Num2[1]),
	(w1[0], Cin, Num2[0]);
	
	
	
assign w2[0] = Cin;
assign overflow = w2[n] ^ w2[n-1];

genvar i;

generate 
	for (i = 0; i < n; i=i+1)
		begin: i_loop
			fulladd stage (w2[i], Num1[i], w1[i], S[i], w2[i+1]);
		end
endgenerate

endmodule

module fulladd (Cin, X, Y, S, Cout);
input Cin, X, Y;
output S, Cout;

assign S = Cin ^ X ^ Y;
assign Cout = (X&Y)|(Cin&X)|(Cin&Y);

endmodule

module get_V (Carries, V);
input [1:0] Carries;
output V;

xor(V, Carries);
endmodule

module get_N (in, N);
input in;
output N;

assign N = in;
endmodule

module get_Z(S, f);
input [3:0] S;
output f;

assign f = !S;
endmodule 