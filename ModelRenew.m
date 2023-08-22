function [newX,newY,newAlfa,newb,newInvH] = ModelRenew(X,Y,InvH,delta,C,N,Xk,Yk,Alfa,Flag,K_Alfa)
%{ 
通过判断Flag选择当前更新策略：0--冗余更新；1--最小Alfa更新
X:模型支持向量X   Y:模型支持向量Y  InvH  Alfa模型参数
delta C N :模型超参数
Xk Yk:待更新的样本
Flag:更新标志
K_Alfa:更新方式标志
%}
%% 判断Alfa最大是否替换，之后冗余更新与最小Alfa更新交替策略
%if max(abs(Alfa-mean(Alfa)))>K_Alfa*std(Alfa)  % 广义拉伊达准则
%    [~,n]=max(abs(Alfa-mean(Alfa)));

if Flag==0
    tempX=[X;Xk];
    dis=pdist(tempX);
    dis=squareform(dis);
    dis=tril(dis,-1)+triu(9999*ones(N+1,N+1),0);
    [min_x,min_y]=find(dis==min(min(dis)));
    n=min(min(min_x),min(min_y));
else
    [~,n]=min(abs(Alfa));
end

%% 计算InvG
Iex=eye(N);
Iex(N,n)=1;
Iex(n,n)=0;
Iex(N,N)=0;
Iex(n,N)=1;

InvH1=Iex*InvH*Iex;
h11=InvH1(1:N-1,1:N-1);
h12=InvH1(1:N-1,N);
h21=InvH1(N,1:N-1);
h22=InvH1(N,N);
InvG=h11-h12*h21/h22;
InvG=(InvG+InvG')/2;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% gj=zeros(1,N-1);
% for j=1:n-1
%     gj(j)=exp(-((Xk-X(j,:))*(Xk-X(j,:))')/2/(delta*delta));
% end
% if n~=N
%     gj(n)=exp(-((Xk-X(N,:))*(Xk-X(N,:))')/2/(delta*delta));
% end
% for j=n+1:N-1
%     gj(j)=exp(-((Xk-X(j,:))*(Xk-X(j,:))')/2/(delta*delta));
% end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%避免循环
X(n,:)=X(N,:);
a2=repmat(Xk,N-1,1)-X(1:N-1,:);
dist2=sum(a2.*a2,2);
gj=exp(-dist2*delta)';
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
kj=1+1/C;
rj=kj-gj*InvG*gj';

Mat=gj*InvG;
H=Mat'*Mat;
H=(H+H')/2;%保证H为对称矩阵

InvH2=[InvG+H/rj,-InvG*gj'/rj;-gj*InvG/rj,1/rj];
Y(n)=Y(N);
Y(N)=Yk;
X(n,:)=X(N,:);
X(N,:)=Xk;

e=ones(1,N);
%%返回值
newX=X;
newY=Y;
newAlfa=InvH2*Y-InvH2*e'*(e*InvH2*Y/(e*InvH2*e'));%列向量
newb=e*InvH2*Y/(e*InvH2*e');
newInvH=InvH2;
end
