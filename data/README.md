# Data folder (lightweight)

Large assets (e.g., WAV files) are not included in this lightweight repo to keep size down.
You can still run everything using the small demo text files provided here.

If you want to regenerate from audio, place a WAV (e.g., `OSR_us_000_0017_8k.wav`) in `data/`
and run the MATLAB helper:
```matlab
wav_to_txt('data/OSR_us_000_0017_8k.wav','data/speechnoise.txt')
```
