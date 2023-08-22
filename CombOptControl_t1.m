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
rX_Smax3,rY_Smax3,rAlfa_Smax3,rH_Smax3]...
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

P=OP(1);  % 预测步数
M=OP(2);  % 控制步数
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

% 模型误差容忍度（单步）
PermitErr_Nox = OP(16);  
PermitErr_Etem = OP(17);
PermitErr_Rtem = OP(18);
PermitErr_CO = OP(297);
PermitErr_Smax = OP(149);  % 0.02

% 更新时增量速率约束(无用)
Nox_rate_limit = OP(330);
Etem_rate_limit = OP(331); 
Rtem_rate_limit = OP(332);
CO_rate_limit = OP(333);
Smax_rate_limit = OP(150); 

% 增量的归一化参数，上下限相同
norm_limit_Load = OP(334);
norm_limit_O2 = OP(335);
norm_limit_Fuel = OP(336);
norm_limit_Sec = OP(337);
norm_limit_Sofa = OP(338);
norm_limit_Fp = OP(207);  % 0.2

norm_limit_Nox = OP(339);
norm_limit_Etem = OP(340);
norm_limit_Rtem = OP(341);
norm_limit_CO = OP(342);  % 0.35
norm_limit_Smax = OP(153); % O2量绝对偏差 0.08

% 参数上下限，在构建指标时costfunction，需要对全量归一化，这和对增量归一化有区别
% 而d_Nox,u_Nox用于确定Nox优化范围，超出范围给予惩罚，d_Rtem,u_Rtem同理 
max_Nox=OP(121);min_Nox=OP(113);
max_Rtem=OP(123);min_Rtem=OP(115);
max_Smax=OP(162);min_Smax=OP(163);  % 归一化参数
u_Nox=OP(13);d_Nox=0;  % SCR入口NOx浓度合理区间 upLimit_NOx
u_Rtem=OP(14);d_Rtem=OP(15);  % 再热汽温不惩罚区间
% u_Smax=OP(164);d_Smax=OP(165);  % 不惩罚区间
u_Nox_norm=(u_Nox-min_Nox)/(max_Nox-min_Nox);  % 不惩罚区间归一化，用于指标J计算
d_Nox_norm=(d_Nox-min_Nox)/(max_Nox-min_Nox); 
u_Rtem_norm=(u_Rtem-min_Rtem)/(max_Rtem-min_Rtem); 
d_Rtem_norm=(d_Rtem-min_Rtem)/(max_Rtem-min_Rtem); 
% u_Smax_norm=(u_Smax-min_Smax)/(max_Smax-min_Smax); 
% d_Smax_norm=(d_Smax-min_Smax)/(max_Smax-min_Smax);

% 优化区间上下限
u_Sofa=OP(20:21); u_Sec=OP(22:27); u_O2=OP(35); u_Fuel=OP(36:41); u_Fp=OP(208);
l_Sofa =OP(42:43); l_Sec=OP(44:49); l_O2=OP(57); l_Fuel=OP(58:63); l_Fp=OP(209); 
% 结构风险约束 用于归一化参数
u_opt_bias_norm = max([u_O2',u_Fuel',u_Sec',u_Sofa',u_Fp'],abs([l_O2',l_Fuel',l_Sec',l_Sofa', l_Fp']));
% 控制变量变化速率约束
lim_rSofa=OP(64:65); lim_rSec=OP(66:71); lim_rO2=OP(79); lim_rFuel=OP(80:85); lim_rFp=OP(210);
% 控制变量输出死区
dz_Sofa=OP(86:87); dz_Sec=OP(88:93); dz_O2=OP(101); dz_Fuel=OP(102:107); dz_Fp=OP(211);
% f(x)+手偏小于此值不再优化，偏置为0（认为设备关闭）不控制死区
% dzl_Sofa=OP(343); dzl_Sec=OP(344); dzl_Fuel=OP(346); dzl_Fp=OP(212); % dzl_O2=OP(345); dzl_Fp=OP(345);
% 控制量绝对上下限
au_Sofa=OP(245:246); au_Sec=OP(247:252); au_O2=OP(260); au_Fuel=OP(261:266); au_Fp=OP(213);
al_Sofa=OP(223:224); al_Sec=OP(225:230); al_O2=OP(238); al_Fuel=OP(239:244); al_Fp=OP(214);

% SVM参数归一化上下限
%min_Fuel=OP(108); min_Sec=OP(109); min_Sofa=OP(110); min_O2=OP(111);
%min_Load=OP(112); min_Nox=OP(113); min_Etem=OP(114); min_Rtem=OP(115);
%max_Fuel=OP(108); max_Sec=OP(109); max_Sofa=OP(110); max_O2=OP(111);
%max_Load=OP(112); max_Nox=OP(113); max_Etem=OP(114); max_Rtem=OP(115);

% 送风机电流相关参数
qI=OP(300);  % 送风机电流在性能指标中的权值
max_Iblower=OP(298); min_Iblower=OP(299);  % 送风机电流归一化上下限
max_Load=OP(120); min_Load=OP(112);
max_O2=OP(119); min_O2=OP(111);
% 送风机电流与氧量和负荷的折算关系 I_blower=a*O2_I+b*Load_I+c
a_Iblower=OP(301);b_Iblower=OP(302);c_Iblower=OP(303);  
% 总煤量作为输入的归一化上下限
%max_coalneed=OP(304); min_coalneed=OP(305);
% 再热汽温挡板归一化下限 再热汽温挡板影响因子
%min_Damper=OP(278); max_Damper=OP(279); factor_Damper=OP(280);

K_Alfa=OP(281);  % 更新策略—最大Alfa替换

%  性能指标中控制量增量权值
w_Sofa=OP(124:125); w_Sec=OP(126:131); w_O2=OP(139); w_Fuel=OP(140:145); w_Fp=OP(215);
% L_CO=OP(101);thr_CO=OP(102);
% L_NOx=OP(103);thr_NOx=OP(104);
% NOx加权系数 效率加权系数 汽温加权系数，结构风险(无用),qst氧量绝对偏差系数
qn=OP(180);qe=OP(181);qt=OP(182);qbias=OP(282);qst=OP(166);

MaxFunEvals=OP(183); %OP(183);  % 最大函数计算次数
%MaxNumCRenew=OP(184);  % 允许模型最大连续更新次数

coef=OP(186:191);  % ABCDEF层煤强制增量开关
deltaU=OP(192:197);  % ABCDEF层煤强制增量
COALmax_mill=OP(292);  % 单台给煤机最大给煤量

% 爬山算法相关
HC_State=OP(269);  % 爬山算法开关
%{
HC_O2_State=OP(270);  % 爬山算法开关
HC_Air_State=OP(271);
HC_Bias_State=OP(272);
HC_O2_C=OP(273);  % 氧量控制增量变步长系数
HC_Air_C=OP(274);  % 风量控制增量变步长系数
HC_Bias_C=OP(275);  % 煤量控制增量变步长系数
HC_MaxOptNum=OP(276);  % 爬山寻优最大次数
%}
%% IO数据解析
% -------数据段
% Mill_state=IO(1:6);
% millnum=sum(IO(1:6));  % 磨煤机启动数量
% ALL_Mill=IO(117);  %  k时刻四层煤量需求指令之和

% 当前及k历史Load Nox 排烟温度 再热汽温数据
Load_k=IO(8); Load_k1=IO(9); Load_k2=IO(294);  % k时刻负荷

Nox_k=IO(10); Nox_k1=IO(11); Nox_k2=IO(12); %Nox_k3=IO(13);
Etem_k=IO(14); Etem_k1=IO(15); Etem_k2=IO(16); %Etem_k3=IO(17);
Rtem_k=IO(18); Rtem_k1=IO(19); Rtem_k2=IO(20); %Rtem_k3=IO(21);
% CO_k=IO(95); CO_k1=IO(408); %CO_k2=IO(409);
CO_k=IO(445); CO_k1=IO(446); CO_k2=IO(447);
Smax_k=IO(460); Smax_k1=IO(461); Smax_k2=IO(462); 

O2_k = IO(96); O2_k1 = IO(141);  % k,k-1,k-2时刻实测氧量
O2_k2 = IO(142); O2_k3 = IO(295); O2_k4 = IO(296);  % k-2,k-3,k-4时刻实测氧量

% k-5, k-6时刻实际控制量,控制量和反馈仅存在微小差别，但是O2选择反馈进行预测和更新
Fuel_k5 = IO(342:347); Fuel_k6 = IO(364:369);
Sec_k5 = IO(348:353); Sec_k6 = IO(370:375);
Sofa_k5 = IO(354:355); Sofa_k6 = IO(376:377);
Fp_k5 = IO(356); Fp_k6 = IO(378);  % 一次风压

Trh_Damper_k = IO(160); %Trh_Damper_k1 = IO(161); % k、k-1时刻再热汽温挡板开度
% k-2时刻控制量输出，爬山法用
%u_k2=IO(22:43)';
% k-1时刻控制量输出
%u_k1=IO(44:65)';
% 上一次飞灰含碳变化时对应的控制输入
% u_cfh=IO(267:289)';

%--- ---辅助逻辑段
% Smax、CO、NOx、再热、烟温模型连续更新次数 状态标志
NumCRenew_Smax=IO(464);NumCRenew_CO=IO(437);NumCRenew_Nox=IO(88); NumCRenew_Etem=IO(89); NumCRenew_Rtem=IO(90);
StaCRenew_Smax=IO(466); StaCRenew_CO=IO(448);StaCRenew_Nox=IO(91); StaCRenew_Etem=IO(92); StaCRenew_Rtem=IO(93);

e_Smax_sum=IO(467);
e_CO_sum=IO(449);
e_Nox_sum=IO(147);  % NOx、效率、烟温累计预测偏差
e_Etem_sum=IO(148);
e_Rtem_sum=IO(149);        

Flag=0 ;%IO(159);  % 根据Flag奇偶性交替选择更新策略

%eRtem_k1=IO(162);  % k-1时刻汽温偏差,用于PI控制
eRtem_k=IO(162);  
eCO_k1=IO(176);  % 上一时刻，CO偏差
eCO_k=IO(176);

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
IO(292)=cfh;  % k时刻飞灰含碳值传出,下次使用
%IO(188)=cfh_k1;  % k-1时刻飞灰含碳值传出,下次使用

% 上一时刻飞灰是否更新标志，防止数据异常出现测量值连续变化的情况
flag_cfh=IO(290);
%max_cfh=5;
%min_cfh=0;  %归一化上下限
%norm_limit_Cfh=IO(342);
%% 锅炉效率计算
%计算时考虑元素分析
%Etem_k=Etem_k; % k时刻排烟温度Etem_k
%Co_k=IO(57);  % k时刻CO浓度
%O2_k=O2_k;  % k时刻O2浓度
%Cfh=Co_k*0.001*6/1000;  % 根据CO估算飞灰含碳
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
Cpy=0.8967+0.0013*Etem_k-0.000003*Etem_k*Etem_k; %烟气比热
Sg=Vgy*Cpy*(Etem_k-20)/Qnet;  %干烟气热损失

V_H2O=1.24*((9*h+Mar)+1.293*ALPHA*Vgk0*0.001);
Q_H2O=V_H2O*1.5093*(Etem_k-20);
Sm=Q_H2O/Qnet;  %水分热损失
Suc=337.27*100*Aar/Qnet*Cfh./(1-Cfh);  %飞灰含碳热损失

IO(407)=0.9917-Suc-Sm-Sg;  % 锅炉效率k时刻计算值
%% O2量PID控制投切逻辑  CO决定，这里始终不投入PID
PI_max_Co = OP(287);  % CO上下限
PI_min_Co = OP(288);

if (CO_k<=PI_max_Co)&&(CO_k>=PI_min_Co)
    O2_switch = 1;   %在上下限内时，不投入PID控制
else
    O2_switch = 1;
end
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

%% 程序启动赋值阶段，避免计算
if (sum(Fuel_k6)~=0)  % 数据维护中最大迟延为6  
    %% 增量格式，构造输入，归一化
    Load_inc_k1_norm=((Load_k1-Load_k2)+norm_limit_Load)./(2*norm_limit_Load);  
    %Fangle_inc_k5_norm=((Fangle_k5-Fangle_k6)+norm_limit_Fangle)./(2*norm_limit_Fangle);   
    % 氧量更新模型时，采用实测值
    O2_inc_k1_norm=((O2_k1-O2_k2)+norm_limit_O2)./(2*norm_limit_O2);
    %O2_inc_k2_norm=((O2_k2-O2_k3)+norm_limit_O2)./(2*norm_limit_O2);
    %O2_inc_k3_norm=((O2_k3-O2_k4)+norm_limit_O2)./(2*norm_limit_O2);
    
    % 给煤量及风门采用迟延指定阶数的数据
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
    Nox_inc_k=Nox_k-Nox_k1;  % 预测值y 不归一化
    
    Etem_inc_k1=Etem_k1-Etem_k2;  % 用于约束模型更新
    Etem_inc_k1_norm=(Etem_inc_k1 + norm_limit_Etem)./(2*norm_limit_Etem);
    Etem_inc_k=Etem_k-Etem_k1;  % 预测值y 不归一化
    
    Rtem_inc_k1=Rtem_k1-Rtem_k2;  % 用于约束模型更新
    Rtem_inc_k1_norm=(Rtem_inc_k1 + norm_limit_Rtem)./(2*norm_limit_Rtem);
    Rtem_inc_k=Rtem_k-Rtem_k1;  % 预测值y 不归一化
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
    
    %% 计算偏差
    % 预测偏差，k时刻预测值-k时刻采样值(增量)
    e_Smax_k=(P_Smax_k-Smax_inc_k); 
    e_CO_k=(P_CO_k-CO_inc_k);
    e_Nox_k=(P_Nox_k-Nox_inc_k);
    e_Etem_k=(P_Etem_k-Etem_inc_k);
    e_Rtem_k=(P_Rtem_k-Rtem_inc_k);
    
    %error_Nox_k=e_Nox_k;  % 优化求解用
    %error_Etem_k=e_Etem_k;
    %error_Rtem_k=e_Rtem_k; 
    
    % 累计误差
%     ListError_CO(2:end) = ListError_CO(1:length(ListError_CO)-1);
%     ListError_CO(1) = abs(e_CO_k);
%     ListError_Nox(2:end) = ListError_Nox(1:end-1);
%     ListError_Nox(1) = e_Nox_k;
%     ListError_Etem(2:end) = ListError_Etem(1:end-1);
%     ListError_Etem(1) = e_Etem_k;
%     ListError_Rtem(2:end) = ListError_Rtem(1:end-1);
%     ListError_Rtem(1) = e_Rtem_k;
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
    %% 模型更新

    % 单步预报误差超过容忍度&增量在规定范围内 才更新Smax
    % CO
     % Smax
    if  abs(e_Smax_sum)>= PermitErr_Smax && abs(Smax_inc_k1) <= Smax_rate_limit
        [rX_Smax,rY_Smax,rAlfa_Smax,rb_Smax,rH_Smax] = ModelRenew(X_Smax,Y_Smax,H_Smax,Delta_Smax,C_Smax,NumSupVec_Smax,Input_Smax,Smax_inc_k,Alfa_Smax,Flag,K_Alfa);
        % 采用更新后的参数重新计算偏差
        X_Smax=rX_Smax; Alfa_Smax=rAlfa_Smax; b_Smax=rb_Smax; %Y_Smax=rY_Smax; H_Smax=rH_Smax;
        % 对k时刻Smax重新预测
        a=repmat(Input_Smax,NumSupVec_Smax,1)-X_Smax;
        dist=sum(a.*a,2);
        K=exp(-dist*Delta_Smax)';
        P_Smax_k=K*Alfa_Smax+b_Smax;  % k时刻Smax重新预测值 增量且未归一化
        IO(463)=P_Smax_k+Smax_k1;  % k时刻Smax预测值 全量
        e_Smax_k=P_Smax_k-Smax_inc_k;  % 更新后预测误差
        NumCRenew_Smax=NumCRenew_Smax+1;  % 连续更新次数
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
    
    % CO   
    if  abs(e_CO_sum)>= PermitErr_CO && abs(CO_inc_k1) <= CO_rate_limit
        [rX_CO,rY_CO,rAlfa_CO,rb_CO,rH_CO] = ModelRenew(X_CO,Y_CO,H_CO,Delta_CO,C_CO,NumSupVec_CO,Input_CO,CO_inc_k,Alfa_CO,Flag,K_Alfa);
        % 采用更新后的参数重新计算偏差
        X_CO=rX_CO; Alfa_CO=rAlfa_CO; b_CO=rb_CO; %Y_CO=rY_CO; H_CO=rH_CO;
        % 对k时刻CO重新预测
        a=repmat(Input_CO,NumSupVec_CO,1)-X_CO;
        dist=sum(a.*a,2);
        K=exp(-dist*Delta_CO)';
        P_CO_k=K*Alfa_CO+b_CO;  % k时刻CO重新预测值 增量且未归一化
        IO(436)=P_CO_k+CO_k1;  % k时刻CO预测值 全量
        e_CO_k=P_CO_k-CO_inc_k;
        NumCRenew_CO=NumCRenew_CO+1;  % 连续更新次数
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
    
    % Nox
    if  abs(e_Nox_sum)>= PermitErr_Nox && abs(Nox_inc_k1) <= Nox_rate_limit
        [rX_Nox,rY_Nox,rAlfa_Nox,rb_Nox,rH_Nox] = ModelRenew(X_Nox,Y_Nox,H_Nox,Delta_Nox,C_Nox,NumSupVec_Nox,Input_Nox,Nox_inc_k,Alfa_Nox,Flag,K_Alfa);
        % 采用更新后的参数重新计算偏差
        X_Nox=rX_Nox; Alfa_Nox=rAlfa_Nox; b_Nox=rb_Nox; %Y_Nox=rY_Nox; H_Nox=rH_Nox;
        % 对k时刻NOx重新预测
        a=repmat(Input_Nox,NumSupVec_Nox,1)-X_Nox;
        dist=sum(a.*a,2);
        K=exp(-dist*Delta_Nox)';
        P_Nox_k=K*Alfa_Nox+b_Nox;  % k时刻NOx重新预测值 增量且未归一化
        IO(173)=P_Nox_k+Nox_k1;  % 模型更新后，k时刻NOx预测值 全量
        e_Nox_k=P_Nox_k-Nox_inc_k;
        NumCRenew_Nox=NumCRenew_Nox+1;  % 连续更新次数
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
        
        % 采用更新后的参数重新计算偏差
        X_Etem=rX_Etem; Alfa_Etem=rAlfa_Etem; b_Etem=rb_Etem;% H_Etem=rH_Etem; Y_Etem=rY_Etem; 
        % 对k时刻Etem重新预测
        a=repmat(Input_Etem,NumSupVec_Etem,1)-X_Etem;
        dist=sum(a.*a,2);
        K=exp(-dist*Delta_Etem)';
        P_Etem_k=K*Alfa_Etem+b_Etem;  % k时刻Etem重新预测值 增量且未归一化
        IO(174)=P_Etem_k+Etem_k1;  % 模型更新后，k时刻Etem预测值 全量   
        e_Etem_k=P_Etem_k-Etem_inc_k;  % 预测误差
        NumCRenew_Etem=NumCRenew_Etem+1;
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
        % 采用更新后的参数重新计算偏差
        X_Rtem=rX_Rtem; Alfa_Rtem=rAlfa_Rtem; b_Rtem=rb_Rtem;% H_Rtem=rH_Rtem; Y_Rtem=rY_Rtem;
        % 对k时刻Rtem重新预测
        a=repmat(Input_Rtem,NumSupVec_Rtem,1)-X_Rtem;
        dist=sum(a.*a,2);
        K=exp(-dist*Delta_Rtem)';
        P_Rtem_k=K*Alfa_Rtem+b_Rtem;  % k时刻Rtem重新预测值 增量且未归一化
        IO(175)=P_Rtem_k+Rtem_k1;  % 模型更新后
        e_Rtem_k=(P_Rtem_k-Rtem_inc_k);
        NumCRenew_Rtem=NumCRenew_Rtem+1;
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
    %% 选择优化算法 爬山优化 sqp
    if (HC_State==0) % 未启动爬山寻优 HC_State==0
        control_num=16;  % 16个控制量 O2-1 Fuel-6 Sec-6 Sofa-2 Fp-1
        %M = 2;
        R1=diag([w_O2',w_Fuel',w_Sec',w_Sofa',w_Fp']);  %  权值对角矩阵，惩罚系数，对增量的惩罚
        %R2=repmat({R1},M,1);
        %R=blkdiag(R2{:});
        R=R1;
    
        %1.输出约束归一化 上下限约束归一化
        %upLimit_NOx=(upLimit_NOx-min_NOx)/(max_NOx-min_NOx);
        %upLimit_Tem=(upLimit_Tem-min_Tem)/(max_Tem-min_Tem);
        %downLimit_NOx=(downLimit_NOx-min_NOx)/(max_NOx-min_NOx);
        %downLimit_Tem=(downLimit_Tem-min_Tem)/(max_Tem-min_Tem);
        %2.控制量绝对约束归一化
        %3.控制量增量归一化
        %4.控制量变化死区归一化
        %5.控制量强制增量归一化    
        S=cell(M,M);
        for i=1:M
            for j=1:M
                if i>=j
                    S{i,j}=eye(control_num);
                else
                    S{i,j}=zeros(control_num);
                end
            end
        end
        S=cell2mat(S);
        invS=inv(S);  
       %% 确定初始优化区间
        % 优化区间确定:优化范围约束，绝对上下限约束和速率约束
        % 上一时刻优化偏置，维护的数据，全量,k时刻未优化时保持不变。
        % 优化偏置量，当前时刻，未优化的量，即保持为上一时刻的值
        %Fangle_opt_bias_k1=IO(458);  % 从DCS读取
        O2_opt_bias_k1=IO(385);  % 从DCS读取
        Fuel_opt_bias_k1=IO(386:391);
        Sec_opt_bias_k1=IO(392:397);
        Sofa_opt_bias_k1=IO(398:399);
        Fp_opt_bias_k1=IO(400);
        opt_bias_k1=[O2_opt_bias_k1',Fuel_opt_bias_k1',Sec_opt_bias_k1',Sofa_opt_bias_k1',Fp_opt_bias_k1'];

        % k时刻原逻辑f(x)+sbias全量输出，绝对上下限
        O2_fnb_k=IO(97);
        Fuel_fnb_k=IO(98:103);
        Sec_fnb_k=IO(104:109);
        Sofa_fnb_k=IO(110:111);
        Fp_fnb_k=IO(112);
        
        fnb_k=[O2_fnb_k',Fuel_fnb_k',Sec_fnb_k',Sofa_fnb_k',Fp_fnb_k'];
        %{
        % 停磨时风门关闭速率为原速率的10倍
        % MinDampOpen=(Op(19)-min_SecAir)/(max_SecAir-min_SecAir);  % 停磨时二次风门最小开度 Op(19)
        % 6台给煤机状态 IO(1:6)
         if(IO(1)==0)  % A层停
            u_Fuel(1)=0;  % A磨煤量优化区间上下限修改为0，不对A磨煤机优化量进行优化
            l_Fuel(1)=0;
            umin(5)=MinDampOpen;  % A二次风设为绝对下限5
            umax(5)=MinDampOpen;
            lim_rSofa(5)=10*lim_Sofa(5);  %风门变化速率加大
         end
        %}
       %% 优化区间动态修改
        % 停磨后，修改给煤与二次风门优化区间上下限为0,不再优化
        % 取手自动状态和停磨信号
        % 磨手动，不优化对应层磨
        MillState = logical(IO(1:6));  % 手自动状态
        for i = 1:6
            if(MillState(i)==0)  % A层停，不优化A层给煤输出
                u_Fuel(i)=0; % 上下限设置为0
                l_Fuel(i)=0;
                %u_Sec(i)=0;
                %l_Sec(i)=0;  
                % 避免停磨时冲突,放大
                %au_Fuel(i)=100;
                %al_Fuel(i)=0;
                %au_Sec(i)=100;
                %al_Sec(i)=0;                
            end
        end
        
    
        % 获得磨煤机启停状态
        Millqt = logical(IO(179:184));  % 磨煤机启停状态
        % A 层停，不优化对应的二次风门
        if (Millqt(1)==0)
            u_Sec(1)=0;
            l_Sec(1)=0;
            au_Sec(1)=100;
            al_Sec(1)=0;  
        end
        % D 层停，不优化对应的二次风门
        if (Millqt(4)==0)
            u_Sec(6)=0;
            l_Sec(6)=0; 
            au_Sec(6)=100;
            al_Sec(6)=0;   
        end
       
        % F停，不优化对应的二次风门
        if (Millqt(6)==0)
            u_Sec(2)=0;
            l_Sec(2)=0; 
            au_Sec(2)=100;
            al_Sec(2)=0;
        end
        % C层停不优化对应的二次风门
        if (Millqt(3)==0)
            u_Sec(5)=0;
            l_Sec(5)=0; 
            au_Sec(5)=100;
            al_Sec(5)=0;   
        end
        % E层停，不优化对应的二次风门
        if (Millqt(5)==0)
            u_Sec(3)=0;
            l_Sec(3)=0;  
            au_Sec(3)=100;
            al_Sec(3)=0;     
        end
        % B停，不优化对应的二次风门
        if (Millqt(2)==0)
            u_Sec(4)=0;
            l_Sec(4)=0; 
            au_Sec(4)=100;
            al_Sec(4)=0;   
        end
        % 获得动态修改后的上下限约束
        % 停磨后优化上下限变为0，此时不满足约束
        u_Var=[u_O2', u_Fuel', u_Sec', u_Sofa', u_Fp'];
        l_Var=[l_O2', l_Fuel', l_Sec', l_Sofa', l_Fp'];
        
        % 获得此时增量可行域（优化区间约束下的）
        ub_opt_range_lim=u_Var-opt_bias_k1;  % f(x)+s_bias+opt_bias+ub_opt_range_lim < f(x)+s_bias+u_Var
        lb_opt_range_lim=l_Var-opt_bias_k1;
  
        %% 绝对量上下限约束 100 0 针对fnb_k+opt_bias_k1 DCS系统和燃烧优化系统一起输出控制量
        % 如果停磨不考虑绝对上下限     
        au_Var=[au_O2', au_Fuel', au_Sec', au_Sofa', au_Fp'];  
        al_Var=[al_O2', al_Fuel', al_Sec', al_Sofa', al_Fp'];  % 这样构建，仅是为了批量运算。 绝对量下限
        % 获得此时增量可行域（绝对上下限约束下的)
        ub_abs_lim=au_Var-fnb_k-opt_bias_k1;  
        lb_abs_lim=al_Var-fnb_k-opt_bias_k1;
        
        %% 速率约束 +0.5 -0.5 针对 Inc
        % 获得此时增量可行域（速率约束下的）
        ub_rate_lim=[lim_rO2', lim_rFuel', lim_rSec', lim_rSofa', lim_rFp'];
        lb_rate_lim=-[lim_rO2', lim_rFuel', lim_rSec', lim_rSofa',lim_rFp'];
        
        %% 最终增量区间
        ub=min(min(ub_opt_range_lim,ub_abs_lim),ub_rate_lim);
        lb=max(max(lb_opt_range_lim,lb_abs_lim),lb_rate_lim);
        
        %% 防止增量区间下界大于上界,出现情况
        % 如果增量超出所给氛围上限(优化与绝对)，需要往回拉。超出一点点时不考虑。此时上界小于下届速率
        err=lb>ub;  % 下届大于上界，出现无解
        % 如果err出现在给煤机中，在下面的等式约束中将忽略掉等式约束条件
        
        erru=ub<lb_rate_lim;  % 上届小于速度下届，不能被一次拉回，此时出现情况1,2之一
        ub(err & erru)=lb(err & erru);  % 修改上界与下届一致，为最小速率
        
        % 如果增量超出所给氛围下限(优化与绝对)，需要上拉。速率范围内不考虑，自动拉回。此时下界大于上届速率
        errl=lb>ub_rate_lim;  % 下届大于速度上界
        lb(err & errl)=ub(err & errl);
       
        % 情况1：
        % 当fnb_k+opt_bias_k1落在绝对上下限时，可行域 feasible，
        % 当fnb_k+opt_bias_k1落在绝对上下限外时，可能无可行域
        % infeasible，特别是增减负荷剧烈期间，风门，给煤量变化剧烈。
        % 此时需要扩大下界（超过上绝对界限）或者下界（超过下绝对界限）。
        % 超过绝对上界限，能出现无可行域情况，动态修改下界
        % 超过绝对下界限,此时lb为正，上界取最小被速率限制，动态修改上界
        % 情况2：
        % 因为动态优化区间的修改导致 opt_bias在单个优化速率范围内不能被拉回
        % 当opt_bias_k1+lb_rate_lim > u_Var(优化区间上限),减小lb到opt_bias_k1-u_Var 
        % 当opt_bias_k1+ub_rate_lim(速率上界)< l_Var(优化区间下限)
 
       %% 防止异常情况，最终一个约束可能不合理
        err=lb>ub;  % 继续出现下届大于上界，出现无解
        ub(err)=0;
        lb(err)=0;
       %% 优化控制量初始点
        % 一般情况
        u0 = zeros(control_num,1);
        % 特殊情况 如果上下限lb ub 相等，
        mdf=lb==ub;
        u0(mdf)=lb(mdf);
        %% 等式约束
        Aeq = zeros(1, control_num);  % 给煤机等式约束
        Aeq(1, 2:7) = 1;  % 总煤量约束
        %Coal_enforce_set = sum(u0(Aeq & mdf));  % 给煤增量强制设定值之和
        % 扩大其余给煤上下限约束
        %Aeq_norm = logical(Aeq-(Aeq & mdf));  % 给煤机约束在正常范围内的给煤机
        %if Coal_enforce_set > 0
        %   lb(Aeq_norm) = lb(Aeq_norm) - Coal_enforce_set/(sum(Aeq_norm)-1);  % 减一是为了给予一定的松弛度
        %elseif (Coal_enforce_set < 0)
        %   ub(Aeq_norm) = ub(Aeq_norm) + Coal_enforce_set/(sum(Aeq_norm)-1);  % 减一是为了给予一定的松弛度
        %end
        %IO(191:212)=ub';
        %IO(213:234)=lb';
        % 区间、初始点归一化
        norm_limt_var=zeros(control_num,1);  % 列向量
        norm_limt_var(1)=norm_limit_O2 ; 
        norm_limt_var(2:7)=norm_limit_Fuel;
        norm_limt_var(8:13)=norm_limit_Sec; 
        norm_limt_var(14:15)=norm_limit_Sofa;
        norm_limt_var(16)=norm_limit_Fp;
        lb_norm=(lb'+norm_limt_var)./(2*norm_limt_var);
        ub_norm=(ub'+norm_limt_var)./(2*norm_limt_var);
          
        % 初始点归一化
        u0=(u0+norm_limt_var)./(2.*norm_limt_var);
       
       %%  等式约束 总煤量约束
        % 当前实际控制量 ，全量 fnb_k
        % 等式约束 总煤量约束，若有停运的设备增量为0
        % 低负荷时D F给煤机停运；相应的二次风门开度变小，到10%, 燃尽风门最低到18%
        beq = 0.5*sum(Aeq);  % 等于0，归一化后为0.5
    
       %% 新增风门指标，府谷不需要
       %% fmincon SQP
        % 数据准备
        % k 到 k5
        Fuel_k5_k = [IO(342:347)';IO(320:325)';IO(298:303)';IO(23:28)';IO(45:50)';IO(67:72)'];  % k-5;k-4;k-3;k-2;k-1
        Sec_k5_k = [IO(348:353)';IO(326:331)';IO(304:309)';IO(29:34)';IO(51:56)';IO(73:78)'];  
        Sofa_k5_k = [IO(354:355)';IO(332:333)';IO(310:311)';IO(35:36)';IO(57:58)';IO(79:80)'];  
        Fp_k5_k = [IO(356);IO(334);IO(312);IO(37);IO(59);IO(81)];  

        %增量格式并归一化
        Load_inc_k_norm=((Load_k-Load_k1)+norm_limit_Load)./(2*norm_limit_Load);
        %Fangle_inc_k4_k_norm=((Fangle_k5_k(2:end,:)-Fangle_k5_k(1:end-1,:))+norm_limit_Fangle)./(2*norm_limit_Fangle);
        
        O2_inc_k_norm=((O2_k-O2_k1)+norm_limit_O2)./(2*norm_limit_O2);
        O2_inc_k1_norm=((O2_k1-O2_k2)+norm_limit_O2)./(2*norm_limit_O2);
        O2_inc_k2_norm=((O2_k2-O2_k3)+norm_limit_O2)./(2*norm_limit_O2);
        
        Fuel_inc_k4_k_norm=((Fuel_k5_k(2:end,:)-Fuel_k5_k(1:end-1,:))+norm_limit_Fuel)./(2*norm_limit_Fuel);
        Sec_inc_k4_k_norm=((Sec_k5_k(2:end,:)-Sec_k5_k(1:end-1,:))+norm_limit_Sec)./(2*norm_limit_Sec);
        Sofa_inc_k4_k_norm=((Sofa_k5_k(2:end,:)-Sofa_k5_k(1:end-1,:))+norm_limit_Sofa)./(2*norm_limit_Sofa); 
        Fp_inc_k4_k_norm=((Fp_k5_k(2:end,:)-Fp_k5_k(1:end-1,:))+norm_limit_Fp)./(2*norm_limit_Fp);         
        % Dhflow_inc_k_norm=((Dhflow_k-Dhflow_k1)+norm_limit_Dhflow)./(2*norm_limit_Dhflow);
        
        Smax_inc_k_norm=((Smax_k-Smax_k1)+norm_limit_Smax)./(2*norm_limit_Smax);
        CO_inc_k_norm=((CO_k-CO_k1)+norm_limit_CO)./(2*norm_limit_CO);
        Nox_inc_k_norm=((Nox_k-Nox_k1)+norm_limit_Nox)./(2*norm_limit_Nox);
        Etem_inc_k_norm=((Etem_k-Etem_k1)+norm_limit_Etem)./(2*norm_limit_Etem);
        Rtem_inc_k_norm=((Rtem_k-Rtem_k1)+norm_limit_Rtem)./(2*norm_limit_Rtem);
        Load_k_norm=(Load_k-min_Load)/(max_Load-min_Load);  % k时刻负荷全量归一化，求取送风机电流
        
%         norm_limit_cvar=zeros(control_num,1);  % 用于控制量批量反归一化，列向量 duM  opt_bias_k1' u_Var'
%         norm_limit_cvar(1)=norm_limit_O2;
%         norm_limit_cvar(2:7)=norm_limit_Fuel;
%         norm_limit_cvar(8:20)=norm_limit_Sec;
%         norm_limit_cvar(21:22)=norm_limit_Sofa;
%         norm_limit_cvar(23)=norm_limit_Fp;
%         norm_limit_cvar(24)=norm_limit_Fangle;
        % 如果优化步数大于1。第一步约束合理构造，之后各步仅存在速率约束和等式约束
        % 且将初始点设置为0，即0.5。
        if (M > 1) 
            % 初始值
            u0M = ones(control_num*M,1)*0.5;
            u0M(1:control_num,1) = u0;
            
            % 不等式约束，仅考虑速率上下限
            % 速率约束归一化
            ub_rate_lim_norm = (ub_rate_lim'+norm_limt_var)./(2*norm_limt_var);
            lb_rate_lim_norm = (lb_rate_lim'+norm_limt_var)./(2*norm_limt_var);      
            lbM_norm = zeros(control_num*M,1);  % 多M下届
            ubM_norm = zeros(control_num*M,1);  % 多M上界
            
            lbM_norm(1:control_num,1) = lb_norm;  % 第一步约束不变
            ubM_norm(1:control_num,1) = ub_norm;  % 第一步约束不变           
            for i = 1:M-1  % 之后各步只有速率约束
                lbM_norm(control_num*i+1:control_num*(i+1),1) = lb_rate_lim_norm;  % 速率约束作为上下限
                ubM_norm(control_num*i+1:control_num*(i+1),1) = ub_rate_lim_norm;  % 速率约束作为上下限
            end
            
            % 等式约束 给煤
            AeqM = zeros(M,control_num*M);
            for i = 1:M
                AeqM(i,control_num*(i-1)+1:control_num*i) = Aeq;
            end
            beqM = ones(M,1)*beq;
        else
            u0M = u0;
            lbM_norm = lb_norm;
            ubM_norm = ub_norm;
            AeqM = Aeq;  
            beqM = beq;
        end
        %MaxFunEvals = 10000;
        options = optimset('MaxFunEvals',MaxFunEvals,'Algorithm','sqp');
        
        [duM,~,QP_Flag] = fmincon(@(duM)(CostFunction(duM,P,M,...
            Load_inc_k_norm,O2_inc_k_norm,O2_inc_k1_norm,O2_inc_k2_norm,Fuel_inc_k4_k_norm,Sec_inc_k4_k_norm,Sofa_inc_k4_k_norm,Fp_inc_k4_k_norm,...
            Smax_k1,CO_k1,Nox_k1,Etem_k1,Rtem_k1,cfh,a_Cfh,b_Cfh,...
            Smax_inc_k_norm,CO_inc_k_norm,Nox_inc_k_norm,Etem_inc_k_norm,Rtem_inc_k_norm,...
            NumSupVec_Smax,X_Smax,Alfa_Smax,b_Smax,Delta_Smax,e_Smax_k,...
            NumSupVec_CO,X_CO,Alfa_CO,b_CO,Delta_CO,e_CO_k,...
            NumSupVec_Nox,X_Nox,Alfa_Nox,b_Nox,Delta_Nox,e_Nox_k,...
            NumSupVec_Etem,X_Etem,Alfa_Etem,b_Etem,Delta_Etem,e_Etem_k,...
            NumSupVec_Rtem,X_Rtem,Alfa_Rtem,b_Rtem,Delta_Rtem,e_Rtem_k,...
            Mar,Mad,Aar,Qnet,s,...
            Load_k_norm,O2_k,O2_fnb_k,a_Iblower,b_Iblower,c_Iblower,min_O2,max_O2,min_Iblower,max_Iblower,...
            qe,qn,qt,qI,qbias,qst,invS,R,u_Nox_norm,d_Nox_norm,u_Rtem_norm,d_Rtem_norm,max_Nox,min_Nox,max_Rtem,min_Rtem,max_Smax,min_Smax,...
            u_opt_bias_norm,norm_limt_var,opt_bias_k1,u_Var,norm_limit_Smax,norm_limit_CO,norm_limit_Nox,norm_limit_Etem,norm_limit_Rtem)),...
            u0M,[],[],AeqM,beqM,lbM_norm,ubM_norm,[],options);
      
        % 判断是否有可行解，无可行解u(k)=u(k-1)
        % 根据EXITFLAG是否等于1，判断非线性规划的解是否收敛
        
        % 提取优化结果,并反归一化
        O2_opt_inc = duM(1)*(2*norm_limit_O2)-norm_limit_O2;
        Fuel_opt_inc = duM(2:7)*(2*norm_limit_Fuel)-norm_limit_Fuel;
        Sec_opt_inc = duM(8:13)*(2*norm_limit_Sec)-norm_limit_Sec;
        Sofa_opt_inc = duM(14:15)*(2*norm_limit_Sofa)-norm_limit_Sofa;
        Fp_opt_inc = duM(16)*(2*norm_limit_Fp)-norm_limit_Fp;
   
        % 对增量强制速率约束
        O2_opt_inc(O2_opt_inc<-lim_rO2) = -lim_rO2;
        Fuel_opt_inc(Fuel_opt_inc<-lim_rFuel) = -lim_rFuel(Fuel_opt_inc<-lim_rFuel);
        Sec_opt_inc(Sec_opt_inc<-lim_rSec) = -lim_rSec(Sec_opt_inc<-lim_rSec);   
        Sofa_opt_inc(Sofa_opt_inc<-lim_rSofa) = -lim_rSofa(Sofa_opt_inc<-lim_rSofa);
        Fp_opt_inc(Fp_opt_inc<-lim_rFp) = -lim_rFp(Fp_opt_inc<-lim_rFp);
 
        O2_opt_inc(O2_opt_inc>lim_rO2) = lim_rO2;
        Fuel_opt_inc(Fuel_opt_inc>lim_rFuel) = lim_rFuel(Fuel_opt_inc>lim_rFuel);
        Sec_opt_inc(Sec_opt_inc>lim_rSec) = lim_rSec(Sec_opt_inc>lim_rSec);   
        Sofa_opt_inc(Sofa_opt_inc>lim_rSofa) = lim_rSofa(Sofa_opt_inc>lim_rSofa);
        Fp_opt_inc(Fp_opt_inc>lim_rFp) = lim_rFp(Fp_opt_inc>lim_rFp);    
         
        % 可能造成增量不满足等式约束，强制等式约束
%         Non_zero = sum(Fuel_opt_inc);  % 增量之和
%         if (Non_zero>0.01)
%             Fuel_opt_inc(MillState) = Fuel_opt_inc(MillState) - Non_zero/sum(MillState);
%         end
       
        IO(119)=QP_Flag;  % sqp求解状态
        if QP_Flag>=0  % sqp优化得到局部最优解
            % 小于死区的增量置0，这一步在C++中实现
%             
            O2_opt_inc(abs(O2_opt_inc)<dz_O2)=0;
            Fuel_opt_inc(abs(Fuel_opt_inc)<dz_Fuel)=0;
            Sec_opt_inc(abs(Sec_opt_inc)<dz_Sec)=0;
            Sofa_opt_inc(abs(Sofa_opt_inc)<dz_Sofa)=0;
            Fp_opt_inc(abs(Fp_opt_inc)<dz_Fp)=0;     
            % du=[eye(contrl_num),zeros(contrl_num, contrl_num*M-contrl_num)]*duM;
            % 得到的优化偏置
            if (O2_switch)   % 若co满足要求 pid不投入的时候，取结算结果
                O2_opt_bias_k=O2_opt_bias_k1+O2_opt_inc;
            else 
              %% O2控制，CO的PI控制器,O2_switch使用
                Co_Kp = OP(285);
                Co_Ki = OP(286);
                PI_max_Co = OP(287);
                PI_min_Co = OP(288);
                if CO_k>PI_max_Co
                    eCO_k = CO_k-PI_max_Co;
                elseif CO_k<PI_min_Co
                    eCO_k = CO_k-PI_min_Co;
                else
                    eCO_k = 0;
                end
                O2_opt_inc = Co_Kp*(eCO_k-eCO_k1)+Co_Ki*eCO_k;  % PID控制器得到的O2的增量
                % 对 O2_opt_inc 做约束处理
                if O2_opt_inc>ub(1)
                    O2_opt_inc=ub(1);
                elseif O2_opt_inc<lb(1)
                    O2_opt_inc=lb(1);
                end
                O2_opt_bias_k=O2_opt_bias_k1+O2_opt_inc;
            end
            
            Fuel_opt_bias_k=Fuel_opt_bias_k1+Fuel_opt_inc;
            Sec_opt_bias_k=Sec_opt_bias_k1+Sec_opt_inc;
            Sofa_opt_bias_k=Sofa_opt_bias_k1+Sofa_opt_inc;
            Fp_opt_bias_k=Fp_opt_bias_k1+Fp_opt_inc; 
        else  % 无解时保持上一时刻的控制量
            O2_opt_bias_k=O2_opt_bias_k1;
            Fuel_opt_bias_k=Fuel_opt_bias_k1;
            Sec_opt_bias_k=Sec_opt_bias_k1;
            Sofa_opt_bias_k=Sofa_opt_bias_k1; 
            Fp_opt_bias_k=Fp_opt_bias_k1;     
            % C++中采用增量时 ，无解全部为0
            O2_opt_inc=0;
            Fuel_opt_inc=zeros(6,1);
            Sec_opt_inc=zeros(6,1);
            Sofa_opt_inc=zeros(2,1);
            Fp_opt_inc=0;
         end
        Fuel_opt_bias_k=Fuel_opt_bias_k+coef.*deltaU;  % 强制增量（取的0）,全量无手偏时考虑  % 功能无用
        %% 气温偏差
        if Rtem_k>u_Rtem   %  track中的upLimit_Rtem
            eRtem_k=Rtem_k-u_Rtem;
        elseif Rtem_k<d_Rtem
            eRtem_k=Rtem_k-d_Rtem;
        else
            eRtem_k=0;
        end
        %% 只考虑汽温PID控制器
        %超温 eRtem_k为正 du_SupTem为正 上减下加
        %低温 eTk为负 du_SupTem为负 上加下减
        %SupTem_Kp = OP(0);
        %SupTem_Ki = Op(0);
        %du_SupTem = SupTem_Kp*(eRtem_k-eRtem_k1)+SupTem_Ki*eRtem_k;  % 增量式PID 得到的是△u
        %du_coalbias=du_SupTem;
   
        %---------切换式需要加速率限制，目前叠加式不需要---------2019.08.22
        %         if abs(du_coalbais) > min(lim_dAMillBias,min(lim_dBMillBias,min(lim_dCMillBias,lim_dDMillBias)))
        %             du_coalbais = sign(du_coalbais)*min(lim_dAMillBias,min(lim_dBMillBias,min(lim_dCMillBias,lim_dDMillBias)));
        %         end
        %------------------------------------------------------
       
        %---------四层磨-----三层磨------2019.08.21.css.增加了判断最小余量
        % 需要确认是否有两层磨运行的情况
        %{
        if millnum==4
            if du_coalbais>0
                du_coalbaismax1=uu(1)-umin(1)+uu(2)-umin(2);
                du_coalbaismax2=umax(3)-uu(3)+umax(4)-uu(4);
                du_coalbaismax=min(du_coalbaismax1,du_coalbaismax2);
                du_coalbais=min(du_coalbais,du_coalbaismax);
                %上层减下层加
                uu(1) = uu(1) - du_coalbais; %减
                if uu(1)<umin(1)
                    uu(2) = uu(2)-(umin(1)-uu(1));
                    uu(1) = umin(1);
                    if  uu(2)<umin(2)
                        uu(2) = umin(2) ;
                    end
                end
                
                uu(4) = uu(4) + du_coalbais;%加
                if uu(4)>umax(4)
                    uu(3) = uu(3)+uu(4)-umax(4);
                    uu(4) = umax(4);
                    if uu(3)>umax(3)
                        uu(3) = umax(3);
                    end
                end
                
            else
                du_coalbaismax1=umax(1)-uu(1)+umax(2)-uu(2);
                du_coalbaismax2=uu(3)-umin(3)+uu(4)-umin(4);
                du_coalbaismax=min(du_coalbaismax1,du_coalbaismax2);
                du_coalbais=-min(-du_coalbais,du_coalbaismax);
                %上层加下层减
                uu(1) = uu(1) - du_coalbais;%加
                if uu(1)>umax(1)
                    uu(2) = uu(2)+(uu(1)-umax(1));
                    uu(1) = umax(1);
                    if uu(2)>umax(2)
                        uu(2) = umax(2);
                    end
                end
                
                uu(4) = uu(4) + du_coalbais;%减
                if uu(4)<umin(4)
                    uu(3) = uu(3)-(umin(4)-uu(4));
                    uu(4) = umin(4);
                    if uu(3)<umin(3)
                        uu(3) = umin(3);
                    end
                end
            end
            
            
            
        elseif millnum==3%%上面两层有一层要减，下面两层有一层要加
            if du_coalbais>0
                if IO(1)==1
                    du_coalbaismax1=uu(1)-umin(1);
                elseif IO(2)==1
                    du_coalbaismax1=uu(2)-umin(2);
                end
                if IO(4)==1
                    du_coalbaismax2=umax(4)-uu(4);
                elseif IO(3)==1
                    du_coalbaismax2=umax(3)-uu(3);
                end
                du_coalbaismax=min(du_coalbaismax1,du_coalbaismax2);
                du_coalbais=min(du_coalbais,du_coalbaismax);
                %上层减下层加
                if IO(1)==1
                    uu(1) = uu(1) - du_coalbais;
                else
                    uu(2) = uu(2) - du_coalbais;
                end
                if  IO(4)==1
                    uu(4) = uu(4) + du_coalbais;
                else
                    uu(3) = uu(3) + du_coalbais;
                end
                
            else
                if IO(1)==1
                    du_coalbaismax1=umax(1)-uu(1);
                elseif IO(2)==1
                    du_coalbaismax1=umax(2)-uu(2);
                end
                if IO(4)==1
                    du_coalbaismax2=uu(4)-umin(4);
                elseif IO(3)==1
                    du_coalbaismax2=uu(3)-umin(3);
                end
                du_coalbaismax=min(du_coalbaismax1,du_coalbaismax2);
                du_coalbais=-min(-du_coalbais,du_coalbaismax);
                %上层加下层减
                if IO(1)==1
                    uu(1) = uu(1) - du_coalbais;
                else
                    uu(2) = uu(2) - du_coalbais;
                end
                if  IO(4)==1
                    uu(4) = uu(4) + du_coalbais;
                else
                    uu(3) = uu(3) + du_coalbais;
                end
            end
        end
        
        %---------四层磨-----三层磨------2019.08.21.css.增加了判断最小余量
        %}
       %% 汽温和负荷快速变化控制器
       %% 给煤机满煤约束 81.9t/h--------之后需要替换煤量需求总量最大值
        %         if (uu(1) > (81.9 -2*IO(87) - IO(107)- IO(108)))
        %             uu(1) = 81.9 - 2*IO(87) - IO(107);
        %         end
        %
        %         if (uu(2) > (81.9 - 2*IO(87) - IO(109)- IO(110)))
        %             uu(2) = 81.9 - 2*IO(87) - IO(108);
        %         end
        %
        %         if (uu(3) > (81.9 - 2*IO(87) - IO(111)- IO(112)))
        %             uu(3) = 81.9 - 2*IO(87) - IO(109);
        %           end
        %
        %         if (uu(4) > (81.9 - 2*IO(87) - IO(113)- IO(114)))
        %             uu(4) = 81.9 - 2*IO(87) - IO(110);
        %         end
        % ↓↓ 2018-01-03+_by_HYF
        %——————————————2019.8.9  hp修改————————————————————————
        % 右边所有量要进行归一化，或者对左边控制量进行反归一化后再归一化
        % 不能超过最大给煤量
        err=(Fuel_opt_bias_k + Fuel_fnb_k)>COALmax_mill;
        mid=(COALmax_mill-Fuel_fnb_k);
        Fuel_opt_bias_k(err)=mid(err);
        %% SQP优化算法，最后输出 Var_opt_bias_k 再加一道约束
        % 优化区间下界约束
        % 优化区间上下限,重新读一遍
        
%         u_Sofa=OP(20:21); u_Sec=OP(22:34); u_O2=OP(35); u_Fuel=OP(36:41); u_Fp=OP(208);
%         l_Sofa =OP(42:43); l_Sec=OP(44:56); l_O2=OP(57); l_Fuel=OP(58:63); l_Fp=OP(209);
%         O2_opt_bias_k(O2_opt_bias_k<l_O2)=l_O2;
%         Fuel_opt_bias_k(Fuel_opt_bias_k<l_Fuel)=l_Fuel(Fuel_opt_bias_k<l_Fuel);
%         Sec_opt_bias_k(Sec_opt_bias_k<l_Sec)=l_Sec(Sec_opt_bias_k<l_Sec);
%         Sofa_opt_bias_k(Sofa_opt_bias_k<l_Sofa)=l_Sofa(Sofa_opt_bias_k<l_Sofa);
%         Fp_opt_bias_k(Fp_opt_bias_k<l_Fp)=l_Fp(Fp_opt_bias_k<l_Fp);
%          
%         优化区间上界约束
%         O2_opt_bias_k(O2_opt_bias_k>u_O2)=u_O2(O2_opt_bias_k>u_O2);
%         Fuel_opt_bias_k(Fuel_opt_bias_k>u_Fuel)=u_Fuel(Fuel_opt_bias_k>u_Fuel);
%         Sec_opt_bias_k(Sec_opt_bias_k>u_Sec)=u_Sec(Sec_opt_bias_k>u_Sec);
%         Sofa_opt_bias_k(Sofa_opt_bias_k>u_Sofa)=u_Sofa(Sofa_opt_bias_k>u_Sofa);
%         Fp_opt_bias_k(Fp_opt_bias_k>u_Fp)=u_Fp(Fp_opt_bias_k>u_Fp);
    
        % 绝对上界约束
        err=(O2_opt_bias_k+O2_fnb_k)>au_O2;  %  氧量
        mid=au_O2-O2_fnb_k;
        O2_opt_bias_k(err)=mid(err); % 此时输出的绝对量
        
        err=(Fuel_opt_bias_k+Fuel_fnb_k)>au_Fuel;  % Fuel
        mid=au_Fuel-Fuel_fnb_k;
        Fuel_opt_bias_k(err)=mid(err);
        
        err=(Sec_opt_bias_k+Sec_fnb_k)>au_Sec;  % Sec
        mid=au_Sec-Sec_fnb_k;
        Sec_opt_bias_k(err)=mid(err);
        
        err=(Sofa_opt_bias_k+Sofa_fnb_k)>au_Sofa;  % Sofa
        mid=au_Sofa-Sofa_fnb_k;
        Sofa_opt_bias_k(err)=mid(err);
        
        err=(Fp_opt_bias_k+Fp_fnb_k)>au_Fp;  % Fp
        mid=au_Fp-Fp_fnb_k;
        Fp_opt_bias_k(err)=mid(err);
        
        
        % 绝对下届约束
        O2_opt_bias_k((O2_opt_bias_k+O2_fnb_k)<al_O2)=al_O2-O2_fnb_k;  % 此时输出的绝对量
        err=(Fuel_opt_bias_k+Fuel_fnb_k)<al_Fuel;
        mid=al_Fuel-Fuel_fnb_k;
        Fuel_opt_bias_k(err)=mid(err);
        
        err=(Sec_opt_bias_k+Sec_fnb_k)<al_Sec;
        mid=al_Sec-Sec_fnb_k;
        Sec_opt_bias_k(err)=mid(err);
        
        err=(Sofa_opt_bias_k+Sofa_fnb_k)<al_Sofa;
        mid=al_Sofa-Sofa_fnb_k;
        Sofa_opt_bias_k(err)=mid(err);
        
        Fp_opt_bias_k((Fp_opt_bias_k+Fp_fnb_k)<al_Fp)=al_Fp-Fp_fnb_k;
      
        % 可能造成增量不满足等式约束，强制等式约束
        Non_zero = sum(Fuel_opt_bias_k);  % 增量之和
        if abs(Non_zero)>0.01
            Fuel_opt_bias_k(MillState) = Fuel_opt_bias_k(MillState) - Non_zero/sum(MillState);
        end
         
%         % 速率上限约束
%         O2_opt_bias_k((O2_opt_bias_k-O2_opt_bias_k1)>lim_rO2)=O2_opt_bias_k1+lim_rO2;
%         Fuel_opt_bias_k((Fuel_opt_bias_k-Fuel_opt_bias_k1)>lim_rFuel)=Fuel_opt_bias_k1+lim_rFuel;
%         Sec_opt_bias_k((Sec_opt_bias_k-Sec_opt_bias_k1)>lim_rSec)=Sec_opt_bias_k1+lim_rSec;
%         Sofa_opt_bias_k((Sofa_opt_bias_k-Sofa_opt_bias_k1)>lim_rSofa)=Sofa_opt_bias_k1+lim_rSofa;
% 
%         % 速率下限约束
%         O2_opt_bias_k((O2_opt_bias_k-O2_opt_bias_k1)>lim_rO2)=O2_opt_bias_k1+lim_rO2;
%         Fuel_opt_bias_k((Fuel_opt_bias_k-Fuel_opt_bias_k1)>lim_rFuel)=Fuel_opt_bias_k1+lim_rFuel;
%         Sec_opt_bias_k((Sec_opt_bias_k-Sec_opt_bias_k1)>lim_rSec)=Sec_opt_bias_k1+lim_rSec;
%         Sofa_opt_bias_k((Sofa_opt_bias_k-Sofa_opt_bias_k1)>lim_rSofa)=Sofa_opt_bias_k1+lim_rSofa;

        % 全量中k-1时刻控制量更新采用此时模型的输出，但是增量模型与全量存在区别
        % 采用实际控制量，因为f(x)+s_bias是DCS系统决定的，只有优化bias可控。
        IO(385:400)=[O2_opt_bias_k;Fuel_opt_bias_k;Sec_opt_bias_k;Sofa_opt_bias_k;Fp_opt_bias_k];   
        %IO(434)=Fp_opt_bias_k;  % 优化偏置
        %IO(458)=Fangle_opt_bias_k;  % 优化偏置
        
        % 优化增量
        IO(410:425)=[O2_opt_inc;Fuel_opt_inc;Sec_opt_inc;Sofa_opt_inc;Fp_opt_inc];
        % 一次风压优化输出
        %IO(435)=Fp_opt_inc;
        % 燃烧器摆角
        %IO(459)=Fangle_opt_inc;
        %IO(20:29)=IO(30:39);  % k-2时刻控制量=k-1时刻空置量
        IO(157)=0;  % 爬山次数
        IO(158)=Nox_k;  % 爬山算法中的广义前一时刻NOx
    else  % 爬山寻优算法
        %{
        QP_Flag=1;
        uu(1)=uu(1)*(max_MillBias-min_MillBias)+min_MillBias;
        uu(2)=uu(2)*(max_MillBias-min_MillBias)+min_MillBias;
        uu(3)=uu(3)*(max_MillBias-min_MillBias)+min_MillBias;
        uu(4)=uu(4)*(max_MillBias-min_MillBias)+min_MillBias;
        uu(5)=uu(5)*(max_SecAir-min_SecAir)+min_SecAir;
        uu(6)=uu(6)*(max_SecAir-min_SecAir)+min_SecAir;
        uu(7)=uu(7)*(max_SecAir-min_SecAir)+min_SecAir;
        uu(8)=uu(8)*(max_SecAir-min_SecAir)+min_SecAir;
        uu(9)=uu(9)*(max_OFA-min_OFA)+min_OFA;
        uu(10)=uu(10)*(max_O2-min_O2)+min_O2;
        HC_Cycle=Op(177);%5
        HC_Count=IO(101);
        if HC_Count==0
            HC_u_k_2=uuu';
            HC_u_k_1=uu';
            HC_u_k=uu';
            HC_u_min=[l_AMillBias;l_BMillBias;l_CMillBias;l_DMillBias;l_ASecAir;l_BSecAir;l_CSecAir;l_DSecAir;l_OFA;l_O2];
            HC_u_max=[u_AMillBias;u_BMillBias;u_CMillBias;u_DMillBias;u_ASecAir;u_BSecAir;u_CSecAir;u_DSecAir;u_OFA;u_O2];
            HC_u_min=IO(59:68)'-HC_u_min;    %优化上限
            HC_u_max=IO(59:68)'+HC_u_max;    %优化下限
            HC_O2_Count=IO(95);              %氧量爬山寻优次数
            HC_Air_Count=IO(96);             %氧量爬山寻优次数
            HC_Bias_Count=IO(97);            %氧量爬山寻优次数
            %% 完成一次寻优周期，复位
            if ((HC_O2_State && HC_O2_Count>HC_MaxOptNum)||(~HC_O2_State))&&((HC_Air_State && HC_Air_Count>HC_MaxOptNum)||(~HC_Air_State))&&((HC_Bias_State && HC_Bias_Count>HC_MaxOptNum)||(~HC_Bias_State))
                HC_O2_Count=0;
                HC_Air_Count=0;
                HC_Bias_Count=0;
                IO(95)=HC_O2_Count;
                IO(96)=HC_Air_Count;
                IO(97)=HC_Bias_Count;
            end
            %% 氧量爬山
            if ~HC_O2_State
                HC_O2_Count=0;
                IO(95)=HC_O2_Count;
            end
            if HC_O2_State && HC_O2_Count<=HC_MaxOptNum
                HC_deltaO2_k_1=HC_u_k_1(10)-HC_u_k_2(10);
                if HC_deltaO2_k_1~=0
                    HC_deltaO2_k=-HC_O2_C*(IO(8)-IO(102))/HC_deltaO2_k_1;%计算当前时刻增量
                    if abs(HC_deltaO2_k)>lim_dO2
                        HC_deltaO2_k=sign(HC_deltaO2_k)*lim_dO2;
                    end
                else
                    HC_deltaO2_k=lim_dO2;
                end
                HC_u_k(10)=HC_u_k_1(10)+HC_deltaO2_k;
                HC_u_k((HC_u_k>HC_u_max)==1)=HC_u_max((HC_u_k>HC_u_max)==1);
                HC_u_k((HC_u_k<HC_u_min)==1)=HC_u_min((HC_u_k<HC_u_min)==1);
                uu=HC_u_k;
                HC_O2_Count=HC_O2_Count+1;
                HC_Air_Count=0;
                HC_Bias_Count=0;
                IO(95)=HC_O2_Count;
                IO(96)=HC_Air_Count;
                IO(97)=HC_Bias_Count;
                IO(98)=HC_deltaO2_k;
            end
            %% 风量爬山
            if ~HC_Air_State
                HC_Air_Count=0;
                IO(96)=HC_Air_Count;
            end
            if HC_Air_State && HC_Air_Count<=HC_MaxOptNum
                if (HC_O2_State && HC_O2_Count>HC_MaxOptNum)||(~HC_O2_State)
                    HC_deltaAir_k_1=HC_u_k_1(9)-HC_u_k_2(9);
                    if HC_deltaAir_k_1~=0
                        HC_deltaAir_k=-HC_Air_C*(IO(8)-IO(102))/HC_deltaAir_k_1;%计算当前时刻增量
                        if abs(HC_deltaAir_k)>lim_dOFA
                            HC_deltaAir_k=sign(HC_deltaAir_k)*lim_dOFA;
                        end
                    else
                        HC_deltaAir_k=lim_dOFA;
                    end
                    HC_u_k(5)=HC_u_k_1(5)+HC_deltaAir_k;
                    HC_u_k(6)=HC_u_k_1(6)+HC_deltaAir_k;
                    HC_u_k(9)=HC_u_k_1(9)+HC_deltaAir_k;
                    HC_u_k(7:8)=HC_u_k(7:8)-HC_deltaAir_k;
                    HC_u_k((HC_u_k>HC_u_max)==1)=HC_u_max((HC_u_k>HC_u_max)==1);
                    HC_u_k((HC_u_k<HC_u_min)==1)=HC_u_min((HC_u_k<HC_u_min)==1);
                    uu=HC_u_k;
                    HC_Air_Count=HC_Air_Count+1;
                    HC_Bias_Count=0;
                    IO(96)=HC_Air_Count;
                    IO(97)=HC_Bias_Count;
                    IO(99)=HC_deltaAir_k;
                end
            end
            %% 给煤偏置爬山
            if ~HC_Bias_State
                HC_Bias_Count=0;
                IO(97)=HC_Bias_Count;
            end
            if HC_Bias_State && HC_Bias_Count<=HC_MaxOptNum
                if ((HC_O2_State && HC_O2_Count>HC_MaxOptNum)||(~HC_O2_State))&&((HC_Air_State && HC_Air_Count>HC_MaxOptNum)||(~HC_Air_State))
                    HC_deltaBias_k_1=HC_u_k_1(2)-HC_u_k_2(2);
                    if HC_deltaBias_k_1~=0
                        HC_deltaBias_k=-HC_Bias_C*(IO(8)-IO(102))/HC_deltaBias_k_1;%计算当前时刻增量
                        if abs(HC_deltaBias_k)>lim_dMedMillBias
                            HC_deltaBias_k=sign(HC_deltaBias_k)*lim_dMedMillBias;
                        end
                    else
                        HC_deltaBias_k=lim_dMedMillBias;
                    end
                    HC_u_k(1)=HC_u_k_1(1)-HC_deltaBias_k;
                    HC_u_k(2)=HC_u_k_1(2)-HC_deltaBias_k;
                    HC_u_k(3)=HC_u_k_1(3)+HC_deltaBias_k;
                    HC_u_k(4)=HC_u_k_1(4)+HC_deltaBias_k;
                    HC_u_k((HC_u_k>HC_u_max)==1)=HC_u_max((HC_u_k>HC_u_max)==1);
                    HC_u_k((HC_u_k<HC_u_min)==1)=HC_u_min((HC_u_k<HC_u_min)==1);
                    uu=HC_u_k;
                    HC_Bias_Count=HC_Bias_Count+1;
                    IO(100)=HC_deltaBias_k;
                    IO(97)=HC_Bias_Count;
                end
            end
            HC_Count=HC_Count+1;
            IO(20:29)=IO(30:39);
            IO(102)=IO(8);
        else
            uu=uu';
            HC_Count=HC_Count+1;
        end
        if HC_Count>=HC_Cycle
            HC_Count=0;
        end
        IO(101)=HC_Count;
        %}
        QP_Flag=1;
    end
else  % IO未初始化完成时
    
    QP_Flag=1;  % SQP算法初始化时，默认为1
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
    
    % Cfh
    %StaCRenew_Cfh = 0;
    %NumCRenew_Cfh = 0;
    %rX_Cfh = X_Cfh;
    %rY_Cfh = Y_Cfh;
    %rAlfa_Cfh = [Alfa_Cfh; b_Cfh];
    %rH_Cfh = H_Cfh;
    % 在启动赋值阶段将绝对上下限保存为IO中上下限和速率，避免出现IO均为0，c中执行最终约束时全关到0
    % 绝对上限
    %IO(191:212)=OP(245:266);
    % 绝对下限
    %IO(213:234)=OP(223:244);
    % 速率
    %IO(235:256)=OP(64:85);
end

%% 调试时仿真测试优化效果
%     %归一化
%     uu_opti(1)=(uu(1)-min_MillBias)/(max_MillBias-min_MillBias);
%     uu_opti(2)=(uu(2)-min_MillBias)/(max_MillBias-min_MillBias);
%     uu_opti(3)=(uu(3)-min_MillBias)/(max_MillBias-min_MillBias);
%     uu_opti(4)=(uu(4)-min_MillBias)/(max_MillBias-min_MillBias);
%     uu_opti(5)=(uu(5)-min_SecAir)/(max_SecAir-min_SecAir);
%     uu_opti(6)=(uu(6)-min_SecAir)/(max_SecAir-min_SecAir);
%     uu_opti(7)=(uu(7)-min_SecAir)/(max_SecAir-min_SecAir);
%     uu_opti(8)=(uu(8)-min_SecAir)/(max_SecAir-min_SecAir);
%     uu_opti(9)=(uu(9)-min_OFA)/(max_OFA-min_OFA);
%     uu_opti(10)=(uu(10)-min_O2)/(max_O2-min_O2);
% 
%     %排烟温度预测
%     Input_BoiEff=[uu_opti(1:10),Load_k1,Tpy_k2,Tpy_k1];
%     a=repmat(Input_BoiEff,NumSupVec_BoiEff,1)-rX_BoiEff;
%     dist=sum(a.*a,2);
%     K_BoiEff=exp(-dist/2/(delta_BoiEff*delta_BoiEff))';
%     P_BoiEff_k=K_BoiEff*Alfa_BoiEff+b_BoiEff;
% 
% 
%     %对k时刻飞灰含碳预测
%     Input_cfh=[uu_opti(1:10),Load_k1,cfh_1];%k-1时刻烟温绝对量模型输入
%     a=repmat(Input_cfh,NumSupVec_cfh,1)-rX_cfh;
%     dist=sum(a.*a,2);
%     k_cfh=exp(-dist/2/(delta_cfh*delta_cfh))';
%     P_cfh_k=k_cfh*Alfa_cfh+b_cfh;
% 
%     P_BoiEff_k=(P_BoiEff_k)*(max_BoiEff-min_BoiEff)+min_BoiEff;
%     P_cfh_k=(P_cfh_k)*(max_cfh-min_cfh)+min_cfh;
% 
%     Cpy=0.8967+0.0013*P_BoiEff_k-0.000003*P_BoiEff_k*P_BoiEff_k;  %烟气比热
%     Sg=Vgy*Cpy*(P_BoiEff_k-20)/Qnet;   %干烟气热损失
% 
%     V_H2O=1.24*((9*h+Mar)+1.293*ALPHA*Vgk0*0.001);
%     Q_H2O=V_H2O*1.5093*(P_BoiEff_k-20);
%     Sm=Q_H2O/Qnet;   %水分热损失
% 
%     Suc=337.27*100*Aar/Qnet*P_cfh_k./(100-P_cfh_k);  %飞灰含碳热损失
%     IO(187)=0.9917-Suc-Sm-Sg;

%% 返回时设置IO，数据维护
IO(294)=Load_k1;  % k-2时刻负荷更新
IO(9)=Load_k;  % k-1时刻负荷更新
IO(119)=QP_Flag;

IO(461:462) = IO(460:461);  %  k-1、k-2时刻Smax更新，维护数据
IO(446:447)=IO(445:446);  % k-1、k-2、k-3时刻CO更新，维护数据
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
IO(265)=cfh_L_k;  % 上一时刻AB侧飞灰，维护数据,不用维护，仅需维修k时飞灰含碳
IO(266)=cfh_R_k;

% 右侧飞灰测量值上一次变化时对应的模型输入量（归一化后的值）用于飞灰模型更新
% IO(267:289)=u_cfh;
IO(290)=flag_cfh;   % 表示上个时刻飞灰含碳是否更新
%% 逻辑维护
% 根据Flag奇偶性交替选择更新策略
if Flag == 0
    Flag=1;
else
    Flag=0;
end

IO(7)=1;  % ComError 组件工作状态标志
% Smax、CO、NOx、效率、烟温模型连续更新次数
IO(464)=NumCRenew_Smax; IO(437)=NumCRenew_CO; IO(88)=NumCRenew_Nox; IO(89)=NumCRenew_Etem;  IO(90)=NumCRenew_Rtem; 
% Smax、CO、NOx、效率、烟温模型连续更新状态标志
IO(466)=StaCRenew_Smax; IO(448)=StaCRenew_CO; IO(91)=StaCRenew_Nox; IO(92)=StaCRenew_Etem; IO(93)=StaCRenew_Rtem; 
% Smax、CO、NOx、Etem、Rtem预测偏差
IO(465)=e_Smax_k; IO(438)=e_CO_k; IO(120)=e_Nox_k; IO(121)=e_Etem_k; IO(122)=e_Rtem_k;
% Smax、CO、NOx、效率、烟温累计预测偏差
IO(467)=e_Smax_sum; IO(449)=e_CO_sum; IO(147)=e_Nox_sum; IO(148)=e_Etem_sum; IO(149)=e_Rtem_sum; %IO(449)=e_CO_sum; 

IO(162)=eRtem_k;  % k-1时刻汽温偏差值 PI用，归一化
IO(176)=eCO_k; % k-1刻，CO偏差 PI用 ，未归一化
IO(177)=Load_change_State;  % 系统负荷变动状态

% 预测误差list返回
% rListError_CO=ListError_CO;
% rListError_Nox=ListError_Nox; 
% rListError_Etem=ListError_Etem;
% rListError_Rtem=ListError_Rtem; 
% rListError_Cfh=ListError_Cfh;

% IO返回
rIO=IO;

%% 多模型参数返回
% 模型参数返回
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
        
        



