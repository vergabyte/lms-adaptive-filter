function fft_compare(file_a, file_b, Fs)
% Compare magnitude spectra of two 1-col text signals.
%   fft_compare('results/ERROR.txt','results/Y_OUT.txt', 8000)
a = readmatrix(file_a); a = a(:);
b = readmatrix(file_b); b = b(:);
N = 2^nextpow2(min(length(a), length(b)));
A = abs(fft(a(1:N)))./N; B = abs(fft(b(1:N)))./N;
f = (0:N-1)*(Fs/N);
figure; 
subplot(2,1,1); plot(f(1:N/2), A(1:N/2)); title(['Spectrum: ' file_a]);
xlabel('Hz'); ylabel('|A(f)|');
subplot(2,1,2); plot(f(1:N/2), B(1:N/2)); title(['Spectrum: ' file_b]);
xlabel('Hz'); ylabel('|B(f)|');
end
