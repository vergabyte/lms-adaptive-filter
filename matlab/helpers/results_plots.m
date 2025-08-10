% Plot results from results/*.txt
d = readmatrix('results/DESIRED.txt');
e = readmatrix('results/ERROR.txt');
y = readmatrix('results/Y_OUT.txt');

figure(1);
subplot(3,1,1); plot(d); title('Desired'); xlabel('n'); ylabel('amp');
subplot(3,1,2); plot(e); title('Error');   xlabel('n'); ylabel('amp');
subplot(3,1,3); plot(y); title('Adaptive output'); xlabel('n'); ylabel('amp');
