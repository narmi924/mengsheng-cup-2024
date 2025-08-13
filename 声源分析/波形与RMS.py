import librosa
import numpy as np
import matplotlib.pyplot as plt


# 加载 mp3文件
audio_file = '4.mp3'  #1, 2, 3, 4分别为打开/关闭灯光，打开/关闭空调
y, sr = librosa.load(audio_file, sr=None)

# 绘制波形
plt.figure(figsize=(10, 6))
plt.plot(np.linspace(0, len(y) / sr, len(y)), y)
plt.title("guan bi kong tiao 2m ")
plt.xlabel("Time (s)")
plt.ylabel("Amplitude")
plt.show()

# 计算信号的 RMS（Root Mean Square）值作为信号强度
rms = librosa.feature.rms(y=y)
print(f"RMS value: {np.mean(rms)}")
