function [rIO,...
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
rX_Etem3,rY_Etem3,rAlfa_Etem3,rH_Etem3,...
rX_Smax1,rY_Smax1,rAlfa_Smax1,rH_Smax1,...
rX_Smax2,rY_Smax2,rAlfa_Smax2,rH_Smax2,...
rX_Smax3,rY_Smax3,rAlfa_Smax3,rH_Smax3] ...
= CombOptTrack_t1(IO,OP,...
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
X_Etem3,Y_Etem3,Alfa_Etem3,H_Etem3,...
X_Smax1,Y_Smax1,Alfa_Smax1,H_Smax1,...
X_Smax2,Y_Smax2,Alfa_Smax2,H_Smax2,...
X_Smax3,Y_Smax3,Alfa_Smax3,H_Smax3)

Load_k1 = IO(9);  % k-1时刻负荷
%% 选择模型
if (Load_k1>=258) && (Load_k1<376)
    X_Smax=X_Smax1; Y_Smax=Y_Smax1; Alfa_Smax=Alfa_Smax1; H_Smax=H_Smax1;
    X_CO=X_CO1; Y_CO=Y_CO1; Alfa_CO=Alfa_CO1; H_CO=H_CO1;
    X_Nox=X_Nox1; Y_Nox=Y_Nox1; Alfa_Nox=Alfa_Nox1; H_Nox=H_Nox1;
    X_Etem=X_Etem1; Y_Etem=Y_Etem1; Alfa_Etem=Alfa_Etem1; H_Etem=H_Etem1;
    X_Rtem=X_Rtem1; Y_Rtem=Y_Rtem1; Alfa_Rtem=Alfa_Rtem1; H_Rtem=H_Rtem1;
    model_index=1;
elseif (Load_k1>=376) && (Load_k1<495)
    X_Smax=X_Smax2; Y_Smax=Y_Smax2; Alfa_Smax=Alfa_Smax2; H_Smax=H_Smax2;
    X_CO=X_CO2; Y_CO=Y_CO2; Alfa_CO=Alfa_CO2; H_CO=H_CO2;
    X_Nox=X_Nox2; Y_Nox=Y_Nox2; Alfa_Nox=Alfa_Nox2; H_Nox=H_Nox2;
    X_Etem=X_Etem2; Y_Etem=Y_Etem2; Alfa_Etem=Alfa_Etem2; H_Etem=H_Etem2;
    X_Rtem=X_Rtem2; Y_Rtem=Y_Rtem2; Alfa_Rtem=Alfa_Rtem2; H_Rtem=H_Rtem2;
    model_index=2;
elseif (Load_k1>=495)
    X_Smax=X_Smax3; Y_Smax=Y_Smax3;Alfa_Smax=Alfa_Smax3; H_Smax=H_Smax3;   
    X_CO=X_CO3; Y_CO=Y_CO3; Alfa_CO=Alfa_CO3; H_CO=H_CO3;
    X_Nox=X_Nox3; Y_Nox=Y_Nox3; Alfa_Nox=Alfa_Nox3; H_Nox=H_Nox3;
    X_Etem=X_Etem3; Y_Etem=Y_Etem3; Alfa_Etem=Alfa_Etem3; H_Etem=H_Etem3;
    X_Rtem=X_Rtem3; Y_Rtem=Y_Rtem3; Alfa_Rtem=Alfa_Rtem3; H_Rtem=H_Rtem3;
    model_index=3;
else
    X_Smax=X_Smax1; Y_Smax=Y_Smax1; Alfa_Smax=Alfa_Smax1; H_Smax=H_Smax1;
    X_CO=X_CO1; Y_CO=Y_CO1; Alfa_CO=Alfa_CO1; H_CO=H_CO1;
    X_Nox=X_Nox1; Y_Nox=Y_Nox1; Alfa_Nox=Alfa_Nox1; H_Nox=H_Nox1;
    X_Etem=X_Etem1; Y_Etem=Y_Etem1; Alfa_Etem=Alfa_Etem1; H_Etem=H_Etem1;
    X_Rtem=X_Rtem1; Y_Rtem=Y_Rtem1; Alfa_Rtem=Alfa_Rtem1; H_Rtem=H_Rtem1;
    model_index=1;
end

NumSupVec_Nox = OP(6);  % 支持向量个数
NumSupVec_Etem = OP(9);
NumSupVec_Rtem = OP(12);
NumSupVec_CO = OP(296);  
NumSupVec_Smax = OP(148);

% Alfa b数据解析
b_Nox=Alfa_Nox(NumSupVec_Nox+1);
Alfa_Nox=Alfa_Nox(1:NumSupVec_Nox);

b_Etem=Alfa_Etem(NumSupVec_Etem+1);
Alfa_Etem=Alfa_Etem(1:NumSupVec_Etem);

b_Rtem=Alfa_Rtem(NumSupVec_Rtem+1);
Alfa_Rtem=Alfa_Rtem(1:NumSupVec_Rtem);

b_CO=Alfa_CO(NumSupVec_CO+1);
Alfa_CO=Alfa_CO(1:NumSupVec_CO);

b_Smax=Alfa_Smax(NumSupVec_Smax+1);
Alfa_Smax=Alfa_Smax(1:NumSupVec_Smax);
%% OP中数据解析

%Ts = OP(3);  % 采样周期
Delta_Nox = OP(306);  % Nox模型对应的超参数Delta model_index-1
C_Nox = OP(309);
Delta_Etem = OP(312);
C_Etem = OP(315);
Delta_Rtem = OP(318);
C_Rtem = OP(321);
Delta_CO = OP(324);
C_CO = OP(327);
Delta_Smax = OP(146);
C_Smax = OP(147);

% 模型误差容忍度
PermitErr_Nox = OP(16);  
PermitErr_Etem = OP(17);
PermitErr_Rtem = OP(18);
PermitErr_CO = OP(297);
PermitErr_Smax = OP(149);

% 更新时增量速率约束
Nox_rate_limit = OP(330);
Etem_rate_limit = OP(331); 
Rtem_rate_limit = OP(332); 
CO_rate_limit = OP(333); 
Smax_rate_limit = OP(150); 

% 增量的归一化参数，上下限相同
norm_limit_Load = OP(334);
%norm_limit_Fangle = OP(151);  % 燃烧器摆角 1
norm_limit_O2 = OP(335);
norm_limit_Fuel = OP(336);
norm_limit_Sec = OP(337);
norm_limit_Sofa = OP(338);
norm_limit_Fp = OP(207);  % 0.2
%norm_limit_Dhflow = OP(152);  % 减温水流量 5

norm_limit_Nox = OP(339);
norm_limit_Etem = OP(340);
norm_limit_Rtem = OP(341);
norm_limit_CO = OP(342);  % 0.35
norm_limit_Smax = OP(153); % O2量绝对偏差

% 总煤量作为输入的归一化上下限
%max_coalneed=OP(304); min_coalneed=OP(305);
% 再热汽温挡板归一化下限 再热汽温挡板影响因子
%min_Damper=OP(278); max_Damper=OP(279); factor_Damper=OP(280);

K_Alfa=OP(281);  % 更新策略—最大Alfa替换
%% IO中数据解析 
%% ----------采样数据段
Load_k=IO(8); Load_k1=IO(9); Load_k2=IO(294);  % k时刻负荷
% Fangle_k5 = IO(455); Fangle_k6 = IO(456);  % 燃烧器摆角
O2_k = IO(96); O2_k1 = IO(141);  % k,k-1,k-2时刻实测氧量
O2_k2 = IO(142); O2_k3 = IO(295); O2_k4 = IO(296);

Fuel_k5 = IO(342:347); Fuel_k6 = IO(364:369);
Sec_k5 = IO(348:353); Sec_k6 = IO(370:375);
Sofa_k5 = IO(354:355); Sofa_k6 = IO(376:377);
Fp_k5 = IO(356); Fp_k6 = IO(378);  % 一次风压
% Dhflow_k = IO(468); Dhflow_k1 = IO(469); Dhflow_k2 = IO(470);  % 减温水流量

Nox_k=IO(10); Nox_k1=IO(11); Nox_k2=IO(12); %Nox_k3=IO(13);
Etem_k=IO(14); Etem_k1=IO(15); Etem_k2=IO(16); %Etem_k3=IO(17);
Rtem_k=IO(18); Rtem_k1=IO(19); Rtem_k2=IO(20); %Rtem_k3=IO(21);
CO_k=IO(445); CO_k1=IO(446); CO_k2=IO(447);
Smax_k=IO(460); Smax_k1=IO(461); Smax_k2=IO(462);

Trh_Damper_k = IO(160);  % k、k-1时刻再热汽温挡板开度
%Trh_Damper_k1 = IO(161);
%% --------------辅助逻辑段
% O2量绝对偏差、CO、NOx、再热、烟温模型连续更新次数 状态标志
NumCRenew_Smax=IO(464);NumCRenew_CO=IO(437);NumCRenew_Nox=IO(88); NumCRenew_Etem=IO(89); NumCRenew_Rtem=IO(90);
StaCRenew_Smax=IO(466);StaCRenew_CO=IO(448);StaCRenew_Nox=IO(91); StaCRenew_Etem=IO(92); StaCRenew_Rtem=IO(93);

e_Smax_sum=IO(467);
e_CO_sum=IO(449);
e_Nox_sum=IO(147);  % NOx、效率、烟温累计预测偏差
e_Etem_sum=IO(148);
e_Rtem_sum=IO(149);

Flag=0;  %IO(159);  % 根据Flag奇偶性交替选择更新策略

%eT_k1=IO(162);  % k-1时刻汽温偏差滤波后值
eRtem_k=IO(162);
eCO_k1=IO(176);  % 上一时刻，CO偏差
eCO_k=IO(176);

%% 系统负荷变动状态判断
% 0为稳定负荷 1为快速上升	若-1为快速下降
% 负荷变动阈值
coalneed_k=IO(170);  % k时刻六层煤量需求指令之和
coalneed_k1=IO(169);  % k-1时刻6层煤量需求指令之和
Load_Change=OP(289);
% 煤量需求变动速率
%Coal_Change=OP(290);
%Load_change_State=IO(177);

% 判断系统负荷变化状态
if (coalneed_k-coalneed_k1)>Load_Change
    Load_change_State=1;
elseif (coalneed_k-coalneed_k1)<-1*Load_Change
    Load_change_State=-1;
else
    Load_change_State=0;
end
IO(177)=Load_change_State;

%% 飞灰含碳值筛选
%cfh_L_k1=IO(265);  % k-1时刻A侧飞灰 
%cfh_R_k1=IO(266);  % k-1时刻B侧飞灰
cfh_L_k=IO(263);  % k时刻A侧飞灰
cfh_R_k=IO(264);  % k时刻B侧飞灰
cfh_k1=IO(292);  % 去除坏点后的k-1时刻飞灰含碳测量值 维护的
%cfh_k2=IO(188);  % 去除坏点后的k-2时刻飞灰含碳测量值 维护的

if (cfh_L_k>0) && (cfh_L_k<10) && (cfh_R_k>0) && (cfh_R_k<10)
    cfh=(cfh_L_k+cfh_R_k)/2;  % 获得k时刻飞灰含碳
elseif (cfh_L_k<=0) || (cfh_L_k>10) && (cfh_R_k>0) && (cfh_R_k<10)
    cfh=cfh_R_k;  % R侧的值更佳
    %cfh_L_k=cfh_R_k;  % 当前时刻
    %cfh_L_k1=cfh_R_k1;
elseif (cfh_R_k<=0) || (cfh_R_k>10) && (cfh_L_k>0) && (cfh_L_k<10)
    cfh=cfh_L_k;
    %cfh_R_k=cfh_L_k;
    %cfh_R_k1=cfh_L_k1;
else  
    cfh=cfh_k1;
    %cfh_L_k=cfh;
    %cfh_R_k=cfh;
end

IO(292)=cfh;   % k时刻飞灰含碳值传出,下次使用
%IO(188)=cfh_k1;   % k-1时刻飞灰含碳值传出,下次使用

% 上一时刻飞灰是否更新标志，防止数据异常出现测量值连续变化的情况
%flag_cfh=IO(290);
%max_cfh=5;
%min_cfh=0;  %归一化上下限
%norm_limit_Cfh=IO(342);
%% 锅炉效率计算
%计算时考虑元素分析
Tem_py_k=Etem_k; % k时刻排烟温度Etem_k
%Co_k=IO(57);  % k时刻CO浓度
%O2_k=O2_k;  % k时刻O2浓度
%Tem_py_k=0; % k时刻排烟温度Etem_k
a_Cfh = OP(217);
b_Cfh = OP(216);
Cfh=CO_k*a_Cfh+b_Cfh;  % 根据CO估算飞灰含碳
Cfh=Cfh/100;

% 工业分析无输入时仍采用常数计算 Mar Mad Aar St Vdaf(Vdaf干燥无灰基挥发分) Q 
if (IO(257)==0) ||( IO(258)==0) || (IO(259)==0) || (IO(260)==0)|| (IO(261)==0) || (IO(262)==0) 
    Mar=11.3/100;  % Mt=Mar全水分
    Mad=6.50/100;  % 空气干燥基水分
    Aar=17.71/100;  % 收到基灰分
    Qnet=21.73*1000;  % 低位发热量，标准煤20908
    Xar2ad=(1-Mar)/(1-Mad);  % 收到基-空气干燥机转换系数
    c=Xar2ad*47.58/100;
    h=Xar2ad*3.92/100;
    n=Xar2ad*0.82/100;
    % s=Xar2ad*2.09/100;
    s=0.24/100;  % St,ar(全硫)
    o=1-c-h-n-s-Mar-Aar;
else
    Mar=IO(257)/100;
    Mad=IO(258)/100;
    Aar=IO(259)/100;  %收到基灰分
    Qnet=IO(262)*1000;    %低位发热量，标准煤20908
    Xar2ad=(1-Mar)/(1-Mad);   %收到基-空气干燥机转换系数
    c=Xar2ad*47.58/100;
    h=Xar2ad*3.92/100;
    n=Xar2ad*0.82/100;
    %s=Xar2ad*2.09/100;
    s=IO(260)/100;
    o=1-c-h-n-s-Mar-Aar;
end

ALPHA=21/(21-O2_k);    %过量空气系数
Vgk0=100*(0.089*(c+0.375*s)+0.265*h-0.0333*o);  %理论空气量
Vgy0=1.866*(c+0.375*s)+0.79*Vgk0+0.8*n;  %理论烟气量
Vgy=Vgy0+(ALPHA-1)*Vgk0;  %烟气量
Cpy=0.8967+0.0013*Tem_py_k-0.000003*Tem_py_k*Tem_py_k; %烟气比热
Sg=Vgy*Cpy*(Tem_py_k-20)/Qnet;  %干烟气热损失

V_H2O=1.24*((9*h+Mar)+1.293*ALPHA*Vgk0*0.001);
Q_H2O=V_H2O*1.5093*(Tem_py_k-20);
Sm=Q_H2O/Qnet;  %水分热损失
Suc=337.27*100*Aar/Qnet*Cfh./(1-Cfh);  %飞灰含碳热损失

IO(407)=0.9917-Suc-Sm-Sg;  % 锅炉效率k时刻计算值

%% 程序启动赋值阶段，避免计算
if (sum(Fuel_k6)~=0)
    %% 增量格式，构造输入，归一化
    Load_inc_k1_norm=((Load_k1-Load_k2)+norm_limit_Load)./(2*norm_limit_Load);
    %Fangle_inc_k5_norm=((Fangle_k5-Fangle_k6)+norm_limit_Fangle)./(2*norm_limit_Fangle);
    O2_inc_k1_norm=((O2_k1-O2_k2)+norm_limit_O2)./(2*norm_limit_O2);
    %O2_inc_k2_norm=((O2_k2-O2_k3)+norm_limit_O2)./(2*norm_limit_O2);
    %O2_inc_k3_norm=((O2_k3-O2_k4)+norm_limit_O2)./(2*norm_limit_O2);
     
    Fuel_inc_k5_norm=((Fuel_k5-Fuel_k6)+norm_limit_Fuel)./(2*norm_limit_Fuel);
    Sec_inc_k5_norm=((Sec_k5-Sec_k6)+norm_limit_Sec)./(2*norm_limit_Sec);
    Sofa_inc_k5_norm=((Sofa_k5-Sofa_k6)+norm_limit_Sofa)./(2*norm_limit_Sofa);
    Fp_inc_k5_norm=((Fp_k5-Fp_k6)+norm_limit_Fp)./(2*norm_limit_Fp);   
    %Dhflow_inc_k1_norm=((Dhflow_k1-Dhflow_k2)+norm_limit_Dhflow)./(2*norm_limit_Dhflow);  % 迟延时间为1
    Smax_inc_k1=Smax_k1-Smax_k2;  % 用于约束模型更新
    Smax_inc_k1_norm=(Smax_inc_k1+norm_limit_Smax)./(2*norm_limit_Smax);
    Smax_inc_k=Smax_k-Smax_k1;  % 预测值不归一化
  
    CO_inc_k1=CO_k1-CO_k2;  % 用于约束模型更新
    CO_inc_k1_norm=(CO_inc_k1+norm_limit_CO)./(2*norm_limit_CO);
    CO_inc_k=CO_k-CO_k1;  % 预测值不归一化
    
    Nox_inc_k1=Nox_k1-Nox_k2;  % 用于约束模型更新
    Nox_inc_k1_norm=(Nox_inc_k1+norm_limit_Nox)./(2*norm_limit_Nox);
    Nox_inc_k=Nox_k-Nox_k1;  % 预测值不归一化
    
    Etem_inc_k1=Etem_k1-Etem_k2;  % 用于约束模型更新
    Etem_inc_k1_norm=(Etem_inc_k1 + norm_limit_Etem)./(2*norm_limit_Etem);
    Etem_inc_k=Etem_k-Etem_k1;  % 预测值不归一化
    
    Rtem_inc_k1=Rtem_k1-Rtem_k2;  % 用于约束模型更新
    Rtem_inc_k1_norm=(Rtem_inc_k1 + norm_limit_Rtem)./(2*norm_limit_Rtem);
    Rtem_inc_k=Rtem_k-Rtem_k1;  % 预测值不归一化
    %Trh_Damper_k1=(Trh_Damper_k1-min_Damper)/(max_Damper-min_Damper);
    %coalneed_k1=(coalneed_k1-min_coalneed)/(max_coalneed-min_coalneed);
    
    %Load_k=(Load_k-min_Load)/(max_Load-min_Load);
    %Trh_Damper_k=(Trh_Damper_k-min_Damper)/(max_Damper-min_Damper);
    %coalneed_k=(coalneed_k-min_coalneed)/(max_coalneed-min_coalneed);  
    
    % k-1时刻增量模型输入计算，用于计算k时刻输出预测值，并根据预测偏差决定是否更新模型
    Input_var = [Load_inc_k1_norm',O2_inc_k1_norm',Fuel_inc_k5_norm',Sec_inc_k5_norm',Sofa_inc_k5_norm',Fp_inc_k5_norm'];
    
    Input_Smax=[Input_var,Smax_inc_k1_norm'];        
    Input_CO=[Input_var,CO_inc_k1_norm']; 
    Input_Nox=[Input_var,Nox_inc_k1_norm']; 
    Input_Etem=[Input_var,Etem_inc_k1_norm']; 
    Input_Rtem=[Input_var,Rtem_inc_k1_norm']; 
    %% CO、Nox、Etem、Rtem预测
   % 对k时刻Smax预测
    a=repmat(Input_Smax,NumSupVec_Smax,1)-X_Smax;
    dist=sum(a.*a,2);
    K=exp(-dist*Delta_Smax)';
    P_Smax_k=K*Alfa_Smax+b_Smax;  % k时刻Smax预测值 增量且未归一化
    IO(463)=P_Smax_k+Smax_k1;  % k时刻Smax预测值 全量
    
    % 对k时刻CO预测
    a=repmat(Input_CO,NumSupVec_CO,1)-X_CO;
    dist=sum(a.*a,2);
    K=exp(-dist*Delta_CO)';
    P_CO_k=K*Alfa_CO+b_CO;  % k时刻CO预测值 增量且未归一化
    IO(436)=P_CO_k+CO_k1;  % k时刻CO预测值 全量
    
    % 对k时刻NOx预测
    a=repmat(Input_Nox,NumSupVec_Nox,1)-X_Nox;
    dist=sum(a.*a,2);
    K=exp(-dist*Delta_Nox)';
    P_Nox_k=K*Alfa_Nox+b_Nox;  % k时刻NOx预测值 增量且未归一化
    IO(173)=P_Nox_k+Nox_k1;  % k时刻NOx预测值 全量
    
    % 对k时刻Etem预测
    a=repmat(Input_Etem,NumSupVec_Etem,1)-X_Etem;
    dist=sum(a.*a,2);
    K=exp(-dist*Delta_Etem)';
    P_Etem_k=K*Alfa_Etem+b_Etem;  % k时刻排烟温度 增量且未归一化
    IO(174)=P_Etem_k+Etem_k1; 
    
    % 对k时刻Rtem预测
    a=repmat(Input_Rtem,NumSupVec_Rtem,1)-X_Rtem;
    dist=sum(a.*a,2);
    K=exp(-dist*Delta_Rtem)';
    P_Rtem_k=K*Alfa_Rtem+b_Rtem;   % k时刻再热汽温预测值 增量且未归一化
    IO(175)=P_Rtem_k+Rtem_k1;

    %% 飞灰含碳预测，30min一个数据，更新频率较慢
    %{
    % 归一化
    %cfh=(cfh-min_cfh)/(max_cfh-min_cfh);   %当前时刻飞灰归一化
    %cfh_1=(cfh_1-min_cfh)/(max_cfh-min_cfh);  %前一时刻飞灰归一化
    % cfh_inc_norm_k1 = ((cfh_k1-cfh_k2)+norm_limit_Cfh)./(2*norm_limit_Cfh);
    % 对当前时刻飞灰含碳预测
    if cfh_k1~=0 && cfh_L_k1~=0 && cfh_R_k1~=0  % 初始时刻避免计算  增量始终为0
        Input_cfh=[Input_var,cfh_inc_norm_k1];
        a=repmat(Input_cfh,NumSupVec,1)-X_Cfh;
        dist=sum(a.*a,2);
        K=exp(-dist*Delta_Cfh)';
        P_Cfh_k=K*Alfa_Cfh+b_Cfh;
        IO(186)=P_Cfh_k;   %飞灰含碳预测值增量
    end
    
    % 判断飞灰是否变化（按右侧飞灰），变化后且超过模型容忍度才开始更新，第一次变化时仅记录
    % 右侧飞灰两次测量值之差大于0.015认为测量值变化，防止数据异常波动
    if (abs(cfh_R_k-cfh_R_k1)>0.015) && (flag_cfh==0) && (cfh_R_k1~=0) && (cfh~=0) && (cfh_k2~=0) 
        u_cfh_k1=IO(300:300+26-1);  % k-1变化点数据
        u_cfh_k2=IO(325:325+26-1);  % k-2变化点数据
        flag_cfh=1; % 变化标志
        if  (u_cfh_k2(1)==0) && (u_cfh_k2(2)==0) && (u_cfh_k2(5)==0) && (u_cfh_k2(6)==0) % 初始时刻
            % 初次测量值变化时记录输入u_cfh，作为下一次更新的输入
            u_cfh_k2=u_cfh_k1;
            u_cfh_k1=[];  % 当前的输入绝对量
            
            rX_cfh=X_cfh;
            rY_cfh=Y_cfh;
            rAlfa_cfh=[Alfa_cfh; b_cfh];
            rInvH_cfh=InvH_cfh;
        else
            % 否则利用30min前输入与当前飞灰测量均值，对模型进行更新
            updateX_cfh=[u_cfh,cfh_1];  % 上一次飞灰采样点输入（30min前的x)
            updateY_cfh=cfh;  % 当前飞灰测量值（对应30min前的y）
            a=repmat(updateX_cfh,NumSupVec_cfh,1)-X_cfh;
            dist=sum(a.*a,2);
            k_cfh=exp(-dist/2/(delta_cfh*delta_cfh))';
            updateY_cfh_p=k_cfh*Alfa_cfh+b_cfh;  % 飞灰含碳预测值
            
            e_cfh=abs(updateY_cfh_p-updateY_cfh);  % 预测误差,
            % 判断模型是否更新
            if e_cfh>PermitErr_cfh/(max_cfh-min_cfh)   %更新
                [rX_cfh,rY_cfh,rAlfa_cfh,rb_cfh,rInvH_cfh] =ModelRenew(X_cfh,Y_cfh,InvH_cfh,delta_cfh,C_cfh,NumSupVec_cfh,updateX_cfh,updateY_cfh,Alfa_cfh,Flag,K_Alfa);
                Flag=Flag+1;    %交替更新标志
                rAlfa_cfh=[rAlfa_cfh; rb_cfh];
            else  % 不更新
                rX_cfh=X_cfh;
                rY_cfh=Y_cfh;
                rAlfa_cfh=[Alfa_cfh; b_cfh];
                rInvH_cfh=InvH_cfh;
            end
            % 保存当前输入，作为下一次更新的输入
            u_cfh=[uu(1:9),O2_k1,Load_k1,coalneed_k1];
        end
    else  % 不更新
        flag_cfh=0;
        rX_cfh=X_cfh;
        rY_cfh=Y_cfh;
        rAlfa_cfh=[Alfa_cfh; b_cfh];
        rInvH_cfh=InvH_cfh; 
    end
    %}
    %% 计算预测偏差  
    % 预测偏差，k时刻预测值-k时刻采样值

    e_Smax_k=(P_Smax_k-Smax_inc_k);   
    e_CO_k=(P_CO_k-CO_inc_k);
    e_Nox_k=(P_Nox_k-Nox_inc_k);
    e_Etem_k=(P_Etem_k-Etem_inc_k);
    e_Rtem_k=(P_Rtem_k-Rtem_inc_k);
    
    % 累计误差
%     ListError_CO(2:length(ListError_CO)) = ListError_CO(1:length(ListError_CO)-1);
%     ListError_CO(1) = abs(e_CO_k);
%     ListError_Nox(2:length(ListError_Nox)) = ListError_Nox(1:length(ListError_Nox)-1);
%     ListError_Nox(1) = abs(e_Nox_k);
%     ListError_Etem(2:length(ListError_Etem)) = ListError_Etem(1:length(ListError_Etem)-1);
%     ListError_Etem(1) = abs(e_Etem_k);
%     ListError_Rtem(2:length(ListError_Rtem)) = ListError_Rtem(1:length(ListError_Rtem)-1);
%     ListError_Rtem(1) = abs(e_Rtem_k);
%     ErrorNum_CO=OP(198);  % CO累计误差窗口长度
%     ErrorNum_Nox=OP(198);  % NOx累计误差窗口长度
%     ErrorNum_Etem=OP(199);
%     ErrorNum_Rtem=OP(200);
%     e_CO_sum = sum(ListError_CO(1:ErrorNum_CO));  % CO累计误差
%     e_Nox_sum = sum(ListError_Nox(1:ErrorNum_Nox));  % NOx累计误差
%     e_Etem_sum = sum(ListError_Etem(1:ErrorNum_Etem)); 
%     e_Rtem_sum = sum(ListError_Rtem(1:ErrorNum_Rtem));

     e_Smax_sum = abs(e_Smax_k);  % Smax累计误差
     e_CO_sum = abs(e_CO_k);  % CO累计误差
     e_Nox_sum = abs(e_Nox_k);  % NOx累计误差
     e_Etem_sum = abs(e_Etem_k); 
     e_Rtem_sum = abs(e_Rtem_k); 
    %% PI控制防止越界 计算与上下限偏差
    % 再热蒸汽PI控制 全量相减，再归一化
    % 低再出口汽温上限 下限
    upLimit_Rtem=OP(14); downLimit_Tem=OP(15);
    min_Rtem=OP(115); max_Rtem=OP(123);
    %upLimit_Rtem=(upLimit_Rtem-min_Rtem)/(max_Rtem-min_Rtem);
    %downLimit_Tem=(downLimit_Tem-min_Rtem)/(max_Rtem-min_Rtem);
    if Rtem_k>upLimit_Rtem
        eRtem_k=Rtem_k-upLimit_Rtem;
    elseif Rtem_k<downLimit_Tem
        eRtem_k=Rtem_k-downLimit_Tem;
    else
        eRtem_k = 0; % k时刻汽温偏差滤波后值
    end
    eRtem_k=eRtem_k/(max_Rtem-min_Rtem);  % 此处归一化为保持与首阳山计算逻辑
    
    % Co PI控制，偏差结果均未归一化
    PI_max_CO= OP(287);
    PI_min_CO = OP(288);
    if CO_k>PI_max_CO
        eCO_k = CO_k-PI_max_CO;
    elseif CO_k<PI_min_CO
        eCO_k = CO_k-PI_min_CO;
    else
        eCO_k = 0;
    end

    %% 模型更新
    % 单步预报误差超过容忍度&增量在规定范围内 才更新
    if  abs(e_Smax_k)>=PermitErr_Smax && abs(Smax_inc_k1) <= Smax_rate_limit  % PermitErr_Smax
        [rX_Smax,rY_Smax,rAlfa_Smax,rb_Smax,rH_Smax] = ModelRenew(X_Smax,Y_Smax,H_Smax,Delta_Smax,C_Smax,NumSupVec_Smax,Input_Smax,Smax_inc_k,Alfa_Smax,Flag,K_Alfa);
        if StaCRenew_Smax==1  % 为1代表模型上次进行了更新
            NumCRenew_Smax=NumCRenew_Smax+1;  % 连续更新次数
        end
        StaCRenew_Smax=1;
        rAlfa_Smax=[rAlfa_Smax; rb_Smax];
    else   % 不更新
        StaCRenew_Smax=0;
        NumCRenew_Smax=0;
        rX_Smax=X_Smax;
        rY_Smax=Y_Smax;
        rAlfa_Smax=[Alfa_Smax; b_Smax];
        rH_Smax=H_Smax;
    end
    
    if  abs(e_CO_k)>=PermitErr_CO && abs(CO_inc_k1) <= CO_rate_limit  % PermitErr_CO
        [rX_CO,rY_CO,rAlfa_CO,rb_CO,rH_CO] = ModelRenew(X_CO,Y_CO,H_CO,Delta_CO,C_CO,NumSupVec_CO,Input_CO,CO_inc_k,Alfa_CO,Flag,K_Alfa);
        if StaCRenew_CO==1  % 为1代表模型上次进行了更新
            NumCRenew_CO=NumCRenew_CO+1;  % 连续更新次数
        end
        StaCRenew_CO=1;
        rAlfa_CO=[rAlfa_CO; rb_CO];
    else   % 不更新
        StaCRenew_CO=0;
        NumCRenew_CO=0;
        rX_CO=X_CO;
        rY_CO=Y_CO;
        rAlfa_CO=[Alfa_CO; b_CO];
        rH_CO=H_CO;
    end
    
    if  abs(e_Nox_k)>= PermitErr_Nox && abs(Nox_inc_k1) <= Nox_rate_limit
        [rX_Nox,rY_Nox,rAlfa_Nox,rb_Nox,rH_Nox] = ModelRenew(X_Nox,Y_Nox,H_Nox,Delta_Nox,C_Nox,NumSupVec_Nox,Input_Nox,Nox_inc_k,Alfa_Nox,Flag,K_Alfa);
        if StaCRenew_Nox==1  % 为1代表模型上次进行了更新
            NumCRenew_Nox=NumCRenew_Nox+1;  % 连续更新次数
        end
        StaCRenew_Nox=1;
        rAlfa_Nox=[rAlfa_Nox; rb_Nox];
    else   % 不更新
        StaCRenew_Nox=0;
        NumCRenew_Nox=0;
        rX_Nox=X_Nox;
        rY_Nox=Y_Nox;
        rAlfa_Nox=[Alfa_Nox; b_Nox];
        rH_Nox=H_Nox;
    end
 
    % 排烟温度模型更新
    if abs(e_Etem_sum)>PermitErr_Etem && abs(Etem_inc_k1) <= Etem_rate_limit
        [rX_Etem,rY_Etem,rAlfa_Etem,rb_Etem,rH_Etem] = ModelRenew(X_Etem,Y_Etem,H_Etem,Delta_Etem,C_Etem,NumSupVec_Etem,Input_Etem,Etem_inc_k,Alfa_Etem,Flag,K_Alfa);
        
        if StaCRenew_Etem==1 %为1代表模型上次进行了更新
            NumCRenew_Etem=NumCRenew_Etem+1;
        end
        StaCRenew_Etem=1;
        rAlfa_Etem=[rAlfa_Etem; rb_Etem];
    else
        StaCRenew_Etem=0;
        NumCRenew_Etem=0;
        rX_Etem=X_Etem;
        rY_Etem=Y_Etem;
        rAlfa_Etem=[Alfa_Etem; b_Etem];
        rH_Etem=H_Etem;
    end
    
    % 再热气温模型更新
    if abs(e_Rtem_sum)>PermitErr_Rtem && abs(Rtem_inc_k1) <= Rtem_rate_limit
        [rX_Rtem,rY_Rtem,rAlfa_Rtem,rb_Rtem,rH_Rtem] = ModelRenew(X_Rtem,Y_Rtem,H_Rtem,Delta_Rtem,C_Rtem,NumSupVec_Rtem,Input_Rtem,Rtem_inc_k,Alfa_Rtem,Flag,K_Alfa);
        
        if StaCRenew_Rtem==1 %为1代表模型上次进行了更新
            NumCRenew_Rtem=NumCRenew_Rtem+1;
        end
        StaCRenew_Rtem=1;
        rAlfa_Rtem=[rAlfa_Rtem; rb_Rtem];
    else
        StaCRenew_Rtem=0;
        NumCRenew_Rtem=0;
        rX_Rtem=X_Rtem;
        rY_Rtem=Y_Rtem;
        rAlfa_Rtem=[Alfa_Rtem; b_Rtem];
        rH_Rtem=H_Rtem;
    end
    
else  % IO未初始化完成时
    e_Smax_k = 0;  % 预测误差为0
    e_CO_k = 0;  % 预测误差为0
    e_Nox_k = 0;  % 预测误差为0
    e_Rtem_k = 0;
    e_Etem_k = 0;
    % Smax
    StaCRenew_Smax = 0;  % 连续更新转态
    NumCRenew_Smax = 0;  % 连续更新次数
    rX_Smax = X_Smax;  % 返回的Smax模型支持向量
    rY_Smax = Y_Smax;
    rAlfa_Smax = [Alfa_Smax; b_Smax];
    rH_Smax = H_Smax;
    % CO
    StaCRenew_CO = 0;  % 连续更新转态
    NumCRenew_CO = 0;  % 连续更新次数
    rX_CO = X_CO;  % 返回的CO模型支持向量
    rY_CO = Y_CO;
    rAlfa_CO = [Alfa_CO; b_CO];
    rH_CO = H_CO;
    % Nox
    StaCRenew_Nox = 0;  % 连续更新转态
    NumCRenew_Nox = 0;  % 连续更新次数
    rX_Nox = X_Nox;  % 返回的Nox模型支持向量
    rY_Nox = Y_Nox;
    rAlfa_Nox = [Alfa_Nox; b_Nox];
    rH_Nox = H_Nox;
    % Etem
    StaCRenew_Etem = 0;
    NumCRenew_Etem = 0;
    rX_Etem = X_Etem;
    rY_Etem = Y_Etem;
    rAlfa_Etem = [Alfa_Etem; b_Etem];
    rH_Etem = H_Etem;   
    % Rtem
    StaCRenew_Rtem = 0;
    NumCRenew_Rtem = 0;
    rX_Rtem = X_Rtem;
    rY_Rtem = Y_Rtem;
    rAlfa_Rtem = [Alfa_Rtem; b_Rtem];
    rH_Rtem = H_Rtem;

end

%% 跟踪时，输出，C++操作
%{ 
%C为最下层时（D停C开）时，C的参考量为100 代表A、B、C、D四台磨煤机启停状态
if(IO(4)==0)  % D层全关
    if(IO(3)==1)  % C层开
        IO(65)=100; % k时刻原逻辑10个控制量输出，用于确定优化范围  C此时能全开
    end
end
%}
%% 返回时IO设置 数据维护
IO(294)=Load_k1;  % k-2时刻负荷更新
IO(9)=Load_k;  % k-1时刻负荷更新

IO(461:462) = IO(460:461);  %  k-1、k-2时刻Smax更新，维护数据
IO(446:447)=IO(445:446);  % k-1、k-2时刻CO更新，维护数据
IO(11:13)=IO(10:12);  % k-1、k-2、k-3时刻NOx更新，维护数据
IO(15:17)=IO(14:16);  % k-1、k-2、k-3时刻Etem更新
IO(19:21)=IO(18:20);  % k-1、k-2、k-3时刻Rtem更新
IO(161)=Trh_Damper_k;  % k-1时刻再热汽温挡板更新
IO(169)=coalneed_k;  % k-1时刻总煤量更新

IO(296)=O2_k3;  % k-4时刻O2测量值更新 
IO(295)=O2_k2;  % k-3时刻O2测量值更新 
IO(142)=O2_k1;  % k-2时刻O2测量值更新 
IO(141)=O2_k;  % k-1时刻O2测量值更新 

%IO(451:456)=IO(450:455);  % k-1到k-6时刻燃烧器摆角更新
IO(363:378)=IO(341:356);  % k-6时刻22个控制量更新，维护数据
IO(341:356)=IO(319:334);  % k-5时刻22个控制量更新
IO(319:334)=IO(297:312);  % k-4时刻22个控制量更新
IO(297:312)=IO(22:37);  % k-3时刻22个控制量更新
IO(22:37)=IO(44:59);  % k-2时刻22个控制量输出 
IO(44:59)=IO(66:81);  % k-1时刻22个控制量更新  k时刻采样输入

%IO(440:444)=IO(439:443);  % k-2到k-6时刻一次风压更新
%IO(439)=IO(432);  % k-1时刻一次风压更新
%IO(469:470)=IO(468:469);  % k-1,k-2时刻减温水流量更新
% k-1时刻前四个煤量偏置控制量置0，使切换到control时初值为0
%IO(30)=0; IO(31)=0; IO(32)=0; IO(33)=0;
% k时刻前四个煤量偏置控制量置0，使control切换到track时值刷新为0
% 使interface显示的偏置量为0
%IO(40)=0; IO(41)=0; IO(42)=0; IO(43)=0;
%IO(77:80)=IO(81:84);  % k-1时刻4个给煤量更新  k-1时刻A,B,C,D层平均煤量需求
%IO(73:76)=IO(77:80);  % k-2时刻4个给煤量更新，学习用

IO(158)=Nox_k;  % 爬山算法中的广义前一时刻NOx

%  飞灰数据更新
IO(265)=cfh_L_k;  % 上一时刻AB侧飞灰，维护数据
IO(266)=cfh_R_k;
%IO(290)=flag_cfh; 
%% IO设置 逻辑维护
% 根据Flag奇偶性交替选择更新策略
if Flag == 0
    Flag=1;
else
    Flag=0;
end

IO(159)=Flag;
IO(7)=1;  % ComError 组件工作状态标志
% Smax、CO、NOx、效率、烟温模型连续更新次数
IO(464)=NumCRenew_Smax; IO(437)=NumCRenew_CO; IO(88)=NumCRenew_Nox; IO(89)=NumCRenew_Etem;  IO(90)=NumCRenew_Rtem; 
% Smax、CO、NOx、效率、烟温模型连续更新状态标志
IO(466)=StaCRenew_Smax; IO(448)=StaCRenew_CO; IO(91)=StaCRenew_Nox; IO(92)=StaCRenew_Etem; IO(93)=StaCRenew_Rtem; 
% Smax、CO、NOx、Etem、Rtem预测偏差
IO(465)=e_Smax_k; IO(438)=e_CO_k; IO(120)=e_Nox_k; IO(121)=e_Etem_k; IO(122)=e_Rtem_k;
% Smax、CO、NOx、效率、烟温累计预测偏差
IO(467)=e_Smax_sum; IO(449)=e_CO_sum; IO(147)=e_Nox_sum; IO(148)=e_Etem_sum; IO(149)=e_Rtem_sum; 

IO(162)=eRtem_k;  % k-1时刻汽温偏差滤波后值 PI用 归一化
IO(176)=eCO_k; % k-1刻，CO偏差 PI用 未归一化
IO(177)=Load_change_State;  % 系统负荷变动状态

% 预测误差list返回
% rListError_CO=ListError_CO;
% rListError_Nox=ListError_Nox;
% rListError_Etem=ListError_Etem;
% rListError_Rtem=ListError_Rtem; 

rIO=IO;
% 模型参数返回
switch model_index
    case 1
        rX_Smax1=rX_Smax; rY_Smax1=rY_Smax; rAlfa_Smax1= rAlfa_Smax; rH_Smax1=rH_Smax;
        rX_Smax2=X_Smax2; rY_Smax2=Y_Smax2;rAlfa_Smax2= Alfa_Smax2;rH_Smax2=H_Smax2;
        rX_Smax3=X_Smax3; rY_Smax3=Y_Smax3;rAlfa_Smax3= Alfa_Smax3;rH_Smax3=H_Smax3;
        
        rX_CO1=rX_CO; rY_CO1=rY_CO; rAlfa_CO1= rAlfa_CO; rH_CO1=rH_CO;
        rX_CO2=X_CO2; rY_CO2=Y_CO2;rAlfa_CO2= Alfa_CO2;rH_CO2=H_CO2;
        rX_CO3=X_CO3; rY_CO3=Y_CO3;rAlfa_CO3= Alfa_CO3;rH_CO3=H_CO3;
        
        rX_Nox1=rX_Nox; rY_Nox1=rY_Nox; rAlfa_Nox1= rAlfa_Nox; rH_Nox1=rH_Nox;
        rX_Nox2=X_Nox2; rY_Nox2=Y_Nox2;rAlfa_Nox2= Alfa_Nox2;rH_Nox2=H_Nox2;
        rX_Nox3=X_Nox3; rY_Nox3=Y_Nox3;rAlfa_Nox3= Alfa_Nox3;rH_Nox3=H_Nox3;
        
        rX_Etem1=rX_Etem; rY_Etem1=rY_Etem; rAlfa_Etem1=rAlfa_Etem; rH_Etem1=rH_Etem;
        rX_Etem2=X_Etem2; rY_Etem2=Y_Etem2;rAlfa_Etem2= Alfa_Etem2;rH_Etem2=H_Etem2;
        rX_Etem3=X_Etem3; rY_Etem3=Y_Etem3;rAlfa_Etem3= Alfa_Etem3;rH_Etem3=H_Etem3;
   
        rX_Rtem1=rX_Rtem; rY_Rtem1=rY_Rtem; rAlfa_Rtem1=rAlfa_Rtem; rH_Rtem1=rH_Rtem;
        rX_Rtem2=X_Rtem2; rY_Rtem2=Y_Rtem2;rAlfa_Rtem2= Alfa_Rtem2;rH_Rtem2=H_Rtem2;
        rX_Rtem3=X_Rtem3; rY_Rtem3=Y_Rtem3;rAlfa_Rtem3= Alfa_Rtem3;rH_Rtem3=H_Rtem3;
    case 2
        rX_Smax1=X_Smax1; rY_Smax1=Y_Smax1;rAlfa_Smax1= Alfa_Smax1;rH_Smax1=H_Smax1;
        rX_Smax2=rX_Smax; rY_Smax2=rY_Smax; rAlfa_Smax2=rAlfa_Smax; rH_Smax2=rH_Smax;
        rX_Smax3=X_Smax3; rY_Smax3=Y_Smax3;rAlfa_Smax3= Alfa_Smax3;rH_Smax3=H_Smax3;
       
        rX_CO1=X_CO1; rY_CO1=Y_CO1;rAlfa_CO1= Alfa_CO1;rH_CO1=H_CO1;
        rX_CO2=rX_CO; rY_CO2=rY_CO; rAlfa_CO2=rAlfa_CO; rH_CO2=rH_CO;
        rX_CO3=X_CO3; rY_CO3=Y_CO3;rAlfa_CO3= Alfa_CO3;rH_CO3=H_CO3;
  
        rX_Nox1=X_Nox1; rY_Nox1=Y_Nox1;rAlfa_Nox1= Alfa_Nox1;rH_Nox1=H_Nox1;
        rX_Nox2=rX_Nox; rY_Nox2=rY_Nox; rAlfa_Nox2=rAlfa_Nox; rH_Nox2=rH_Nox;
        rX_Nox3=X_Nox3; rY_Nox3=Y_Nox3;rAlfa_Nox3= Alfa_Nox3;rH_Nox3=H_Nox3;
        
        rX_Etem1=X_Etem1; rY_Etem1=Y_Etem1;rAlfa_Etem1= Alfa_Etem1;rH_Etem1=H_Etem1;
        rX_Etem2=rX_Etem; rY_Etem2=rY_Etem; rAlfa_Etem2=rAlfa_Etem; rH_Etem2=rH_Etem;
        rX_Etem3=X_Etem3; rY_Etem3=Y_Etem3;rAlfa_Etem3= Alfa_Etem3;rH_Etem3=H_Etem3;
        
        rX_Rtem1=X_Rtem1; rY_Rtem1=Y_Rtem1;rAlfa_Rtem1= Alfa_Rtem1;rH_Rtem1=H_Rtem1;
        rX_Rtem2=rX_Rtem; rY_Rtem2=rY_Rtem; rAlfa_Rtem2=rAlfa_Rtem; rH_Rtem2=rH_Rtem;
        rX_Rtem3=X_Rtem3; rY_Rtem3=Y_Rtem3;rAlfa_Rtem3= Alfa_Rtem3;rH_Rtem3=H_Rtem3;
    case 3  
        rX_Smax1=X_Smax1; rY_Smax1=Y_Smax1;rAlfa_Smax1= Alfa_Smax1;rH_Smax1=H_Smax1;
        rX_Smax2=X_Smax2; rY_Smax2=Y_Smax2;rAlfa_Smax2= Alfa_Smax2;rH_Smax2=H_Smax2;
        rX_Smax3=rX_Smax; rY_Smax3=rY_Smax; rAlfa_Smax3=rAlfa_Smax; rH_Smax3=rH_Smax;
              
        rX_CO1=X_CO1; rY_CO1=Y_CO1;rAlfa_CO1= Alfa_CO1;rH_CO1=H_CO1;
        rX_CO2=X_CO2; rY_CO2=Y_CO2;rAlfa_CO2= Alfa_CO2;rH_CO2=H_CO2;
        rX_CO3=rX_CO; rY_CO3=rY_CO; rAlfa_CO3=rAlfa_CO; rH_CO3=rH_CO;
        
        rX_Nox1=X_Nox1; rY_Nox1=Y_Nox1;rAlfa_Nox1= Alfa_Nox1;rH_Nox1=H_Nox1;
        rX_Nox2=X_Nox2; rY_Nox2=Y_Nox2;rAlfa_Nox2= Alfa_Nox2;rH_Nox2=H_Nox2;
        rX_Nox3=rX_Nox; rY_Nox3=rY_Nox; rAlfa_Nox3=rAlfa_Nox; rH_Nox3=rH_Nox;
       
        rX_Etem1=X_Etem1; rY_Etem1=Y_Etem1;rAlfa_Etem1= Alfa_Etem1;rH_Etem1=H_Etem1;
        rX_Etem2=X_Etem2; rY_Etem2=Y_Etem2;rAlfa_Etem2= Alfa_Etem2;rH_Etem2=H_Etem2;
        rX_Etem3=rX_Etem; rY_Etem3=rY_Etem; rAlfa_Etem3=rAlfa_Etem; rH_Etem3=rH_Etem;

        rX_Rtem1=X_Rtem1; rY_Rtem1=Y_Rtem1;rAlfa_Rtem1= Alfa_Rtem1;rH_Rtem1=H_Rtem1;
        rX_Rtem2=X_Rtem2; rY_Rtem2=Y_Rtem2;rAlfa_Rtem2= Alfa_Rtem2;rH_Rtem2=H_Rtem2;
        rX_Rtem3=rX_Rtem; rY_Rtem3=rY_Rtem; rAlfa_Rtem3=rAlfa_Rtem; rH_Rtem3=rH_Rtem;      
end
end

