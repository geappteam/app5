clear all
close all
clc

%% Test autocorrelation with the use of FFT and IFFT
nb_data = 256;

%%Uncomment line below if it needs 
%%a number of data of power of 2 (realistic)
%nb_data = 2^randi(5);

x = rand(nb_data, 1);

R_Recoded = autocorrelate(x);
R_Recoded = R_Recoded(1:length(R_Recoded)/2);

R_Matlab = xcorr(x);
R_Matlab = R_Matlab(length(R_Matlab)/2:end-1);

k = 1:(length(x)-1);

figure()
plot(k, R_Recoded, 'o--b', k, R_Matlab, 'r');
legend('Recoded','Matlab')
xlabel('k delay')
ylabel('Correlation')
title('Autocorrelation validation test with recoded and Matlab''s original function')
