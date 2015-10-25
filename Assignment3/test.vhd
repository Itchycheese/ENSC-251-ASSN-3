-- Testing File

library STD;                            -- you don't need STD, it is automatic
library IEEE;                           -- but may need other libraries
use IEEE.std_logic_1164.all;            -- basic logic types
use STD.textio.all;                     -- basic I/O
use IEEE.std_logic_textio.all;          -- I/O for logic types

architecture test of hello_world is -- where declarations are placed
  subtype word_32 is std_logic_vector(31 downto 0);  -- simple name
  signal four_32 : word_32 := x"00000004";           -- just four in hex
  signal counter : integer := 1;                     -- initialized counter
begin  -- where parallel code is placed
  my_print : process is                  -- a process is parallel
               variable my_line : line;  -- type 'line' comes from textio
             begin
               write(my_line, string'("Hello World"));   -- formatting
               writeline(output, my_line);               -- write to "output"
               write(my_line, string'("four_32 = "));    -- formatting 
               hwrite(my_line, four_32); -- format type std_logic_vector as hex
               write(my_line, string'("  counter= "));
               write(my_line, counter);  -- format 'counter' as integer
               write(my_line, string'(" at time "));
               write(my_line, now);                     -- format time
               writeline(output, my_line);              -- write to display
               wait;
             end process my_print;
end architecture test;