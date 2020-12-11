function p16_mod_1e10(n)
    MOD = uint64(10000000000);
    ANS = uint64(0);
    for ii=1:n
        ANS = mod(ANS + fpow(uint64(ii), uint64(ii), MOD), MOD);
    end
    disp(ANS)
end

function d = fpow(a, p, MOD)
    if p == 0
        d = 1;
    else
        p2 = idivide(p, uint64(2));
        aa = fpow(a, p2, MOD);
        if mod(p, 2) == 1
            d = mod(aa * aa * a, MOD);
        else
            d = mod(aa * aa, MOD);
        end
    end
end