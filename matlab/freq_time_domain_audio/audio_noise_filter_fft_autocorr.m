[Y, Fs]=audioread('OSR_us_000_0017_8k.wav'); %fs sampling frequency
%Task 1
rat=(randn(size(Y)))./100;
s=Y+rat;

N=length(s); %number of samples
Ts=1/Fs;   %sampling period
t=0:Ts:(N-1)*Ts; %discrete sampling times to calculate signal samples

figure(1)
plot(t,s)
hold on;
plot(t,Y)
hold off;

%Do the fft and plot it

sff=fft(s);
sff=abs(fft(s).^2);  %mag power of signal
df= Fs/N;            %frequency resolution
k= 0:(N-1);          %frequency indices
freqs=k*df;          %discrete frequencies

%FIR Task 2
figure(2)
stem(freqs, sff./N)

f1=60; f2=7940;
b=fir1(50, [f1/(Fs),f2/(Fs)]);
figure(3)
freqz(b,1)

yss=filter(b,1,s);


%Task 3
[rtt,lags]=xcorr(yss,yss,50);
figure(4)
stem(lags,rtt)

qss=fft(rtt);
qss=abs(fft(rtt).^2); 
%[qss,lags]=xcorr(rtt,rtt,100);
figure(5)
stem(lags, qss./N)


