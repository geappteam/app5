%% Test autocorrelation with the use of FFT and IFFT
clear all
close all
clc

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

%% Generate random floats values for a signal
N = 256;
MIN_SIG_VALUE = 0.0;
MAX_SIG_VALUE = 5.0;

%Export in .txt file
fileID = fopen('signal_test_values.txt','w');
for i = 1:N
    fprintf(fileID,'%f\n',(MIN_SIG_VALUE + (MAX_SIG_VALUE-MIN_SIG_VALUE).*rand(N,1)));
end
fclose(fileID);
%% Test autocorrelation with the use of FFT and IFFT (Import values from CCS)
clear all
close all
clc

formatSpec = '%f';

pre_autocorrelation_data_C_file = fopen('pre_autocorrelation_values_C.txt','r');
pre_autocorrelation_data_C = fscanf(pre_autocorrelation_data_C_file,formatSpec);

autocorrelation_results_C_file = fopen('test_autocorrelation_results_C.txt','r');
autocorrelation_results_C = fscanf(autocorrelation_results_C_file,formatSpec);

fclose(pre_autocorrelation_data_C_file);
fclose(autocorrelation_results_C_file);

% Number of signal data in input
number_of_data_input = length(pre_autocorrelation_data_C);

R_Recoded = autocorrelate(pre_autocorrelation_data_C);
R_Recoded = R_Recoded(1:length(R_Recoded)/2);

R_Matlab = xcorr(pre_autocorrelation_data_C);
R_Matlab = R_Matlab(length(R_Matlab)/2:end-1);

k = 1:(length(pre_autocorrelation_data_C)-1);

figure()
plot(k, R_Recoded, 'o--b', k, R_Matlab, 'r', k, autocorrelation_results_C, '*--g');
legend('Recoded','Matlab')
xlabel('k delay')
ylabel('Correlation')
title('Autocorrelation validation test with recoded and Matlab''s original function')