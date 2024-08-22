/* 
 * Do not change Module name 
*/
`timescale 1ns/1ps

module main(input clk,input resetn,input[3:1] r, output[3:1] g);
    reg[0:1] state;
    always @ (posedge clk)
    begin 
        if (~resetn) state=2'b00;
        case (state)
            2'b00: 
                begin 
                    if (r[1]) state<=2'b01;
                    if (~r[1]&r[2]) state<=2'b10;
                    if (~r[1]&~r[2]&r[3]) state<=2'b11;
                end
            2'b01: 
                begin 
                    if (~r[1]) state<=0;
                end
            2'b10: 
                begin 
                    if (~r[2]) state<=0;
                end
            2'b11: 
                begin 
                    if (~r[3]) state<=0;
                end
        endcase
    end
    assign g[1]=state==1;
    assign g[2]=state==2;
    assign g[3]=state==3;
endmodule

module test;
    reg resetn;
    reg[3:1] r;
    wire[3:1] g;
    wire[0:1] state;
    reg clk;
    main m(clk,resetn,r,g);
    
    initial
        begin
            $display("Start");
            resetn= 0;
            clk=1;
            #1 resetn=1;
            
            $display("Set ~r[1], ~r[2], ~r[3]");
            r=3'b000;
            clk=1; #1 clk=0;
            #1 $display("Expect g=0: Got g=",g);
            $display("Set r[1]");
            r=3'b001;
            clk=1; #1 clk=0;
            #1 $display("Expected g=1: Got g=",g);
            $display("Set ~r[1]");
            r=3'b000;
            clk=1; #1 clk=0;
            #1 $display("Expected g=0: Got g=",g);
            $display("Set ~r[1] r[2]");
            r=3'b010;
            clk=1; #1 clk=0;
            #1 $display("Expected g=2: Got g=",g);
            $display("Set ~r[2]");
            r=3'b000;
            clk=1; #1 clk=0;
            #1 $display("Expected g=0: Got g=",g);
            $display("Set ~r[1], ~r[2], r[3]");
            r=3'b100;
            clk=1; #1 clk=0;
            #1 $display("Expected g=4: Got g=",g);
            $display("Set ~r[3]");
            r=3'b000;
            clk=1; #1 clk=0;
            #1 $display("Expected g=0: Got g=",g);
            $display("Setting reset");
            resetn=0;
            #1 $display("Expected g=0: Got g=",g);
            $display("Setting r[1] without clk");
            r=3'b001;
            #1 $display("Expect g=0: Got g=",g);
            $finish ;
        end
endmodule
