function J=CostFunction(duM,P,M,...
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
u_opt_bias_norm,norm_limit_var,opt_bias_k1,u_Var,norm_limit_Smax,norm_limit_CO,norm_limit_Nox,norm_limit_Etem,norm_limit_Rtem)

%% 输入数据构建 默认M=1,第一步时，不加入任何duM，全为真实数据  %第一步输入全为k时刻值或k-4时刻值
%Input_Load = ones(P,1)*Load_inc_k_norm; 
control_num = 16;
if M == 1
    Input_Load =ones(P,1)*0.5;
    Input_Load(1)= Load_inc_k_norm;
    
    Input_O2 = ones(P,1)*0.5;  % 归一化后0为0.5
    Input_O2(1,1)=O2_inc_k_norm;  %Input_O2(1,2)=O2_inc_k1_norm;Input_O2(1,3)=O2_inc_k2_norm;
    Input_O2(2,1)=duM(1);  %Input_O2(2,2)=O2_inc_k_norm; Input_O2(2,3)=O2_inc_k1_norm;
    %Input_O2(3,2)=duM(1); Input_O2(3,3)=O2_inc_k_norm;
    %Input_O2(4,3)=duM(1);  % O2优化x 

    Input_Fuel = ones(P,6)*0.5;
    Input_Fuel(1:5,:)= Fuel_inc_k4_k_norm;
    Input_Fuel(6,:)= duM(2:7)';  % 给煤量优化x

    Input_Sec = ones(P,6)*0.5;
    Input_Sec(1:5,:)= Sec_inc_k4_k_norm;
    Input_Sec(6,:)= duM(8:13)';

    Input_Sofa = ones(P,2)*0.5;
    Input_Sofa(1:5,:)= Sofa_inc_k4_k_norm;
    Input_Sofa(6,:)= duM(14:15)';

    Input_Fp = ones(P,1)*0.5;
    Input_Fp(1:5,:)= Fp_inc_k4_k_norm;
    Input_Fp(6,:)= duM(16)';
else
    Input_Load =ones(P,1)*0.5;
    Input_Load(1)= Load_inc_k_norm;
    
    Input_O2 = ones(P,1)*0.5;  % 归一化后0为0.5
    Input_O2(1,1)=O2_inc_k_norm;  % 第一步为k时刻采集样本值
    % Input_O2(2,1)=duM(1);
    for i = 1:M  % M步控制
        Input_O2(i+1,1)=duM((i-1)*control_num+1)';  % O2量多步
    end

    Input_Fuel = ones(P,6)*0.5;
    Input_Fuel(1:5,:)= Fuel_inc_k4_k_norm;
    % Input_Fuel(6,:)= duM(2:7)';  % 给煤量优化x
    for i = 1:M
        Input_Fuel(5+i,:)= duM((i-1)*control_num+2:(i-1)*control_num+7)';  % 给煤量优化x
    end
    
    Input_Sec = ones(P,6)*0.5;
    Input_Sec(1:5,:)= Sec_inc_k4_k_norm;
    % Input_Sec(6,:)= duM(8:20)';
    for i = 1:M
        Input_Sec(5+i,:)= duM((i-1)*control_num+8:(i-1)*control_num+13)'; 
    end

    Input_Sofa = ones(P,2)*0.5;
    Input_Sofa(1:5,:)= Sofa_inc_k4_k_norm;
    % Input_Sofa(6,:)= duM(21:22)';
    for i = 1:M
        Input_Sofa(5+i,:)= duM((i-1)*control_num+14:(i-1)*control_num+15)'; 
    end
    
    Input_Fp = ones(P,1)*0.5;
    Input_Fp(1:5,:)= Fp_inc_k4_k_norm;
    % Input_Fp(6,:)= duM(23)';
    for i = 1:M
        Input_Fp(5+i,:)= duM((i-1)*control_num+16)'; 
    end     

end

%% 分隔屏最高温度 费县该项为O2量绝对偏差，此偏差应该越小越好
Smax=zeros(1,P+1);  % 预测的增量保存,归一化后的结果
Smax(1)=Smax_inc_k_norm;
Smax_iter=Smax(1);
for i=1:P
    Input_Nox=[Input_Load(i),Input_O2(i,:),Input_Fuel(i,:),Input_Sec(i,:),Input_Sofa(i,:),Input_Fp(i,:),Smax_iter]; % 从第k时刻开始
    a=repmat(Input_Nox,NumSupVec_Smax,1)-X_Smax;
    dist=sum(a.*a,2);
    K=exp(-dist*Delta_Smax)';
    Smax(1+i)=K*Alfa_Smax+b_Smax-e_Smax_k;  % k时刻NOx预测值 增量且未归一化 加入反馈校正后的k+1时刻效率的估计值
    Smax_iter=(Smax(1+i)+norm_limit_Smax)/(2*norm_limit_Smax);
end
% 建模时，预测增量值未归一化处理，直接求全量
Smax(1) = Smax(1) + Smax_k1;
for i=1:P
    Smax(i+1)=Smax(i+1)+Smax(i);
end
%% 排烟温度预测
Etem=zeros(1,P+1);  % 预测的增量保存,归一化后的结果
Etem(1)=Etem_inc_k_norm;
Etem_iter=Etem(1);
for i=1:P
    Input_Nox=[Input_Load(i),Input_O2(i,:),Input_Fuel(i,:),Input_Sec(i,:),Input_Sofa(i,:),Input_Fp(i,:),Etem_iter];
    a=repmat(Input_Nox,NumSupVec_Etem,1)-X_Etem;
    dist=sum(a.*a,2);
    K=exp(-dist*Delta_Etem)';
    Etem(1+i)=K*Alfa_Etem+b_Etem-e_Etem_k;  % k时刻NOx预测值 增量且未归一化 加入反馈校正后的k+1时刻效率的估计值
    Etem_iter=(Etem(1+i)+norm_limit_Etem)/(2*norm_limit_Etem);
end
% 建模时，预测增量值未归一化处理，直接求全量
Etem(1) = Etem(1) + Etem_k1;
for i=1:P
    Etem(i+1)=Etem(i+1)+Etem(i);
end
% Je=sum(E(3:P+2));%未来P个效率预测值的累加和，下标从3开始
% %排烟温度越低越好，所以去掉负号

%% CO估计飞灰含碳
CO=zeros(1,P+1);  % 预测的增量保存,归一化后的结果
CO(1)=CO_inc_k_norm;
CO_iter=CO(1);
for i=1:P
    Input_CO=[Input_Load(i),Input_O2(i,:),Input_Fuel(i,:),Input_Sec(i,:),Input_Sofa(i,:),Input_Fp(i,:),CO_iter];
    a=repmat(Input_CO,NumSupVec_CO,1)-X_CO;
    dist=sum(a.*a,2);
    K=exp(-dist*Delta_CO)';
    CO(1+i)=K*Alfa_CO+b_CO-e_CO_k;  % k时刻NOx预测值 增量且未归一化 加入反馈校正后的k+1时刻效率的估计值
    CO_iter=(CO(1+i)+norm_limit_CO)/(2*norm_limit_CO);
end
% 建模时，预测增量值未归一化处理，直接求全量
CO(1) = CO(1) + CO_k1;
for i=1:P
    CO(i+1)=CO(i+1)+CO(i);
end

% CO求飞灰含碳
Cfh=CO*a_Cfh+b_Cfh;  % 根据CO估算飞灰含碳

%% 效率计算
% cfh;
Xar2ad=(1-Mar)/(1-Mad);   %收到基-空气干燥机转换系数
c=Xar2ad*47.58/100;
h=Xar2ad*3.92/100;
n=Xar2ad*0.82/100;
o=1-c-h-n-s-Mar-Aar;

ALPHA=21/(21-O2_k);    %过量空气系数
Vgk0=100*(0.089*(c+0.375*s)+0.265*h-0.0333*o);  %理论空气量
Vgy0=1.866*(c+0.375*s)+0.79*Vgk0+0.8*n;  %理论烟气量
Vgy=Vgy0+(ALPHA-1)*Vgk0;  %烟气量

Cpy=0.8967+0.0013.*Etem-0.000003.*Etem.*Etem;  %烟气比热
Sg=Vgy*Cpy.*(Etem-20)/Qnet;   %干烟气热损失

V_H2O=1.24*((9*h+Mar)+1.293*ALPHA*Vgk0*0.001);
Q_H2O=V_H2O*1.5093*(Etem-20);
Sm=Q_H2O/Qnet;   %水分热损失

Suc=337.27*100*Aar/Qnet*Cfh./(100-Cfh);  %飞灰含碳热损失
eff=0.9917-Suc-Sm-Sg;   %p步预测效率序列
eff_=(eff-0.8)/(1-0.8);   %归一化

%% 送风机电流，防止氧量一直开到最大，此时风机出力大，不经济
opt_bias_k=2*duM(1:control_num).*norm_limit_var-norm_limit_var+opt_bias_k1';

% 求优化后时刻O2全量,并对O2和负荷归一化后计算送风机电流  Blower=f(O2_norm,Load_norm);
O2_opt=O2_fnb_k+opt_bias_k(1);   % 反归一化 fnb_O2 为指令
O2_opt_norm = (O2_opt-min_O2)/(max_O2-min_O2);
% 负荷k时刻全量
% Load_k
% 送风机电流与氧量负荷关系，多元线性回归，送风机电流归一化
I_blower=a_Iblower*O2_opt_norm+b_Iblower*Load_k_norm+c_Iblower;
I_blower_=(I_blower-min_Iblower)/(max_Iblower-min_Iblower);   % 归一化
% eff_sum=sum(eff_(3:P+2));
% Je=-eff_sum+qI*I_index;  % 效率尽可能高，加负号

%% Nox预测
Nox=zeros(1,P+1);  % 预测的增量保存,归一化后的结果
Nox(1)=Nox_inc_k_norm;
Nox_iter=Nox(1);

for i=1:P
    Input_Nox=[Input_Load(i),Input_O2(i,:),Input_Fuel(i,:),Input_Sec(i,:),Input_Sofa(i,:),Input_Fp(i,:),Nox_iter];
    a=repmat(Input_Nox,NumSupVec_Nox,1)-X_Nox;
    dist=sum(a.*a,2);
    K=exp(-dist*Delta_Nox)';
    Nox(1+i)=K*Alfa_Nox+b_Nox-e_Nox_k;  % k时刻NOx预测值 增量且未归一化 加入反馈校正后的k+1时刻效率的估计值
    Nox_iter = (Nox(1+i)+norm_limit_Nox)/(2*norm_limit_Nox);
end
% 求全量
Nox(1)=Nox(1)+Nox_k1;
for i=1:P
    Nox(i+1)=Nox(i+1)+Nox(i);
end
%% 再热气温预测
Rtem=zeros(1,P+1);  % 预测的增量保存,归一化后的结果
Rtem(1)=Rtem_inc_k_norm;
Rtem_iter=Rtem(1);
for i=1:P
    Input_Rtem=[Input_Load(i),Input_O2(i,:),Input_Fuel(i,:),Input_Sec(i,:),Input_Sofa(i,:),Input_Fp(i,:),Rtem_iter];
    a=repmat(Input_Rtem,NumSupVec_Rtem,1)-X_Rtem;
    dist=sum(a.*a,2);
    K=exp(-dist*Delta_Rtem)';
    Rtem(1+i)=K*Alfa_Rtem+b_Rtem-e_Rtem_k;  % k时刻Rtem预测值 增量且未归一化 加入反馈校正后的k+1时刻效率的估计值
    Rtem_iter = (Rtem(1+i)+norm_limit_Rtem)/(2*norm_limit_Rtem);
end

% 求全量
Rtem(1)=Rtem(1)+Rtem_k1;
for i=1:P
    Rtem(i+1)=Rtem(i+1)+Rtem(i);
end


%% 优化指标
% 对全量归一化
Smax=(Smax-min_Smax)./(max_Smax-min_Smax);
Rtem=(Rtem-min_Rtem)./(max_Rtem-min_Rtem);
Nox=(Nox-min_Nox)./(max_Nox-min_Nox);
% 对优化偏置量归一化
opt_bias_k_ = opt_bias_k./u_opt_bias_norm';
J= -qe*sum(eff_(2:P+1))/P+...  % 效率尽可能高，加负号
    qst*sum(abs(Smax))/P+...
    qI*I_blower_+...
    ((duM(1:control_num)-0.5))'*R*((duM(1:control_num)-0.5))/control_num + ... % (invS*(duM-0.5))'*R*(invS*(duM-0.5))/control_num+... 只对第一步做约束
    0.5*sum(abs(Nox(2:P+1)-u_Nox_norm)+abs(Nox(2:P+1)-d_Nox_norm)-abs(u_Nox_norm-d_Nox_norm))/P*qn+...
    0.5*sum(abs(Rtem(2:P+1)-u_Rtem_norm)+abs(Rtem(2:P+1)-d_Rtem_norm)-abs(u_Rtem_norm-d_Rtem_norm))/P*qt+...
    qbias*sum(opt_bias_k_.*opt_bias_k_)/control_num;
 
%  qbias*0.1*sum(opt_bias_k'*opt_bias_k)/max(u_Var)/22; % 与f(x)+s_bias偏差过大带来的惩罚 duM为归一化后的优化增量 
% 送风机风力加大带来的电力损耗惩罚
% 与f(x)+s_bias偏差过大带来的惩罚 duM为归一化后的优化增量 
% AirWeight*[Mill_state(1), Mill_state(2), Mill_state(3), Mill_state(4)]*(duM(5:8)-[u0_ASecAir;u0_BSecAir;u0_CSecAir;u0_DSecAir])*...
% [Mill_state(1), Mill_state(2), Mill_state(3), Mill_state(4)]*(duM(5:8)-[u0_ASecAir;u0_BSecAir;u0_CSecAir;u0_DSecAir]);

    
end
