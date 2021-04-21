----------------------------------------------------------------------------------
-- Company:
-- Engineer:
--
-- Create Date: 03/16/2021 01:38:25 PM
-- Design Name:
-- Module Name: vga_sync - Behavioral
-- Project Name:
-- Target Devices:
-- Tool Versions:
-- Description:
--
-- Dependencies:
--
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity vga_sync is
 port(
 clk, reset: in std_logic;
 I_CLK_50MHZ : in std_logic;
 bram_data_in : in std_logic_vector(31 downto 0);
 bram_addr_out : out std_logic_vector(15 downto 0);

 hsync, vsync: out std_logic;

 vga_r : out std_logic_vector(3 downto 0) := "1111";
 vga_g : out std_logic_vector(3 downto 0) := "1111";
 vga_b : out std_logic_vector(3 downto 0) := "1111"

 -- pixel_x, pixel_y: out std_logic_vector (9 downto 0)
 );
end vga_sync;

architecture Behavioral of vga_sync is



   -- VGA 640-by-480 sync parameters
   constant HD: integer := 640; --horizontal display area
   constant HF: integer := 16 ; --h. front porch
   constant HR: integer := 96 ; --h. retrace
   constant HB: integer := 48 ; --h. back porch
   constant VD: integer := 480; --vertical display area
   constant VF: integer := 10; --v. front porch
   constant VR: integer := 2; --v. retrace
   constant VB: integer := 33; --v. back porch

   -- mod-2 counter
   signal mod2_reg, mod2_next: std_logic;
   -- sync counters
   signal v_count_reg, v_count_next: unsigned(9 downto 0);
   signal h_count_reg, h_count_next: unsigned(9 downto 0);
   -- output buffer
   signal v_sync_reg, h_sync_reg: std_logic;
   signal v_sync_next, h_sync_next: std_logic;
   -- status signal
   signal h_end, v_end, pixel_tick: std_logic;

   -- Signals added by KAB
   signal pixel_x, pixel_y : std_logic_vector (9 downto 0) := (others => '0');
   signal previous_pixel_x, previous_pixel_y : std_logic_vector (9 downto 0) := (others => '0');

   signal bram_addr : std_logic_vector(15 downto 0) := (others => '0');
   signal previous_bram_addr : std_logic_vector(15 downto 0);

   signal active_data_bits : std_logic_vector(3 downto 0);

   signal vga_r_temp : std_logic_vector(3 downto 0);
   signal vga_g_temp : std_logic_vector(3 downto 0);
   signal vga_b_temp : std_logic_vector(3 downto 0);

begin



  process (I_CLK_50MHZ, reset)
  begin
      if reset = '1' then
        mod2_reg <= '0';
        v_count_reg <= (others=>'0');
        h_count_reg <= (others=>'0');
        v_sync_reg <= '0';
        h_sync_reg <= '0';
      elsif (rising_edge(I_CLK_50MHZ)) then -- set for 50 MHz clock
        mod2_reg <= mod2_next;
        v_count_reg <= v_count_next;
        h_count_reg <= h_count_next;
        v_sync_reg <= v_sync_next;
        h_sync_reg <= h_sync_next;
      end if;
    -- end if;
  end process;

  BRAM_ADDR_CONV : process(clk, reset)
  begin
    if (rising_edge(clk)) then
      previous_bram_addr <= bram_addr;
      if (previous_bram_addr /= bram_addr) then
        bram_addr_out <= bram_addr;
      end if;
    end if;
  end process;

  BRAM_DATA_2_PIXEL : process(clk, reset)
  begin
    if (reset = '1') then
      vga_r_temp <= (others => '0');
      vga_g_temp <= (others => '0');
      vga_b_temp <= (others => '0');
    elsif (rising_edge(clk)) then
      -- vga_g_temp <= bram_data_in(3 downto 0);
      case( to_integer(unsigned(pixel_x)) mod 8 ) is
        when 0 =>  -- bram_data_in(3 downto 0)
          -- set red value
          case( bram_data_in(3 downto 2) ) is
            when "00" =>
              vga_r_temp <= X"0";
            when "01" =>
              vga_r_temp <= X"7";
            when "10" =>
              vga_r_temp <= X"B";
            when "11" =>
              vga_r_temp <= X"F";
            when others =>
              vga_r_temp <= X"0";
          end case;

          -- set green value
          if (bram_data_in(1 downto 1) = "1") then
            vga_g_temp <= X"F";
          else
            vga_g_temp <= X"0";
          end if;

          -- set blue value
          if (bram_data_in(0 downto 0) = "1") then
            vga_b_temp <= X"F";
          else
            vga_b_temp <= X"0";
          end if;

        when 1 =>  -- bram_data_in(7 downto 4)
          -- set red value
          case( bram_data_in(7 downto 6) ) is
            when "00" =>
              vga_r_temp <= X"0";
            when "01" =>
              vga_r_temp <= X"7";
            when "10" =>
              vga_r_temp <= X"B";
            when "11" =>
              vga_r_temp <= X"F";
            when others =>
              vga_r_temp <= X"0";
          end case;

          -- set green value
          if (bram_data_in(5 downto 5) = "1") then
            vga_g_temp <= X"F";
          else
            vga_g_temp <= X"0";
          end if;

          -- set blue value
          if (bram_data_in(4 downto 4) = "1") then
            vga_b_temp <= X"F";
          else
            vga_b_temp <= X"0";
          end if;

        when 2 => -- bram_data_in(11 downto 8)
          -- set red value
          case( bram_data_in(11 downto 10) ) is
            when "00" =>
              vga_r_temp <= X"0";
            when "01" =>
              vga_r_temp <= X"7";
            when "10" =>
              vga_r_temp <= X"B";
            when "11" =>
              vga_r_temp <= X"F";
            when others =>
              vga_r_temp <= X"0";
          end case;

          -- set green value
          if (bram_data_in(9 downto 9) = "1") then
            vga_g_temp <= X"F";
          else
            vga_g_temp <= X"0";
          end if;

          -- set blue value
          if (bram_data_in(8 downto 8) = "1") then
            vga_b_temp <= X"F";
          else
            vga_b_temp <= X"0";
          end if;

        when 3 => -- bram_data_in(15 downto 12)
          -- set red value
          case( bram_data_in(15 downto 14) ) is
            when "00" =>
              vga_r_temp <= X"0";
            when "01" =>
              vga_r_temp <= X"7";
            when "10" =>
              vga_r_temp <= X"B";
            when "11" =>
              vga_r_temp <= X"F";
            when others =>
              vga_r_temp <= X"0";
          end case;

          -- set green value
          if (bram_data_in(13 downto 13) = "1") then
            vga_g_temp <= X"F";
          else
            vga_g_temp <= X"0";
          end if;

         -- set blue value
         if (bram_data_in(12 downto 12) = "1") then
           vga_b_temp <= X"F";
         else
           vga_b_temp <= X"0";
         end if;

        when 4 => -- bram_data_in(19 downto 16)
          -- set red value
          case( bram_data_in(19 downto 18) ) is
            when "00" =>
              vga_r_temp <= X"0";
            when "01" =>
              vga_r_temp <= X"7";
            when "10" =>
              vga_r_temp <= X"B";
            when "11" =>
              vga_r_temp <= X"F";
            when others =>
              vga_r_temp <= X"0";
          end case;

          -- set green value
          if (bram_data_in(17 downto 17) = "1") then
            vga_g_temp <= X"F";
          else
            vga_g_temp <= X"0";
          end if;

          -- set blue value
          if (bram_data_in(16 downto 16) = "1") then
            vga_b_temp <= X"F";
          else
            vga_b_temp <= X"0";
          end if;

        when 5 => -- bram_data_in(23 downto 20)
          -- set red value
          case( bram_data_in(23 downto 22) ) is
            when "00" =>
              vga_r_temp <= X"0";
            when "01" =>
              vga_r_temp <= X"7";
            when "10" =>
              vga_r_temp <= X"B";
            when "11" =>
              vga_r_temp <= X"F";
            when others =>
              vga_r_temp <= X"0";
          end case;

          -- set green value
          if (bram_data_in(21 downto 21) = "1") then
            vga_g_temp <= X"F";
          else
            vga_g_temp <= X"0";
          end if;

          -- set blue value
          if (bram_data_in(20 downto 20) = "1") then
            vga_b_temp <= X"F";
          else
            vga_b_temp <= X"0";
          end if;

        when 6 => -- bram_data_in(27 downto 24)
          -- set red value
          case( bram_data_in(27 downto 26) ) is
            when "00" =>
              vga_r_temp <= X"0";
            when "01" =>
              vga_r_temp <= X"7";
            when "10" =>
              vga_r_temp <= X"B";
            when "11" =>
              vga_r_temp <= X"F";
            when others =>
              vga_r_temp <= X"0";
          end case;

          -- set green value
          if (bram_data_in(25 downto 25) = "1") then
            vga_g_temp <= X"F";
          else
            vga_g_temp <= X"0";
          end if;

          -- set blue value
          if (bram_data_in(24 downto 24) = "1") then
            vga_b_temp <= X"F";
          else
            vga_b_temp <= X"0";
          end if;

        when 7 => -- bram_data_in(31 downto 28)
          -- set red value
          case( bram_data_in(31 downto 30) ) is
            when "00" =>
              vga_r_temp <= X"0";
            when "01" =>
              vga_r_temp <= X"7";
            when "10" =>
              vga_r_temp <= X"B";
            when "11" =>
              vga_r_temp <= X"F";
            when others =>
              vga_r_temp <= X"0";
          end case;

          -- set green value
          if (bram_data_in(29 downto 29) = "1") then
            vga_g_temp <= X"F";
          else
            vga_g_temp <= X"0";
          end if;

          -- set blue value
          if (bram_data_in(28 downto 28) = "1") then
            vga_b_temp <= X"F";
          else
            vga_b_temp <= X"0";
          end if;

        when others =>
      end case;
    end if;
  end process;

  -- mod-2 circuit to generate 25 MHz enable tick
  mod2_next <= not mod2_reg;
  -- 25 MHz pixel tick
  pixel_tick <= '1' when mod2_reg='1' else '0';
  -- status
  h_end <= -- end of horizontal counter
  '1' when h_count_reg = (HD + HF + HR + HB - 1) else --799
  '0';
  v_end <= -- end of vertical counter
  '1' when v_count_reg = (VD + VF + VR + VB - 1) else --524
  '0';

  -- horizontal and vertical sync, buffered to avoid glitch
  h_sync_next <=
  '0' when (h_count_reg >= (HD + HF)) --656
  and (h_count_reg <= (HD + HF + HR - 1)) else --751
  '1';
  v_sync_next <=
  '0' when (v_count_reg >= (VD + VF)) --490
  and (v_count_reg <= (VD + VF + VR - 1)) else --491
  '1';

  -- mod-800 horizontal sync counter
  process (h_count_reg, h_end, pixel_tick)
  begin
    if pixel_tick='1' then -- 25 MHz tick
      if h_end='1' then
        h_count_next <= (others=>'0');
      else
        h_count_next <= h_count_reg + 1;
      end if;
    else
      h_count_next <= h_count_reg;
    end if;
  end process;

  -- mod-525 vertical sync counter
  process (v_count_reg, h_end, v_end, pixel_tick)
  begin
    if pixel_tick='1' and h_end='1' then
      if (v_end='1') then
        v_count_next <= (others=>'0');
      else
        v_count_next <= v_count_reg + 1;
      end if;
    else
      v_count_next <= v_count_reg;
    end if;
  end process;

  -- output signal
  hsync <= not(h_sync_reg);
  vsync <= not(v_sync_reg);
  pixel_x <= std_logic_vector(h_count_reg);
  pixel_y <= std_logic_vector(v_count_reg);

  bram_addr <= std_logic_vector(to_unsigned((to_integer(unsigned(pixel_y)) * 80 + to_integer(unsigned(pixel_x)) / 8), 16));

  -- vga_r <= "0000";
  -- vga_g <= "0000";
  -- vga_b <= "1111";
  vga_r <= vga_r_temp when (h_count_reg < HD) and (v_count_reg < VD) else
  (others => '0');
  vga_g <= vga_g_temp when (h_count_reg < HD) and (v_count_reg < VD) else
  (others => '0');
  vga_b <= vga_b_temp when (h_count_reg < HD) and (v_count_reg < VD) else
  (others => '0');

end Behavioral;
