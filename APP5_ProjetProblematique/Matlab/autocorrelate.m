function [ R ] = autocorrelate( x )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    x = cat(1, zeros(length(x)-1, 1), x);
    R = ifft(abs(fft(x)).^2);
end

