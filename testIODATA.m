clc
clear all
% 历史数据
load('FEIXIANIO.mat');

num_test = 100;
start_test = 1;  
%% 模型参数

[X_CO1]=importdata('X_CO1.txt'); [X_CO2]=importdata('X_CO2.txt'); [X_CO3]=importdata('X_CO3.txt'); 
X_CO1 = X_CO1'; X_CO2 = X_CO2'; X_CO3 = X_CO3'; 
[Y_CO1]=importdata('Y_CO1.txt'); [Y_CO2]=importdata('Y_CO2.txt'); [Y_CO3]=importdata('Y_CO3.txt');
[Alfa_CO1]=importdata('Alfa_CO1.txt'); [Alfa_CO2]=importdata('Alfa_CO2.txt'); [Alfa_CO3]=importdata('Alfa_CO3.txt'); 
[H_CO1]=importdata('H_CO1.txt'); [H_CO2]=importdata('H_CO2.txt'); [H_CO3]=importdata('H_CO3.txt'); 

[X_Nox1]=importdata('X_Nox1.txt'); [X_Nox2]=importdata('X_Nox2.txt'); [X_Nox3]=importdata('X_Nox3.txt'); 
X_Nox1 = X_Nox1'; X_Nox2 = X_Nox2'; X_Nox3 = X_Nox3'; 
[Y_Nox1]=importdata('Y_Nox1.txt'); [Y_Nox2]=importdata('Y_Nox2.txt'); [Y_Nox3]=importdata('Y_Nox3.txt');
[Alfa_Nox1]=importdata('Alfa_Nox1.txt'); [Alfa_Nox2]=importdata('Alfa_Nox2.txt'); [Alfa_Nox3]=importdata('Alfa_Nox3.txt'); 
[H_Nox1]=importdata('H_Nox1.txt'); [H_Nox2]=importdata('H_Nox2.txt'); [H_Nox3]=importdata('H_Nox3.txt'); 

[X_Etem1]=importdata('X_Etem1.txt'); [X_Etem2]=importdata('X_Etem2.txt'); [X_Etem3]=importdata('X_Etem3.txt'); 
X_Etem1 = X_Etem1'; X_Etem2 = X_Etem2'; X_Etem3 = X_Etem3'; 
[Y_Etem1]=importdata('Y_Etem1.txt'); [Y_Etem2]=importdata('Y_Etem2.txt'); [Y_Etem3]=importdata('Y_Etem3.txt');
[Alfa_Etem1]=importdata('Alfa_Etem1.txt'); [Alfa_Etem2]=importdata('Alfa_Etem2.txt'); [Alfa_Etem3]=importdata('Alfa_Etem3.txt'); 
[H_Etem1]=importdata('H_Etem1.txt'); [H_Etem2]=importdata('H_Etem2.txt'); [H_Etem3]=importdata('H_Etem3.txt'); 

[X_Rtem1]=importdata('X_Rtem1.txt'); [X_Rtem2]=importdata('X_Rtem2.txt'); [X_Rtem3]=importdata('X_Rtem3.txt'); 
X_Rtem1 = X_Rtem1'; X_Rtem2 = X_Rtem2'; X_Rtem3 = X_Rtem3'; 
[Y_Rtem1]=importdata('Y_Rtem1.txt'); [Y_Rtem2]=importdata('Y_Rtem2.txt'); [Y_Rtem3]=importdata('Y_Rtem3.txt');
[Alfa_Rtem1]=importdata('Alfa_Rtem1.txt'); [Alfa_Rtem2]=importdata('Alfa_Rtem2.txt'); [Alfa_Rtem3]=importdata('Alfa_Rtem3.txt'); 
[H_Rtem1]=importdata('H_Rtem1.txt'); [H_Rtem2]=importdata('H_Rtem2.txt'); [H_Rtem3]=importdata('H_Rtem3.txt'); 

% 飞灰含碳模型使用常值，现在不满足建模条件
%% 误差list
ListError_CO=zeros(20,1);  ListError_Nox=zeros(20,1); ListError_Rtem=zeros(20,1); ListError_Etem=zeros(20,1);

% Op点表
[OP]=importdata('IOOP/OP.txt');
OP = OP;
% IO点表
IO = FEIXIANIO;

%%
IO_save = zeros(100,length(IO));  % 每一行一次IO记录

O2_opt_bias_k=IO(385)*0;
Fuel_opt_bias_k=IO(386:391)*0;
Sec_opt_bias_k=IO(392:397)*0;
Sofa_opt_bias_k=IO(398:399)*0;
Fp_opt_bias_k=IO(400)*0;

rIO = zeros(471,1);

for i = start_test:start_test+num_test
    IO = FEIXIANIO(i,:)';
    
    
    %% bias反馈，不采用
    IO(385) = O2_opt_bias_k;
    IO(386:391) = Fuel_opt_bias_k;
    IO(392:397) = Sec_opt_bias_k;
    IO(398:399) = Sofa_opt_bias_k;
    IO(400) = Fp_opt_bias_k;
   
    if (i-start_test+1) <= 100
        [rIO,...
        rX_CO1,rY_CO1,rAlfa_CO1,rH_CO1,...
        rX_CO2,rY_CO2,rAlfa_CO2,rH_CO2,...
        rX_CO3,rY_CO3,rAlfa_CO3,rH_CO3,...
        rX_Nox1,rY_Nox1,rAlfa_Nox1,rH_Nox1,...
        rX_Nox2,rY_Nox2,rAlfa_Nox2,rH_Nox2,...
        rX_Nox3,rY_Nox3,rAlfa_Nox3,rH_Nox3,...
        rX_Rtem1,rY_Rtem1,rAlfa_Rtem1,rH_Rtem1,...
        rX_Rtem2,rY_Rtem2,rAlfa_Rtem2,rH_Rtem2,...
        rX_Rtem3,rY_Rtem3,rAlfa_Rtem3,rH_Rtem3,...
        rX_Etem1,rY_Etem1,rAlfa_Etem1,rH_Etem1,...
        rX_Etem2,rY_Etem2,rAlfa_Etem2,rH_Etem2,...
        rX_Etem3,rY_Etem3,rAlfa_Etem3,rH_Etem3] ...
        = CombOptControl_t1(IO,OP,...
        X_CO1,Y_CO1,Alfa_CO1,H_CO1,...
        X_CO2,Y_CO2,Alfa_CO2,H_CO2,...
        X_CO3,Y_CO3,Alfa_CO3,H_CO3,...
        X_Nox1,Y_Nox1,Alfa_Nox1,H_Nox1,...
        X_Nox2,Y_Nox2,Alfa_Nox2,H_Nox2,...
        X_Nox3,Y_Nox3,Alfa_Nox3,H_Nox3,...
        X_Rtem1,Y_Rtem1,Alfa_Rtem1,H_Rtem1,...
        X_Rtem2,Y_Rtem2,Alfa_Rtem2,H_Rtem2,...
        X_Rtem3,Y_Rtem3,Alfa_Rtem3,H_Rtem3,...
        X_Etem1,Y_Etem1,Alfa_Etem1,H_Etem1,...
        X_Etem2,Y_Etem2,Alfa_Etem2,H_Etem2,...
        X_Etem3,Y_Etem3,Alfa_Etem3,H_Etem3);            
    elseif (i-start_test+1) > 100
        [rIO,...
        rX_CO1,rY_CO1,rAlfa_CO1,rH_CO1,...
        rX_CO2,rY_CO2,rAlfa_CO2,rH_CO2,...
        rX_CO3,rY_CO3,rAlfa_CO3,rH_CO3,...
        rX_Nox1,rY_Nox1,rAlfa_Nox1,rH_Nox1,...
        rX_Nox2,rY_Nox2,rAlfa_Nox2,rH_Nox2,...
        rX_Nox3,rY_Nox3,rAlfa_Nox3,rH_Nox3,...
        rX_Rtem1,rY_Rtem1,rAlfa_Rtem1,rH_Rtem1,...
        rX_Rtem2,rY_Rtem2,rAlfa_Rtem2,rH_Rtem2,...
        rX_Rtem3,rY_Rtem3,rAlfa_Rtem3,rH_Rtem3,...
        rX_Etem1,rY_Etem1,rAlfa_Etem1,rH_Etem1,...
        rX_Etem2,rY_Etem2,rAlfa_Etem2,rH_Etem2,...
        rX_Etem3,rY_Etem3,rAlfa_Etem3,rH_Etem3] ...
        = CombOptControl_t1(IO,OP,...
        X_CO1,Y_CO1,Alfa_CO1,H_CO1,...
        X_CO2,Y_CO2,Alfa_CO2,H_CO2,...
        X_CO3,Y_CO3,Alfa_CO3,H_CO3,...
        X_Nox1,Y_Nox1,Alfa_Nox1,H_Nox1,...
        X_Nox2,Y_Nox2,Alfa_Nox2,H_Nox2,...
        X_Nox3,Y_Nox3,Alfa_Nox3,H_Nox3,...
        X_Rtem1,Y_Rtem1,Alfa_Rtem1,H_Rtem1,...
        X_Rtem2,Y_Rtem2,Alfa_Rtem2,H_Rtem2,...
        X_Rtem3,Y_Rtem3,Alfa_Rtem3,H_Rtem3,...
        X_Etem1,Y_Etem1,Alfa_Etem1,H_Etem1,...
        X_Etem2,Y_Etem2,Alfa_Etem2,H_Etem2,...
        X_Etem3,Y_Etem3,Alfa_Etem3,H_Etem3);          
    end
    
    % 记录结果
    IO_save(i-start_test+1,:)=rIO';
    % 返回IO、模型参数
    % IO=rIO;
    
    X_CO1=rX_CO1; Y_CO1=rY_CO1;Alfa_CO1=rAlfa_CO1;H_CO1=rH_CO1;
    X_CO2=rX_CO2; Y_CO2=rY_CO2;Alfa_CO2=rAlfa_CO2;H_CO2=rH_CO2;
    X_CO3=rX_CO3; Y_CO3=rY_CO3;Alfa_CO3=rAlfa_CO3;H_CO3=rH_CO3;
 
    X_Nox1=rX_Nox1; Y_Nox1=rY_Nox1;Alfa_Nox1=rAlfa_Nox1;H_Nox1=rH_Nox1;
    X_Nox2=rX_Nox2; Y_Nox2=rY_Nox2;Alfa_Nox2=rAlfa_Nox2;H_Nox2=rH_Nox2;
    X_Nox3=rX_Nox3; Y_Nox3=rY_Nox3;Alfa_Nox3=rAlfa_Nox3;H_Nox3=rH_Nox3;
    
    X_Etem1=rX_Etem1; Y_Etem1=rY_Etem1;Alfa_Etem1=rAlfa_Etem1;H_Etem1=rH_Etem1;
    X_Etem2=rX_Etem2; Y_Etem2=rY_Etem2;Alfa_Etem2=rAlfa_Etem2;H_Etem2=rH_Etem2;
    X_Etem3=rX_Etem3; Y_Etem3=rY_Etem3;Alfa_Etem3=rAlfa_Etem3;H_Etem3=rH_Etem3;

    X_Rtem1=rX_Rtem1; Y_Rtem1=rY_Rtem1;Alfa_Rtem1=rAlfa_Rtem1;H_Rtem1=rH_Rtem1;
    X_Rtem2=rX_Rtem2; Y_Rtem2=rY_Rtem2;Alfa_Rtem2=rAlfa_Rtem2;H_Rtem2=rH_Rtem2;     
    X_Rtem3=rX_Rtem3; Y_Rtem3=rY_Rtem3;Alfa_Rtem3=rAlfa_Rtem3;H_Rtem3=rH_Rtem3;
    
    
    % 燃烧优化系统输出此时的优化偏置
    %  观测优化bias
    disp(i)
    O2_opt_bias_k=rIO(385);
    Fuel_opt_bias_k=rIO(386:391);
    
    Sec_opt_bias_k=rIO(392:397);
    Sofa_opt_bias_k=rIO(398:399);
    Fp_opt_bias_k=rIO(400);
end
