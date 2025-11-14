`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 10/08/2020 05:43:37 PM
// Design Name: 
// Module Name: HDMI_wrapp
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module HDMI_wrapp 
(
    (* clock_signal = "yes" *) input i_clk_pixel_x5,   //371.25MHz
    (* clock_signal = "yes" *) input i_clk_pixel,      //74.25MHz
//    clk_audio,      //48KHz
//    rgb,                // where 60Hz???
//    audio_sample_word0,
//    audio_sample_word1,
    output [2:0] tmds_p,
    output [2:0] tmds_n,
    output tmds_clock_p,
    output tmds_clock_n,
    
//    input i_aclk,
    input [23:0] i_data,
    input i_valid,
    output o_ready,
    input i_sof,
    input i_eol,
    
    input i_rstn
        /* ,
    cx,
    cy,
    frame_width,
    frame_height,
    screen_width,
    screen_height,
    screen_start_x,
    screen_start_y
*/    
);

    parameter AUDIO_BIT_WIDTH = 16,
       BIT_WIDTH =12,
       BIT_HEIGHT = 10;


//    input clk_audio;

//    input [AUDIO_BIT_WIDTH-1:0] audio_sample_word0;
//    input [AUDIO_BIT_WIDTH-1:0] audio_sample_word1;
    

/*    
    output [BIT_WIDTH-1:0] cx;
    output [BIT_HEIGHT-1:0] cy;
    
    output [BIT_WIDTH-1:0] frame_width;
    output [BIT_HEIGHT-1:0] frame_height;
    output [BIT_WIDTH-1:0] screen_width;
    output [BIT_HEIGHT-1:0] screen_height;
    output [BIT_WIDTH-1:0] screen_start_x;
    output [BIT_HEIGHT-1:0] screen_start_y;
*/

    wire [BIT_WIDTH-1:0] cx;
    wire [BIT_HEIGHT-1:0] cy;
    wire hs, vs;
    wire [BIT_WIDTH-1:0] frame_width;
    wire [BIT_HEIGHT-1:0] frame_height;
    wire [BIT_WIDTH-1:0] screen_width;
    wire [BIT_HEIGHT-1:0] screen_height;
    wire [BIT_WIDTH-1:0] screen_start_x;
    wire [BIT_HEIGHT-1:0] screen_start_y;
    wire ready;
    reg [23:0] rgb_o;
    
    
    hdmi 
    #(  19,     //  VIDEO_ID_CODE
        12,     //  BIT_WIDTH
        10,      //  BIT_HEIGHT
        1'b1,       //  DVI_OUTPUT 
        1'b0,       // DDRIO
        50.00,//59.94,   //VIDEO_REFRESH_RATE
        44100,  //AUDIO_RATE
        16,     //AUDIO_BIT_WIDTH
        {8'h55,8'h6e,8'h6b,8'h6e,8'h6f,8'h77,8'h6e, 8'd0},  //VENDOR_NAME
        {8'h46,8'h50,8'h47,8'h41, 96'h0},   //PRODUCT_DESCRIPTION
        8'h00   //SOURCE_DEVICE_INFORMATION
        ) 
   hdmi_inst 
    (
    .clk_pixel_x10 (i_clk_pixel_x5),
    .clk_pixel (i_clk_pixel),
//    .clk_audio (),//(clk_audio),
    .rgb2 (rgb_o),
//    .audio_sample_word (),
//    .audio_sample_word0 (),//(audio_sample_word0),
//    .audio_sample_word1 (),//(audio_sample_word1),
    .tmds_p (tmds_p),
    .tmds_clock_p (tmds_clock_p),
    .tmds_n (tmds_n),
    .tmds_clock_n (tmds_clock_n),
    .cx (cx),
    .cy (cy),
    .hsync (hs),
    .vsync (vs),
    .frame_width (frame_width),
    .frame_height (frame_height),
    .screen_width (screen_width),
    .screen_height (screen_height),
    .screen_start_x (screen_start_x),
    .screen_start_y (screen_start_y),
    .video_data_period (ready),
    .rstn (i_rstn)   
    );

   //assign rgb = (cx <= (screen_start_x + screen_width/3)) ? 24'h0000ff:
   //             (cx > (screen_start_x + screen_width/3) && cx <= (screen_start_x + screen_width/3*2)) ? 24'h00ff00:
   //            24'h990000;
   
always@(posedge i_clk_pixel, negedge i_rstn)
begin
     if (i_rstn == 0)
        rgb_o <= 24'h000000;
     else
        rgb_o <= i_data;
/*        (cx <= (screen_start_x + screen_width/3)) ? 24'h0000ff:
                (cx > (screen_start_x + screen_width/3) && cx <= (screen_start_x + screen_width/3*2)) ? 24'h00ff00:
               24'hff0000;
*/end
//   assign rgb_o = (cx <= (screen_start_x + screen_width/3)) ? 24'h0000ff:
//                (cx > (screen_start_x + screen_width/3) && cx <= (screen_start_x + screen_width/3*2)) ? 24'h00ff00:
//               24'hff0000;

//   assign rgb = (cx <= 312) ? 24'h000088:(cx>312 && cx<=552) ? 24'h003300:24'hee0000;
//reg [2:0] state;
/*
   always@(posedge i_clk_pixel, negedge i_rstn)
   begin
        if(i_rstn == 0)
        begin
            state <= 0;
        end
        else
            case(state)
                0:begin
                    
                end
            endcase     
   end
*/   
//    assign o_ready = (   
assign o_ready = ready;
//assign rgb = i_data;
                
endmodule
