function wav_to_txt(in_wav, out_txt)
% WAV to text (mono average). Usage: wav_to_txt('data/speechnoise.wav','data/speechnoise.txt')
[y, ~] = audioread(in_wav);
if size(y,2) > 1, y = mean(y,2); end
writematrix(y, out_txt, 'Delimiter',' ');
end
