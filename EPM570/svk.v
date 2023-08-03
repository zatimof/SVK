// Top-level module
module svk(	addr,
				data,
				MSP_RD,
				MSP_WR,
				dig_p1,
				dig_p2,
				dig_p3,
				dig_p4,
				usb_port,
				USB_RST,
				USB_ARE,
				USB_AWE,
				USB_TXE,
				USB_RXF,
				SDAC_MOSI,
				SDAC_SCLK,
				SDAC_CS12,
				SDAC_CS34,
				SDAC_LOAD,
				SDAC_CLR,
				SIN_MOSI,
				SIN_SCLK,
				SIN_CS,
				SIN_LOAD,
				SIN_CLR,
				DPFL_CS,
				DP_MOSI,
				DPA_CS,
				DP_CLK,
				FL_CLK,
				F_U10,
				F_U1,
				F_DC10,
				F_DC1,
				E_BID,
				E_MISO,
				E_MOSI,
				E_SCK, 
				LED_B,
				GCLK,
				SPI_CLK,
				SPI_CS,
				SPI_MOSI,
				SPI_MISO,
				SPI_RST);

parameter 	ver1_adr=8'd251,
				ver2_adr=8'd252,
				ver3_adr=8'd253,
				ver4_adr=8'd254,
				sr_adr=8'd255,
				ver1=8'd0,
				ver2=8'd0,
				ver3=8'd0,
				ver4=8'd1;			//1.0.0.0
				
input	MSP_RD,
		MSP_WR,
		USB_TXE,
		USB_RXF,
		E_MISO,
		SPI_MISO,
		GCLK,
		F_U10,
		F_U1,
		F_DC10,
		F_DC1;
				
input [7:0] addr;

output	USB_RST,
			USB_ARE,
			USB_AWE,
			SDAC_MOSI,
			SDAC_SCLK,
			SDAC_CS12,
			SDAC_CS34,
			SDAC_LOAD,
			SDAC_CLR,
			SIN_MOSI,
			SIN_SCLK,
			SIN_CS,
			SIN_LOAD,
			SIN_CLR,
			FL_CLK,
			DPFL_CS,
			DP_MOSI,
			DPA_CS,
			DP_CLK,
			E_BID,
			E_MOSI,
			E_SCK,
			LED_B,
			SPI_CLK,
			SPI_CS,
			SPI_MOSI,
			SPI_RST;

inout [7:0]	data,
				usb_port,
				dig_p1,
				dig_p2,
				dig_p3,
				dig_p4;

wire 	DPCLK,
		FMCLK,
		MCLK,
		WR_F,
		U10_F,
		U1_F,
		DC10_F,
		DC1_F,
		BUSY,
		SPI1_ERR,
//		SPI2_ERR,
//		SPI3_ERR,
		arclk,
		ardin,
		arshft,
		drclk,
		drdin,
		drdout,
		drshft,
		erase,
		oscena,
		progr,
		busy,
		osc,
		rtpbusy;
				
reg 	RD,
		WR,
		WR_S,
		U10,
		U10_S,
		U1,
		U1_S,
		DC10,
		DC10_S,
		DC1,
		DC1_S;
		
assign 	data=((addr==ver1_adr)&&(RD==1'b0))?ver1:8'bz,
			data=((addr==ver2_adr)&&(RD==1'b0))?ver2:8'bz,
			data=((addr==ver3_adr)&&(RD==1'b0))?ver3:8'bz,
			data=((addr==ver4_adr)&&(RD==1'b0))?ver4:8'bz,
			data=((addr==sr_adr)&&(RD==1'b0))?{1'b0, 1'b0, 1'b0, SPI1_ERR, ~USB_RXF, ~USB_TXE, 1'b0, BUSY}:8'bz,
			WR_F=WR_S&~WR,
			U10_F=(U10_S&~U10)|(U10&~U10_S),
			U1_F=(U1_S&~U1)|(U1&~U1_S),
			DC10_F=(DC10_S&~DC10)|(DC10&~DC10_S),
			DC1_F=(DC1_S&~DC1)|(DC1&~DC1_S);		
			
// Define combinational logic circuit
usb M1(RD, WR, data, addr, USB_ARE, USB_AWE, usb_port);
io M2(RD, WR, data, addr, dig_p1, dig_p2, dig_p3, dig_p4);
clk M3(GCLK, MCLK, LED_B, DPCLK, FMCLK);
rst M4(WR, data, addr, USB_RST, SIN_CLR, SDAC_CLR, SPI_RST);
fl M5(WR_F, data, addr, GCLK, FL_CLK);
sdac M6(WR_F, data, addr, GCLK, MCLK, SIN_MOSI, SIN_SCLK, SIN_CS, SIN_LOAD, arclk, ardin, arshft, drclk, drdin, drdout, drshft, erase, oscena, progr);
vdac M7(WR, data, addr, DPCLK, SDAC_MOSI, SDAC_SCLK, SDAC_CS12, SDAC_CS34, SDAC_LOAD);
//sdac M6(WR, data, addr, GCLK, SDAC_MOSI, SDAC_SCLK, SDAC_CS12, SDAC_CS34, SDAC_LOAD);
dp M8(WR, data, addr, DPCLK, DPA_CS, DPFL_CS, DP_CLK, DP_MOSI);
fm M9(GCLK, RD, data, addr, FMCLK, U10_F, U1_F, DC10_F, DC1_F);
ee M10(RD, WR, data, addr, DPCLK, GCLK, E_BID, E_MOSI, E_MISO, E_SCK, BUSY);
spi M11(WR, data, addr, DPCLK, SPI_CLK, SPI_CS, SPI_MOSI, SPI_MISO, SPI1_ERR);
mem_altufm_none_5ar M12(arclk, ardin, arshft, busy, drclk, drdin, drdout, drshft, erase, osc, oscena, progr, rtpbusy);

// Define flip-flops and registers
always @(posedge GCLK)
begin 
	if(MSP_WR)
		RD<=MSP_RD;
	else
		RD<=1'b1;
		
	if(MSP_RD)
		WR<=MSP_WR;
	else
		WR<=1'b1;
	
	WR_S<=WR;
	U10<=F_U10;
	U10_S<=U10;
	U1<=F_U1;
	U1_S<=U1;
	DC10<=F_DC10;
	DC10_S<=DC10;
	DC1<=F_DC1;
	DC1_S<=DC1;
end
endmodule

//--------------------------------------------------------------------------------------------------------
module usb(	RD,
				WR,
				data,
				addr,
				USB_ARE,
				USB_AWE,
				usb_port);

parameter usb_adr=8'd6;

input	RD,
		WR;
		
input [7:0] addr;

output	USB_ARE,
			USB_AWE;
inout [7:0] data, usb_port;

assign	data=((addr==usb_adr)&&(RD==1'b0))?usb_port:8'bz,
			usb_port=((addr==usb_adr)&&(RD==1'b1))?data:8'bz,
			USB_ARE=(addr==usb_adr)?RD:1'b1,
			USB_AWE=(addr==usb_adr)?WR:1'b1;
endmodule

//-----------------------------------------------------------------------------------------------------------
module io(	RD,
				WR,
				data,
				addr,
				dig_p1,
				dig_p2,
				dig_p3,
				dig_p4);

parameter	io_p1_adr=8'd1,
				io_p2_adr=8'd2,
				io_p3_adr=8'd3,
				io_p4_adr=8'd4,
				io_upr_adr=8'd5;

input	RD,
		WR;
		
input [7:0] addr;

inout [7:0]	data,
				dig_p1,
				dig_p2,
				dig_p3,
				dig_p4;

reg [7:0]	o1,
				o2,
				o3,
				o4,
				upr;

assign 	data=((addr==io_p1_adr)&&(!RD)&&(!upr[0]))?dig_p1:8'bz,
			data=((addr==io_p2_adr)&&(!RD)&&(!upr[1]))?dig_p2:8'bz,
			data=((addr==io_p3_adr)&&(!RD)&&(!upr[2]))?dig_p3:8'bz,
			data=((addr==io_p4_adr)&&(!RD)&&(!upr[3]))?dig_p4:8'bz,
			dig_p1=upr[0]?o1:8'bz,
			dig_p2=upr[1]?o2:8'bz,
			dig_p3=upr[2]?o3:8'bz,
			dig_p4=upr[3]?o4:8'bz;

always @(negedge WR)
begin
if(addr==io_upr_adr)
	upr<=data;
	
if(addr==io_p1_adr)
	o1<=data;
	
if(addr==io_p2_adr)
	o2<=data;
	
if(addr==io_p3_adr)
	o3<=data;
	
if(addr==io_p4_adr)
	o4<=data;
end
endmodule 

//-----------------------------------------------------------------------------------------------------------
module clk(	GCLK,
				MCLK,
				LED_B,
				DPCLK,
				FMCLK);

input	GCLK;
		
output 	MCLK,
			DPCLK;
output reg	LED_B,
				FMCLK;

reg [23:0] 	cnt;

assign 	MCLK=cnt[0],
			DPCLK=cnt[6];
			
always @(posedge GCLK)
begin
	cnt<=cnt+24'd1;
	
	if(cnt==24'd9216000)
	begin
		FMCLK=1'b1;
		LED_B=~LED_B;
		cnt<=24'd0;
	end
	else
		FMCLK=1'b0;
end
endmodule 

//-----------------------------------------------------------------------------------------------------------
module rst(	WR,
				data,
				addr,
				USB_RST,
				SIN_CLR,
				SDAC_CLR,
				SPI_RST);

parameter	rst_adr=8'd0;

input	WR;
input [7:0] addr;

output 	USB_RST,
			SIN_CLR,
			SDAC_CLR,
			SPI_RST;
			
inout [7:0]	data;
reg [7:0] reset;

assign 	USB_RST=reset[0],
			SDAC_CLR=reset[1],
			SIN_CLR=reset[2],
			SPI_RST=reset[3];

always @(negedge WR)
if(addr==rst_adr)
	reset<=data;
				
endmodule 

//-----------------------------------------------------------------------------------------------------------
module fl (	WR_F,
				data,
				addr,
				GCLK,
				FL_CLK);

parameter	fl_ml_adr=8'd19,
				fl_st_adr=8'd20;
	
input WR_F, GCLK;
input [7:0] addr;
inout [7:0]	data;
output reg FL_CLK;

reg [15:0] flr1, flr2;
reg [7:0] tmp;
			
always @(posedge GCLK)
begin
	if(flr2==16'd0)
	begin
		FL_CLK=~FL_CLK;
		flr2=flr1+16'd1;
	end
	else
		flr2=flr2-16'd1;
		
	if((WR_F==1'b1)&&(addr==fl_ml_adr))	
		tmp<=data;
	
	if((WR_F==1'b1)&&(addr==fl_st_adr))	
		flr1<={data,tmp};
end
endmodule 

//-----------------------------------------------------------------------------------------------------------
module sdac (	WR_F,
					data,
					addr,
					GCLK,
					MCLK,
					SIN_MOSI,
					SIN_SCLK,
					SIN_CS,
					SIN_LOAD,
					arclk,
					ardin,
					arshft,
					drclk,
					drdin,
					drdout,
					drshft,
					erase,
					oscena,
					progr);

parameter	dds_ml_adr=8'd17,
				dds_st_adr=8'd18;
	
input WR_F, GCLK, MCLK, drdout;
input [7:0] addr;
inout [7:0]	data;
output SIN_MOSI, SIN_SCLK, SIN_LOAD, arclk, ardin, drclk, drdin, arshft, erase, oscena, progr;
output reg SIN_CS, drshft;

reg [4:0] point;
reg [7:0] tmp;
reg [23:0] shift;
reg [15:0] memr, ddsr, point1;
reg  drshft_s, arc;
wire drshft_f;

assign 	progr=1'b0,
			erase=1'b0,
			oscena=1'b0,
			ardin=1'b0,		
			drdin=1'b0,
			drclk=MCLK,
			arshft=drshft,
			arclk=MCLK|arc,
			SIN_SCLK=GCLK,
			SIN_MOSI=shift[point],
			SIN_LOAD=1'b0,
			drshft_f=drshft_s&~drshft;

always @(negedge MCLK)
begin

	if(point1==16'd16)
		arc=1'b0;
		
	if(point1==16'd15)
	begin
		arc=1'b1;
		drshft=1'b1;
	end
	
	memr[point1[3:0]]=drdout;
	point1=point1-16'd1;
	
	if(point1==16'hffff)
	begin
		drshft=1'b0;
		point1=ddsr+16'd16;
	end
end			
			
always @(posedge GCLK)
begin
	drshft_s<=drshft;
	
	if(drshft_f)
	begin
		shift[15:0]=memr;
		shift[23:16]=8'h17;
		SIN_CS=1'b0;
		point=5'd23;
	end
	else
	begin
		point=point-5'd1;
		if(point==5'd31)
		begin
			SIN_CS=1'b1;
			shift[0]=1'b0;
			point=5'd0;
		end
	end
	
	if((WR_F==1'b1)&&(addr==dds_ml_adr))	
		tmp<=data;
	
	if((WR_F==1'b1)&&(addr==dds_st_adr))	
		ddsr<={data,tmp};
end
endmodule 

//-----------------------------------------------------------------------------------------------------------
module vdac(	WR,
					data,
					addr,
					DPCLK,
					SDAC_MOSI,
					SDAC_SCLK,
					SDAC_CS12,
					SDAC_CS34,
					SDAC_LOAD);

parameter	ur1_ml_adr=8'd7,
				ur1_st_adr=8'd8,
				ur2_ml_adr=8'd9,
				ur2_st_adr=8'd10,
				ur3_ml_adr=8'd11,
				ur3_st_adr=8'd12,
				ur4_ml_adr=8'd13,
				ur4_st_adr=8'd14;
	
input WR, DPCLK;
input [7:0] addr;
inout [7:0]	data;
output SDAC_MOSI, SDAC_SCLK, SDAC_LOAD, SDAC_CS34;
output reg SDAC_CS12;

reg [6:0] point;
reg [7:0] tmp;
reg [95:0] shift;
reg [15:0] memr, ddsr, point1;
reg  drshft_s, arc;
wire drshft_f;

assign 	SDAC_SCLK=DPCLK,
			SDAC_MOSI=shift[point],
			SDAC_CS34=~SDAC_CS12,
			SDAC_LOAD=1'b0;

always @(posedge DPCLK)
begin
	if((point==7'd0)||(point==7'd48))
		SDAC_CS12=1'b0;
	if((point==7'd24)||(point==7'd72))
		SDAC_CS12=1'b1;
	point=point-7'd1;
	if(point==7'd127)
		point=7'd95;
end

always @(negedge WR)
begin
if(addr==ur1_ml_adr)
	tmp<=data;
	
if(addr==ur1_st_adr)
	shift[39:24]<={data,tmp};
	
if(addr==ur2_ml_adr)
	tmp<=data;
	
if(addr==ur2_st_adr)
	shift[87:72]<={data,tmp};
	
if(addr==ur3_ml_adr)
	tmp<=data;
	
if(addr==ur3_st_adr)
	shift[15:0]<={data,tmp};
	
if(addr==ur4_ml_adr)
	tmp<=data;
	
if(addr==ur4_st_adr)
	shift[63:48]<={data,tmp};
	
shift[23:16]=8'h10;
shift[47:40]=8'h10;
shift[71:64]=8'h11;
shift[95:88]=8'h11;
end
endmodule
/*
//-----------------------------------------------------------------------------------------------------------
module sdac (	WR,
					data,
					addr,
					GCLK,
					SDAC_MOSI,
					SDAC_SCLK,
					SDAC_CS12,
					SDAC_CS34,
					SDAC_LOAD);

parameter	dac_ml_adr=8'd26,
				dac_st_adr=8'd27;
	
input WR, GCLK;
input [7:0] addr;
inout [7:0]	data;
output SDAC_MOSI, SDAC_SCLK, SDAC_CS12, SDAC_LOAD;
output reg SDAC_CS34;

reg [4:0] point;
reg [23:0] shift;
reg [15:0] memr;
reg  start, start_s;
wire start_f;

assign 	SDAC_SCLK=GCLK,
			SDAC_MOSI=shift[point],
			SDAC_LOAD=1'b0,
			SDAC_CS12=1'b1,
			start_f=start&~start_s;

always @(posedge GCLK)
begin
	start_s<=start;
	
	if(start_f)
	begin
		shift[15:0]=memr;
		shift[23:16]=8'h17;
		SDAC_CS34=1'b0;
		point=5'd23;
	end
	else
	begin
		point=point-5'd1;
		if(point==5'd31)
		begin
			SDAC_CS34=1'b1;
			shift[0]=1'b0;
			point=5'd0;
		end
	end
end

always @(negedge WR)
begin
if(addr==dac_ml_adr)
begin
	memr[7:0]<=data;
	start=1'b0;
end
	
if(addr==dac_st_adr)
begin
	memr[15:8]<=data;
	start=1'b1;
end
end
endmodule 

//-----------------------------------------------------------------------------------------------------------
module pdac(	STB5,
					dac_port);

input STB5;
output reg [4:0] dac_port;

wire [4:0] sin5 [15:0];
reg [3:0] point5;

assign	sin5[0]=5'd16,
			sin5[1]=5'd22,
			sin5[2]=5'd27,
			sin5[3]=5'd30,
			sin5[4]=5'd31,
			sin5[5]=5'd30,
			sin5[6]=5'd27,
			sin5[7]=5'd22,
			sin5[8]=5'd16,
			sin5[9]=5'd10,
			sin5[10]=5'd5,
			sin5[11]=5'd1,
			sin5[12]=5'd0,
			sin5[13]=5'd1,
			sin5[14]=5'd5,
			sin5[15]=5'd10;

always @(posedge STB5)
begin
	dac_port<=sin5[point5];
	point5=point5+4'd1;
end
endmodule 
*/

//-----------------------------------------------------------------------------------------------------------
module dp(	WR,
				data,
				addr,
				DPCLK,
				DPA_CS,
				DPFL_CS,
				DP_CLK,
				DP_MOSI);

parameter 	dp_an_adr=8'd15,
				dp_fl_adr=8'd16;

input WR,
		DPCLK;
		
input [7:0] addr;

inout [7:0] data;
				
output 	DPFL_CS,
			DP_CLK,
			DP_MOSI;
			
output reg DPA_CS;

reg [19:0] shift;
reg [4:0] point;

assign 	DP_CLK=~DPCLK,
			DPFL_CS=~DPA_CS,
			DP_MOSI=shift[point];

always @(posedge DPCLK)
begin
	if(point==5'd0)
		DPA_CS=1'b0;
		
	if(point==5'd10)
		DPA_CS=1'b1;
		
	point=point-5'd1;
	
	if(point==5'b11111)
		point=5'b10011;
end

always @(negedge WR)
begin
if(addr==dp_fl_adr)
	shift[7:0]<=data;
	
if(addr==dp_an_adr)
	shift[17:10]<=data;
	
shift[9:8]=2'b00;
shift[19:18]=2'b00;
end
endmodule 

//-----------------------------------------------------------------------------------------------------------
module fm(	GCLK,
				RD,
				data,
				addr,
				FMCLK,
				U10_F,
				U1_F,
				DC10_F,
				DC1_F);

parameter 	fm_rms10_ml_adr=8'd21,
				fm_rms10_st_adr=8'd22,
				fm_rms1_ml_adr=8'd23,
				fm_rms1_st_adr=8'd24,
				fm_dc10_ml_adr=8'd25,
				fm_dc10_st_adr=8'd26,
				fm_dc1_ml_adr=8'd27,
				fm_dc1_st_adr=8'd28;

input GCLK,
		RD,
		FMCLK,
		U10_F,
		U1_F,
		DC10_F,
		DC1_F;
		
input [7:0] addr;

inout [7:0] data;

reg [15:0] 	fu10,
				fu1,
				fdc10,
				fdc1,
				cnt1,
				cnt2,
				cnt3,
				cnt4;

assign 	data=((addr==fm_rms10_st_adr)&&(!RD))?fu10[15:8]:8'bz,
			data=((addr==fm_rms10_ml_adr)&&(!RD))?fu10[7:0]:8'bz,
			data=((addr==fm_rms1_st_adr)&&(!RD))?fu1[15:8]:8'bz,
			data=((addr==fm_rms1_ml_adr)&&(!RD))?fu1[7:0]:8'bz,
			data=((addr==fm_dc10_st_adr)&&(!RD))?fdc10[15:8]:8'bz,
			data=((addr==fm_dc10_ml_adr)&&(!RD))?fdc10[7:0]:8'bz,
			data=((addr==fm_dc1_st_adr)&&(!RD))?fdc1[15:8]:8'bz,
			data=((addr==fm_dc1_ml_adr)&&(!RD))?fdc1[7:0]:8'bz;
			
always @(posedge GCLK)
begin
	if(U10_F)
		cnt1=cnt1+16'd1;
		
	if(U1_F)
		cnt2=cnt2+16'd1;
		
	if(DC10_F)
		cnt3=cnt3+16'd1;
		
	if(DC1_F)
		cnt4=cnt4+16'd1;

	if(FMCLK)
	begin
		fu10=cnt1;
		fu1=cnt2;
		fdc10=cnt3;
		fdc1=cnt4;
		cnt1=16'd0;
		cnt2=16'd0;
		cnt3=16'd0;
		cnt4=16'd0;
	end
end
endmodule

//-----------------------------------------------------------------------------------------------------------
module ee(	RD,
				WR_F,
				data,
				addr,
				DPCLK,
				GCLK,
				E_BID,
				E_MOSI,
				E_MISO,
				E_SCK,
				BUSY);

parameter 	ee_data_ml_adr=8'd29,
				ee_data_st_adr=8'd30,
				ee_adr_adr=8'd31,
				ee_upr_adr=8'd32;

input RD,
		WR_F,
		DPCLK,
		GCLK,
		E_MISO;
		
output 	E_BID,
			E_MOSI,
			E_SCK,
			BUSY;
			
input [7:0] addr;

inout [7:0] data;

reg 	E_BID,
		DPCLK_S;
		
reg [31:0] 	eero,
				eeri;
				
reg [4:0] 	point;

wire 	DPCLK_F;

assign 	DPCLK_F=~DPCLK&DPCLK_S,
			E_SCK=DPCLK_S,
			E_MOSI=eero[point],
			BUSY=eero[30],
			data=((addr==ee_data_st_adr)&&(!RD))?eeri[15:8]:8'bz,
			data=((addr==ee_data_ml_adr)&&(!RD))?eeri[7:0]:8'bz;

always @(posedge GCLK)
begin 
	DPCLK_S<=DPCLK;
	
	if(WR_F)
	begin
		if(addr==ee_data_ml_adr)
			eero[7:0]=data;
		if(addr==ee_data_st_adr)
			eero[15:8]=data;
		if(addr==ee_adr_adr)
			eero[23:16]=data;
		if((addr==ee_upr_adr)&&(data[7:2]==6'b010101))
		begin
			eero[31:24]=data;
			point<=5'd27;
		end
	end
	
	if(DPCLK_F&&BUSY)
		if(point!=5'd0)
		begin
			point<=point-5'd1;
			eeri[point]=E_MISO;
			E_BID=1'b1;
		end
		else
		begin
			eeri[0]=E_MISO;
			eero[30]=1'b0;
			E_BID=1'b0;
			point<=5'd27;
		end
end
endmodule

//-----------------------------------------------------------------------------------------------------------
module spi(	WR,
				data,
				addr,
				DPCLK,
				SPI_CLK,
				SPI_CS,
				SPI_MOSI,
				SPI_MISO,
				SPI1_ERR);

parameter 	spi_r1_adr=8'd33,
				spi_r2_adr=8'd34,
				spi_r3_adr=8'd35,
				spi_r4_adr=8'd36,
				spi_r5_adr=8'd37,
				spi_r6_adr=8'd38;

input WR,
		DPCLK,
		SPI_MISO;
		
input [7:0] addr;

inout [7:0] data;
				
output 	SPI_CLK,
			SPI_MOSI;
			
output reg 	SPI_CS,
				SPI1_ERR;

reg [48:0] shifto, shifti;
reg [5:0] point;

assign 	SPI_CLK=DPCLK,
			SPI_MOSI=shifto[point];
			
always @(negedge DPCLK)
begin
	if(point==6'd48)
	begin
		SPI_CS=1'b1;
		point=6'd0;
	end
	else
		SPI_CS=1'b0;
	
	shifti[point]=SPI_MISO;
	point=point+6'd1;
		
	if(shifto==shifti)
		SPI1_ERR=1'b0;
	else
		SPI1_ERR=1'b1;
end

always @(negedge WR)
begin
if(addr==spi_r1_adr)
	shifto[7:0]<=data;
	
if(addr==spi_r2_adr)
	shifto[15:8]<=data;
	
if(addr==spi_r3_adr)
	shifto[23:16]<=data;
	
if(addr==spi_r4_adr)
	shifto[31:24]<=data;
	
if(addr==spi_r5_adr)
	shifto[39:32]<=data;
	
if(addr==spi_r6_adr)
	shifto[47:40]<=data;
end
endmodule

