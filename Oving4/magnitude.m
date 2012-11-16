function retval = magnitude (vector)
    vector = vector.^2;
    retval = sqrt(sum(vector));
endfunction