% Générer les coeficients d'un filtre FIR passe-haut d'ordre 62 à coupure 
% fc = 80 Hz en format Q15
fe = 8000;
fc = 80;
Ordre = 10;

N = Ordre+1;
coeff = fir1(Ordre, fc/(fe/2), 'high');
figure(1)
[h,w] = freqz(coeff, 1, 1000);

while abs(h(21)) > db2mag(-3)
    Ordre = Ordre + 2;
    N = N + 2;
    coeff = fir1(N-1, fc/(fe/2), 'high');
    [h,w] = freqz(coeff, 1, 1000);
end

figure(1)
freqz(coeff, 1, 1000);

coeff_q15 = round(coeff*2^15);

tt = 0:200;
y = sin(2*pi*tt*80/8000);
fy = filter(coeff, 1, y);
figure(2)
plot(tt,y, tt, fy);

% Écrire le fichier .dat
fileID = fopen('../includes/coeffsFIR.dat','w');
fprintf(fileID, '#define FIRNbCOEFFS %d\n', N);
fprintf(fileID, '#define FIRNbCOEFFS_FOLDED %d\n', ceil(N/2));

fprintf(fileID, 'const short CoeffsFIR[FIRNbCOEFFS] = {\n');
for i=1:N-1
    fprintf(fileID, '    %d,\n', coeff_q15(i));
end
fprintf(fileID, '    %d\n', coeff_q15(N));
fprintf(fileID, '};\n\n');

% fprintf(fileID, 'const short CoeffsFIR_FOLDED[FIRNbCOEFFS_FOLDED] = {\n');
% for i=1:ceil(N/2)-1
%     fprintf(fileID, '    %d,\n', coeff_q15(i));
% end
% fprintf(fileID, '    %d\n', coeff_q15(ceil(N/2)));
% fprintf(fileID, '};\n');

fclose(fileID);



