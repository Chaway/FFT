clear
close all
T = 2*pi;
N = 64;
t= (0:N-1)*T/N;
y = cos(t) + 0.5*cos(2*t) + 0.8*cos(5*t);
x = fft(y)';
stem(0:N-1,abs(x)/N,'.');