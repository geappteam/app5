clear all
close all
clc
%% Low-Pass Biquad Filters generation
% Nb of filters to do
NbFilt = 6;

%Fondamental frequencies of each guitare cords
FO_CORD1 = 82.407;
FO_CORD2 = 110.000;
FO_CORD3 = 146.832;
FO_CORD4 = 195.998;
FO_CORD5 = 246.942;
FO_CORD6 = 329.628;

%Sampling frequency
fs = 8000;

%Nyquist frequency
fNyq = fs/2;

%Oscillation in the bandpass according to specs
oscillation_dB = 3;

%Order N needed to create the waterfall form
N = 4;

%Cutoff frequency
fc = @(fo) 1.5*fo;

% 2Q13/Real converter
n2Q13_multiplier = 2^13;
n2Q13_divider = 1\n2Q13_multiplier;
%% CORD 1
%Filter order (N) 4
[A1 B1 C1 D1] = cheby1(N, oscillation_dB, fc(FO_CORD1)/fNyq);

% 2 parts of order N=2 as a waterfall
[sos1 gain_global1] = ss2sos(A1,B1,C1,D1, 'up', 'inf');

[b a] = sos2tf(sos1, gain_global1); 
figure()
zplane(b,a); 
title('Poles and zeros of the filter IIR Biquad for cord 1')
figure()
freqz(b,a);
title('Frequency response of the filter IIR Biquad for cord 1')

%Convert values in 2Q13 form (Also keeps poles inside of the unit-circle)
if (sqrt(sos1(1,6)) >= 1)
    sos1(1,6) = floor(sos1(1,6)*n2Q13_multiplier)*n2Q13_divider;
end
if (sqrt(sos1(2,6)) >= 1)
    sos1(2,6) = floor(sos1(2,6)*n2Q13_multiplier)*n2Q13_divider;
end
sos1 = round(sos1*n2Q13_multiplier);
gain_global1 = round(gain_global1.*n2Q13_multiplier);

%% CORD 2
%Filter order (N) 4
[A2 B2 C2 D2] = cheby1(N, oscillation_dB, fc(FO_CORD2)/fNyq);

% 2 parts of order N=2 as a waterfall
[sos2 gain_global2] = ss2sos(A2,B2,C2,D2, 'up', 'inf');

[b a] = sos2tf(sos2, gain_global2); 
figure()
zplane(b,a); 
title('Poles and zeros of the filter IIR Biquad for cord 2')
figure()
freqz(b,a);
title('Frequency response of the filter IIR Biquad for cord 2')

%Convert values in 2Q13 form (Also keeps poles inside of the unit-circle)
if (sqrt(sos2(1,6)) >= 1)
    sos2(1,6) = floor(sos2(1,6)*n2Q13_multiplier)*n2Q13_divider;
end
if (sqrt(sos2(2,6)) >= 1)
    sos2(2,6) = floor(sos2(2,6)*n2Q13_multiplier)*n2Q13_divider;
end
sos2 = round(sos2*n2Q13_multiplier);
gain_global2 = round(gain_global2.*n2Q13_multiplier);

%% CORD 3
%Filter order (N) 4
[A3 B3 C3 D3] = cheby1(N, oscillation_dB, fc(FO_CORD3)/fNyq);

% 2 parts of order N=2 as a waterfall
[sos3 gain_global3] = ss2sos(A3,B3,C3,D3, 'up', 'inf');

[b a] = sos2tf(sos3, gain_global3); 
figure()
zplane(b,a); 
title('Poles and zeros of the filter IIR Biquad for cord 3')
figure()
freqz(b,a);
title('Frequency response of the filter IIR Biquad for cord 3')

%Convert values in 2Q13 form (Also keeps poles inside of the unit-circle)
if (sqrt(sos3(1,6)) >= 1)
    sos3(1,6) = floor(sos3(1,6)*n2Q13_multiplier)*n2Q13_divider;
end
if (sqrt(sos3(2,6)) >= 1)
    sos3(2,6) = floor(sos3(2,6)*n2Q13_multiplier)*n2Q13_divider;
end
sos3 = round(sos3*n2Q13_multiplier);
gain_global3 = round(gain_global3.*n2Q13_multiplier);

%% CORD 4
%Filter order (N) 4
[A4 B4 C4 D4] = cheby1(N, oscillation_dB, fc(FO_CORD4)/fNyq);

% 2 parts of order N=2 as a waterfall
[sos4 gain_global4] = ss2sos(A4,B4,C4,D4, 'up', 'inf');

[b a] = sos2tf(sos4, gain_global4); 
figure()
zplane(b,a); 
title('Poles and zeros of the filter IIR Biquad for cord 4')
figure()
freqz(b,a);
title('Frequency response of the filter IIR Biquad for cord 4')

%Convert values in 2Q13 form (Also keeps poles inside of the unit-circle)
if (sqrt(sos4(1,6)) >= 1)
    sos4(1,6) = floor(sos4(1,6)*n2Q13_multiplier)*n2Q13_divider;
end
if (sqrt(sos4(2,6)) >= 1)
    sos4(2,6) = floor(sos4(2,6)*n2Q13_multiplier)*n2Q13_divider;
end
sos4 = round(sos4*n2Q13_multiplier);
gain_global4 = round(gain_global4.*n2Q13_multiplier);

%% CORD 5
%Filter order (N) 4
[A5 B5 C5 D5] = cheby1(N, oscillation_dB, fc(FO_CORD5)/fNyq);

% 2 parts of order N=2 as a waterfall
[sos5 gain_global5] = ss2sos(A5,B5,C5,D5, 'up', 'inf');

[b a] = sos2tf(sos5, gain_global5); 
figure()
zplane(b,a); 
title('Poles and zeros of the filter IIR Biquad for cord 5')
figure()
freqz(b,a);
title('Frequency response of the filter IIR Biquad for cord 5')

%Convert values in 2Q13 form (Also keeps poles inside of the unit-circle)
if (sqrt(sos5(1,6)) >= 1)
    sos5(1,6) = floor(sos5(1,6)*n2Q13_multiplier)*n2Q13_divider;
end
if (sqrt(sos5(2,6)) >= 1)
    sos5(2,6) = floor(sos5(2,6)*n2Q13_multiplier)*n2Q13_divider;
end
sos5 = round(sos5*n2Q13_multiplier);
gain_global5 = round(gain_global5.*n2Q13_multiplier);

%% CORD 6
%Filter order (N) 4
[A6 B6 C6 D6] = cheby1(N, oscillation_dB, fc(FO_CORD6)/fNyq);

% 2 parts of order N=2 as a waterfall
[sos6 gain_global6] = ss2sos(A6,B6,C6,D6, 'up', 'inf');

[b a] = sos2tf(sos6, gain_global6); 
figure()
zplane(b,a); 
title('Poles and zeros of the filter IIR Biquad for cord 6')
figure()
freqz(b,a);
title('Frequency response of the filter IIR Biquad for cord 6')

%Convert values in 2Q13 form (Also keeps poles inside of the unit-circle)
if (sqrt(sos6(1,6)) >= 1)
    sos6(1,6) = floor(sos6(1,6)*n2Q13_multiplier)*n2Q13_divider;
end
if (sqrt(sos6(2,6)) >= 1)
    sos6(2,6) = floor(sos6(2,6)*n2Q13_multiplier)*n2Q13_divider;
end
sos6 = round(sos6*n2Q13_multiplier);
gain_global6 = round(gain_global6.*n2Q13_multiplier);

%% Write txt file of the coefficients values 
fileID = fopen('coeffsIIR.txt','w');

sos = [sos1;sos2;sos3;sos4;sos5;sos6];
gain = [gain_global1;gain_global2;gain_global3;gain_global4;gain_global5;gain_global6];
for i = 1:NbFilt
    fprintf(fileID, '//FILTER %d,\n',i);
    fprintf(fileID, '//Global gain\n');
    fprintf(fileID, '\t%d\n',gain(i));
    fprintf(fileID, '//Coefficients\n');  
    fprintf(fileID, '\t{%d, %d, %d, %d, %d, %d},\n',sos(2*i-1,1),sos(2*i-1,2),sos(2*i-1,3),sos(2*i-1,4),sos(2*i-1,5),sos(2*i-1,6));
    fprintf(fileID, '\t{%d, %d, %d, %d, %d, %d}',sos(2*i,1),sos(2*i,2),sos(2*i,3),sos(2*i,4),sos(2*i,5),sos(2*i,6));
    fprintf(fileID, '\n\n');
end
fclose(fileID);