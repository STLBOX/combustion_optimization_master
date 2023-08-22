% 加入压力后的模型
clc; clear; close all;
%% step1: 读取数据
load('FEIXIANMODELDATA.mat')
DATA(1:800,1) = 200;  % 仅为程序能跑
NUMNUM = 90000;  % 120000
DATA1 = DATA(1:NUMNUM,:); 
%%
% 单模型or多模型
single_model = false; 
% 增量格式
INC_DATA1 = DATA1(2:end,:) - DATA1(1:end-1,:);
fuel_num = 6;
sec_num = 6;
sofa_num = 2;
o2_num = 1;
fp_num = 1;
load_num = 1; 
fangle_num = 1;
dhflow_num = 1;

% 负荷
Load = INC_DATA1(:,1);
% 燃烧器摆角
%Fangle = INC_DATA1(:,1);
% 氧量
O2 = INC_DATA1(:,2);
% 给煤量
Fuel = INC_DATA1(:,3:3+fuel_num-1);
% 二次风  AFE BCD
Sec = INC_DATA1(:,9:9+sec_num-1);
% 燃尽风  后墙 前墙
Sofa = INC_DATA1(:,15:15+sofa_num-1);
% 一次风压
Fp = INC_DATA1(:,17:17+fp_num-1);
% 减温水流量
%Dhflow = INC_DATA1(:,1);
% 预测变量  
% CO
CO = INC_DATA1(:,24);  % 原始21 滤波24  
% Nox
Nox = INC_DATA1(:,23);
% 再热气温
Rtem = INC_DATA1(:,19); 
% 排烟温度
Etem = INC_DATA1(:,20);
% O2量差异
Smax = INC_DATA1(:,27);

% NOx_base  Nox_base(k) + Nox(k) = Nox(k+1)
CO_base = DATA(1:NUMNUM-1,24);
Nox_base = DATA(1:NUMNUM-1,23);
Rtem_base = DATA(1:NUMNUM-1,19);
Etem_base = DATA(1:NUMNUM-1,20);
Smax_base = DATA(1:NUMNUM-1,27);
% Load_base,当前负荷
Load_base = DATA(1:NUMNUM,1);

% 对增量数据归一化，设置归一化参数
% 归一化参数
% global limit_Nox limit_Etem limit_Rtem
limit_Load = 8;
limit_Fangle = 0.7;
limit_O2 = 0.2;
limit_Fuel = 8;  
limit_Sec = 0.6; 
limit_Sofa = 0.4;  % [6, 6];

limit_Fp = 0.2; % 一次风压
limit_Dhflow = 7; % 减温水流量

limit_CO = 5; % CO
limit_Nox = 10;  
limit_Etem = 0.08;
limit_Rtem = 0.45;  % 再热汽温
limit_Smax = 0.08;  % O2量差异

% 归一化
Load_norm = (Load + limit_Load)./(2*limit_Load);
%Fangle_norm = (Fangle + limit_Fangle)./(2*limit_Fangle);
O2_norm = (O2 + limit_O2)./(2*limit_O2);
Fuel_norm = (Fuel + limit_Fuel)./(2*limit_Fuel);
Sec_norm = (Sec + limit_Sec)./(2*limit_Sec);
Sofa_norm = (Sofa + limit_Sofa)./(2*limit_Sofa);
Fp_norm = (Fp + limit_Fp)./(2*limit_Fp);
%Dhflow_norm = (Dhflow + limit_Dhflow)./(2*limit_Dhflow);

Nox_norm = (Nox + limit_Nox)./(2*limit_Nox);
Rtem_norm = (Rtem + limit_Rtem)./(2*limit_Rtem);
Etem_norm = (Etem + limit_Etem)./(2*limit_Etem);
CO_norm = (CO + limit_CO)./(2*limit_CO);
Smax_norm = (Smax + limit_Smax)./(2*limit_Smax);

% 更新模型时需要的速率限制，未使用
rate_limit_Rtem = 2; rate_limit_Etem = 2; rate_limit_Nox = 7; rate_limit_CO = 10; rate_limit_Smax = 10;
% 模型需要在该范围内才更新，未使用
min_CO = 20; min_Rtem = 520; min_Etem = 100; min_Nox = 90; min_Smax = 30;
max_CO = 100; max_Rtem = 620; max_Etem = 150; max_Nox = 250; max_Smax = 480;
%% step2.1 建模构造训练样本 xcell ycell
% 模型允许更新误差设置
CO_PermitError = 0.5;  % CO允许更新误差  0.5
Nox_PermitError = 2;  % NOx允许更新误差  2
Rtem_PermitError = 0.06;  % Rtem允许更新误差  0.06
Etem_PermitError = 0.01;% Etem允许更新误差 0.01
Smax_PermitError = 0.02;  % Smax允许更新误差 0.02

% 迟延时间和阶数设置
delay_o2_smax = 1; delay_o2_co = 1; delay_o2_rtem = 1; delay_o2_etem = 1; delay_o2_nox = 1;  % 关于Rtem、Etem、nox的氧量的迟延
order_o2_smax = 1; order_o2_co = 1; order_o2_rtem = 1; order_o2_etem = 1; order_o2_nox = 1;

delay_fuel_smax = 5; delay_fuel_co = 5; delay_fuel_rtem = 5; delay_fuel_etem = 5; delay_fuel_nox = 5;  
order_fuel_smax = 1; order_fuel_co = 1; order_fuel_rtem = 1; order_fuel_etem = 1; order_fuel_nox = 1;

delay_sec_smax = 5; delay_sec_co = 5; delay_sec_rtem = 5; delay_sec_etem = 5; delay_sec_nox = 5;
order_sec_smax = 1; order_sec_co = 1; order_sec_rtem = 1; order_sec_etem = 1; order_sec_nox = 1;

delay_sofa_smax = 5; delay_sofa_co = 5; delay_sofa_rtem = 5; delay_sofa_etem = 5; delay_sofa_nox = 5; 
order_sofa_smax = 1; order_sofa_co = 1;  order_sofa_rtem = 1; order_sofa_etem = 1; order_sofa_nox = 1;

delay_fp_smax = 5; delay_fp_co = 5; delay_fp_rtem = 5; delay_fp_etem = 5; delay_fp_nox = 5; 
order_fp_smax = 1; order_fp_co = 1;  order_fp_rtem = 1; order_fp_etem = 1; order_fp_nox = 1;

delay_dhflow_smax = 1; delay_dhflow_co = 1; delay_dhflow_rtem = 1; delay_dhflow_etem = 1; delay_dhflow_nox = 1; 
order_dhflow_smax = 1; order_dhflow_co = 1;  order_dhflow_rtem = 1; order_dhflow_etem = 1; order_dhflow_nox = 1;

delay_load_smax = 1; delay_load_co = 1; delay_load_rtem = 1; delay_load_etem = 1; delay_load_nox = 1;
order_load_smax = 1; order_load_co = 1; order_load_rtem = 1; order_load_etem = 1; order_load_nox= 1;
delay_Fangle_smax = 5; delay_Fangle_co = 5; delay_Fangle_rtem = 5; delay_Fangle_etem = 5; delay_Fangle_nox= 5;
order_Fangle_smax = 1; order_Fangle_co = 1; order_Fangle_rtem = 1; order_Fangle_etem = 1; order_Fangle_nox= 1;

order_rtem = 1;  % 不能修改，改了下面要联动修改
order_etem = 1;
order_nox= 1; 
order_co= 1;
order_smax= 1;

sum_order_rtem = order_load_rtem + order_o2_rtem + order_fuel_rtem*fuel_num + order_sec_rtem*sec_num + order_sofa_rtem*sofa_num + order_fp_rtem*fp_num + order_rtem;
sum_order_etem = order_load_etem + order_o2_etem + order_fuel_etem*fuel_num + order_sec_etem*sec_num + order_sofa_etem*sofa_num + order_fp_etem*fp_num + order_etem;
sum_order_nox = order_load_nox + order_o2_nox + order_fuel_nox*fuel_num + order_sec_nox*sec_num + order_sofa_nox*sofa_num + order_fp_nox*fp_num + order_nox;
sum_order_co = order_load_co + order_o2_co + order_fuel_co*fuel_num + order_sec_co*sec_num + order_sofa_co*sofa_num + order_fp_co*fp_num + order_co;
sum_order_smax = order_load_smax + order_o2_smax + order_fuel_smax*fuel_num + order_sec_smax*sec_num + order_sofa_smax*sofa_num + order_fp_smax*fp_num + order_smax;

% 初始化模型,设置初始化模型训练样本区间
start_train = 100;  % x(100) y(101)
end_train = 10000;
% 对于训练样本，前20000个用于初始化模型，后面用于更新
init_train = 8000;

% 构造指定迟延和阶数的训练集，这些数据可以该修改上面的迟延时间和迟延阶数
num_list = [load_num, o2_num, fuel_num, sec_num, sofa_num, fp_num];  % 无减温水流量
data_cell = {Load_norm, O2_norm, Fuel_norm, Sec_norm, Sofa_norm, Fp_norm};

% x_train_rtem  y_train_rtem, y采用不归一化数据
delay_list_rtem = [delay_load_rtem, delay_o2_rtem, delay_fuel_rtem, delay_sec_rtem, delay_sofa_rtem, delay_fp_rtem];
order_list_rtem = [order_load_rtem, order_o2_rtem, order_fuel_rtem, order_sec_rtem, order_sofa_rtem, order_fp_rtem];
x_train_rtem_load = Load_base(start_train:end_train); % 负荷全量，划分模型使用
x_train_rtem = construct_x_sample(start_train, end_train, sum_order_rtem, Load_norm, Rtem_norm,...
                        delay_list_rtem, order_list_rtem, order_load_rtem, data_cell, num_list);
y_train_rtem = Rtem(start_train+1:end_train+1);
y_train_rtem_base = Rtem_base(start_train+1:end_train+1);

% x_train_etem  y_train_etem
x_train_etem_load = Load_base(start_train:end_train); % 负荷全量，划分模型使用
delay_list_etem = [delay_load_etem, delay_o2_etem, delay_fuel_etem, delay_sec_etem, delay_sofa_etem, delay_fp_etem];
order_list_etem = [order_load_etem, order_o2_etem, order_fuel_etem, order_sec_etem, order_sofa_etem, order_fp_etem];
x_train_etem = construct_x_sample(start_train, end_train, sum_order_etem, Load_norm, Etem_norm,...
                        delay_list_etem, order_list_etem, order_load_etem, data_cell, num_list);
y_train_etem = Etem(start_train+1:end_train+1);
y_train_etem_base = Etem_base(start_train+1:end_train+1);

% x_train_nox  y_train_nox
x_train_nox_load = Load_base(start_train:end_train); % 负荷全量,确定模型
delay_list_nox = [delay_load_nox, delay_o2_nox, delay_fuel_nox, delay_sec_nox, delay_sofa_nox, delay_fp_nox];
order_list_nox = [order_load_nox, order_o2_nox, order_fuel_nox, order_sec_nox, order_sofa_nox, order_fp_nox];
x_train_nox = construct_x_sample(start_train, end_train, sum_order_nox, Load_norm, Nox_norm,...
                        delay_list_nox, order_list_nox, order_load_nox, data_cell, num_list);
y_train_nox = Nox(start_train+1:end_train+1);
y_train_nox_base = Nox_base(start_train+1:end_train+1);

% x_train_CO  y_train_CO
x_train_CO_load = Load_base(start_train:end_train); % 负荷全量,确定模型
delay_list_co = [delay_load_co, delay_o2_co, delay_fuel_co, delay_sec_co, delay_sofa_co, delay_fp_co];
order_list_co = [order_load_co, order_o2_co, order_fuel_co, order_sec_co, order_sofa_co, order_fp_co];
x_train_CO = construct_x_sample(start_train, end_train, sum_order_co, Load_norm, CO_norm,...
                        delay_list_co, order_list_co, order_load_co, data_cell, num_list);
y_train_CO = CO(start_train+1:end_train+1);
y_train_CO_base = CO_base(start_train+1:end_train+1);

% x_train_smax  y_train_smax
x_train_smax_load = Load_base(start_train:end_train); % 负荷全量,确定模型
delay_list_smax = [delay_load_smax, delay_o2_smax, delay_fuel_smax, delay_sec_smax, delay_sofa_smax, delay_fp_smax];
order_list_smax = [order_load_smax, order_o2_smax, order_fuel_smax, order_sec_smax, order_sofa_smax, order_fp_smax];
x_train_smax = construct_x_sample(start_train, end_train, sum_order_smax, Load_norm, Smax_norm,...
                        delay_list_smax, order_list_smax, order_load_smax, data_cell, num_list);
y_train_smax = Smax(start_train+1:end_train+1);
y_train_smax_base = Smax_base(start_train+1:end_train+1);


% 将x_train y_train依据Load划分为不同的样本
if single_model == true
    disp('单模型多步预测')
    divide_load = [-1, 1000]; % 划分负荷点取0,1000仅是为编程实现方便
    % 模型参数
    delta_Rtem = 1.2; 
    C_Rtem = 500;
    delta_Etem = 1.2; 
    C_Etem = 500;
    delta_Nox = 1.2; 
    C_Nox = 500;
    delta_CO = 1.2; 
    C_CO = 500;
    delta_Smax = 1.2; 
    C_Smax = 500;
else
    disp('多模型多步预测')
    divide_load = [-1, 258, 376,495, 1000]; % 低于330的负荷点不采用燃烧优化
    delta_Rtem = [1.2, 1.2, 1.2, 1.2]; 
    C_Rtem = [500, 500, 500, 500];
    delta_Etem =  [1.2, 1.2, 1.2, 1.2]; 
    C_Etem = [500, 500, 500, 500]; 
    delta_Nox = [1.2, 1.2, 1.2, 1.2]; 
    C_Nox = [500, 500, 500, 500];
    delta_CO = [1.2, 1.2, 1.2, 1.2]; 
    C_CO = [500, 500, 500, 500];
    delta_Smax = [1.2, 1.2, 1.2, 1.2]; 
    C_Smax = [500, 500, 500, 500];
end
divide_num = length(divide_load) - 1;  % 划分区间数量,对应的模型数量

% 依据Load 和 divide_load 对 x_train(1:init_trian,:) y_train(1:init_trian,:) 进行划分; 得到 xcell_train  ycell_train
% xcell_train_rtem ycell_train_rtem
xcell_train_rtem = cell(1,divide_num);
ycell_train_rtem = cell(1,divide_num);
x_train_init = x_train_rtem(1:init_train,:); % 用于init模型的样本;
y_train_init = y_train_rtem(1:init_train,:); % 用于init模型的样本;
for i = 1:divide_num
    xcell_train_rtem{i} = x_train_init((x_train_rtem_load(1:init_train,:) > divide_load(i)) & (x_train_rtem_load(1:init_train,:) <= divide_load(i+1)),:);
    ycell_train_rtem{i} = y_train_init((x_train_rtem_load(1:init_train,:) > divide_load(i)) & (x_train_rtem_load(1:init_train,:) <= divide_load(i+1)),:);
end

% xcell_train_etem ycell_train_etem
xcell_train_etem = cell(1,divide_num);
ycell_train_etem = cell(1,divide_num);
x_train_init = x_train_etem(1:init_train,:); % 用于init模型的样本;
y_train_init = y_train_etem(1:init_train,:); % 用于init模型的样本;
for i = 1:divide_num
    xcell_train_etem{i} = x_train_init((x_train_etem_load(1:init_train,:) > divide_load(i)) & (x_train_etem_load(1:init_train,:) <= divide_load(i+1)),:);
    ycell_train_etem{i} = y_train_init((x_train_etem_load(1:init_train,:) > divide_load(i)) & (x_train_etem_load(1:init_train,:) <= divide_load(i+1)),:);
end

% xcell_train_nox ycell_train_nox
xcell_train_nox = cell(1,divide_num);
ycell_train_nox = cell(1,divide_num);
x_train_init = x_train_nox(1:init_train,:); % 用于init模型的样本;
y_train_init = y_train_nox(1:init_train,:); % 用于init模型的样本;
for i = 1:divide_num
    xcell_train_nox{i} = x_train_init((x_train_nox_load(1:init_train,:) > divide_load(i)) & (x_train_nox_load(1:init_train,:) <= divide_load(i+1)),:);
    ycell_train_nox{i} = y_train_init((x_train_nox_load(1:init_train,:) > divide_load(i)) & (x_train_nox_load(1:init_train,:) <= divide_load(i+1)),:);
end

% xcell_train_CO ycell_train_CO
xcell_train_CO = cell(1,divide_num);
ycell_train_CO = cell(1,divide_num);
x_train_init = x_train_CO(1:init_train,:); % 用于init模型的样本;
y_train_init = y_train_CO(1:init_train,:); % 用于init模型的样本;
for i = 1:divide_num
    xcell_train_CO{i} = x_train_init((x_train_CO_load(1:init_train,:) > divide_load(i)) & (x_train_CO_load(1:init_train,:) <= divide_load(i+1)),:);
    ycell_train_CO{i} = y_train_init((x_train_CO_load(1:init_train,:) > divide_load(i)) & (x_train_CO_load(1:init_train,:) <= divide_load(i+1)),:);
end

% xcell_train_smax ycell_train_smax
xcell_train_smax = cell(1,divide_num);
ycell_train_smax = cell(1,divide_num);
x_train_init = x_train_smax(1:init_train,:); % 用于init模型的样本;
y_train_init = y_train_smax(1:init_train,:); % 用于init模型的样本;
for i = 1:divide_num
    xcell_train_smax{i} = x_train_init((x_train_smax_load(1:init_train,:) > divide_load(i)) & (x_train_smax_load(1:init_train,:) <= divide_load(i+1)),:);
    ycell_train_smax{i} = y_train_init((x_train_smax_load(1:init_train,:) > divide_load(i)) & (x_train_smax_load(1:init_train,:) <= divide_load(i+1)),:);
end
%% step2.2 利用 xcell ycell 初始化 models
% 前train_init个样本初始化，后面的样本用于更新训练

% 支持向量个数
sv_len = 500;

% 初始化模型
for i=1:divide_num
    % models_Rtem
    models_Rtem(i).delta = delta_Rtem(i);
    models_Rtem(i).C = C_Rtem(i);
    models_Rtem(i).x = xcell_train_rtem{i}(end-sv_len+1:end, :);
    models_Rtem(i).y = ycell_train_rtem{i}(end-sv_len+1:end, :);
    [a,b,H] = model_fit(models_Rtem(i).x, models_Rtem(i).y, models_Rtem(i).delta, models_Rtem(i).C);
    models_Rtem(i).H = H;
    models_Rtem(i).a = a;
    models_Rtem(i).b = b;

    % models_Etem
    models_Etem(i).delta = delta_Etem(i);
    models_Etem(i).C = C_Etem(i);
    models_Etem(i).x = xcell_train_etem{i}(end-sv_len+1:end, :);
    models_Etem(i).y = ycell_train_etem{i}(end-sv_len+1:end, :);
    [a,b,H] = model_fit(models_Etem(i).x, models_Etem(i).y, models_Etem(i).delta, models_Etem(i).C);
    models_Etem(i).H = H;
    models_Etem(i).a = a;
    models_Etem(i).b = b;
    
    % models_Nox
    models_Nox(i).delta = delta_Nox(i);
    models_Nox(i).C = C_Nox(i);
    models_Nox(i).x = xcell_train_nox{i}(end-sv_len+1:end, :);
    models_Nox(i).y = ycell_train_nox{i}(end-sv_len+1:end, :);
    [a,b,H] = model_fit(models_Nox(i).x, models_Nox(i).y, models_Nox(i).delta, models_Nox(i).C);
    models_Nox(i).H = H;
    models_Nox(i).a = a;
    models_Nox(i).b = b;

    % models_CO
    models_CO(i).delta = delta_CO(i);
    models_CO(i).C = C_CO(i);
    models_CO(i).x = xcell_train_CO{i}(end-sv_len+1:end, :);
    models_CO(i).y = ycell_train_CO{i}(end-sv_len+1:end, :);
    [a,b,H] = model_fit(models_CO(i).x, models_CO(i).y, models_CO(i).delta, models_CO(i).C);
    models_CO(i).H = H;
    models_CO(i).a = a;
    models_CO(i).b = b;
    
    % models_Smax
    models_Smax(i).delta = delta_Smax(i);
    models_Smax(i).C = C_Smax(i);
    models_Smax(i).x = xcell_train_smax{i}(end-sv_len+1:end, :);
    models_Smax(i).y = ycell_train_smax{i}(end-sv_len+1:end, :);
    [a,b,H] = model_fit(models_Smax(i).x, models_Smax(i).y, models_Smax(i).delta, models_Smax(i).C);
    models_Smax(i).H = H;
    models_Smax(i).a = a;
    models_Smax(i).b = b; 
end

%% step2.2 利用 x_train(init_train+1:end,:) y_train(init_train+1:end,:) 更新初始化模型

p = 1;  % 预测步数
train_len = length(x_train_rtem);
disp('更新 models_Rtem')
[y_pred_update_rtem,UpdateRate_update_Rtem] = simulink_predict(x_train_rtem, y_train_rtem, x_train_rtem_load,...
                                                   init_train, p, divide_load, models_Rtem, Rtem_PermitError, limit_Rtem,...
                                                   y_train_rtem_base, rate_limit_Rtem, min_Rtem, max_Rtem);
                                               
y_true_update_rtem = y_train_rtem(init_train+1:train_len-p+1, 1);
y_update_rtem_base = y_train_rtem_base(init_train+1:train_len-p+1, 1);  % 反归一化使用

disp('更新 models_Etem')
[y_pred_update_etem,UpdateRate_update_Etem] = simulink_predict(x_train_etem, y_train_etem, x_train_etem_load,...
                                                   init_train, p, divide_load, models_Etem, Etem_PermitError, limit_Etem,...
                                                    y_train_etem_base, rate_limit_Etem, min_Etem, max_Etem);
y_true_update_etem = y_train_etem(init_train+1:train_len-p+1,1);
y_update_etem_base = y_train_etem_base(init_train+1:train_len-p+1, 1);

p = 1;
disp('更新 models_Nox')
[y_pred_update_nox,UpdateRate_update_Nox] = simulink_predict(x_train_nox, y_train_nox, x_train_nox_load,...
                                                   init_train, p, divide_load, models_Nox, Nox_PermitError, limit_Nox,...
                                                    y_train_nox_base, rate_limit_Nox, min_Nox, max_Nox);
y_true_update_nox = y_train_nox(init_train+1:train_len-p+1,1);
y_update_nox_base = y_train_nox_base(init_train+1:train_len-p+1, 1);

disp('更新 models_CO')
[y_pred_update_CO,UpdateRate_update_CO] = simulink_predict(x_train_CO, y_train_CO, x_train_CO_load,...
                                                   init_train, p, divide_load, models_CO, CO_PermitError, limit_CO,...
                                                    y_train_CO_base, rate_limit_CO, min_CO, max_CO);
y_true_update_CO = y_train_CO(init_train+1:train_len-p+1,1);
y_update_CO_base = y_train_CO_base(init_train+1:train_len-p+1, 1);


disp('更新 models_Smax')
[y_pred_update_smax,UpdateRate_update_Smax] = simulink_predict(x_train_smax, y_train_smax, x_train_smax_load,...
                                                   init_train, p, divide_load, models_Smax, Smax_PermitError, limit_Smax,...
                                                    y_train_smax_base, rate_limit_Smax, min_Smax, max_Smax);
y_true_update_smax = y_train_smax(init_train+1:train_len-p+1,1);
y_update_smax_base = y_train_smax_base(init_train+1:train_len-p+1, 1);
%% step3.1 单步与多步预测测试 构造测试样本x_test, y_test

start_test = 20000; % 仿真开始点
end_test = 25000; % 仿真样本数
test_len = end_test-start_test+1; % 测试样本数量
x_test_load = Load_base(start_test:end_test); % 负荷全量，确定模型使用

% x_test_rtem  y_test_rtem
x_test_rtem = construct_x_sample(start_test, end_test, sum_order_rtem, Load_norm, Rtem_norm,...
                        delay_list_rtem, order_list_rtem, order_load_rtem, data_cell, num_list);
y_test_rtem = Rtem(start_test+1:end_test+1);
y_test_rtem_base = Rtem_base(start_test+1:end_test+1);

% x_train_etem  y_train_etem
x_test_etem = construct_x_sample(start_test, end_test, sum_order_etem, Load_norm, Etem_norm,...
                        delay_list_etem, order_list_etem, order_load_etem, data_cell, num_list);
y_test_etem = Etem(start_test+1:end_test+1);
y_test_etem_base = Etem_base(start_test+1:end_test+1);

% x_test_nox y_test_nox
x_test_nox = construct_x_sample(start_test, end_test, sum_order_nox, Load_norm, Nox_norm,...
                        delay_list_nox, order_list_nox, order_load_nox, data_cell, num_list);
y_test_nox = Nox(start_test+1:end_test+1);
y_test_nox_base = Nox_base(start_test+1:end_test+1);  

% x_test_CO y_test_CO
x_test_CO = construct_x_sample(start_test, end_test, sum_order_co, Load_norm, CO_norm,...
                        delay_list_co, order_list_co, order_load_co, data_cell, num_list);
y_test_CO = CO(start_test+1:end_test+1);
y_test_CO_base = CO_base(start_test+1:end_test+1);  

% x_test_smax y_test_smax
x_test_smax = construct_x_sample(start_test, end_test, sum_order_smax, Load_norm, Smax_norm,...
                        delay_list_smax, order_list_smax, order_load_smax, data_cell, num_list);
y_test_smax = Smax(start_test+1:end_test+1);
y_test_smax_base = Smax_base(start_test+1:end_test+1);  
%% step3.2 单步与多步预测测试 利用 models_Rtem models_Etem 进行测试
p = 20;  % 预测步数

init_test = 0; % 从1开始test

disp('models_Rtem 测试')
[y_pred_test_rtem, UpdateRate_test_Rtem] = simulink_predict(x_test_rtem, y_test_rtem,  x_test_load,...
                                          init_test, p, divide_load, models_Rtem, Rtem_PermitError, limit_Rtem,...
                                          y_test_rtem_base, rate_limit_Rtem, min_Rtem, max_Rtem);
                                                          
disp('models_Etem 测试')
[y_pred_test_etem, UpdateRate_test_Etem] = simulink_predict(x_test_etem, y_test_etem,  x_test_load,...
                                           init_test, p, divide_load, models_Etem, Etem_PermitError, limit_Etem,...
                                           y_test_etem_base, rate_limit_Etem, min_Etem, max_Etem);
  
disp('models_Nox 测试')
[y_pred_test_nox, UpdateRate_test_Nox] = simulink_predict(x_test_nox, y_test_nox,  x_test_load,...
                                          init_test, p, divide_load, models_Nox, Nox_PermitError, limit_Nox,...
                                          y_test_nox_base, rate_limit_Nox, min_Nox, max_Nox);

disp('models_CO 测试')
[y_pred_test_CO, UpdateRate_test_CO] = simulink_predict(x_test_CO, y_test_CO,  x_test_load,...
                                          init_test, p, divide_load, models_CO, CO_PermitError, limit_CO,...
                                          y_test_CO_base, rate_limit_CO, min_CO, max_CO);
                                      
disp('models_Smax 测试')
[y_pred_test_smax, UpdateRate_test_Smax] = simulink_predict(x_test_smax, y_test_smax,  x_test_load,...
                                          init_test, p, divide_load, models_Smax, Smax_PermitError, limit_Smax,...
                                          y_test_smax_base, rate_limit_Smax, min_Smax, max_Smax);
%% 3.3 反归一结果，统一构造成 zeros(test_len-p, p) 形式，以画图

% y_true_test_rtem y_true_test_rtem
y_true_test_rtem_abs = y_test_rtem + y_test_rtem_base;
y_true_test_etem_abs = y_test_etem + y_test_etem_base;
y_true_test_nox_abs = y_test_nox + y_test_nox_base;
y_true_test_CO_abs = y_test_CO + y_test_CO_base;
y_true_test_smax_abs = y_test_smax + y_test_smax_base;

y_true_test_rtem = zeros(test_len-p+1, p);
y_true_test_etem = zeros(test_len-p+1, p);
y_true_test_nox = zeros(test_len-p+1, p);
y_true_test_CO = zeros(test_len-p+1, p);
y_true_test_smax = zeros(test_len-p+1, p);

for i = 1:p
    y_true_test_rtem(:, i) = y_true_test_rtem_abs(i:test_len-p+i);
    y_true_test_etem(:, i) = y_true_test_etem_abs(i:test_len-p+i);
    y_true_test_nox(:, i) = y_true_test_nox_abs(i:test_len-p+i);
    y_true_test_CO(:, i) = y_true_test_CO_abs(i:test_len-p+i);
    y_true_test_smax(:, i) = y_true_test_smax_abs(i:test_len-p+i);
end
 
% y_pred_test_rtem y_pred_test_etem
y_pred_test_rtem(:,1) = y_test_rtem_base(1:test_len-p+1,1) + y_pred_test_rtem(:,1);
y_pred_test_etem(:,1) = y_test_etem_base(1:test_len-p+1,1) + y_pred_test_etem(:,1);
y_pred_test_nox(:,1) = y_test_nox_base(1:test_len-p+1,1) + y_pred_test_nox(:,1);
y_pred_test_CO(:,1) = y_test_CO_base(1:test_len-p+1,1) + y_pred_test_CO(:,1);
y_pred_test_smax(:,1) = y_test_smax_base(1:test_len-p+1,1) + y_pred_test_smax(:,1);


for i = 2:p
    y_pred_test_rtem(:,i) = y_pred_test_rtem(:,i-1) + y_pred_test_rtem(:,i);
    y_pred_test_etem(:,i) = y_pred_test_etem(:,i-1) + y_pred_test_etem(:,i);
    y_pred_test_nox(:,i) = y_pred_test_nox(:,i-1) + y_pred_test_nox(:,i);
    y_pred_test_CO(:,i) = y_pred_test_CO(:,i-1) + y_pred_test_CO(:,i);
   y_pred_test_smax(:,i) = y_pred_test_smax(:,i-1) + y_pred_test_smax(:,i);
end

if single_model == false
    MI_y_true_test_rtem = y_true_test_rtem;
    MI_y_pred_test_rtem = y_pred_test_rtem;
    MI_MAE_rtem = sum(abs(y_true_test_rtem - y_pred_test_rtem),1)/length(y_true_test_rtem);
    
    MI_y_true_test_etem = y_true_test_etem;
    MI_y_pred_test_etem = y_pred_test_etem;
    MI_MAE_etem = sum(abs(y_true_test_etem - y_pred_test_etem),1)/length(y_true_test_etem);

    MI_y_true_test_nox = y_true_test_nox;
    MI_y_pred_test_nox = y_pred_test_nox;
    MI_MAE_nox = sum(abs(y_true_test_nox - y_pred_test_nox),1)/length(y_true_test_nox);
    
    MI_y_true_test_CO = y_true_test_CO;
    MI_y_pred_test_CO = y_pred_test_CO;
    MI_MAE_CO = sum(abs(y_true_test_CO - y_pred_test_CO),1)/length(y_true_test_CO);

    MI_y_true_test_smax = y_true_test_smax;
    MI_y_pred_test_smax = y_pred_test_smax;
    MI_MAE_smax = sum(abs(y_true_test_smax - y_pred_test_smax),1)/length(y_true_test_smax);

    save('MI_result.mat','MI_y_true_test_rtem','MI_y_pred_test_rtem','MI_MAE_rtem',...
         'MI_y_true_test_etem','MI_y_pred_test_etem','MI_MAE_etem',...
         'MI_y_true_test_nox','MI_y_pred_test_nox','MI_MAE_nox', ...
         'MI_y_true_test_CO','MI_y_pred_test_CO','MI_MAE_CO',...
         'MI_y_true_test_smax','MI_y_pred_test_smax','MI_MAE_smax',...
         'x_test_load')
else
    SI_y_true_test_rtem = y_true_test_rtem;
    SI_y_pred_test_rtem = y_pred_test_rtem;
    SI_MAE_rtem = sum(abs(y_true_test_rtem - y_pred_test_rtem),1)/length(y_true_teMI_y_true_test_noxst_rtem);
    
    SI_y_true_test_etem = y_true_test_etem;
    SI_y_pred_test_etem = y_pred_test_etem;
    SI_MAE_etem = sum(abs(y_true_test_etem - y_pred_test_etem),1)/length(y_true_test_etem);
    
    SI_y_true_test_nox = y_true_test_nox;
    SI_y_pred_test_nox = y_pred_test_nox;
    SI_MAE_nox = sum(abs(y_true_test_nox - y_pred_test_nox),1)/length(y_true_test_nox);

    SI_y_true_test_CO = y_true_test_CO;
    SI_y_pred_test_CO = y_pred_test_CO;
    SI_MAE_CO = sum(abs(y_true_test_CO - y_pred_test_CO),1)/length(y_true_test_CO);

    
    save('SI_result.mat','SI_y_true_test_rtem','SI_y_pred_test_rtem','SI_MAE_rtem',...
         'SI_y_true_test_etem','SI_y_pred_test_etem','SI_MAE_etem',...
         'SI_y_true_test_nox','SI_y_pred_test_nox','SI_MAE_nox' ,...
         'SI_y_true_test_CO','SI_y_pred_test_CO','SI_MAE_CO')
end

% y_pred_update
y_pred_update_etem = y_pred_update_etem + y_update_etem_base;
y_true_update_etem = y_true_update_etem + y_update_etem_base;
y_pred_update_rtem = y_pred_update_rtem + y_update_rtem_base;
y_true_update_rtem = y_true_update_rtem + y_update_rtem_base;
y_pred_update_nox = y_pred_update_nox + y_update_nox_base;
y_true_update_nox = y_true_update_nox + y_update_nox_base;
y_pred_update_CO = y_pred_update_CO + y_update_CO_base;
y_true_update_CO = y_true_update_CO + y_update_CO_base;
y_pred_update_smax = y_pred_update_smax + y_update_smax_base;
y_true_update_smax = y_true_update_smax + y_update_smax_base;
%% 4.1 单步预测结果画图 （对更新过程 和 测试过程分析)
draw_h1 = false;
if draw_h1 == true
    figure()
    s = 1;
    e = 10;
    subplot(4,2,1)
    plot(y_true_update_etem(s:e),'r','LineWidth',2)
    hold on
    plot(y_pred_update_etem(s:e),'b','LineWidth',2)
    % 计算 MAE
    MAE = sum(abs((y_true_update_etem-y_pred_update_etem)))/length(y_true_update_etem);
    legend('true','pred')
    xlabel(['更新模型样本','  MAE=',num2str(round(MAE,2)), ' 模型更新率',num2str(round(UpdateRate_update_Etem*100,2)),'%'])
    ylabel('排烟温度(℃)')
    set(gca,'FontSize',12);

    subplot(4,2,2)
    plot(y_true_test_etem(s:e,1),'r','LineWidth',2)
    hold on
    plot(y_pred_test_etem(s:e,1),'b','LineWidth',2)
    % 计算 MAE
    MAE = sum(abs((y_true_test_etem(:,1)-y_pred_test_etem(:,1))))/length(y_true_test_etem);
    legend('true','pred')
    xlabel(['测试样本','  MAE=',num2str(round(MAE,2)), '  模型更新率',num2str(round(UpdateRate_test_Etem*100,2)),'%'])
    ylabel('排烟温度(℃)')
    set(gca,'FontSize',12);

    subplot(4,2,3)
    plot(y_true_update_rtem(s:e),'r','LineWidth',2)
    hold on
    plot(y_pred_update_rtem(s:e),'b','LineWidth',2)
    % 计算 MAE
    MAE = sum(abs((y_true_update_rtem-y_pred_update_rtem)))/length(y_true_update_rtem);
    legend('true','pred')
    xlabel(['更新模型样本','  MAE=',num2str(round(MAE,2)), ' 模型更新次数',num2str(round(UpdateRate_update_Rtem*100,2)),'%'])
    ylabel('再热汽温(℃)')
    set(gca,'FontSize',12);

    subplot(4,2,4)
    plot(y_true_test_rtem(s:e,1),'r','LineWidth',2)
    hold on
    plot(y_pred_test_rtem(s:e,1),'b','LineWidth',2)
    % 计算 MAE
    MAE = sum(abs((y_true_test_rtem(:,1)-y_pred_test_rtem(:,1))))/length(y_true_test_rtem);
    legend('true','pred')
    xlabel(['测试样本','  MAE=',num2str(round(MAE,2)), '  模型更新率',num2str(round(UpdateRate_test_Rtem*100,2)),'%'])
    ylabel('再热汽温(℃)')
    set(gca,'FontSize',12);


    subplot(4,2,5)
    plot(y_true_update_nox(s:e),'r','LineWidth',2)
    hold on
    plot(y_pred_update_nox(s:e),'b','LineWidth',2)
    % 计算 MAE
    MAE = sum(abs((y_true_update_nox-y_pred_update_nox)))/length(y_true_update_nox);
    legend('true','pred')
    xlabel(['更新模型样本','  MAE=',num2str(round(MAE,2)), ' 模型更新次数',num2str(round(UpdateRate_update_Nox*100,2)),'%'])
    ylabel('Nox/(mg/m^3)')
    set(gca,'FontSize',12);

    subplot(4,2,6)
    plot(y_true_test_nox(s:e,1),'r','LineWidth',2)
    hold on
    plot(y_pred_test_nox(s:e,1),'b','LineWidth',2)
    % 计算 MAE
    MAE = sum(abs((y_true_test_nox(:,1)-y_pred_test_nox(:,1))))/length(y_true_test_nox);
    legend('true','pred')
    xlabel(['测试样本','  MAE=',num2str(round(MAE,2)), '  模型更新率',num2str(round(UpdateRate_test_Nox*100,2)),'%'])
    ylabel('Nox/(mg/m^3)')
    set(gca,'FontSize',12);


    subplot(4,2,7)
    plot(y_true_update_CO(s:e),'r','LineWidth',2)
    hold on
    plot(y_pred_update_CO(s:e),'b','LineWidth',2)
    % 计算 MAE
    MAE = sum(abs((y_true_update_CO-y_pred_update_CO)))/length(y_true_update_CO);
    legend('true','pred')
    xlabel(['更新模型样本','  MAE=',num2str(round(MAE,2)), ' 模型更新次数',num2str(round(UpdateRate_update_CO*100,2)),'%'])
    ylabel('CO/(mg/m^3)')
    set(gca,'FontSize',12);

    subplot(4,2,8)
    plot(y_true_test_CO(s:e,1),'r','LineWidth',2)
    hold on
    plot(y_pred_test_CO(s:e,1),'b','LineWidth',2)
    % 计算 MAE
    MAE = sum(abs((y_true_test_CO(:,1)-y_pred_test_CO(:,1))))/length(y_true_test_CO);
    legend('true','pred')
    xlabel(['测试样本','  MAE=',num2str(round(MAE,2)), '  模型更新率',num2str(round(UpdateRate_test_CO*100,2)),'%'])
    ylabel('CO/(mg/m^3)')
    set(gca,'FontSize',12);
end
%% 4.2 多步预测结果画图 (测试集)
figure()
s = 4000;
e = 5000;
p = 20;
subplot(5,1,1)
plot(s:e, y_true_test_etem(s:e,1),'r','LineWidth',2)
hold 
for i=s+20:20:e
    plot(i-p:i-1, y_pred_test_etem(i-p,:), 'b', 'LineWidth', 2)
    hold on
end
legend('true','pred')
xlabel('测试样本')
ylabel('排烟温度(℃)')
set(gca,'FontSize',12);

subplot(5,1,2)
plot(s:e, y_true_test_rtem(s:e,1),'r','LineWidth',2)
hold 
for i=s+20:20:e
    plot(i-p:i-1, y_pred_test_rtem(i-p,:), 'b', 'LineWidth', 2)
    hold on
end
legend('true','pred')
xlabel('测试样本')
ylabel('再热汽温(℃)')
set(gca,'FontSize',12);


subplot(5,1,3)
plot(s:e, y_true_test_nox(s:e,1),'r','LineWidth',2)
hold 
for i=s+20:20:e
    plot(i-p:i-1, y_pred_test_nox(i-p,:), 'b', 'LineWidth', 2)
    hold on
end
legend('true','pred')
xlabel('测试样本')
ylabel('Nox/(mg/m^3)')
set(gca,'FontSize',12);

subplot(5,1,4)
plot(s:e, y_true_test_CO(s:e,1),'r','LineWidth',2)
hold 
for i=s+20:20:e
    plot(i-p:i-1, y_pred_test_CO(i-p,:), 'b', 'LineWidth', 2)
    hold on
end
legend('true','pred')
xlabel('测试样本')
ylabel('CO/(mg/m^3)')
set(gca,'FontSize',12);

%% 4.3绘制负荷
figure()
plot(s:e, x_test_load(s:e,1),'r','LineWidth',2)
hold 
legend('load')
xlabel('测试样本')
ylabel('负荷/(MW)')
set(gca,'FontSize',12);
%% 4.4观测单个模型多步预测结果 Nox为例
figure()
subplot(2,1,1)
s=30000;
e=39900;
plot(s:e, y_true_test_nox(s:e,1),'r','LineWidth',2)
hold
for i=s+20:20:e
    plot(i-p:i-1, y_pred_test_nox(i-p,:), 'b', 'LineWidth', 2)
    hold on
end
legend('true','pred')
ylabel('NOx/(mg/m^3)')
set(gca,'FontSize',14);
subplot(2,1,2)
plot(s:e, x_test_load(s:e,1),'r','LineWidth',2)
hold 
legend('load')
xlabel('测试样本')
ylabel('负荷/(MW)')
set(gca,'FontSize',14);
%%
% MI_y_true_test_nox01 = MI_y_true_test_nox;
% MI_y_pred_test_nox01 = MI_y_pred_test_nox;
% MI_MAE_nox01 = MI_MAE_nox;
% UpdateRate_test_nox01 = num2str(round(UpdateRate_test_Nox*100,2));
% save('nox01.mat','MI_y_true_test_nox01','MI_y_pred_test_nox01','MI_MAE_nox01','UpdateRate_test_nox01')
figure()
s=3000;
e=4000;
plot(s:e, y_true_test_smax(s:e,1),'r','LineWidth',2)
hold on
for i=s+20:20:e
    plot(i-p:i-1, y_pred_test_smax(i-p,:), 'b', 'LineWidth', 2)
    hold on
end
legend('true','pred')
xlabel('测试样本')
ylabel('NOx/(mg/m^3)')
set(gca,'FontSize',14);

%% 保存数据 
saveflag = 1;
if saveflag == 1
for i = 2:divide_num 
    % NOx模型参数 3 个
    Alfa_Nox = [models_Nox(i).a; models_Nox(i).b];
    str_Alfa_Nox = sprintf("Alfa_Nox%d.txt",i-1);
    save(str_Alfa_Nox,'Alfa_Nox','-ascii');
 
    H_Nox = models_Nox(i).H;
    str_H_Nox = sprintf("H_Nox%d.txt",i-1);
    save(str_H_Nox,'H_Nox','-ascii');
    
    X_Nox = models_Nox(i).x';
    str_X_Nox = sprintf("X_Nox%d.txt",i-1);
    save(str_X_Nox,'X_Nox','-ascii');
    
    Y_Nox = models_Nox(i).y;
    str_Y_Nox = sprintf("Y_Nox%d.txt",i-1);
    save(str_Y_Nox,'Y_Nox','-ascii');
  
    % Etem模型参数 4 个
    Alfa_Etem = [models_Etem(i).a; models_Etem(i).b];
    str_Alfa_Etem = sprintf("Alfa_Etem%d.txt",i-1);
    save(str_Alfa_Etem,'Alfa_Etem','-ascii');
 
    H_Etem = models_Etem(i).H;
    str_H_Etem = sprintf("H_Etem%d.txt",i-1);
    save(str_H_Etem,'H_Etem','-ascii');
    
    X_Etem = models_Etem(i).x';
    str_X_Etem = sprintf("X_Etem%d.txt",i-1);
    save(str_X_Etem,'X_Etem','-ascii');
   
    Y_Etem = models_Etem(i).y;
    str_Y_Etem = sprintf("Y_Etem%d.txt",i-1);
    save(str_Y_Etem,'Y_Etem','-ascii');
    
    % Rtem模型参数 4 个
    Alfa_Rtem = [models_Rtem(i).a; models_Rtem(i).b];
    str_Alfa_Rtem = sprintf("Alfa_Rtem%d.txt",i-1);
    save(str_Alfa_Rtem,'Alfa_Rtem','-ascii');
 
    H_Rtem = models_Rtem(i).H;
    str_H_Rtem = sprintf("H_Rtem%d.txt",i-1);
    save(str_H_Rtem,'H_Rtem','-ascii');
    
    X_Rtem = models_Rtem(i).x';
    str_X_Rtem = sprintf("X_Rtem%d.txt",i-1);
    save(str_X_Rtem,'X_Rtem','-ascii');
    
    Y_Rtem = models_Rtem(i).y;
    str_Y_Rtem = sprintf("Y_Rtem%d.txt",i-1);
    save(str_Y_Rtem,'Y_Rtem','-ascii');

    % CO模型参数 4 个
    Alfa_CO = [models_CO(i).a; models_CO(i).b];
    str_Alfa_CO = sprintf("Alfa_CO%d.txt",i-1);
    save(str_Alfa_CO,'Alfa_CO','-ascii');
 
    H_CO = models_CO(i).H;
    str_H_CO = sprintf("H_CO%d.txt",i-1);
    save(str_H_CO,'H_CO','-ascii');
    
    X_CO = models_CO(i).x';
    str_X_CO = sprintf("X_CO%d.txt",i-1);
    save(str_X_CO,'X_CO','-ascii');
    
    Y_CO = models_CO(i).y;
    str_Y_CO = sprintf("Y_CO%d.txt",i-1);
    save(str_Y_CO,'Y_CO','-ascii');

    % Smax模型参数 4 个
    Alfa_Smax = [models_Smax(i).a; models_Smax(i).b];
    str_Alfa_Smax = sprintf("Alfa_Smax%d.txt",i-1);
    save(str_Alfa_Smax,'Alfa_Smax','-ascii');
 
    H_Smax = models_Smax(i).H;
    str_H_Smax = sprintf("H_Smax%d.txt",i-1);
    save(str_H_Smax,'H_Smax','-ascii');
    
    X_Smax = models_Smax(i).x';
    str_X_Smax = sprintf("X_Smax%d.txt",i-1);
    save(str_X_Smax,'X_Smax','-ascii');
    
    Y_Smax = models_Smax(i).y;
    str_Y_Smax = sprintf("Y_Smax%d.txt",i-1);
    save(str_Y_Smax,'Y_Smax','-ascii');
end
end

%% 验证track
models_Nox_v = models_Nox;
valid_track = 0;

if valid_track==1
    % 用于验证track的正确性
    start_test = 5; % 仿真开始点
    end_test = 800; % 仿真样本数
    test_len = end_test-start_test+1; % 测试样本数量
    x_test_load = Load_base(start_test:end_test); % 负荷全量，确定模型使用
    % x_test_rtem  y_test_rtem
    x_test_rtem = construct_x_sample(start_test, end_test, sum_order_rtem, Load_norm, Rtem_norm,...
                            delay_list_rtem, order_list_rtem, order_load_rtem, data_cell_dhflow, num_list_dhflow);
    y_test_rtem = Rtem(start_test+1:end_test+1);
    y_test_rtem_base = Rtem_base(start_test+1:end_test+1);
    % x_train_etem  y_train_etem
    x_test_etem = construct_x_sample(start_test, end_test, sum_order_etem, Load_norm, Etem_norm,...
                            delay_list_etem, order_list_etem, order_load_etem, data_cell, num_list);
    y_test_etem = Etem(start_test+1:end_test+1);
    y_test_etem_base = Etem_base(start_test+1:end_test+1);
    % x_test_nox y_test_nox
    x_test_nox = construct_x_sample(start_test, end_test, sum_order_nox, Load_norm, Nox_norm,...
                            delay_list_nox, order_list_nox, order_load_nox, data_cell, num_list);
    y_test_nox = Nox(start_test+1:end_test+1);
    y_test_nox_base = Nox_base(start_test+1:end_test+1); 

    % x_test_CO y_test_CO
    x_test_CO = construct_x_sample(start_test, end_test, sum_order_co, Load_norm, CO_norm,...
                            delay_list_co, order_list_co, order_load_co, data_cell, num_list);
    y_test_CO = CO(start_test+1:end_test+1);
    y_test_CO_base = CO_base(start_test+1:end_test+1); 


    % x_test_Smax y_test_Smax
    x_test_smax = construct_x_sample(start_test, end_test, sum_order_smax, Load_norm, Smax_norm,...
                            delay_list_smax, order_list_smax, order_load_smax, data_cell_dhflow, num_list_dhflow);
    y_test_smax = Smax(start_test+1:end_test+1);
    y_test_smax_base = Smax_base(start_test+1:end_test+1); 

    p = 1;  % 预测步数
    init_test = 0; 
    %{
    disp('models_Rtem track验证')
    [y_pred_test_rtem, UpdateRate_test_Rtem] = simulink_predict(x_test_rtem, y_test_rtem,  x_test_load,...
                                              init_test, p, divide_load, models_Rtem, Rtem_PermitError, limit_Rtem,...
                                              y_test_rtem_base, rate_limit_Rtem, min_Rtem, max_Rtem);

    disp('models_Etem track验证')
    [y_pred_test_etem, UpdateRate_test_Etem] = simulink_predict(x_test_etem, y_test_etem,  x_test_load,...
                                               init_test, p, divide_load, models_Etem, Etem_PermitError, limit_Etem,...
                                               y_test_etem_base, rate_limit_Etem, min_Etem, max_Etem); 
    %}
    disp('models_Nox track验证')
    [y_pred_test_nox, UpdateRate_test_Nox] = simulink_predict(x_test_nox, y_test_nox,  x_test_load,...
                                              init_test, p, divide_load, models_Nox_v, Nox_PermitError, limit_Nox,...
                                              y_test_nox_base, rate_limit_Nox, min_Nox, max_Nox);
    disp('models_CO track验证')
    [y_pred_test_CO, UpdateRate_test_CO] = simulink_predict(x_test_CO, y_test_CO,  x_test_load,...
                                              init_test, p, divide_load, models_CO, CO_PermitError, limit_CO,...
                                              y_test_CO_base, rate_limit_CO, min_CO, max_CO);

    disp('models_Smax track验证')
    [y_pred_test_smax, UpdateRate_test_Smax] = simulink_predict(x_test_smax, y_test_smax,  x_test_load,...
                                              init_test, p, divide_load, models_Smax, Smax_PermitError, limit_Smax,...
                                              y_test_smax_base, rate_limit_Smax, min_Smax, max_Smax);
    % y_pred_test_rtem y_pred_test_etem
    %y_pred_test_rtem(:,1) = y_test_rtem_base(1:test_len-p+1,1) + y_pred_test_rtem(:,1);
    %y_pred_test_etem(:,1) = y_test_etem_base(1:test_len-p+1,1) + y_pred_test_etem(:,1);
    y_pred_test_nox(:,1) = y_test_nox_base(1:test_len-p+1,1) + y_pred_test_nox(:,1);
    y_pred_test_CO(:,1) = y_test_CO_base(1:test_len-p+1,1) + y_pred_test_CO(:,1);
    y_pred_test_smax(:,1) = y_test_smax_base(1:test_len-p+1,1) + y_pred_test_smax(:,1);
end
%% function

% 构造x样本函数这里以Rtem为例
function x_train_rtem = construct_x_sample(start_train, end_train, sum_order_rtem, Load_norm, Rtem_norm,...
                        delay_list_rtem, order_list_rtem, order_load_rtem, data_cell, num_list)
% x_train_rtem  y_train_rtem
x_train_rtem = zeros(end_train-start_train+1, sum_order_rtem);
%x_train_rtem(:,1) = Load_norm(start_train:end_train); % 负荷归一化
x_train_rtem(:,end) = Rtem_norm(start_train:end_train); % Rtem
%k = order_load_rtem + 1; % 构造时，初始赋值列
k = 1;
for i = 1:length(delay_list_rtem)  % 不同类操作量数量
    delay_i = delay_list_rtem(i);
    norm_i = data_cell{i};
    for n = 1:num_list(i) % 同类操作量数量
        for j = 1:order_list_rtem(i) % 阶数
            % start-delay+2-order    delay和order决定行位置， n决定列位置
            x_train_rtem(:, k) = norm_i(start_train-delay_i+2-j:end_train-delay_i+2-j, n);
            k = k + 1;
        end
    end
end
end


% 以Rtem为例,p步预测
function [y_pred_update_rtem,UpdateRate_update_Rtem] = simulink_predict(x_train_rtem, y_train_rtem,  x_train_rtem_load,...
                                                       init_train, p, divide_load, models_Rtem, Rtem_PermitError, limit_Rtem,...
                                                       y_train_rtem_base, Rtem_rate_limit, Min_Rtem, Max_Rtem)
UpdateNum_Rtem = 0;
train_len = length(x_train_rtem);
y_pred_update_rtem = zeros(train_len-init_train-p+1, p); % 记录每一步预测结果
for i = init_train+1:train_len-p+1 % train_len-p+1,因为p步预测需要用到后面的控制x，这里编程略微麻烦，可简化，都是TM说啥统一格式
    x_current = x_train_rtem(i:i+p-1,:); % 模拟优化后的的控制量
    y_current = y_train_rtem(i,1); % 当前单步预测真实值
    load_current = x_train_rtem_load(i); % 当前负荷
    rtem_current = y_train_rtem_base(i); % 当前rtem
   
    % 根据当前负荷，选择模型预测
    model_index = select_model(load_current, divide_load);
    % 进行多步迭代预测并返回预测结果ycu_pred, 传入模型model_index
    y_current_pred = one_point_multi_step_pred(models_Rtem(model_index), x_current, p, limit_Rtem);
    y_pred_update_rtem(i-init_train,:) = y_current_pred;
 
    % 判断单步预测结果，是否更新模型
    if abs(y_current_pred(1) - y_current)>= Rtem_PermitError && abs(y_current) <= Rtem_rate_limit %% && rtem_current>=Min_Rtem && rtem_current<=Max_Rtem
        % 需要联动 删除 model_fit() 中的H=InvH
        % models_Rtem(model_index) = model_updata_no_agument(models_Rtem(model_index),x_current(1,:),y_current);
     
        
        model = models_Rtem(model_index);
        [newX,newY,newAlfa,newb,newInvH] = ModelRenew(model.x, model.y, model.H, model.delta, model.C,...
                                                     500, x_current(1,:), y_current, model.a, 0, 3);  
        models_Rtem(model_index).x = newX;
        models_Rtem(model_index).y = newY;                                     
        models_Rtem(model_index).a = newAlfa; 
        models_Rtem(model_index).b = newb; 
        models_Rtem(model_index).H = newInvH; 

        UpdateNum_Rtem = UpdateNum_Rtem + 1;
    end
  
    if mod(i,int16((train_len-init_train-p+1)/3)) == 0
        formatSpec = '进度：%0.2f%%, 更新次数：%d \n';
        fprintf(formatSpec,(i-init_train)*100/(train_len-init_train-p+1),UpdateNum_Rtem);
    end
end
UpdateRate_update_Rtem = UpdateNum_Rtem/length(y_pred_update_rtem);
end


function model = model_updata_no_agument(model, x_last, y_current)
abs_a = abs(model.a);
a_min_index = find(abs_a == min(abs_a));
del_index = a_min_index(1);
model.x(del_index, :) = x_last;
model.y(del_index) = y_current;
% 更新a,b, H更新一部分
n = length(model.x);
%K = rbf_kernel(model.x, model.x, model.delta);
% 更新H

Hp = rbf_kernel(model.x, model.x(del_index, :), model.delta);
model.H(:, del_index) = Hp;
model.H(del_index, :) = Hp';
model.H(del_index,del_index) = model.H(del_index,del_index) + 1/model.C;

%model.H = K + eye(n)/model.C;
InvH = (model.H)^-1;
E = ones(n,1);
Q= InvH - InvH*E*(E'*InvH)/(E'*InvH*E);
RT = E'*InvH/(E'*InvH*E);
model.a = Q*model.y;
model.b = RT*model.y; 
end




function y_pred = one_point_multi_step_pred(model, x, p, limit_var)
y_pred = zeros(1,p);
x_iter = x(1,:);
for i = 1:p
    y_p = predict(model, x_iter);
    y_pred(i) = y_p;
    if i < p
        x_iter = x(i+1,:);
        % 负荷不变
        % 减温水流量不变
        %if len(x_iter) == 26
        %    x_iter(25)= x(25,1); % 减温水流量为状态量
        %end
        % x_iter(end) = x(1,1);
        % 氧量保持不变
        % x_iter(2) = x(1,2);
        % NOx采用预测数据
        x_iter(end) = (y_p+limit_var)/(2*limit_var);
    end  
end

end

function model_index = select_model(load, divide_load)
models_num = length(divide_load) - 1;
for num = 1:models_num
    if (load > divide_load(num)) && (load <= divide_load(num+1))
        model_index = num;
        break
    end
end
end

function [x_train_ag, y_train_ag] = data_augment(x_train, y_train, limit_var)
[xl, xw] = size(x_train);
[yl, yw] = size(y_train);
x_train_ag = zeros(3*xl, xw);
y_train_ag = zeros(3*yl, yw);

x_train_ag(1:xl, :) = x_train;
x_train_ag(xl+1:2*xl, :) = x_train;
x_train_ag(xl+1:2*xl, end) = x_train_ag(xl+1:2*xl, end) + (2)/(2*limit_var);

x_train_ag(2*xl+1:3*xl, :) = x_train;
x_train_ag(2*xl+1:3*xl, end) = x_train_ag(2*xl+1:3*xl, end) + (-2)/(2*limit_var);

y_train_ag(1:yl, :) = y_train;
y_train_ag(yl+1:2*yl, :) = y_train;
y_train_ag(2*yl+1:3*yl, :) = y_train;
end

function [alpha,belta,H] = model_fit(x, y, delta, C)
n = length(x);
K = rbf_kernel(x, x, delta);
H = K + eye(n)/C;
InvH = H^-1;
E = ones(n,1);
Q= InvH - InvH*E*(E'*InvH)/(E'*InvH*E);
RT = E'*InvH/(E'*InvH*E);
alpha = Q*y;
belta = RT*y; 

H = InvH;  % 模型存储InvH,降低计算开销
end

function y_pred = predict(model, x)
H = rbf_kernel(x, model.x, model.delta);
y_pred = H*model.a + model.b;
end

function K = rbf_kernel(x, y, gamma)
%  K(x, y) = exp(-gamma ||x-y||^2)
% 欧式距离的平方
K = (euclidean_dist(x, y)).^2;
K = exp(-gamma*K);
end

function dist = euclidean_dist(x, y)
%{
Args:
x:  shape [m, d]
y: shape [n, d]
Returns:
dist:  shape [m, n]
%}
m = size(x,1); n = size(y,1);
xx = repmat(sum(x.^2,2),1,n);
yy = repmat(sum(y.^2,2),1,m);
yy = yy';
dist = real(sqrt(xx + yy - 2*x*y'));
end











