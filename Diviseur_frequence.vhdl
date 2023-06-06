entity div is
    port (
        clk : in  std_logic;
        reset : in std_logic;
        cout : out std_logic;
        s : out std_logic
    );
end entity div;

architecture archi of div is
    signal counter : integer range 0 to 49 := 0;
    signal carry_out : std_logic := '0';

begin
    process (clk, reset)
    begin
        if (reset = '1') then
            counter <= 0;
            carry_out <= '0';
            s <= '0';
        elsif (rising_edge(clk)) then
            if (counter = 49) then
                counter <= 0;
                carry_out <= '1';
            else
                counter <= counter + 1;
                carry_out <= '0';
            end if;
        end if;
    end process;

    s <= '1' when (counter < 25) else '0';
    cout <= carry_out;
end architecture archi;
