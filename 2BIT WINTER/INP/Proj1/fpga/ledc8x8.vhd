library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

entity ledc8x8 is
port (
	RESET : in std_logic;
	SMCLK : in std_logic;
	ROW : out std_logic_vector (0 to 7);
	LED : out std_logic_vector (0 to 7)
);
end ledc8x8;


architecture main of ledc8x8 is
signal counter : std_logic_vector(11 downto 0) := (others => '0');
signal switch : std_logic_vector(20 downto 0) := (others => '0');
signal state : std_logic_vector(1 downto 0) := (others => '0');
signal rows : std_logic_vector(7 downto 0) := (others => '0');
signal leds : std_logic_vector(7 downto 0) := (others => '0');
signal clock_enable : std_logic;


begin

clock_enable_generator: process(SMCLK, RESET)
	begin
		if RESET = '1' then
			counter <= (others => '0');
		elsif SMCLK'event and SMCLK = '1' then
			counter <= counter + 1;
			if counter = "111000010000" then
				clock_enable <= '1';
				counter <= (others => '0');
			else
				clock_enable <= '0';
			end if;
		end if;
	end process clock_enable_generator;

switch_generator: process(SMCLK, RESET)
	begin
		if RESET = '1' then
			switch <= (others => '0');
		elsif SMCLK'event and SMCLK = '1' then
			switch <= switch + 1;
		if switch = "111000010000000000000" then
				state <= state + 1;
				switch <= (others => '0');
			end if;
		end if;
	end process switch_generator;	

rotate: process(RESET, clock_enable, SMCLK)
	begin	
		if RESET = '1' then
			rows <= "10000000"; 
		elsif SMCLK'event and SMCLK = '1' and clock_enable = '1' then
			rows <= rows(0) & rows(7 downto 1);
		end if;
	end process rotate;

decoder: process(rows)
	begin

			if state = "00" then
			case rows is
			when "10000000" => leds <= "11111101";
			when "01000000" => leds <= "11111101";
			when "00100000" => leds <= "11111101";
			when "00010000" => leds <= "11111101";
			when "00001000" => leds <= "11111101";
			when "00000100" => leds <= "11111101";
			when "00000010" => leds <= "10111101";
			when "00000001" => leds <= "11000011";
			when others =>	   leds <= "11111111";
			end case;
			end if;
			if state = "01" then
			case rows is
			when "10000000" => leds <= "11111111";
			when "01000000" => leds <= "11111111";
			when "00100000" => leds <= "11111111";
			when "00010000" => leds <= "11111111";
			when "00001000" => leds <= "11111111";
			when "00000100" => leds <= "11111111";
			when "00000010" => leds <= "11111111";
			when "00000001" => leds <= "11111111";
			when others =>	   leds <= "11111111";
			end case;
			end if;
			if state = "10" then
			case rows is
			when "10000000" => leds <= "10000001";
			when "01000000" => leds <= "10111111";
			when "00100000" => leds <= "10111111";
			when "00010000" => leds <= "10000111";
			when "00001000" => leds <= "10111111";
			when "00000100" => leds <= "10111111";
			when "00000010" => leds <= "10111111";
			when "00000001" => leds <= "10111111";
			when others =>	   leds <= "11111111";
			end case;
			end if;
			if state = "11" then
			case rows is
			when "10000000" => leds <= "11111111";
			when "01000000" => leds <= "11111111";
			when "00100000" => leds <= "11111111";
			when "00010000" => leds <= "11111111";
			when "00001000" => leds <= "11111111";
			when "00000100" => leds <= "11111111";
			when "00000010" => leds <= "11111111";
			when "00000001" => leds <= "11111111";
			when others =>	   leds <= "11111111";
			end case;
			end if;
	end process decoder;
	
	ROW <= rows;
	LED <= leds;
end main;
