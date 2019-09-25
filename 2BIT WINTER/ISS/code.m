% xfrejl00
% Jakub Frejlach

pkg load signal;

% --- 1 ---
#{
poËet vzork˘, vzorkovacÌ frekvenci, Ëas, poËet bin·rnÌch symbol˘
#}

[s, Fs] = audioread('xfrejl00.wav');
%s = s';
sampleCount = length(s);
binarySymbols = sampleCount/16;
time = sampleCount/Fs;
t = (0:(length(s)-1)) / Fs;

% --- 2 ---
#{
graf
#}

sBinary = [];
k = 1;
i = 8;
while i < sampleCount
  if(s(i) < 0)
  sBinary(k) = 0;
  elseif(s(i) > 0)
  sBinary(k) = 1;
  endif
  i = i + 16;
  k++;
endwhile


figure(1);
hold on;
plot(t, s);
stem(linspace(0.0005, 2, 2000), sBinary);
axis([0 0.020 -1 1]);
title('Exercise 2');
xlabel('t') ;
ylabel('s[n], symbols');
hold off;



% --- 3 ---
#{
polohy nul a pÛl˘ na jednotkovÈ kruûnici, filtr je stabilnÌ, protoûe
vöechny jeho pÛly leûÌ uvnit¯ jednotkovÈ kruûnice
#}
B = [0.0192 -0.0185 -0.0185 0.0192];
A = [1.0000 -2.8870 2.7997 -0.9113];

figure(2);
zplane(B, A);
title('Exercise 3');


% --- 4 ---
#{
Jedn· se o dolnÌ propusù, meznÌ frekvence je 488 Hz.
#}
figure(3);
fq = freqz(B,A,Fs/2);
fq1 = abs(fq(1:1000));
[minValue, fqMin] = min(fq1);
hold on
plot(abs(fq));
plot(fqMin,minValue,'o','MarkerSize',10);
xlabel('f [Hz]');
ylabel('H [z]');
title('Exercise 4');
grid;
hold off;

% --- 5 ---
#{
Je nutno zhruba o 16 vzork˘ p¯edbÏhnout, hodnotu jsme vizu·lnÏ odhadli
#}
figure(4);
ss = filter(B, A, s);
hold on
plot(t, s);
plot(t, ss);
axis([0 0.020 -1 1]);
xlabel('t') ;
ylabel('s[n], ss[n]');
title('Exercise 5');
hold off

% --- 6 ---
#{
graf
#}
ssShifted = shift(ss, -16);
ssShiftedBinary = [];
k = 1;
i = 8;
while i < sampleCount
  if(ssShifted(i) < 0)
  ssShiftedBinary(k) = 0;
  elseif(ssShifted(i) > 0)
  ssShiftedBinary(k) = 1;
  endif
  i = i + 16;
  k++;
endwhile
figure(5);
hold on;
plot(t, s);
plot(t, ss);
plot(t, shift(ss, -16));
stem(linspace(0.0005, 2, 2000), ssShiftedBinary);
axis([0 0.020 -1 1]);
title('Exercise 6');
xlabel('t') ;
ylabel('s[n], ss[n], ssShifted[n], symbols');
hold off;

% --- 7 ---
#{
äpatnÈ bin·rnÌ symboly - 77
Chybovost 3,9% -> 4%
#}
errors = nnz(xor(sBinary, ssShiftedBinary));
out=errors/binarySymbols;

% --- 8 ---
#{
Graf a okomentovat
#}
figure(6);
fourier = fft(s); 
vector = (0:sampleCount-1)*Fs/sampleCount; 
module = abs(fourier);
hold on
plot(vector(1:sampleCount/2), module(1:sampleCount/2));
fourier = fft(ss); 
vector = (0:sampleCount-1)*Fs/sampleCount; 
module = abs(fourier);
plot(vector(1:sampleCount/2), module(1:sampleCount/2));
title('Exercise 8');
xlabel('f [Hz]');
ylabel('H [z]');
hold off

% --- 9 ---
figure(7);
px = hist(s, 100)/sampleCount;
plot(linspace(0, 1, 100),px);
integralValue = sum(px(1:100));
title('Exercise 9');
ylabel('p(x)');

% --- 10 ---
#{
Graf
#}
figure(8);
hold on
[R, lags] = xcorr(s, 'biased');
plot(lags, R);
axis([-50 50]);
title('Exercise 10');


% --- 11 ---
#{
Napsat hodnoty
#}
R0 = R(0+sampleCount);
R1 = R(1+sampleCount);
R16 = R(16+sampleCount);
plot(0,R0,'o','MarkerSize',10);
plot(1,R1,'o','MarkerSize',10);
plot(16,R16,'o','MarkerSize',10);
legend('Coefficients', 'R0', 'R1', 'R16');
hold off

% --- 12 ---
figure(9);
x = linspace(min(s), max(s), 50);
[h,p,r] = hist2opt(s(1:sampleCount-1), s(2:sampleCount), x);
imagesc(-x,x,p);
colorbar;
title('Exercise 12');

% --- 13 ---
%Ouput of function hist2opt is:"hist2: check -- 2d integral should be 1 and is 1"

% --- 14 ---
R1_1 = r;
coefError = abs(R1 - R1_1);