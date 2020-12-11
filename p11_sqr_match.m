% 19293742546274889
function p11_sqr_match()
    match(uint64(11243648596271809))

    MX = uint64(20000000000000000);
    for ii=1:1000000000000
        jj = uint64(ii);
        d = uint64(jj * 10 + 3);
        d2 = uint64(d * d);
        if d2 < uint64(10000000000000000)
            continue;
        end
        if d2 > MX
            break
        end
        if match(d2)
            disp(d2);
        end
        d = uint64(jj * 10 + 7);
        d2 = uint64(d * d);
        if d2 > MX
            break
        end
       if match(d2)
            disp(d2)
       end
    end
end

function b = match(d)
    b = uint64(1);
    for ii=9:-1:1
        if mod(d, 10) ~= ii
            %disp(['NUM: ', num2str(d), ', error: ', num2str(ii)])
            b = 0;
            break;
        end
        d = idivide(d, uint64(100));
    end
end