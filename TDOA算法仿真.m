close all

% 参数设置
a = 40; % 麦克风阵列的长度（厘米）
b = 20; % 麦克风阵列的宽度（厘米）
fs = 20000; % 采样率
c = 343; % 声速（米/秒）
t = 0:1/fs:1; % 时间轴，信号时长1秒

% 麦克风阵列位置(原代位置取麦克风阵列的中心点）
mic_positions = [-a/2, -b/2;      % 麦克风1
                 a/2, -b/2;       % 麦克风2
                 -a/2, b/2;       % 麦克风3
                 a/2, b/2];       % 麦克风4

% 五个已知区域中心的声源坐标
source_positions = [0, 240;  % A区域
                    -50, 240; % B区域
                    -100, 240; % C区域
                    50, 240; % D区域
                    100, 240]; % E区域

% 定义区域边界（每个区域边长为50cm）
regions = struct('A', [-125, -75; 215, 265], ...
                 'B', [-75, -25; 215, 265], ...
                 'C', [-25, 25; 215, 265], ...
                 'D', [25, 75; 215, 265], ...
                 'E', [75, 125; 215, 265]);

% 随机选择一个区域内的声源位置
source_index = randi(5); % 随机选择一个声源中心
random_offset = (rand(1, 2) - 0.5) * 50; % 在该区域内随机偏移
source_position = source_positions(source_index, :) + random_offset;

% 从每个麦克风到声源的距离
distances = sqrt(sum((mic_positions - source_position).^2, 2));

% 模拟信号传播延时
delays = distances / c; % 根据距离计算传播延迟
signals = zeros(length(t), 4);
source_signal = sin(2 * pi * 1000 * t); % 生成一个1kHz的测试信号

% 模拟各个麦克风接收到的信号
for i = 1:4
    signals(:, i) = circshift(source_signal, round(delays(i) * fs));
end

% 计算TDOA
tdoa = zeros(1, 3); % TDOA between microphone pairs
tdoa(1) = delays(2) - delays(1); % Mic2-Mic1
tdoa(2) = delays(3) - delays(1); % Mic3-Mic1
tdoa(3) = delays(4) - delays(1); % Mic4-Mic1

% 使用最小化误差的优化方法估计声源位置
objective_func = @(pos) sum((sqrt(sum((mic_positions(2:end, :) - pos).^2, 2)) - sqrt(sum((mic_positions(1, :) - pos).^2)) - tdoa' * c).^2);

% 使用fminsearch进行优化，初始位置opoint为(0, 0)
opoint = [0, 0];
estimated_position = fminsearch(objective_func, opoint);

% 获取估计的坐标
x_est = estimated_position(1);
y_est = estimated_position(2);

% 区域判定
estimated_region = 'Unknown';
for region = fieldnames(regions)'
    limits = regions.(region{1});
    if x_est >= limits(1, 1) && x_est <= limits(1, 2) && y_est >= limits(2, 1) && y_est <= limits(2, 2)
        estimated_region = region{1};
        break;
    end
end

% 显示估计结果
fprintf('真实声源位置: (%.2f, %.2f)\n', source_position(1), source_position(2));
fprintf('估计声源位置: (%.2f, %.2f)\n', x_est, y_est);
fprintf('声源所在区域: %s\n', estimated_region);

% 绘图
figure;
hold on;

% 绘制麦克风位置
plot(mic_positions(:, 1), mic_positions(:, 2), 'ro', 'MarkerFaceColor', 'r', 'DisplayName', '麦克风位置');

% 绘制区域中心
plot(source_positions(:, 1), source_positions(:, 2), 'gx', 'MarkerSize', 10, 'LineWidth', 2, 'DisplayName', '区域中心');

% 绘制真实声源位置
plot(source_position(1), source_position(2), 'go', 'MarkerSize', 8, 'MarkerFaceColor', 'g', 'DisplayName', '真实声源位置');

% 绘制估计的声源位置
plot(x_est, y_est, 'bx', 'MarkerSize', 10, 'LineWidth', 2, 'DisplayName', '估计声源位置');

% 绘制五个区域的轮廓和代号
region_names = {'A', 'B', 'C', 'D', 'E'};
region_colors = {'k', 'k', 'k', 'k', 'k'}; % 使用黑色边框
for i = 1:length(region_names)
    % 获取每个区域的边界
    limits = regions.(region_names{i});
    % 绘制区域矩形边框
    rectangle('Position', [limits(1, 1), limits(2, 1), 50, 50], ...
              'EdgeColor', region_colors{i}, 'LineWidth', 1.5);
    % 标注区域名称
    text(mean(limits(1, :)), mean(limits(2, :)), region_names{i}, ...
         'HorizontalAlignment', 'center', 'VerticalAlignment', 'middle', ...
         'FontSize', 12, 'FontWeight', 'bold', 'Color', 'k');
end

% 设置图例和标题
legend('show');
title('四点矩形麦克风阵列与区域声源定位');
xlabel('x (厘米)');
ylabel('y (厘米)');
grid on;
axis equal;
hold off;

