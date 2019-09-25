-- cpu.vhd: Simple 8-bit CPU (BrainF*ck interpreter)
-- Copyright (C) 2018 Brno University of Technology,
--                    Faculty of Information Technology
-- Author(s): xfrejl00
--
library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- ----------------------------------------------------------------------------
--                        Entity declaration
-- ----------------------------------------------------------------------------
entity cpu is
 port (
   CLK   : in std_logic;  -- hodinovy signal
   RESET : in std_logic;  -- asynchronni reset procesoru
   EN    : in std_logic;  -- povoleni cinnosti procesoru
 
   -- synchronni pamet ROM
   CODE_ADDR : out std_logic_vector(11 downto 0); -- adresa do pameti
   CODE_DATA : in std_logic_vector(7 downto 0);   -- CODE_DATA <- rom[CODE_cnt] pokud CODE_EN='1'
   CODE_EN   : out std_logic;                     -- povoleni cinnosti
   
   -- synchronni pamet RAM
   DATA_ADDR  : out std_logic_vector(9 downto 0); -- adresa do pameti
   DATA_WDATA : out std_logic_vector(7 downto 0); -- mem[DATA_cnt] <- DATA_WDATA pokud DATA_EN='1'
   DATA_RDATA : in std_logic_vector(7 downto 0);  -- DATA_RDATA <- ram[DATA_cnt] pokud DATA_EN='1'
   DATA_RDWR  : out std_logic;                    -- cteni z pameti (DATA_RDWR='1') / zapis do pameti (DATA_RDWR='0')
   DATA_EN    : out std_logic;                    -- povoleni cinnosti
   
   -- vstupni port
   IN_DATA   : in std_logic_vector(7 downto 0);   -- IN_DATA obsahuje stisknuty znak klavesnice pokud IN_VLD='1' a IN_REQ='1'
   IN_VLD    : in std_logic;                      -- data platna pokud IN_VLD='1'
   IN_REQ    : out std_logic;                     -- pozadavek na vstup dat z klavesnice
   
   -- vystupni port
   OUT_DATA : out  std_logic_vector(7 downto 0);  -- zapisovana data
   OUT_BUSY : in std_logic;                       -- pokud OUT_BUSY='1', LCD je zaneprazdnen, nelze zapisovat,  OUT_WE musi byt '0'
   OUT_WE   : out std_logic                       -- LCD <- OUT_DATA pokud OUT_WE='1' a OUT_BUSY='0'
 );
end cpu;


-- ----------------------------------------------------------------------------
--                      Architecture declaration
-- ----------------------------------------------------------------------------
architecture behavioral of cpu is

	signal pc: std_logic_vector(11 downto 0);
	signal pc_inc: std_logic;
	signal pc_dec: std_logic;
	
	signal cnt: std_logic_vector(7 downto 0);
	signal cnt_inc: std_logic;
	signal cnt_dec: std_logic;
	signal cnt_load_1: std_logic;
	
	signal ptr: std_logic_vector(9 downto 0);
	signal ptr_inc: std_logic;
	signal ptr_dec: std_logic;
	
	signal hex_select: std_logic;
	signal mux: std_logic_vector(1 downto 0) := "00";
	signal tmp: std_logic_vector(7 downto 0);
	
	type fsm_state is (INIT, DECODE, INC_PTR, DEC_PTR, INC_1, INC_2, DEC_1, DEC_2, WHILE_1, WHILE_2, WHILE_3, WHILE_4,
					   END_WHILE_1, END_WHILE_2, END_WHILE_3, END_WHILE_4, END_WHILE_5, END_WHILE_6, PUTCHAR_1, PUTCHAR_2,
					   GETCHAR, COMMENT_1, COMMENT_2, COMMENT_3, VALUE_NUMBER, VALUE_LETTER, VALUE_HEX, HALT, OTHER);
		
	signal pstate: fsm_state;
	signal nstate: fsm_state;

begin

	process(CLK, RESET, pc, pc_inc, pc_dec)
	begin
		if(RESET = '1') then
			pc <= (others => '0');
		elsif(CLK'event and CLK = '1') then
			if(pc_inc = '1') then
				pc <= pc + 1;
			elsif(pc_dec = '1') then
				pc <= pc - 1;
			end if;
		end if;
		CODE_ADDR <= pc;
	end process;

	process(CLK, RESET, ptr, ptr_inc, ptr_dec)
	begin
		if(RESET = '1') then
			ptr <= (others => '0');
		elsif(CLK'event and CLK = '1') then
			if(ptr_inc = '1') then
				ptr <= ptr + 1;
			elsif(ptr_dec = '1') then
				ptr <= ptr - 1;
			end if;
		end if;
		DATA_ADDR <= ptr;
	end process;

	process(CLK, RESET, cnt, cnt_inc, cnt_dec)
	begin 
		if(RESET = '1') then
			cnt <= (others => '0');
		elsif(CLK'event and CLK = '1') then
			if(cnt_load_1 = '1') then
				cnt(7 downto 0) <= "00000001";
			elsif(cnt_inc = '1') then
				cnt <= cnt + 1;
			elsif(cnt_dec = '1') then
				cnt <= cnt - 1;
			end if;
		end if;	
	end process;
	
	process(IN_DATA, DATA_RDATA, mux)
	begin 
		case(mux) is
			when "00" => DATA_WDATA <= IN_DATA;
			when "01" => DATA_WDATA <= DATA_RDATA + 1;
			when "10" => DATA_WDATA <= DATA_RDATA - 1;
			when "11" => DATA_WDATA <= tmp;
			when others =>
		end case;
	end process;

	process(CLK, RESET)
	begin
		if(RESET = '1') then
			pstate <= INIT;
		elsif(CLK'event and CLK = '1') then
			if(EN = '1') then
				pstate <= nstate;
			end if;
		end if;
	end process;

	fsm_nstate: process(CODE_DATA, DATA_RDATA, IN_VLD, OUT_BUSY, cnt, pstate)
	begin
		DATA_RDWR <= '0';
		CODE_EN <= '0';
		DATA_EN <= '0';
		OUT_WE <= '0';
		IN_REQ <= '0';
		
		pc_inc <= '0';
		pc_dec <= '0';
		cnt_inc <= '0';
		cnt_dec <= '0';
		cnt_load_1 <= '0';
		ptr_inc <= '0';
		ptr_dec <= '0';
		
		mux <= "00";
		
		case pstate is
			when INIT =>
				CODE_EN <= '1';
				nstate <= DECODE;
				
			when DECODE =>
				case(CODE_DATA) is
				
					-- Zakladni stavy
					when X"3E" => nstate <= INC_PTR;
					when X"3C" => nstate <= DEC_PTR;
					when X"2B" => nstate <= INC_1;
					when X"2D" => nstate <= DEC_1;
					when X"5B" => nstate <= WHILE_1;
					when X"5D" => nstate <= END_WHILE_1;
					when X"2E" => nstate <= PUTCHAR_1;
					when X"2C" => nstate <= GETCHAR;
					when X"23" => nstate <= COMMENT_1;
					
					-- Hex 0-9
					when X"30" => 
						nstate <= VALUE_HEX;
						hex_select <= '0';
					when X"31" => 
						nstate <= VALUE_HEX;
						hex_select <= '0';
					when X"32" => 
						nstate <= VALUE_HEX;
						hex_select <= '0';
					when X"33" => 
						nstate <= VALUE_HEX;
						hex_select <= '0';
					when X"34" => 
						nstate <= VALUE_HEX;
						hex_select <= '0';
					when X"35" => 
						nstate <= VALUE_HEX;
						hex_select <= '0';
					when X"36" => 
						nstate <= VALUE_HEX;
						hex_select <= '0';
					when X"37" => 
						nstate <= VALUE_HEX;
						hex_select <= '0';
					when X"38" => 
						nstate <= VALUE_HEX;
						hex_select <= '0';
					when X"39" => 
						nstate <= VALUE_HEX;
						hex_select <= '0';
						
					-- Hex A-F
     				when X"41" => 
						nstate <= VALUE_HEX;
						hex_select <= '1';
					when X"42" => 
						nstate <= VALUE_HEX;
						hex_select <= '1';
					when X"43" => 
						nstate <= VALUE_HEX;
						hex_select <= '1';
					when X"44" => 
						nstate <= VALUE_HEX;
						hex_select <= '1';
					when X"45" => 
						nstate <= VALUE_HEX;
						hex_select <= '1';
					when X"46" => 
						nstate <= VALUE_HEX;
						hex_select <= '1';
						
					-- Ukonceni a nedefinovane stavy
					when X"00" => nstate <= HALT;
					when others => nstate <= OTHER;
				end case;
				
			-- Inkrementace ukazatele
			when INC_PTR =>
				ptr_inc <= '1';
				pc_inc <= '1';
				nstate <= INIT;
				
			-- Dekrementace ukazatele
			when DEC_PTR =>
				ptr_dec <= '1';
				pc_inc <= '1';
				nstate <= INIT;
				
			-- Inkrementace hodnoty aktualni bunky
			when INC_1 =>
				DATA_EN <= '1';
				DATA_RDWR <= '1';
				nstate <= INC_2;
			when INC_2 =>
				mux <= "01";
				DATA_EN <= '1';
				DATA_RDWR <= '0';
				pc_inc <= '1';
				nstate <= INIT;
				
			-- Dekrementace hodnoty aktualni bunky
			when DEC_1 =>
				DATA_EN <= '1';
				DATA_RDWR <= '1';
				nstate <= DEC_2;
			when DEC_2 =>
				mux <= "10";
				DATA_EN <= '1';
				DATA_RDWR <= '0';
				pc_inc <= '1';
				nstate <= INIT;
			
			-- Zacatek WHILE
			when WHILE_1 =>
				pc_inc <= '1';
				DATA_EN <= '1';
				DATA_RDWR <= '1';
				nstate <= WHILE_2;
			when WHILE_2 =>	
				if DATA_RDATA /= (DATA_RDATA'range => '0') then
					nstate <= INIT;
					
				else
					cnt_load_1 <= '1';
					CODE_EN <= '1';
					nstate <= WHILE_3;
				end if;
			when WHILE_3 =>
				if cnt = (cnt'range => '0') then
					nstate <= INIT;
				else
					if(CODE_DATA = X"5B") then
						cnt_inc <= '1';
					elsif(CODE_DATA = X"5D") then
						cnt_dec <= '1';
					end if;
				
					pc_inc <= '1';
					nstate <= WHILE_4;
				end if;
			when WHILE_4 =>
				CODE_EN <= '1';
				nstate <= WHILE_3;
				
				
			-- Konec WHILE
			when END_WHILE_1 =>
				DATA_EN <= '1';
				DATA_RDWR <= '1';
				nstate <= END_WHILE_2;
			when END_WHILE_2 =>
				if DATA_RDATA = (DATA_RDATA'range => '0') then
					pc_inc <= '1';
					nstate <= INIT;
				else
					nstate <= END_WHILE_3;
				end if;
			when END_WHILE_3 =>
				cnt_load_1 <= '1';
				pc_dec <= '1';
				nstate <= END_WHILE_4;
			when END_WHILE_4 =>
				if cnt = (cnt'range => '0') then
					nstate <= INIT;
				else
					CODE_EN <= '1';
					nstate <= END_WHILE_5;
				end if;
			when END_WHILE_5 =>
				if(CODE_DATA = X"5D") then
					cnt_inc <= '1';
				elsif(CODE_DATA = X"5B") then
					cnt_dec <= '1';
				end if;
				nstate <= END_WHILE_6;
			when END_WHILE_6 =>
				if cnt = (cnt'range => '0') then
					pc_inc <= '1';
				else
					pc_dec <= '1';
				end if;
				nstate <= END_WHILE_4;
				
				
			-- Vytiksni znak
			when PUTCHAR_1 =>
				if(OUT_BUSY = '1') then
					nstate <= PUTCHAR_1;
				else
					DATA_EN <= '1';
					DATA_RDWR <= '1';
					nstate <= PUTCHAR_2;
				end if;
			when PUTCHAR_2 =>
				OUT_WE <= '1';
				OUT_DATA <= DATA_RDATA;
				pc_inc <= '1';
				nstate <= INIT;
				
			-- Nacti a uloz znak
			when GETCHAR =>
				IN_REQ <= '1';
				if(IN_VLD = '0') then
					nstate <= GETCHAR;
				else
					mux <= "00";
					DATA_EN <= '1';
					DATA_RDWR <= '0';
					pc_inc <= '1';
					nstate <= INIT;
				end if;
				
			-- Komentar
			when COMMENT_1 =>
				pc_inc <= '1';
				nstate <= COMMENT_2;
			when COMMENT_2 =>
				CODE_EN <= '1';
				nstate <= COMMENT_3;
			when COMMENT_3 =>
				if CODE_DATA /= X"23" then
					nstate <= COMMENT_1;
				elsif CODE_DATA = X"23" then
					pc_inc <= '1';
					nstate <= INIT;
				end if;
				
			-- Hodnoty
			when VALUE_HEX =>
				DATA_EN <= '1';
				DATA_RDWR <= '0';
				pc_inc <= '1';
				mux <= "11";
				if hex_select = '0' then
				tmp <= CODE_DATA(3 downto 0) & "0000";
				else
					if(CODE_DATA = X"41") then
						tmp <= "10100000";
					elsif(CODE_DATA = X"42") then
						tmp <= "10110000";
					elsif(CODE_DATA = X"43") then
						tmp <= "11000000";
					elsif(CODE_DATA = X"44") then
						tmp <= "11010000";
					elsif(CODE_DATA = X"45") then
						tmp <= "11100000";
					elsif(CODE_DATA = X"46") then
						tmp <= "11110000";
					end if;
				end if;
				nstate <= INIT;
				
			-- Konec
			when HALT =>
				nstate <= HALT;
				
			-- Nedefinovano
			when OTHER =>
				pc_inc <= '1';
				nstate <= INIT;
				
			when others =>
		end case;
	end process;
end behavioral;