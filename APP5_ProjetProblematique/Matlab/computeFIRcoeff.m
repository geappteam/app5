% G�n�rer les coeficients d'un filtre FIR passe-haut d'ordre 62 � coupure 
% fc = 80 Hz en format Q15
fe = 8000;
fc = 80;
Ordre = 30;
N = Ordre+1;
coeff = fir1(Ordre, fc/(fe/2), 'high');
figure(1)
freqz(coeff, 1, 1000);
coeff_q15 = round(coeff*2^15);

tt = 0:200;
y = sin(2*pi*tt*80/8000);
fy = filter(coeff, 1, y);
figure(2)
plot(tt,y, tt, fy);

% �crire le fichier .dat
fileID = fopen('../includes/direct1FIRcoeffs.dat','w');
fprintf(fileID, '#define FIRNbCOEFFS %d\n', N);
fprintf(fileID, 'const short CoeffsFIR[FIRNbCOEFFS] = {\n');
for i=1:N-1
    fprintf(fileID, '    %d,\n', coeff_q15(i));
end
fprintf(fileID, '    %d\n', coeff_q15(N));
fprintf(fileID, '};\n');
fclose(fileID);