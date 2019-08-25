close all;

mkdir 'pdf';

%% Setup

set(0, 'defaultLineLineWidth', 1.6, 'defaultAxesLineWidth', 1.6);
set(0, 'defaultAxesFontSize', 14, 'defaultAxesFontName', 'Times New Roman');
set(0, 'defaultTextInterpreter', 'latex');

%% Plots

data = readtable('../python/products/txt/data.txt');

copy = unique(data(:, 1:3), 'Rows');
copy.time = zeros(size(copy, 1), 1);

for i = 1:size(copy, 1)
    copy{i, 4} = min(data(string(data{:, 1}) == string(copy{i, 1}) & data{:, 2} == copy{i, 2}, :).time);
end

data = copy;

% Dichotomic

figure('Name', 'dichotomic', 'Position', [100 100 900 600]);

table = data(string(data.algorithm) == "dicho", :);
plot(table.n, table.time);

grid on; 

xlabel('Sequences length [-]');
ylabel('Computation time [ms]');

saveas(gcf, 'pdf/dichotomic.pdf');

% Hash

figure('Name', 'hash', 'Position', [100 100 900 600]);

table = data(string(data.algorithm) == "hash", :);
plot(table.n, table.time);

grid on; 

xlabel('Sequences length [-]');
ylabel('Computation time [ms]');

saveas(gcf, 'pdf/hash.pdf');

% Dynamic

figure('Name', 'dynamic', 'Position', [100 100 900 600]);

table = data(string(data.algorithm) == "dp", :);
plot(table.n, table.time);

grid on; 

xlabel('Sequences length [-]');
ylabel('Computation time [ms]');

saveas(gcf, 'pdf/dynamic.pdf');
